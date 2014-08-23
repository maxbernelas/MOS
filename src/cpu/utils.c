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
 * \file utils.c
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Low-level CPU-related primitives
 */
#include <cpu/cpu_utils.h>

/*******************************************************************************
 * Private definitions
 ******************************************************************************/
/** Value of the IRQ enable mask */
enum
{
	CPU_IRQ_ENABLED = 0,    /**< IRQs enabled */
	CPU_IRQ_DISABLED = 1    /**< IRQs disabled */
};

/**
 * Set the value of the IRQ enable flag
 * \param[in] flags New value of the flag
 * \return The previous value of the IRQ enable flag
 */
static int cpu_irq_set(int flags)
{
	int backup;

	asm(
	"mrs	%0, PRIMASK    \n\t"
	"msr	PRIMASK, %1    \n\t"
	: "=r" (backup)
	: "r" (flags)
	);

	return backup;
}

/*******************************************************************************
 * Public functions
 ******************************************************************************/
void cpu_irq_restore(int flags)
{
	cpu_irq_set(flags);
}

int cpu_irq_enable(void)
{
	return cpu_irq_set(CPU_IRQ_ENABLED);
}

int cpu_irq_disable(void)
{
	return cpu_irq_set(CPU_IRQ_DISABLED);
}

void cpu_dmb(void)
{
	asm("dmb \n\t");
}

void cpu_dsb(void)
{
	asm("dsb \n\t");
}

void cpu_isb(void)
{
	asm("isb \n\t");
}

void cpu_wfi(void)
{
	asm("wfi \n\t");
}

uint32_t cpu_read_psr(void)
{
	uint32_t reg;

	asm(
	"mrs	%0, PSR \n\t"
	: "=r" (reg)
	:
	);

	return reg;
}
