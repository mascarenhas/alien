	version	 "03.00"
	file	 "vacall-m88k.c"
data
gcc2_compiled.:
text
	align	 8
	global	 __vacall
	type	 __vacall,#function
__vacall:
	or.u	 #r13,#r0,#hi16(vacall_function)
	ld	 #r11,#r13,#lo16(vacall_function)
	subu	 #r31,#r31,80
	st	 #r1,#r31,36
.Ltb0:
	st	 #r2,#r31,80
	st	 #r3,#r31,84
	st	 #r4,#r31,88
	st	 #r5,#r31,92
	st	 #r6,#r31,96
	st	 #r7,#r31,100
	st	 #r8,#r31,104
	st	 #r9,#r31,108
	st	 #r0,#r31,40
	addu	 #r13,#r31,112
	st	 #r13,#r31,44
	st	 #r0,#r31,48
	st	 #r0,#r31,52
	addu	 #r2,#r31,40
	jsr.n	 #r11
	st	 #r12,#r31,72
	ld	 #r11,#r31,52
	bcnd.n	 #eq0,#r11,.L4
	cmp	 #r13,#r11,1
	bb0.n	 #ne,#r13,.L40
	cmp	 #r13,#r11,2
	bb1.n	 #ne,#r13,.L7
	cmp	 #r13,#r11,3
.L40:
	ld.b	 #r2,#r31,64
	br	 .L4
	align	 4
.L7:
	bb1.n	 #ne,#r13,.L9
	cmp	 #r13,#r11,4
	ld.bu	 #r2,#r31,64
	br	 .L4
	align	 4
.L9:
	bb1.n	 #ne,#r13,.L11
	cmp	 #r13,#r11,5
	ld.h	 #r2,#r31,64
	br	 .L4
	align	 4
.L11:
	bb1.n	 #ne,#r13,.L13
	cmp	 #r13,#r11,6
	ld.hu	 #r2,#r31,64
	br	 .L4
	align	 4
.L13:
	bb0.n	 #ne,#r13,.L41
	cmp	 #r13,#r11,7
	bb0.n	 #ne,#r13,.L41
	cmp	 #r13,#r11,8
	bb0.n	 #ne,#r13,.L41
	cmp	 #r13,#r11,9
	bb0.n	 #ne,#r13,.L41
	subu	 #r13,#r11,10
	cmp	 #r13,#r13,1
	bb0	 #ls,#r13,.L23
	ld	 #r2,#r31,64
	ld	 #r3,#r31,68
	br	 .L4
	align	 4
.L23:
	ld	 #r11,#r31,52
	cmp	 #r13,#r11,12
	bb1.n	 #ne,#r13,.L25
	cmp	 #r13,#r11,13
	ld	 #r2,#r31,64
	br	 .L4
	align	 4
.L25:
	bb1.n	 #ne,#r13,.L27
	cmp	 #r13,#r11,14
	ld.d	 #r2,#r31,64
	br	 .L4
	align	 4
.L27:
	bb1.n	 #ne,#r13,.L29
	cmp	 #r13,#r11,15
.L41:
	ld	 #r2,#r31,64
	br	 .L4
	align	 4
.L29:
	bb0	 #eq,#r13,.L4
	ld	 #r13,#r31,40
	bb0	 (31-31),#r13,.L32
	ld	 #r2,#r31,48
	br	 .L4
	align	 4
.L32:
	bb0	 (31-30),#r13,.L4
	ld	 #r11,#r31,56
	cmp	 #r13,#r11,1
	bb1.n	 #ne,#r13,.L35
	cmp	 #r13,#r11,2
	ld	 #r13,#r31,48
	ld.bu	 #r2,#r0,#r13
	br	 .L4
	align	 4
.L35:
	bb1.n	 #ne,#r13,.L37
	cmp	 #r13,#r11,4
	ld	 #r13,#r31,48
	ld.hu	 #r2,#r0,#r13
	br	 .L4
	align	 4
.L37:
	bb1	 #ne,#r13,.L4
	ld	 #r13,#r31,48
	ld	 #r2,#r0,#r13
.L4:
.Lte0:
	ld	 #r1,#r31,36
	jmp.n	 #r1
	addu	 #r31,#r31,80

section	 .tdesc,"a"
	word	 66,1,.Ltb0,.Lte0,0x100003f,0x50,0xffffffd4,0xffffffd4
text
.Lfe1:
	size	 __vacall,.Lfe1-__vacall
