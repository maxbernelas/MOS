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
 * \file vectors.c
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Vector table for MOS
 */
#include <kernel/stdint.h>
#include <kernel/stddef.h>
#include <kernel/handlers.h>
#include <cpu/cpu_interrupts.h>

/** Stack base pointer (defined by linker) */
extern uint32_t __stack_base;

/** Type of a function pointer */
typedef void (*func_ptr)(void);

/** Assembly wrapper for system calls */
extern void __svc_handler(void);

/** Vector table */
func_ptr vectors[CPU_INT_NB_VECTORS]
__attribute__((section (".interrupt_vectors"))) =
{
	(func_ptr)&__stack_base,     /* OS stack base */
	kernel_entry,

	/* System handlers */
	handler_nmi,
	handler_hard_fault,
	handler_memmanage,
	handler_busfault,
	handler_usage,
	NULL,                          /* Reserved */
	NULL,                          /* Reserved */
	NULL,                          /* Reserved */
	NULL,                          /* Reserved */
	__svc_handler,
	NULL,                          /* Reserved */
	NULL,                          /* Reserved */
	handler_pendSV,
	handler_systick,

	/* Interrupt handlers */
	[CPU_INT_IRQ_BASE_INDEX ... (CPU_INT_NB_VECTORS - 1)] = handler_interrupt
};
