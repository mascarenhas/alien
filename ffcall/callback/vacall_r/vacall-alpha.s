	.set noreorder
	.set volatile
	.set noat
	.file	1 "vacall-alpha.c"
gcc2_compiled.:
__gnu_compiled_c:
.text
	.align 3
	.globl __vacall_r
	.ent __vacall_r
__vacall_r:
__vacall_r..ng:
	lda $30,-176($30)
	.frame $30,176,$26,0
	stq $26,0($30)
	.mask 0x4000000,-176
	.prologue 1
	stq $16,128($30)
	stq $17,136($30)
	stq $18,144($30)
	stq $19,152($30)
	stq $20,160($30)
	stq $21,168($30)
	stt $f16,80($30)
	stt $f17,88($30)
	stt $f18,96($30)
	stt $f19,104($30)
	stt $f20,112($30)
	stt $f21,120($30)
	stl $31,16($30)
	addq $30,128,$2
	stq $2,24($30)
	stq $31,32($30)
	stl $31,40($30)
	addq $30,176,$4
	stq $4,72($30)
	ldq $16,8($1)
	ldq $27,0($1)
	addq $30,16,$17
	jsr $26,($27),0
	ldl $2,40($30)
	zapnot $2,15,$3
	beq $3,$35
	subq $3,1,$2
	beq $2,$77
	subq $3,2,$2
	bne $2,$38
$77:
	ldl $2,56($30)
	insbl $2,7,$2
	sra $2,56,$0
	br $31,$35
	.align 4
$38:
	subq $3,3,$2
	bne $2,$40
	ldl $2,56($30)
	extbl $2,0,$2
	zapnot $2,1,$0
	br $31,$35
	.align 4
$40:
	subq $3,4,$2
	bne $2,$42
	ldl $2,56($30)
	inswl $2,6,$2
	sra $2,48,$0
	br $31,$35
	.align 4
$42:
	subq $3,5,$2
	bne $2,$44
	ldl $2,56($30)
	extwl $2,0,$2
	zapnot $2,3,$0
	br $31,$35
	.align 4
$44:
	subq $3,6,$2
	bne $2,$46
	ldl $0,56($30)
	br $31,$35
	.align 4
$46:
	subq $3,7,$2
	bne $2,$48
	ldl $2,56($30)
	zapnot $2,15,$0
	br $31,$35
	.align 4
$48:
	subq $3,8,$2
	beq $2,$78
	subq $3,9,$2
	beq $2,$78
	subq $3,10,$2
	beq $2,$78
	ldl $2,40($30)
	zapnot $2,15,$3
	subq $3,11,$2
	beq $2,$78
	subq $3,12,$2
	bne $2,$58
	lds $f0,56($30)
	br $31,$35
	.align 4
$58:
	subq $3,13,$2
	bne $2,$60
	ldt $f0,56($30)
	br $31,$35
	.align 4
$60:
	subq $3,14,$2
	bne $2,$62
$78:
	ldq $0,56($30)
	br $31,$35
	.align 4
$62:
	subq $3,15,$2
	bne $2,$35
	ldl $2,16($30)
	blbc $2,$65
	ldq $0,32($30)
	br $31,$35
	.align 4
$65:
	srl $2,10,$2
	blbc $2,$35
	ldq $3,48($30)
	subq $3,1,$2
	bne $2,$68
	ldq $3,32($30)
	ldq_u $2,0($3)
	extbl $2,$3,$2
	zapnot $2,1,$0
	br $31,$35
	.align 4
$68:
	subq $3,2,$2
	bne $2,$70
	ldq $2,32($30)
	bic $2,6,$3
	ldq $3,0($3)
	bic $2,1,$2
	extwl $3,$2,$3
	zapnot $3,3,$0
	br $31,$35
	.align 4
$70:
	subq $3,4,$2
	bne $2,$72
	ldq $2,32($30)
	ldl $2,0($2)
	zapnot $2,15,$0
	br $31,$35
	.align 4
$72:
	subq $3,8,$2
	bne $2,$74
	ldq $2,32($30)
	ldq $0,0($2)
	br $31,$35
	.align 4
$74:
	subq $3,16,$2
	bne $2,$35
	ldq $2,32($30)
	ldq $0,0($2)
	ldq $1,8($2)
$35:
	ldq $26,0($30)
	addq $30,176,$30
	ret $31,($26),1
	.end __vacall_r
