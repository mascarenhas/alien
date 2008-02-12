/* Trampoline for ia64 CPU */

/*
 * Copyright 2001 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

	.text
	.align 16
	.global tramp#
	.proc tramp#
tramp:
	/* The closure pointer is already in register r1. */
	ld8 r14 = [r1]		/* Move <address> into register r14. */
	adds r15 = 8, r1
	adds r16 = 16, r1
	;;
	/* Jump to r14. */
	ld8 r18 = [r14]
	ld8 r15 = [r15]		/* Move <variable> into register r15. */
	adds r17 = 8, r14
	;;
	ld8 r16 = [r16]		/* Move <data> into register r16. */
	ld8 r1 = [r17]
	mov b6 = r18
	;;
	st8 [r15] = r16		/* Store <data> into <variable>. */
	br b6
	;;
	.endp tramp#
