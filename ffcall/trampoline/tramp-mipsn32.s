/* Trampoline for mips CPU */

/*
 * Copyright 1996-1998 Bruno Haible, <bruno@clisp.org>
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
	lw	$2,24($25)
	lw	$3,28($25)
	sw	$3,0($2)
	lw	$25,32($25)
	/* The called function expects to see its own address in $25. */
	j	$25
	/* Some Mips hardware running Irix-4.0.5 needs this nop. */
	nop
	/* We'll actually store the data words immediately after the code. */
	/* The assembler just doesn't like ".word" inside section .text. */
	.data
$LC0:
	.word	0x12345678
$LC1:
	.word	0x73554711
$LC2:
	.word	0xbabebec0
	.end	tramp
