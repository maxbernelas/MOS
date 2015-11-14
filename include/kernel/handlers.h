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
void handler_nmi(void) __attribute__((naked));

/** Hard fault handler */
void handler_hard_fault(void) __attribute__((naked));

/** Memory management fault handler */
void handler_memmanage(void) __attribute__((naked));

/** Bus fault handler */
void handler_busfault(void) __attribute__((naked));

/** Usage fault handler */
void handler_usage(void) __attribute__((naked));

/** PendSV handler */
void handler_pendSV(void) __attribute__((naked));

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

/** Systick handler */
void handler_systick(void);

/** Interrupt handler */
void handler_interrupt(void);

#endif
