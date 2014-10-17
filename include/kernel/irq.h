/**
 * \file irq.h
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Interface for IRQ handlers management
 */
#ifndef H_IRQ
#define H_IRQ

/**
 * Prototype of IRQ handlers
 * \param data Private data for IRQ handler needs
 */
typedef void (*irq_handler)(void *data);

/**
 * Register a new IRQ handler
 * \param[in] irq Number of the requested IRQ
 * \param[in] handler IRQ handler to install
 * \param[in] data Private data to pass to the handler
 * \retval 0 Success
 * \retval #EINVAL Invalid IRQ number
 * \retval #EBUSY A handler is already registered for this IRQ
 */
int irq_register(int irq, irq_handler handler, void *data);

/**
 * Release an IRQ
 * \param[in] irq Number of the IRQ to release
 * \retval 0 Success
 * \retval #EINVAL Invalid IRQ number
 * \retval #EBADF No handler registered for this IRQ
 */
int irq_release(int irq);

#endif
