/* Trampoline for rs6000 CPU */

/*
 * Copyright 1995 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

/* Available registers: r0, r11, r10, r8, r7, r6, r5, r4, maybe r9. */
/* However, r0 is special in that it cannot be used as a base register. */

	.globl .tramp
.csect .text[PR]
.tramp:
/* Move <data> into <variable> */
	liu 11,0x1234
	oril 11,11,0x5678
	liu 10,0x7355
	oril 10,10,0x4711
	st 10,0(11)
/* Get <function> */
	liu 10,0xbabe
	oril 10,10,0xbec0
/*
 * gcc-2.6.3 source says:
 * A function pointer is a pointer to a data area whose first word contains
 * the actual address of the function, whose second word contains a pointer
 * to its TOC, and whose third word contains a value to place in the static
 * chain register (r11).
 */
	l 11,8(10)	/* pass static chain in r11 */
	l 2,4(10)	/* pass TOC in r2 */
	l 0,0(10)	/* actual code address */
	mtctr 0
	bctr
