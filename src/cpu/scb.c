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
 * \file scb.c
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * System control block management
 */
#include <cpu/cpu_scb.h>
#include <cpu/cpu_mapping.h>
#include <kernel/stdint.h>
#include <kernel/stddef.h>

/*******************************************************************************
 * Private definitions
 ******************************************************************************/
/** SCB registers map */
typedef struct
{
	uint32_t cpuid;      /**< CPUID register */
	uint32_t icsr;       /**< Interrupt control and state register */
	uint32_t vtor;       /**< Vector table offset register */
	uint32_t aircr;      /**< Application interrupt and reset control register */
	uint32_t scr;        /**< System control register */
	uint32_t ccr;        /**< Configuration and control register */
	uint8_t shpr[12];    /**< System handler priority registers */
	uint32_t shcsr;      /**< System handler control and state register */
	uint32_t cfsr;       /**< Configurable fault status register */
	uint32_t hfsr;       /**< Hard fault status register */
	uint32_t unused;     /**< Unused */
	uint32_t mmfar;      /**< Memory management fault address register */
	uint32_t bfar;       /**< Bus fault address register */
} scb_regs;

/** Set PendSV interrupt bit */
#define SCB_PENDSVSET (1U << 28)

/** Clear PendSV interrupt bit */
#define SCB_PENDSVCLR (1U << 27)

/** Clear Systick interrupt bit */
#define SCB_PENDSTCLR (1U << 25)

/** Reset request bit */
#define SCB_SYSRESETREQ (1U << 2)

/** Deep sleep request bit */
#define SCB_SLEEPDEEP (1U << 2)

/** Trap on division by 0 bit */
#define SCB_DIV_0_TRP (1U << 4)

/** Instruction access violation bit */
#define SCB_IACCVIOL (1U)

/** Data access violation bit */
#define SCB_DACCVIOL (1U << 1)

/** Memory fault on unstacking bit */
#define SCB_MUNSTKERR (1U << 3)

/** Memory fault on stacking error */
#define SCB_MSTKERR (1U << 4)

/** MMAR valid bit */
#define SCB_MMARVALID (1U << 7)

/** Instruction bus error bit */
#define SCB_IBUSERR (1U << 8)

/** Bus fault on unstacking bit */
#define SCB_UNSTKERR (1U << 11)

/** Bus fault on stacking bit */
#define SCB_STKERR (1U << 12)

/** BFAR valid bit */
#define SCB_BFARVALID (1U << 15)

/** Undefined instruction fault bit */
#define SCB_UNDEFINSTR (1U << 16)

/** Invalid state fault bit */
#define SCB_INVSTATE (1U << 17)

/** Invalid PC load fault bit */
#define SCB_INVPC (1U << 18)

/** No coprocessor fault bit */
#define SCB_NOCP (1U << 19)

/** Unaligned access fault bit */
#define SCB_UNALIGNED (1U << 24)

/** Division by zero fault bit */
#define SCB_DIVBYZERO (1U << 25)

/** Pointer used to access the SCB */
static volatile scb_regs *scb = (volatile scb_regs *)CPU_SCB_BASE;

/*******************************************************************************
 * Public functions
 ******************************************************************************/
int scb_get_cpuid(cpuid_t *cpuid)
{
	cpuid->implementer = (scb->cpuid) >> 24;
	cpuid->variant = (scb->cpuid & 0x00F00000) >> 20;
	cpuid->part = (scb->cpuid & 0x0000FFF0) >> 4;
	cpuid->revision = (scb->cpuid & 0x0000000F);

	return 0;
}

int scb_set_pendSV(void)
{
	scb->icsr |= SCB_PENDSVSET;

	return 0;
}

int scb_clear_pendSV(void)
{
	scb->icsr |= SCB_PENDSVCLR;

	return 0;
}

int scb_clear_systick(void)
{
	scb->icsr |= SCB_PENDSTCLR;

	return 0;
}

int scb_request_reset(void)
{
	scb->aircr |= SCB_SYSRESETREQ;

	return 0;
}

int scb_set_deep_sleep(int status)
{
	if(status)
	{
		scb->scr |= SCB_SLEEPDEEP;
	}
	else
	{
		scb->scr &= ~(SCB_SLEEPDEEP);
	}

	return 0;
}

int scb_set_trap_on_div_by_zero(int status)
{
	if(status)
	{
		scb->ccr |= SCB_DIV_0_TRP;
	}
	else
	{
		scb->ccr &= ~(SCB_DIV_0_TRP);
	}

	return 0;
}

int scb_get_usage_fault_information(void *stacked_pc, fault_info_t *info)
{
	info->cause = FAULT_CAUSE_UNKKNOW;
	info->instruction = stacked_pc;
	info->address = NULL;

	/* Try to determine the cause of the fault */
	if(scb->cfsr & SCB_DIVBYZERO)
	{
		info->cause = FAULT_CAUSE_UF_DIV_BY_ZERO;
	}
	else if(scb->cfsr & SCB_UNALIGNED)
	{
		info->cause = FAULT_CAUSE_UF_ACCESS;
	}
	else if(scb->cfsr & SCB_NOCP)
	{
		info->cause = FAULT_CAUSE_UF_NOCP;
	}
	else if(scb->cfsr & SCB_INVPC)
	{
		info->cause = FAULT_CAUSE_UF_INVALID_PC;
	}
	else if(scb->cfsr & SCB_INVSTATE)
	{
		info->cause = FAULT_CAUSE_UF_INVALID_STATE;
	}
	else if(scb->cfsr & SCB_UNDEFINSTR)
	{
		info->cause = FAULT_CAUSE_UF_UNDEF_INSTR;
	}

	return 0;
}

int scb_get_bus_fault_information(void *stacked_pc, fault_info_t *info)
{
	info->cause = FAULT_CAUSE_UNKKNOW;

	if(scb->cfsr & SCB_BFARVALID)
	{
		info->address = (void *)scb->bfar;
	}
	else
	{
		info->address = NULL;
	}

	/* Try to determine the cause of the fault */
	if(scb->cfsr & SCB_STKERR)
	{
		info->cause = FAULT_CAUSE_BF_STACKING_ERROR;
		info->instruction = NULL;
	}
	else if(scb->cfsr & SCB_UNSTKERR)
	{
		info->cause = FAULT_CAUSE_BF_UNSTACKING_ERROR;
		info->instruction = NULL;
	}
	else if(scb->cfsr & SCB_IBUSERR)
	{
		info->cause = FAULT_CAUSE_BF_IBUSERR;
		info->instruction = stacked_pc;
	}

	return 0;
}

int scb_get_mem_manage_fault_information(void *stacked_pc, fault_info_t *info)
{
	info->cause = FAULT_CAUSE_UNKKNOW;

	if(scb->cfsr & SCB_MMARVALID)
	{
		info->address = (void *)scb->mmfar;
	}
	else
	{
		info->address = NULL;
	}

	/* Try to determine the cause of the fault */
	if(scb->cfsr & SCB_MSTKERR)
	{
		info->cause = FAULT_CAUSE_MM_STACKING_ERROR;
		info->instruction = NULL;
	}
	else if(scb->cfsr & SCB_MUNSTKERR)
	{
		info->cause = FAULT_CAUSE_MM_UNSTACKING_ERROR;
		info->instruction = NULL;
	}
	else if(scb->cfsr & SCB_DACCVIOL)
	{
		info->cause = FAULT_CAUSE_MM_DATA_ACCESS;
		info->instruction = stacked_pc;
	}
	else if(scb->cfsr & SCB_IACCVIOL)
	{
		info->cause = FAULT_CAUSE_MM_INSTR_ACCESS;
		info->instruction = stacked_pc;
	}

	return 0;
}
