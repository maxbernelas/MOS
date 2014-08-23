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
 * \file irq.c
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * IRQ handlers management
 */
#include <cpu/cpu_interrupts.h>
#include <kernel/handlers.h>
#include <cpu/cpu_utils.h>
#include <kernel/stddef.h>
#include <kernel/irq.h>
#include <kernel/errno.h>

/*******************************************************************************
 * Private definitions
 ******************************************************************************/
/** Structure for a managed IRQ */
typedef struct
{
	irq_handler handler;  /**< IRQ handler */
	void *data;           /**< IRQ handler parameter */
} irq_slot;

/** Array of registered IRQ handlers */
static irq_slot slots[CPU_INT_NB_IRQ];

/*******************************************************************************
 * Public definitions
 ******************************************************************************/
int irq_register(int irq, irq_handler handler, void *data)
{
	int flags;

	if((irq < 0) || (irq > CPU_INT_NB_IRQ - 1))
	{
		return EINVAL;
	}

	flags = cpu_irq_disable();

	if(slots[irq].handler != NULL)
	{
		cpu_irq_restore(flags);
		return EBUSY;
	}

	slots[irq].handler = handler;
	slots[irq].data = data;
	cpu_isb();
	cpu_irq_restore(flags);

	return 0;
}

int irq_release(int irq)
{
	int flags;

	if((irq < 0) || (irq > CPU_INT_NB_IRQ - 1))
	{
		return EINVAL;
	}

	flags = cpu_irq_disable();

	if(slots[irq].handler == NULL)
	{
		cpu_irq_restore(flags);
		return EBADF;
	}

	slots[irq].handler = NULL;
	cpu_isb();
	cpu_irq_restore(flags);

	return 0;
}

void handler_interrupt(void)
{
	int irq;

	/* Find the IRQ number */
	irq = (cpu_read_psr() & 0xFF) - CPU_INT_IRQ_BASE_INDEX;

	/* Call the registered handler */
	slots[irq].handler(slots[irq].data);
}
