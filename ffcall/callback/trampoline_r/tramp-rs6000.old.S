/* Trampoline for rs6000 CPU with AIX calling convention */

/*
 * Copyright 1995-1999 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

/* Available registers: r0, r12, r11, r10, r9, r8, r7, r6, r5, r4, r3. */
/* However, r0 is special in that it cannot be used as a base register. */
/* And r3...r10 should not be clobbered because they contain the first 8
 * integer arguments to the function being called. */

	.globl tramp_r
	.globl .tramp_r
.csect tramp_r[DS]
tramp_r:
	.long .tramp_r, 0, 0
.csect .text[PR]
.tramp_r:
/* Move <data> into register r11 */
	l 11,0(2)	/* get <data> */
/* Get <function> */
	l 12,4(2)
/*
 * gcc-2.6.3 source says:
 * A function pointer is a pointer to a data area whose first word contains
 * the actual address of the function, whose second word contains a pointer
 * to its TOC, and whose third word contains a value to place in the static
 * chain register (r11). But we have already placed our information in r11.
 */
/*	l 11,8(12)	   pass static chain in r11 */
	l 2,4(12)	/* pass TOC in r2 */
	l 0,0(12)	/* actual code address */
	mtctr 0
	bctr

_section_.text:
.csect .data[RW]
	.long _section_.text
