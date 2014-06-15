/**
 * \file handlers.c
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Exception handlers implementation
 */
#include <kernel/handlers.h>

void handler_nmi(void)
{
	while(1)
		;
}

void handler_hard_fault(void)
{
	while(1)
		;
}

void handler_memmanage(void)
{
	while(1)
		;
}

void handler_busfault(void)
{
	while(1)
		;
}

void handler_usage(void)
{
	while(1)
		;
}

int handler_svc(uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4,
                uint32_t num)
{
	(void)num;
	(void)p1;
	(void)p2;
	(void)p3;
	(void)p4;

	return 0;
}

void handler_pendSV(void)
{
	while(1)
		;
}

void handler_systick(void)
{
	while(1)
		;
}
