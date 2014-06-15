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
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * \file svc.s
 * This file contains SVC related assembly functions
 * \author Maxime Bernelas <maxime@bernelas.fr>
 */
.section .text
.cpu cortex-m3
.thumb
.syntax unified

/* System call handler */
.global __svc_handler
.thumb_func
__svc_handler:
	/* First get the stack pointer */
	tst	lr, #4
	ite	eq
	mrseq	r0, msp
	mrsne	r0, psp
	push	{ lr }                 @ save lr for return from SVC
	push	{ r0 }                 @ save caller stack pointer

	/* Retrieve arguments */
	ldr	r1, [r0, #4]           @ parameter 2
	ldr	r2, [r0, #8]           @ parameter 3
	ldr	r3, [r0, #12]          @ parameter 4
	ldr	r0, [r0]               @ parameter 1
	push	{ r12 }                @ parameter 5 is SVC number

	/* Call handler */
	bl	handler_svc

	add	sp, #4                 @ restore the stack (remove stacked r12)
	pop	{ r1 }                 @ retrieve caller stack pointer
	str	r0, [r1]               @ store return value on stack

	pop	{ pc }                 @ return from SVC

/* User-mode system call wrapper */
.global __do_svc
.thumb_func
__do_svc:
	/* Prepare arguments : r0, r1, r2, r3 are already in place */
	/* Store SVC number (parameter 5) in r12 */
	ldr	r12, [sp]

	/* Call SVC */
	svc	#0
	mov	pc, lr
