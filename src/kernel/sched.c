/*
 * Copyright (c) 2015, Maxime Bernelas
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the owner nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * \file sched.c
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Task management and scheduling routines
 */
#include <cpu/cpu_scb.h>
#include <cpu/cpu_task.h>
#include <cpu/cpu_utils.h>
#include <kernel/kalloc.h>
#include <kernel/list.h>
#include <kernel/sched.h>

/*******************************************************************************
 * Private definitions
 ******************************************************************************/
/** Task states */
typedef enum
{
	TASK_RUNNING,    /**< Currently running task */
	TASK_READY,      /**< Task ready for scheduling */
	TASK_SLEEPING,   /**< Task is sleeping */
	TASK_DEAD        /**< Task terminated */
} task_state;

/** Task structure */
struct _task
{
	void *sp;            /**< Stack pointer */
	task_state state;    /**< State */
	list_item list;      /**< Task list item */
	unsigned char priv;  /**< True if task is privileged */
};

/** List of tasks */
static list_item *task_list = NULL;

/** Current task pointer */
static task_t *current_task = NULL;

/*******************************************************************************
 * Private functions
 ******************************************************************************/
/**
 * Elect next task for scheduling
 * \return Handler of the elected task
 */
static task_t * sched_elect(void)
{
	list_item *tmp;
	task_t *t;

	/* Elect next ready task in the list (round-robin scheduling) */
	tmp = current_task ? current_task->list.next : NULL;
	while(tmp)
	{
		t = LIST_GET_OBJECT(tmp, task_t, list);

		if(t->state == TASK_READY)
		{
			return t;
		}

		tmp = tmp->next;
	}

	/* No ready task found, elect idle task (first in the task list) */
	return LIST_GET_OBJECT(task_list, task_t, list);
}

/** Task termination routine */
static void task_exit(void)
{
	current_task->state = TASK_DEAD;

	scb_set_pendSV();

	/* Wait until scheduler executes and removes this task */
	while(1)
		;
}

/** CPU idle task (task 0) */
static void idle_task(void *arg)
{
	(void)arg;

	while(1)
	{
		cpu_wfi();
	}
}

/*******************************************************************************
 * Public functions
 ******************************************************************************/
task_t *sched_create_task(void (*f)(void *), void *arg, size_t stack_size,
                          unsigned char priv)
{
	task_t *t;

	/*
	 * Allocate task struct and stack at the same time to avoid allocation
	 * overhead
	 */
	t = kmalloc(sizeof(*t) + stack_size);
	if(t == NULL)
		return NULL;

	/* TODO: should make sure stack pointer is correctly aligned */
	t->sp = ((unsigned char *)t) + sizeof(*t) + stack_size;
	t->state = TASK_READY;
	t->priv = priv;
	t->list.next = NULL;
	t->list.prev = NULL;

	/* Create task context */
	t->sp = cpu_task_create_context(t->sp, (void *)f, arg, task_exit);

	list_add_tail(&task_list, &t->list);

	return t;
}

void sched_sleep(void)
{
	if(current_task)
		current_task->state = TASK_SLEEPING;
	scb_set_pendSV();
}

void sched_yield(void)
{
	if(current_task)
		current_task->state = TASK_READY;
	scb_set_pendSV();
}

int sched_init(void)
{
	task_t *idle;

	/* Create idle task */
	idle = sched_create_task(idle_task, NULL, 256, 0);
	if(idle == NULL)
		return 1;

	return 0;
}

void schedule(void)
{
	task_t *next;

	next = sched_elect();

	/* current_task my be NULL on the very first context switch */
	if(current_task)
	{
		/* Check if current task has terminated */
		if(current_task->state == TASK_DEAD)
		{
			list_remove(&task_list, &current_task->list);
			kfree(current_task);
		}
		else
		{
			current_task->sp = CPU_GET_PSP();
		}
	}

	current_task = next;
	current_task->state = TASK_RUNNING;

	CPU_SET_PSP(current_task->sp);
}
