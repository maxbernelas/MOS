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

#endif
