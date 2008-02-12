	.file	"avcall-rs6000.c"
gcc2_compiled.:
	.section	".text"
	.align 2
	.globl __builtin_avcall
	.type	 __builtin_avcall,@function
__builtin_avcall:
	.extern __mulh
	.extern __mull
	.extern __divss
	.extern __divus
	.extern __quoss
	.extern __quous
	stwu 1,-1040(1)
	mflr 0
	stw 31,1036(1)
	stw 0,1044(1)
	mr 31,3
	lwz 9,20(31)
	addi 0,1,56
	addi 9,9,-32
	subfc 9,31,9
	srawi 3,9,2
	cmpwi 0,3,8
	bc 4,1,.L4
	mr 11,0
	addi 3,3,-8
	addi 9,31,64
.L6:
	lwz 0,0(9)
	addic. 3,3,-1
	stw 0,0(11)
	addi 9,9,4
	addi 11,11,4
	bc 4,2,.L6
.L4:
	lwz 9,1056(31)
	addi 9,9,-1064
	subfc 9,31,9
	srawi. 3,9,3
	bc 12,2,.L9
	cmpwi 0,3,1
	bc 12,2,.L12
	cmpwi 0,3,2
	bc 12,2,.L15
	cmpwi 0,3,3
	bc 12,2,.L18
	cmpwi 0,3,4
	bc 12,2,.L21
	cmpwi 0,3,5
	bc 12,2,.L24
	cmpwi 0,3,6
	bc 12,2,.L27
	cmpwi 0,3,7
	bc 12,2,.L30
	cmpwi 0,3,8
	bc 12,2,.L33
	cmpwi 0,3,9
	bc 12,2,.L36
	cmpwi 0,3,10
	bc 12,2,.L39
	cmpwi 0,3,11
	bc 12,2,.L42
	cmpwi 0,3,12
	bc 12,2,.L45
	lfd 13,1160(31)
.L45:
	lfd 12,1152(31)
.L42:
	lfd 11,1144(31)
.L39:
	lfd 10,1136(31)
.L36:
	lfd 9,1128(31)
.L33:
	lfd 8,1120(31)
.L30:
	lfd 7,1112(31)
.L27:
	lfd 6,1104(31)
.L24:
	lfd 5,1096(31)
.L21:
	lfd 4,1088(31)
.L18:
	lfd 3,1080(31)
.L15:
	lfd 2,1072(31)
.L12:
	lfd 1,1064(31)
.L9:
	lwz 11,0(31)
	lwz 3,32(31)
	lwz 4,36(31)
	mtlr 11
	lwz 5,40(31)
	lwz 6,44(31)
	lwz 7,48(31)
	lwz 8,52(31)
	lwz 9,56(31)
	lwz 10,60(31)
	crxor 6,6,6
	blrl
	lwz 0,12(31)
	cmpwi 0,0,1
	bc 12,2,.L50
	cmpwi 0,0,0
	bc 12,2,.L102
	cmpwi 0,0,2
	bc 12,2,.L103
	cmpwi 0,0,3
	bc 12,2,.L103
	cmpwi 0,0,4
	bc 12,2,.L103
	cmpwi 0,0,5
	bc 12,2,.L104
	cmpwi 0,0,6
	bc 12,2,.L104
	cmpwi 0,0,7
	bc 12,2,.L102
	cmpwi 0,0,8
	bc 12,2,.L102
	cmpwi 0,0,9
	bc 12,2,.L102
	cmpwi 0,0,10
	bc 12,2,.L102
	lwz 9,12(31)
	addi 0,9,-11
	cmplwi 0,0,1
	bc 4,1,.L105
	cmpwi 0,9,13
	bc 4,2,.L73
	frsp 0,1
	lwz 9,8(31)
	stfs 0,0(9)
	b .L50
.L73:
	cmpwi 0,9,14
	bc 4,2,.L75
	lwz 9,8(31)
	stfd 1,0(9)
	b .L50
.L75:
	cmpwi 0,9,15
	bc 12,2,.L102
	cmpwi 0,9,16
	bc 4,2,.L50
	lwz 0,4(31)
	andi. 9,0,1
	bc 12,2,.L80
	lwz 9,16(31)
	cmpwi 0,9,1
	bc 4,2,.L81
	lwz 9,8(31)
	lbz 0,0(3)
	stb 0,0(9)
	b .L50
.L81:
	cmpwi 0,9,2
	bc 4,2,.L83
	lwz 9,8(31)
	lhz 0,0(3)
	sth 0,0(9)
	b .L50
.L83:
	cmpwi 0,9,4
	bc 4,2,.L85
	lwz 9,8(31)
	lwz 0,0(3)
	stw 0,0(9)
	b .L50
.L85:
	cmpwi 0,9,8
	bc 4,2,.L87
	lwz 0,0(3)
	lwz 9,8(31)
	stw 0,0(9)
	lwz 11,8(31)
	lwz 0,4(3)
	stw 0,4(11)
	b .L50
.L87:
	addi 0,9,3
	srwi 10,0,2
	addic. 10,10,-1
	bc 12,0,.L50
	slwi 11,10,2
.L91:
	lwzx 0,11,3
	lwz 9,8(31)
	addic. 10,10,-1
	stwx 0,11,9
	addi 11,11,-4
	bc 4,0,.L91
	b .L50
.L80:
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
	cmpwi 0,0,2
	bc 4,2,.L97
.L104:
	lwz 9,8(31)
	sth 3,0(9)
	b .L50
.L97:
	cmpwi 0,0,4
	bc 4,2,.L99
.L102:
	lwz 9,8(31)
	stw 3,0(9)
	b .L50
.L99:
	cmpwi 0,0,8
	bc 4,2,.L50
.L105:
	lwz 9,8(31)
	stw 3,0(9)
	lwz 11,8(31)
	stw 4,4(11)
.L50:
	li 3,0
	lwz 0,1044(1)
	mtlr 0
	lwz 31,1036(1)
	la 1,1040(1)
	blr
.Lfe1:
	.size	 __builtin_avcall,.Lfe1-__builtin_avcall
	.ident	"GCC: (GNU) 2.95.2 19991024 (release)"
