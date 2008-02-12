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
	st 27,-20(1)
	st 28,-16(1)
	st 29,-12(1)
	st 30,-8(1)
	st 31,-4(1)
	st 0,8(1)
	stu 1,-224(1)
	l 29,LC..0(2)
	cal 11,280(1)
	l 27,0(29)
	st 3,-32(11)
	st 9,-8(11)
	st 10,-4(11)
	st 5,-24(11)
	st 6,-20(11)
	st 7,-16(11)
	st 8,-12(11)
	lil 0,0
	cal 29,248(1)
	cal 28,92(1)
	st 29,60(1)
	st 0,68(1)
	st 28,88(1)
	st 4,-28(11)
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
	st 0,56(1)
	st 0,64(1)
	cal 3,56(1)
	st 2,20(1)
	l 0,0(27)
	l 2,4(27)
	mtlr 0
	l 11,8(27)
	brl
	l 2,20(1)
	l 9,68(1)
	cmpi 0,9,0
	bc 12,2,L..4
	cmpi 0,9,1
	bc 12,2,L..42
	cmpi 0,9,2
	bc 4,2,L..7
	lbz 0,80(1)
	sli 0,0,24
	srai 3,0,24
	b L..4
L..7:
	cmpi 0,9,3
	bc 4,2,L..9
L..42:
	lbz 3,80(1)
	b L..4
L..9:
	cmpi 0,9,4
	bc 4,2,L..11
	lha 3,80(1)
	b L..4
L..11:
	cmpi 0,9,5
	bc 4,2,L..13
	lhz 3,80(1)
	b L..4
L..13:
	cmpi 0,9,6
	bc 12,2,L..43
	cmpi 0,9,7
	bc 12,2,L..43
	cmpi 0,9,8
	bc 12,2,L..43
	cmpi 0,9,9
	bc 12,2,L..43
	cal 0,-10(9)
	cmpli 0,0,1
	bc 12,1,L..23
	l 3,80(1)
	l 4,84(1)
	b L..4
L..23:
	l 0,68(1)
	cmpi 0,0,12
	bc 4,2,L..25
	lfs 1,80(1)
	b L..4
L..25:
	cmpi 0,0,13
	bc 4,2,L..27
	lfd 1,80(1)
	b L..4
L..27:
	cmpi 0,0,14
	bc 4,2,L..29
L..43:
	l 3,80(1)
	b L..4
L..29:
	cmpi 0,0,15
	bc 4,2,L..4
	l 0,56(1)
	andil. 9,0,1
	bc 12,2,L..32
	l 3,64(1)
	b L..4
L..32:
	andil. 9,0,1024
	bc 12,2,L..4
	l 0,72(1)
	cmpi 0,0,1
	bc 4,2,L..35
	l 9,64(1)
	lbz 3,0(9)
	b L..4
L..35:
	cmpi 0,0,2
	bc 4,2,L..37
	l 9,64(1)
	lhz 3,0(9)
	b L..4
L..37:
	cmpi 0,0,4
	bc 4,2,L..39
	l 9,64(1)
	b L..44
L..39:
	cmpi 0,0,8
	bc 4,2,L..4
	l 9,64(1)
	l 4,4(9)
L..44:
	l 3,0(9)
L..4:
	cal 1,224(1)
	l 0,8(1)
	mtlr 0
	l 27,-20(1)
	l 28,-16(1)
	l 29,-12(1)
	l 30,-8(1)
	l 31,-4(1)
	br
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
