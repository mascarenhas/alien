	.file	"avcall-rs6000.c"
gcc2_compiled.:
	.section	".text"
	.align 2
	.globl __builtin_avcall
	.type	 __builtin_avcall,@function
__builtin_avcall:
	stwu 1,-1040(1)
	mflr 0
	stw 31,1036(1)
	stw 0,1044(1)
	mr 31,3
	addi 7,1,8
	lwz 9,20(31)
	addi 11,9,-40
	subf 11,31,11
	srawi 11,11,2
	lwz 9,1064(31)
	addi 10,9,-1072
	subf 10,31,10
	srawi 10,10,3
	subfic 3,10,8
	cmpw 0,3,11
	bc 4,0,.L4
	addi 8,31,40
.L6:
	add 9,10,3
	slwi 9,9,2
	add 9,9,7
	slwi 0,3,2
	lwzx 0,8,0
	stw 0,-32(9)
	addi 3,3,1
	cmpw 0,3,11
	bc 12,0,.L6
.L4:
	lwz 9,1064(31)
	addi 11,9,-1072
	subf 11,31,11
	srawi. 11,11,3
	bc 12,2,.L9
	cmpwi 0,11,1
	bc 12,2,.L12
	cmpwi 0,11,2
	bc 12,2,.L15
	cmpwi 0,11,3
	bc 12,2,.L18
	cmpwi 0,11,4
	bc 12,2,.L21
	cmpwi 0,11,5
	bc 12,2,.L24
	cmpwi 0,11,6
	bc 12,2,.L27
	cmpwi 0,11,7
	bc 12,2,.L30
	cmpwi 0,11,8
	bc 12,2,.L33
	cmpwi 0,11,9
	bc 12,2,.L36
	cmpwi 0,11,10
	bc 12,2,.L39
	cmpwi 0,11,11
	bc 12,2,.L42
	cmpwi 0,11,12
	bc 12,2,.L45
	lfd 13,1168(31)
.L45:
	lfd 12,1160(31)
.L42:
	lfd 11,1152(31)
.L39:
	lfd 10,1144(31)
.L36:
	lfd 9,1136(31)
.L33:
	lfd 8,1128(31)
.L30:
	lfd 7,1120(31)
.L27:
	lfd 6,1112(31)
.L24:
	lfd 5,1104(31)
.L21:
	lfd 4,1096(31)
.L18:
	lfd 3,1088(31)
.L15:
	lfd 2,1080(31)
.L12:
	lfd 1,1072(31)
.L9:
	lwz 11,0(31)
	lwz 3,40(31)
	lwz 4,44(31)
	lwz 5,48(31)
	lwz 6,52(31)
	lwz 7,56(31)
	lwz 8,60(31)
	lwz 9,64(31)
	lwz 10,68(31)
	mtlr 11
	crxor 6,6,6
	blrl
	lwz 0,12(31)
	cmpwi 0,0,1
	bc 12,2,.L50
	cmpwi 0,0,0
	bc 12,2,.L102
	lwz 0,12(31)
	cmpwi 0,0,2
	bc 12,2,.L103
	lwz 0,12(31)
	cmpwi 0,0,3
	bc 12,2,.L103
	lwz 0,12(31)
	cmpwi 0,0,4
	bc 12,2,.L103
	lwz 0,12(31)
	cmpwi 0,0,5
	bc 12,2,.L104
	lwz 0,12(31)
	cmpwi 0,0,6
	bc 12,2,.L104
	lwz 0,12(31)
	cmpwi 0,0,7
	bc 12,2,.L102
	lwz 0,12(31)
	cmpwi 0,0,8
	bc 12,2,.L102
	lwz 0,12(31)
	cmpwi 0,0,9
	bc 12,2,.L102
	lwz 0,12(31)
	cmpwi 0,0,10
	bc 12,2,.L102
	lwz 9,12(31)
	addi 9,9,-11
	cmplwi 0,9,1
	bc 4,1,.L105
	lwz 0,12(31)
	cmpwi 0,0,13
	bc 4,2,.L73
	lwz 9,8(31)
	stfs 1,0(9)
	b .L50
.L73:
	lwz 0,12(31)
	cmpwi 0,0,14
	bc 4,2,.L75
	lwz 9,8(31)
	stfd 1,0(9)
	b .L50
.L75:
	lwz 0,12(31)
	cmpwi 0,0,15
	bc 12,2,.L102
	lwz 0,12(31)
	cmpwi 0,0,16
	bc 4,2,.L50
	lwz 0,4(31)
	andi. 9,0,1
	bc 12,2,.L80
	lwz 0,16(31)
	cmpwi 0,0,1
	bc 4,2,.L81
	lwz 9,8(31)
	lbz 0,0(3)
	stb 0,0(9)
	b .L50
.L81:
	lwz 0,16(31)
	cmpwi 0,0,2
	bc 4,2,.L83
	lwz 9,8(31)
	lhz 0,0(3)
	sth 0,0(9)
	b .L50
.L83:
	lwz 0,16(31)
	cmpwi 0,0,4
	bc 4,2,.L85
	lwz 9,8(31)
	lwz 0,0(3)
	stw 0,0(9)
	b .L50
.L85:
	lwz 0,16(31)
	cmpwi 0,0,8
	bc 4,2,.L87
	lwz 9,8(31)
	lwz 0,0(3)
	stw 0,0(9)
	lwz 9,8(31)
	lwz 0,4(3)
	stw 0,4(9)
	b .L50
.L87:
	lwz 9,16(31)
	addi 10,9,3
	srwi 10,10,2
	addic. 10,10,-1
	bc 12,0,.L50
.L91:
	lwz 11,8(31)
	slwi 9,10,2
	lwzx 0,9,3
	stwx 0,9,11
	addic. 10,10,-1
	bc 4,0,.L91
	b .L50
.L80:
	lwz 0,4(31)
	andi. 9,0,512
	bc 12,2,.L50
	lwz 0,16(31)
	cmpwi 0,0,1
	bc 4,2,.L95
.L103:
	lwz 9,8(31)
	stb 3,0(9)
	b .L50
.L95:
	lwz 0,16(31)
	cmpwi 0,0,2
	bc 4,2,.L97
.L104:
	lwz 9,8(31)
	sth 3,0(9)
	b .L50
.L97:
	lwz 0,16(31)
	cmpwi 0,0,4
	bc 4,2,.L99
.L102:
	lwz 9,8(31)
	stw 3,0(9)
	b .L50
.L99:
	lwz 0,16(31)
	cmpwi 0,0,8
	bc 4,2,.L50
.L105:
	lwz 9,8(31)
	stw 3,0(9)
	lwz 9,8(31)
	stw 4,4(9)
.L50:
	li 3,0
	lwz 0,1044(1)
	mtlr 0
	lwz 31,1036(1)
	la 1,1040(1)
	blr
.Lfe1:
	.size	 __builtin_avcall,.Lfe1-__builtin_avcall
	.ident	"GCC: (GNU) 2.95.2 19991024 (release/franzo)"
