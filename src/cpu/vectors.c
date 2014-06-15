/**
 * \file vectors.c
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Vector table for MOS
 */
#include <kernel/stdint.h>
#include <kernel/stddef.h>
#include <kernel/handlers.h>
#include <cpu/cpu_interrupts.h>

/** Stack base pointer (defined by linker) */
extern uint32_t __stack_base;

/** Type of a function pointer */
typedef void (*func_ptr)(void);

/** Assembly wrapper for system calls */
extern void __svc_handler(void);

/** Vector table */
func_ptr vectors[CPU_INT_NB_VECTORS] __attribute__((section (".interrupt_vectors"))) =
{
	(func_ptr)&__stack_base,     /* OS stack base */
	kernel_entry,

	/* System handlers */
	handler_nmi,
	handler_hard_fault,
	handler_memmanage,
	handler_busfault,
	handler_usage,
	NULL,                          /* Reserved */
	NULL,                          /* Reserved */
	NULL,                          /* Reserved */
	NULL,                          /* Reserved */
	__svc_handler,
	NULL,                          /* Reserved */
	NULL,                          /* Reserved */
	handler_pendSV,
	handler_systick,
};
