	.set noreorder
	.set volatile
	.set noat
	.file	1 "proto.c"
gcc2_compiled.:
__gnu_compiled_c:
.rdata
	.align 3
$C32:
	.quad 0xbabebec0
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
	lda $1,$C32
	lda $2,22136
	ldah $2,4660($2)
	ldq $27,0($1)
	lda $1,18193
	ldah $1,29525($1)
	stq $1,0($2)
	jsr $26,($27),0
	ldgp $29,0($26)
	ldq $26,0($30)
	addq $30,16,$30
	ret $31,($26),1
	.end tramp
.rdata
	.align 3
$C33:
	.quad 0xbabebec0
.text
	.align 3
	.globl jump
	.ent jump
jump:
	ldgp $29,0($27)
jump..ng:
	.frame $30,0,$26,0
	.prologue 1
	lda $1,$C33
	ldq $1,0($1)
	jmp $31,($1),0
	.align 4
	.end jump
