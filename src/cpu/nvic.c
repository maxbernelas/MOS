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
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * \file nvic.c
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Nested vectored interrupt controller management
 */
#include <kernel/stdint.h>
#include <cpu/cpu_interrupts.h>
#include <cpu/cpu_mapping.h>

/*******************************************************************************
 * Private definitions
 ******************************************************************************/
/** NVIC register map */
typedef struct
{
	uint32_t iser[3]; /**< Interrupt set-enable registers */
	uint32_t icer[3]; /**< Interrupt clear-enable registers */
	uint32_t ispr[3]; /**< Interrupt set-pending registers */
	uint32_t icpr[3]; /**< Interrupt clear-pending registers */
	uint32_t iabr[3]; /**< Interrupt active bit registers */
	uint32_t ipr[20]; /**< Interrupt priority registers */
} nvic_regs;

/** Pointer used to access the NVIC */
static volatile nvic_regs *regs = (volatile nvic_regs *)CPU_NVIC_BASE;

/*******************************************************************************
 * Public definitions
 ******************************************************************************/
int nvic_irq_enable(int irq)
{
	if((irq < 0) || (irq > CPU_INT_NB_IRQ - 1))
	{
		return 1;
	}

	regs->iser[irq / 32] = (1U << (irq % 32));

	return 0;
}

int nvic_irq_disable(int irq)
{
	if((irq < 0) || (irq > CPU_INT_NB_IRQ - 1))
	{
		return 1;
	}

	regs->icer[irq / 32] = (1U << (irq % 32));

	return 0;
}

int nvic_irq_clear(int irq)
{
	if((irq < 0) || (irq > CPU_INT_NB_IRQ - 1))
	{
		return 1;
	}

	regs->ispr[irq / 32] = (1U << (irq % 32));

	return 0;
}
