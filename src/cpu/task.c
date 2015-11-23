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
 * \file task.c
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * CPU-specific task handling routines
 */
#include <kernel/stdint.h>
#include <cpu/cpu_task.h>
#include <cpu/cpu_utils.h>
#include <kernel/string.h>

/*******************************************************************************
 * Private definitions
 ******************************************************************************/
/** Saved task context */
typedef struct
{
	uint32_t r4;    /**< Saved R4 */
	uint32_t r5;    /**< Saved R5 */
	uint32_t r6;    /**< Saved R6 */
	uint32_t r7;    /**< Saved R7 */
	uint32_t r8;    /**< Saved R8 */
	uint32_t r9;    /**< Saved R9 */
	uint32_t r10;   /**< Saved R10 */
	uint32_t r11;   /**< Saved R11 */
} task_context;

/*******************************************************************************
 * Public functions
 ******************************************************************************/
void * cpu_task_create_context(void *sp, void *func, void *arg, void *stop_func)
{
	cpu_ex_stack_frame *ex_frame;
	char *csp;

	csp = sp;

	/* Create the exception stack frame */
	csp -= sizeof(cpu_ex_stack_frame);
	ex_frame = (cpu_ex_stack_frame *)csp;
	ex_frame->r0 = (uint32_t)arg;
	ex_frame->r1 = 0;
	ex_frame->r2 = 0;
	ex_frame->r3 = 0;
	ex_frame->r12 = 0;
	ex_frame->lr = (uint32_t)stop_func;
	ex_frame->pc = (uint32_t)func;
	ex_frame->psr = 0x21000000; /* Thumb mode, no carry in status flags */

	/* All other registers set to 0 in task context */
	csp -= sizeof(task_context);
	memset(csp, 0x00, sizeof(task_context));

	return csp;
}

void cpu_task_save_context(void)
{
	asm volatile(
	"mrs	r0, psp       \n\t"
	"stmdb	r0!, {r4-r11} \n\t"
	"msr	psp, r0       \n\t"
	:
	:
	: "r0"
	);
}

void cpu_task_restore_context(void)
{
	asm volatile(
	"mrs	r0, psp       \n\t"
	"ldmia	r0!, {r4-r11} \n\t"
	"msr	psp, r0       \n\t"
	:
	:
	: "r0"
	);
}
