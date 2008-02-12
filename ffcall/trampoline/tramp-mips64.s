/* Trampoline for mips CPU in 64-bit mode */

/*
 * Copyright 1996 Bruno Haible, <bruno@clisp.org>
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
	.globl	main
	.ent	main
main:
	.end	main
	.globl	tramp
	.ent	tramp
tramp:
	/* We can assume that our own address (=tramp) is in $25. */
	ld	$2,$LC0-tramp($25)
	ld	$3,$LC1-tramp($25)
	sd	$3,0($2)
	ld	$25,$LC2-tramp($25)
	/* The called function expects to see its own address in $25. */
	j	$25
	/* Some Mips hardware running Irix-4.0.5 needs this nop. */
	nop
$LC0:
	.dword	0x1234567813578765
$LC1:
	.dword	0x7355471143622155
$LC2:
	.dword	0xbabebec0dea0ffab
	.end	tramp
