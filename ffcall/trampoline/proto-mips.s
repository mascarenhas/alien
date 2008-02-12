	.file	1 "proto.c"
	.set	nobopt
	.abicalls
gcc2_compiled.:
__gnu_compiled_c:
	.text
	.align	2
	.globl	tramp
	.align	2
	.globl	jump

	.text
	.text
	.ent	tramp
tramp:
	.frame	$sp,32,$31		# vars= 0, regs= 2/0, args= 16, extra= 8
	.mask	0x90000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	subu	$sp,$sp,32
	.cprestore 16
	li	$2,1934950400			# 0x73550000
	ori	$2,$2,0x4711
	sw	$31,28($sp)
	sw	$28,24($sp)
	sw	$2,305419896
	li	$25,-1161904448
	jal	$31,$25
	lw	$31,28($sp)
	#nop
	.set	noreorder
	.set	nomacro
	j	$31
	addu	$sp,$sp,32
	.set	macro
	.set	reorder

	.end	tramp
	.text
	.ent	jump
jump:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	li	$2,-1161953280			# 0xbabe0000
	ori	$2,$2,0xbec0
	j	$2
	.end	jump
