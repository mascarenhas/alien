	.file	"avcall-rs6000.c"
.toc
.csect .text[PR]
gcc2_compiled.:
__gnu_compiled_c:
	.align 2
	.globl __builtin_avcall
	.globl .__builtin_avcall
.csect __builtin_avcall[DS]
__builtin_avcall:
	.long .__builtin_avcall, TOC[tc0], 0
.csect .text[PR]
.__builtin_avcall:
	.extern __mulh
	.extern __mull
	.extern __divss
	.extern __divus
	.extern __quoss
	.extern __quous
	mflr 0
	st 29,-12(1)
	st 30,-8(1)
	st 31,-4(1)
	st 0,8(1)
	stu 1,-1096(1)
	mr 31,3
	l 9,20(31)
	cal 0,56(1)
	cal 9,-32(9)
	sf 9,31,9
	srai 3,9,2
	cmpi 0,3,8
	bc 4,1,L..4
	mr 11,0
	cal 3,-8(3)
	cal 9,64(31)
L..6:
	l 0,0(9)
	ai. 3,3,-1
	st 0,0(11)
	cal 9,4(9)
	cal 11,4(11)
	bc 4,2,L..6
L..4:
	l 9,1056(31)
	cal 9,-1060(9)
	sf 9,31,9
	srai. 3,9,3
	bc 12,2,L..9
	cmpi 0,3,1
	bc 12,2,L..12
	cmpi 0,3,2
	bc 12,2,L..15
	cmpi 0,3,3
	bc 12,2,L..18
	cmpi 0,3,4
	bc 12,2,L..21
	cmpi 0,3,5
	bc 12,2,L..24
	cmpi 0,3,6
	bc 12,2,L..27
	cmpi 0,3,7
	bc 12,2,L..30
	cmpi 0,3,8
	bc 12,2,L..33
	cmpi 0,3,9
	bc 12,2,L..36
	cmpi 0,3,10
	bc 12,2,L..39
	cmpi 0,3,11
	bc 12,2,L..42
	cmpi 0,3,12
	bc 12,2,L..45
	lfd 13,1156(31)
L..45:
	lfd 12,1148(31)
L..42:
	lfd 11,1140(31)
L..39:
	lfd 10,1132(31)
L..36:
	lfd 9,1124(31)
L..33:
	lfd 8,1116(31)
L..30:
	lfd 7,1108(31)
L..27:
	lfd 6,1100(31)
L..24:
	lfd 5,1092(31)
L..21:
	lfd 4,1084(31)
L..18:
	lfd 3,1076(31)
L..15:
	lfd 2,1068(31)
L..12:
	lfd 1,1060(31)
L..9:
	l 29,0(31)
	l 3,32(31)
	l 4,36(31)
	l 5,40(31)
	l 6,44(31)
	l 7,48(31)
	l 8,52(31)
	l 9,56(31)
	l 10,60(31)
	st 2,20(1)
	l 0,0(29)
	l 2,4(29)
	mtlr 0
	l 11,8(29)
	brl
	l 2,20(1)
	l 0,12(31)
	cmpi 0,0,1
	bc 12,2,L..50
	cmpi 0,0,0
	bc 12,2,L..102
	cmpi 0,0,2
	bc 12,2,L..103
	cmpi 0,0,3
	bc 12,2,L..103
	cmpi 0,0,4
	bc 12,2,L..103
	cmpi 0,0,5
	bc 12,2,L..104
	cmpi 0,0,6
	bc 12,2,L..104
	cmpi 0,0,7
	bc 12,2,L..102
	cmpi 0,0,8
	bc 12,2,L..102
	cmpi 0,0,9
	bc 12,2,L..102
	cmpi 0,0,10
	bc 12,2,L..102
	l 9,12(31)
	cal 0,-11(9)
	cmpli 0,0,1
	bc 4,1,L..105
	cmpi 0,9,13
	bc 4,2,L..73
	l 9,8(31)
	frsp 0,1
	stfs 0,0(9)
	b L..50
L..73:
	cmpi 0,9,14
	bc 4,2,L..75
	l 9,8(31)
	stfd 1,0(9)
	b L..50
L..75:
	cmpi 0,9,15
	bc 12,2,L..102
	cmpi 0,9,16
	bc 4,2,L..50
	l 0,4(31)
	andil. 9,0,1
	bc 12,2,L..80
	l 9,16(31)
	cmpi 0,9,1
	bc 4,2,L..81
	l 9,8(31)
	lbz 0,0(3)
	stb 0,0(9)
	b L..50
L..81:
	cmpi 0,9,2
	bc 4,2,L..83
	l 9,8(31)
	lhz 0,0(3)
	sth 0,0(9)
	b L..50
L..83:
	cmpi 0,9,4
	bc 4,2,L..85
	l 9,8(31)
	l 0,0(3)
	st 0,0(9)
	b L..50
L..85:
	cmpi 0,9,8
	bc 4,2,L..87
	l 0,0(3)
	l 9,8(31)
	st 0,0(9)
	l 11,8(31)
	l 0,4(3)
	st 0,4(11)
	b L..50
L..87:
	cal 0,3(9)
	sri 10,0,2
	ai. 10,10,-1
	bc 12,0,L..50
	sli 11,10,2
L..91:
	lx 0,11,3
	l 9,8(31)
	ai. 10,10,-1
	stx 0,11,9
	cal 11,-4(11)
	bc 4,0,L..91
	b L..50
L..80:
	andil. 9,0,512
	bc 12,2,L..50
	l 0,16(31)
	cmpi 0,0,1
	bc 4,2,L..95
L..103:
	l 9,8(31)
	stb 3,0(9)
	b L..50
L..95:
	cmpi 0,0,2
	bc 4,2,L..97
L..104:
	l 9,8(31)
	sth 3,0(9)
	b L..50
L..97:
	cmpi 0,0,4
	bc 4,2,L..99
L..102:
	l 9,8(31)
	st 3,0(9)
	b L..50
L..99:
	cmpi 0,0,8
	bc 4,2,L..50
L..105:
	l 9,8(31)
	st 3,0(9)
	l 11,8(31)
	st 4,4(11)
L..50:
	lil 3,0
	cal 1,1096(1)
	l 0,8(1)
	mtlr 0
	l 29,-12(1)
	l 30,-8(1)
	l 31,-4(1)
	br
LT..__builtin_avcall:
	.long 0
	.byte 0,0,32,65,128,3,1,0
	.long 0
	.long LT..__builtin_avcall-.__builtin_avcall
	.short 16
	.byte "__builtin_avcall"
_section_.text:
.csect .data[RW],3
	.long _section_.text
