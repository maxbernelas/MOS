/**
 * \file cpu_nvic.h
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Nested vectored interrupt controller interface
 */
#ifndef H_CPU_NVIC
#define H_CPU_NVIC

/**
 * Enable an interrupt
 * \param[in] irq Number of the interrupt to enable
 * \return 0 on success, 1 on failure
 */
int nvic_irq_enable(int irq);

/**
 * Disable an interrupt
 * \param[in] irq Number of the interrupt to disable
 * \return 0 on success, 1 on failure
 */
int nvic_irq_disable(int irq);

/**
 * Clear an interrupt pending flag
 * \param[in] irq Number of the interrupt flag to clear
 * \return 0 on success, 1 on failure
 */
int nvic_irq_clear(int irq);

#endif
