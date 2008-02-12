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
	.global tramp_r#
	.proc tramp_r#
tramp_r:
	/* The closure pointer is already in register r1. */
	ld8 r14 = [r1]		/* Move <address> into register r14. */
	adds r15 = 8, r1
	;;
	ld8 r15 = [r15]		/* Move <data> into register r15. */
	/* Jump to r14. */
	ld8 r17 = [r14]
	adds r16 = 8, r14
	;;
	ld8 r1 = [r16]
	mov b6 = r17
	;;
	br b6
	;;
	.endp tramp_r#
