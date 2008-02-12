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
	stw 29,-12(1)
	stw 30,-8(1)
	stw 31,-4(1)
	stw 0,8(1)
	stwu 1,-1096(1)
	mr 31,3
	lwz 9,20(31)
	addi 0,1,56
	addi 9,9,-32
	subfc 9,31,9
	srawi 3,9,2
	cmpwi 0,3,8
	bc 4,1,L..4
	mr 11,0
	addi 3,3,-8
	addi 9,31,64
L..6:
	lwz 0,0(9)
	addic. 3,3,-1
	stw 0,0(11)
	addi 9,9,4
	addi 11,11,4
	bc 4,2,L..6
L..4:
	lwz 9,1056(31)
	addi 9,9,-1060
	subfc 9,31,9
	srawi. 3,9,3
	bc 12,2,L..9
	cmpwi 0,3,1
	bc 12,2,L..12
	cmpwi 0,3,2
	bc 12,2,L..15
	cmpwi 0,3,3
	bc 12,2,L..18
	cmpwi 0,3,4
	bc 12,2,L..21
	cmpwi 0,3,5
	bc 12,2,L..24
	cmpwi 0,3,6
	bc 12,2,L..27
	cmpwi 0,3,7
	bc 12,2,L..30
	cmpwi 0,3,8
	bc 12,2,L..33
	cmpwi 0,3,9
	bc 12,2,L..36
	cmpwi 0,3,10
	bc 12,2,L..39
	cmpwi 0,3,11
	bc 12,2,L..42
	cmpwi 0,3,12
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
	lwz 29,0(31)
	lwz 3,32(31)
	lwz 4,36(31)
	lwz 5,40(31)
	lwz 6,44(31)
	lwz 7,48(31)
	lwz 8,52(31)
	lwz 9,56(31)
	lwz 10,60(31)
	stw 2,20(1)
	lwz 0,0(29)
	lwz 2,4(29)
	mtlr 0
	lwz 11,8(29)
	blrl
	lwz 2,20(1)
	lwz 0,12(31)
	cmpwi 0,0,1
	bc 12,2,L..50
	cmpwi 0,0,0
	bc 12,2,L..102
	cmpwi 0,0,2
	bc 12,2,L..103
	cmpwi 0,0,3
	bc 12,2,L..103
	cmpwi 0,0,4
	bc 12,2,L..103
	cmpwi 0,0,5
	bc 12,2,L..104
	cmpwi 0,0,6
	bc 12,2,L..104
	cmpwi 0,0,7
	bc 12,2,L..102
	cmpwi 0,0,8
	bc 12,2,L..102
	cmpwi 0,0,9
	bc 12,2,L..102
	cmpwi 0,0,10
	bc 12,2,L..102
	lwz 9,12(31)
	addi 0,9,-11
	cmplwi 0,0,1
	bc 4,1,L..105
	cmpwi 0,9,13
	bc 4,2,L..73
	lwz 9,8(31)
	frsp 0,1
	stfs 0,0(9)
	b L..50
L..73:
	cmpwi 0,9,14
	bc 4,2,L..75
	lwz 9,8(31)
	stfd 1,0(9)
	b L..50
L..75:
	cmpwi 0,9,15
	bc 12,2,L..102
	cmpwi 0,9,16
	bc 4,2,L..50
	lwz 0,4(31)
	andi. 9,0,1
	bc 12,2,L..80
	lwz 9,16(31)
	cmpwi 0,9,1
	bc 4,2,L..81
	lwz 9,8(31)
	lbz 0,0(3)
	stb 0,0(9)
	b L..50
L..81:
	cmpwi 0,9,2
	bc 4,2,L..83
	lwz 9,8(31)
	lhz 0,0(3)
	sth 0,0(9)
	b L..50
L..83:
	cmpwi 0,9,4
	bc 4,2,L..85
	lwz 9,8(31)
	lwz 0,0(3)
	stw 0,0(9)
	b L..50
L..85:
	cmpwi 0,9,8
	bc 4,2,L..87
	lwz 0,0(3)
	lwz 9,8(31)
	stw 0,0(9)
	lwz 11,8(31)
	lwz 0,4(3)
	stw 0,4(11)
	b L..50
L..87:
	addi 0,9,3
	srwi 10,0,2
	addic. 10,10,-1
	bc 12,0,L..50
	slwi 11,10,2
L..91:
	lwzx 0,11,3
	lwz 9,8(31)
	addic. 10,10,-1
	stwx 0,11,9
	addi 11,11,-4
	bc 4,0,L..91
	b L..50
L..80:
	andi. 9,0,512
	bc 12,2,L..50
	lwz 0,16(31)
	cmpwi 0,0,1
	bc 4,2,L..95
L..103:
	lwz 9,8(31)
	stb 3,0(9)
	b L..50
L..95:
	cmpwi 0,0,2
	bc 4,2,L..97
L..104:
	lwz 9,8(31)
	sth 3,0(9)
	b L..50
L..97:
	cmpwi 0,0,4
	bc 4,2,L..99
L..102:
	lwz 9,8(31)
	stw 3,0(9)
	b L..50
L..99:
	cmpwi 0,0,8
	bc 4,2,L..50
L..105:
	lwz 9,8(31)
	stw 3,0(9)
	lwz 11,8(31)
	stw 4,4(11)
L..50:
	li 3,0
	la 1,1096(1)
	lwz 0,8(1)
	mtlr 0
	lwz 29,-12(1)
	lwz 30,-8(1)
	lwz 31,-4(1)
	blr
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
