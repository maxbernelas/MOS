/*
 * Copyright (c) 2014, Maxime Bernelas
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
 * \file handlers.c
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Exception handlers implementation
 */
#include <cpu/cpu_utils.h>
#include <cpu/cpu_task.h>
#include <kernel/handlers.h>
#include <kernel/sched.h>

/*******************************************************************************
 * Private definitions
 ******************************************************************************/
/**
 * Save stack pointer on fault entry and call a function with this stack pointer
 * as parameter
 * \param[in] func The function to call
 */ 
#define CALL_WITH_STACK_POINTER(func)                                          \
	asm volatile(                                                          \
		"tst	lr, #4 \n\t"                                           \
		"ite	eq \n\t"                                               \
		"mrseq	r0, msp \n\t"                                          \
		"mrsne	r0, psp \n\t"                                          \
		"push { lr } \n\t"                                             \
		"bl " #func " \n\t"                                            \
		"mov pc, lr \n\t"                                              \
	)

/**
 * Dummy fault handler
 * \param[in] sp Value of the stack pointer on fault entry
 */
static void dummy_handler(void *sp) __attribute__((unused));
static void dummy_handler(void *sp)
{
	cpu_ex_stack_frame *frame;

	frame = sp;

	(void)frame;
	while(1)
		;
}

/*******************************************************************************
 * Public functions
 ******************************************************************************/

void handler_nmi(void)
{
	CALL_WITH_STACK_POINTER(dummy_handler);
}

void handler_hard_fault(void)
{
	CALL_WITH_STACK_POINTER(dummy_handler);
}

void handler_memmanage(void)
{
	CALL_WITH_STACK_POINTER(dummy_handler);
}

void handler_busfault(void)
{
	CALL_WITH_STACK_POINTER(dummy_handler);
}

void handler_usage(void)
{
	CALL_WITH_STACK_POINTER(dummy_handler);
}

int handler_svc(uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4,
                uint32_t num)
{
	(void)num;
	(void)p1;
	(void)p2;
	(void)p3;
	(void)p4;

	return 0;
}

void handler_pendSV(void)
{
	cpu_task_save_context();

	schedule();

	cpu_set_privilege(sched_is_task_privileged());
	cpu_task_restore_context();

	CPU_RET_TO_USER();
}

void handler_systick(void)
{
	/* Release processor to next task */
	sched_yield();
}
