	.file	1 "proto64.c"
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
	.frame	$sp,56,$31		# vars= 0, regs= 2/0, args= 32, extra= 8
	.mask	0x90000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	dsubu	$sp,$sp,56
	.cprestore 32
	dli	$2,0x7355471143622155
	dli	$3,0xbabebec0dea0ffab
	sd	$31,48($sp)
	sd	$28,40($sp)
	move	$25,$3
	jal	$31,$25
	ld	$31,48($sp)
	#nop
	.set	noreorder
	.set	nomacro
	j	$31
	daddu	$sp,$sp,56
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
	dli	$3,0xbabebec0dea0ffab
	j	$3
	.end	jump
