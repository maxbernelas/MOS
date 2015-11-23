/**
 * \file cpu_utils.h
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Low-level CPU-related primitives
 */
#ifndef H_CPU_UTILS
#define H_CPU_UTILS

#include <kernel/stdint.h>

/**
 * Restore the value of the IRQ enable flag
 * \param[in] flags The previously saved IRQ enable flag
 */
void cpu_irq_restore(int flags);

/**
 * Enable IRQs
 * \return The previous value of the IRQ enable flag
 */
int cpu_irq_enable(void);

/**
 * Disable IRQs
 * \return The previous value of the IRQ enable flag
 */
int cpu_irq_disable(void);

/** Data memory barrier */
void cpu_dmb(void);

/** Data synchronization barrier */
void cpu_dsb(void);

/** Instruction synchronization barrier */
void cpu_isb(void);

/** Wait for interrupt */
void cpu_wfi(void);

/**
 * Read PSR register
 * \return The value of the PSR register
 */
uint32_t cpu_read_psr(void);

/**
 * Set privilege level for thread mode
 * \param[in] priv True to set thread as privileged, false for unprivileged
 */
void cpu_set_privilege(unsigned int priv);

/**
 * Get the value of the MSP
 * \return Current value of the main stack pointer
 */
#define CPU_GET_MSP()                                                          \
	({                                                                     \
		void *_sp;                                                     \
		asm volatile(                                                  \
		    "mrs	%0, msp \n\t"                                  \
		    : "=r" (_sp)                                               \
		);                                                             \
		_sp;                                                           \
	})

/**
 * Get the value of the PSP
 * \return Current value of the process stack pointer
 */
#define CPU_GET_PSP()                                                          \
	({                                                                     \
		void *_sp;                                                     \
		asm volatile(                                                  \
		    "mrs	%0, psp \n\t"                                  \
		    : "=r" (_sp)                                               \
		);                                                             \
		_sp;                                                           \
	})

/**
 * Set the value of the PSP
 * \param[in] sp New value of the process stack pointer
 */
#define CPU_SET_PSP(sp)                                                        \
	do{                                                                    \
		asm volatile(                                                  \
		    "msr	psp, %0 \n\t"                                  \
		    "dsb                \n\t"                                  \
		    :                                                          \
		    : "r" (sp)                                                 \
		);                                                             \
	} while(0)

/**
 * Set the value of the MSP
 * \param[in] sp New value of the main stack pointer
 */
#define CPU_SET_MSP(sp)                                                        \
	do{                                                                    \
		asm volatile(                                                  \
		    "msr	msp, %0 \n\t"                                  \
		    "dsb                \n\t"                                  \
		    :                                                          \
		    : "r" (sp)                                                 \
		);                                                             \
	} while(0)

/** Structure representing the frame stacked by hardware on exception entry */
typedef struct
{
	uint32_t r0;               /**< stacked R0 */
	uint32_t r1;               /**< Stacked R1 */
	uint32_t r2;               /**< Stacked R2 */
	uint32_t r3;               /**< Stacked R3 */
	uint32_t r12;              /**< Stacked R12 */
	uint32_t lr;               /**< Stacked LR */
	uint32_t pc;               /**< Stacked PC */
	uint32_t psr;              /**< Stacked PSR */
} cpu_ex_stack_frame;

#endif
