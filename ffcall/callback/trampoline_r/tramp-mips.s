/* Trampoline for mips CPU */

/*
 * Copyright 1995-1997 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

/* Available registers: $2, $3. */

	.set	nobopt
	.set	noreorder
	.text
	.globl	tramp
	.ent	tramp
tramp:
	li	$2,0x73550000
	ori	$2,$2,0x4711
	li	$25,0xbabe0000
	ori	$25,$25,0xbec0
	/* The called function expects to see its own address in $25. */
	j	$25
	/* Some Mips hardware running Irix-4.0.5 needs this nop. */
	nop
	.end	tramp
