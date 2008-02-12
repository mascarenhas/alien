	.set noreorder
	.set volatile
	.set noat
	.file	1 "proto64.c"
gcc2_compiled.:
__gnu_compiled_c:
.rdata
	.quad 0
	.align 3
$C32:
	.quad 0x7355471143622155
	.align 3
$C33:
	.quad 0xbabebec0dea0ffab
.text
	.align 3
	.globl tramp
	.ent tramp
tramp:
	ldgp $29,0($27)
tramp..ng:
	lda $30,-16($30)
	.frame $30,16,$26,0
	stq $26,0($30)
	.mask 0x4000000,-16
	.prologue 1
	lda $2,$C33
	lda $3,$C32
	ldq $27,0($2)
	ldq $1,0($3)
	jsr $26,($27),0
	ldgp $29,0($26)
	ldq $26,0($30)
	addq $30,16,$30
	ret $31,($26),1
	.end tramp
.rdata
	.align 3
$C34:
	.quad 0xbabebec0dea0ffab
.text
	.align 3
	.globl jump
	.ent jump
jump:
	ldgp $29,0($27)
jump..ng:
	.frame $30,0,$26,0
	.prologue 1
	lda $2,$C34
	ldq $2,0($2)
	jmp $31,($2),0
	.align 4
	.end jump
