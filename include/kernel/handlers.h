/**
 * \file handlers.h
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Prototypes of the system exception handlers
 */
#ifndef H_HANDLERS
#define H_HANDLERS

#include <kernel/stdint.h>

/** Kernel entry point (reset vector) */
void kernel_entry(void);

/** NMI handler */
void handler_nmi(void);

/** Hard fault handler */
void handler_hard_fault(void);

/** Memory management fault handler */
void handler_memmanage(void);

/** Bus fault handler */
void handler_busfault(void);

/** Usage fault handler */
void handler_usage(void);

/**
 * Supervisor call handler
 * \param p1 First parameter
 * \param p2 Second parameter
 * \param p3 Third parameter
 * \param p4 Fourth parameter
 * \param[in] num Number of the called service
 * \return The return value of the system call
 */
int handler_svc(uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4,
                uint32_t num);

/** PendSV handler */
void handler_pendSV(void);

/** Systick handler */
void handler_systick(void);

/** Interrupt handler */
void handler_interrupt(void);

#endif
