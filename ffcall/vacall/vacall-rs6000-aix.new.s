	.file	"vacall-rs6000.c"
.toc
.csect .text[PR]
gcc2_compiled.:
__gnu_compiled_c:
	.extern vacall_function[RW]
.toc
LC..0:
	.tc vacall_function[TC],vacall_function[RW]
.csect .text[PR]
	.align 2
	.globl __vacall
	.globl .__vacall
.csect __vacall[DS]
__vacall:
	.long .__vacall, TOC[tc0], 0
.csect .text[PR]
.__vacall:
	.extern __mulh
	.extern __mull
	.extern __divss
	.extern __divus
	.extern __quoss
	.extern __quous
	mflr 0
	stw 27,-20(1)
	stw 28,-16(1)
	stw 29,-12(1)
	stw 30,-8(1)
	stw 31,-4(1)
	stw 0,8(1)
	stwu 1,-224(1)
	lwz 29,LC..0(2)
	addi 11,1,280
	lwz 27,0(29)
	stw 3,-32(11)
	stw 9,-8(11)
	stw 10,-4(11)
	stw 5,-24(11)
	stw 6,-20(11)
	stw 7,-16(11)
	stw 8,-12(11)
	li 0,0
	addi 29,1,248
	addi 28,1,92
	stw 29,60(1)
	stw 0,68(1)
	stw 28,88(1)
	stw 4,-28(11)
	stfd 1,92(1)
	stfd 2,100(1)
	stfd 3,108(1)
	stfd 4,116(1)
	stfd 5,124(1)
	stfd 6,132(1)
	stfd 7,140(1)
	stfd 8,148(1)
	stfd 9,156(1)
	stfd 10,164(1)
	stfd 11,172(1)
	stfd 12,180(1)
	stfd 13,188(1)
	stw 0,56(1)
	stw 0,64(1)
	addi 3,1,56
	stw 2,20(1)
	lwz 0,0(27)
	lwz 2,4(27)
	mtlr 0
	lwz 11,8(27)
	blrl
	lwz 2,20(1)
	lwz 9,68(1)
	cmpwi 0,9,0
	bc 12,2,L..4
	cmpwi 0,9,1
	bc 12,2,L..42
	cmpwi 0,9,2
	bc 4,2,L..7
	lbz 0,80(1)
	slwi 0,0,24
	srawi 3,0,24
	b L..4
L..7:
	cmpwi 0,9,3
	bc 4,2,L..9
L..42:
	lbz 3,80(1)
	b L..4
L..9:
	cmpwi 0,9,4
	bc 4,2,L..11
	lha 3,80(1)
	b L..4
L..11:
	cmpwi 0,9,5
	bc 4,2,L..13
	lhz 3,80(1)
	b L..4
L..13:
	cmpwi 0,9,6
	bc 12,2,L..43
	cmpwi 0,9,7
	bc 12,2,L..43
	cmpwi 0,9,8
	bc 12,2,L..43
	cmpwi 0,9,9
	bc 12,2,L..43
	addi 0,9,-10
	cmplwi 0,0,1
	bc 12,1,L..23
	lwz 3,80(1)
	lwz 4,84(1)
	b L..4
L..23:
	lwz 0,68(1)
	cmpwi 0,0,12
	bc 4,2,L..25
	lfs 1,80(1)
	b L..4
L..25:
	cmpwi 0,0,13
	bc 4,2,L..27
	lfd 1,80(1)
	b L..4
L..27:
	cmpwi 0,0,14
	bc 4,2,L..29
L..43:
	lwz 3,80(1)
	b L..4
L..29:
	cmpwi 0,0,15
	bc 4,2,L..4
	lwz 0,56(1)
	andi. 9,0,1
	bc 12,2,L..32
	lwz 3,64(1)
	b L..4
L..32:
	andi. 9,0,1024
	bc 12,2,L..4
	lwz 0,72(1)
	cmpwi 0,0,1
	bc 4,2,L..35
	lwz 9,64(1)
	lbz 3,0(9)
	b L..4
L..35:
	cmpwi 0,0,2
	bc 4,2,L..37
	lwz 9,64(1)
	lhz 3,0(9)
	b L..4
L..37:
	cmpwi 0,0,4
	bc 4,2,L..39
	lwz 9,64(1)
	b L..44
L..39:
	cmpwi 0,0,8
	bc 4,2,L..4
	lwz 9,64(1)
	lwz 4,4(9)
L..44:
	lwz 3,0(9)
L..4:
	la 1,224(1)
	lwz 0,8(1)
	mtlr 0
	lwz 27,-20(1)
	lwz 28,-16(1)
	lwz 29,-12(1)
	lwz 30,-8(1)
	lwz 31,-4(1)
	blr
LT..__vacall:
	.long 0
	.byte 0,0,32,65,128,5,8,0
	.long 0
	.long LT..__vacall-.__vacall
	.short 8
	.byte "__vacall"
_section_.text:
.csect .data[RW],3
	.long _section_.text
