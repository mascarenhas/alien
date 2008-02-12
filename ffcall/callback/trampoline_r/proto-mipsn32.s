	#.file	1 "proto.c"
	.set	nobopt
	.option pic2
	.section	.text
	.text
	.align	2
	.globl	tramp
	.ent	tramp
tramp:
.LFB1:
	.frame	$sp,32,$31		# vars= 0, regs= 2/0, args= 0, extra= 16
	.mask	0x90000000,-8
	.fmask	0x00000000,0
	subu	$sp,$sp,32
.LCFI0:
	sd	$31,24($sp)
.LCFI1:
	sd	$28,16($sp)
.LCFI2:
	.set	noat
	lui	$1,%hi(%neg(%gp_rel(tramp)))
	addiu	$1,$1,%lo(%neg(%gp_rel(tramp)))
	daddu	$gp,$1,$25
	.set	at
	li	$2,1934950400			# 0x73550000
	ori	$2,$2,0x4711
	li	$25,-1161904448
	jal	$31,$25
	ld	$31,24($sp)
	ld	$28,16($sp)
	#nop
	.set	noreorder
	.set	nomacro
	j	$31
	addu	$sp,$sp,32
	.set	macro
	.set	reorder

.LFE1:
	.end	tramp
	.align	2
	.globl	jump
	.ent	jump
jump:
.LFB2:
	.frame	$sp,32,$31		# vars= 0, regs= 1/0, args= 0, extra= 16
	.mask	0x10000000,-16
	.fmask	0x00000000,0
	subu	$sp,$sp,32
.LCFI3:
	sd	$28,16($sp)
.LCFI4:
	.set	noat
	lui	$1,%hi(%neg(%gp_rel(jump)))
	addiu	$1,$1,%lo(%neg(%gp_rel(jump)))
	daddu	$gp,$1,$25
	.set	at
	li	$3,-1161953280			# 0xbabe0000
	ori	$3,$3,0xbec0
	j	$3
.LFE2:
	.end	jump
