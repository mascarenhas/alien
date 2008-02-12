	.file	"vacall-rs6000.c"
gcc2_compiled.:
	.section	".text"
	.align 2
	.globl __vacall_r
	.type	 __vacall_r,@function
__vacall_r:
	.extern __mulh
	.extern __mull
	.extern __divss
	.extern __divus
	.extern __quoss
	.extern __quous
	stwu 1,-176(1)
	mflr 0
	stw 27,156(1)
	stw 28,160(1)
	stw 29,164(1)
	stw 30,168(1)
	stw 31,172(1)
	stw 0,180(1)
	addi 29,1,184
	lwz 12,0(11)
	stw 3,-32(29)
	stw 4,-28(29)
	mtlr 12
	lwz 3,4(11)
	addi 4,1,8
	stw 9,-8(29)
	stw 10,-4(29)
	stw 5,-24(29)
	stw 6,-20(29)
	stw 7,-16(29)
	stw 8,-12(29)
	li 0,0
	addi 28,1,152
	addi 27,1,48
	stw 28,12(1)
	stw 0,20(1)
	stw 27,40(1)
	stfd 1,48(1)
	stfd 2,56(1)
	stfd 3,64(1)
	stfd 4,72(1)
	stfd 5,80(1)
	stfd 6,88(1)
	stfd 7,96(1)
	stfd 8,104(1)
	stw 0,8(1)
	stw 0,16(1)
	blrl
	lwz 9,20(1)
	cmpwi 0,9,0
	bc 12,2,.L4
	cmpwi 0,9,1
	bc 12,2,.L42
	cmpwi 0,9,2
	bc 4,2,.L7
	lbz 0,32(1)
	slwi 0,0,24
	srawi 3,0,24
	b .L4
.L7:
	cmpwi 0,9,3
	bc 4,2,.L9
.L42:
	lbz 3,32(1)
	b .L4
.L9:
	cmpwi 0,9,4
	bc 4,2,.L11
	lha 3,32(1)
	b .L4
.L11:
	cmpwi 0,9,5
	bc 4,2,.L13
	lhz 3,32(1)
	b .L4
.L13:
	cmpwi 0,9,6
	bc 12,2,.L43
	cmpwi 0,9,7
	bc 12,2,.L43
	cmpwi 0,9,8
	bc 12,2,.L43
	cmpwi 0,9,9
	bc 12,2,.L43
	addi 0,9,-10
	cmplwi 0,0,1
	bc 12,1,.L23
	lwz 3,32(1)
	lwz 4,36(1)
	b .L4
.L23:
	lwz 0,20(1)
	cmpwi 0,0,12
	bc 4,2,.L25
	lfs 1,32(1)
	b .L4
.L25:
	cmpwi 0,0,13
	bc 4,2,.L27
	lfd 1,32(1)
	b .L4
.L27:
	cmpwi 0,0,14
	bc 4,2,.L29
.L43:
	lwz 3,32(1)
	b .L4
.L29:
	cmpwi 0,0,15
	bc 4,2,.L4
	lwz 0,8(1)
	andi. 9,0,1
	bc 12,2,.L32
	lwz 3,16(1)
	b .L4
.L32:
	andi. 9,0,1024
	bc 12,2,.L4
	lwz 0,24(1)
	cmpwi 0,0,1
	bc 4,2,.L35
	lwz 9,16(1)
	lbz 3,0(9)
	b .L4
.L35:
	cmpwi 0,0,2
	bc 4,2,.L37
	lwz 9,16(1)
	lhz 3,0(9)
	b .L4
.L37:
	cmpwi 0,0,4
	bc 4,2,.L39
	lwz 9,16(1)
	b .L44
.L39:
	cmpwi 0,0,8
	bc 4,2,.L4
	lwz 9,16(1)
	lwz 4,4(9)
.L44:
	lwz 3,0(9)
.L4:
	lwz 0,180(1)
	mtlr 0
	lwz 27,156(1)
	lwz 28,160(1)
	lwz 29,164(1)
	lwz 30,168(1)
	lwz 31,172(1)
	la 1,176(1)
	blr
.Lfe1:
	.size	 __vacall_r,.Lfe1-__vacall_r
	.ident	"GCC: (GNU) 2.95.2 19991024 (release)"
