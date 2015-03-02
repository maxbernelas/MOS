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
 * \file systick.c
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * SysTick driver implementation
 */
#include <kernel/errno.h>
#include <kernel/stdint.h>
#include <cpu/cpu_mapping.h>

/*******************************************************************************
 * Private definitions
 ******************************************************************************/
/** SysTick register map */
typedef struct
{
	uint32_t ctrl;      /**< Control register */
	uint32_t load;      /**< Reload value register */
	uint32_t val;       /**< Current value register */
	uint32_t calib;     /**< Calibration value register */
} systick_regs;

/** Use AHB as a clock source */
#define SYSTICK_CLKSRC_AHB (1U << 2)

/** Use AHB / 8 as a clock source */
#define SYSTICK_CLKSRC_AHB_DIV_8 (0U)

/** Maximum Systick period when running on AHB clock */
#define SYSTICK_MAX_PERIOD_AHB (1U << 24)

/** Systick enable flag */
#define SYSTICK_ENABLE (1U)

/** Systick IRQ enable flag */
#define SYSTICK_IRQ_ENABLE (1U << 1)

/** Pointer used to acces the SysTick */
static volatile systick_regs *systick = (volatile systick_regs *)CPU_SYSTMR_BASE;

/** Configured SysTick frequency */
static unsigned int systick_freq;

/*******************************************************************************
 * Public functions
 ******************************************************************************/
int systick_setup(unsigned int freq, unsigned int ahb_freq)
{
	uint32_t load;

	/* Setup clocksource and reload value */
	systick->ctrl = SYSTICK_CLKSRC_AHB;
	load = ahb_freq / freq;
	systick_freq = ahb_freq / load;

	if(load > SYSTICK_MAX_PERIOD_AHB)
	{
		/* Switch to AHB / 8 */
		systick->ctrl = SYSTICK_CLKSRC_AHB_DIV_8;
		load = load / 8;
		systick_freq = (ahb_freq / 8) / load;
	}

	if(load < 2)
	{
		systick_freq = 0;
		return EINVAL;
	}

	systick->load = load - 1;

	return 0;
}

int systick_enable(void)
{
	/* Enable interrupt and start timer */
	systick->ctrl |= (SYSTICK_ENABLE | SYSTICK_IRQ_ENABLE);

	return 0;
}

int systick_disable(void)
{
	/* Stop timer and disable interrupt */
	systick->ctrl &= ~(SYSTICK_ENABLE | SYSTICK_IRQ_ENABLE);

	return 0;
}

unsigned int systick_get_freq(void)
{
	return systick_freq;
}
