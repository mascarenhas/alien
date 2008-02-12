/* Trampoline for convex CPU */

/*
 * Copyright 1995 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

/* Available registers: s1, s2, s3, s4, s5, s6, s7, s0. */

.globl _tramp
_tramp:
	ld.w #0x73554711,s1
	st.w s1,0x12345678
	jmp 0xbabebec0
	ds.h 0
