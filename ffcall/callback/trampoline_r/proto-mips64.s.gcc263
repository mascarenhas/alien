	.file	1 "proto64.c"
	.set	nobopt
	.abicalls

 # GNU C 2.6.3 [AL 1.1, MM 40] Silicon Graphics Mips compiled by GNU C

 # Cc1 defaults:

 # Cc1 arguments (-G value = 8, Cpu = 4000, ISA = 3):
 # -mfp64 -mgp64 -quiet -dumpbase -mips3 -mlong64 -mabicalls -O2
 # -fomit-frame-pointer -o

gcc2_compiled.:
__gnu_compiled_c:
	.sdata
	.align	3
$LC0:
	.dword	0x7355471143622155
	.align	3
$LC1:
	.dword	0xbabebec0dea0ffab
	.text
	.align	2
	.globl	tramp
	.sdata
	.align	3
$LC2:
	.dword	0xbabebec0dea0ffab
	.text
	.align	2
	.globl	jump

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
	ld	$3,$LC1
	ld	$2,$LC0
	sd	$31,48($sp)
	sd	$28,40($sp)
	move	$25,$3
	jal	$31,$25
	ld	$31,48($sp)
	daddu	$sp,$sp,56
	j	$31
	.end	tramp
	.ent	jump
jump:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	ld	$3,$LC2
	#nop
	j	$3
	.end	jump
