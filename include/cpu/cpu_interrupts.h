/**
 * \file cpu_interrupts.h
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Interfaces related to interrupt handling
 */
#ifndef H_CPU_INTERRUPTS
#define H_CPU_INTERRUPTS

/** Number of IRQ vector entries */
#define CPU_INT_NB_IRQ (43)

/** Index of the first IRQ handler */
#define CPU_INT_IRQ_BASE_INDEX (16)

/** Number of entries in the vector table */
#define CPU_INT_NB_VECTORS (CPU_INT_NB_IRQ + CPU_INT_IRQ_BASE_INDEX)

#endif
