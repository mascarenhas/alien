	version	 "03.00"
	file	 "avcall-m88k.c"
data
gcc2_compiled.:
text
	align	 8
	global	 __builtin_avcall
	type	 __builtin_avcall,#function
__builtin_avcall:
	subu	 #r31,#r31,48
	st	 #r1,#r31,36
	st	 #r25,#r31,32
.Ltb0:
	or	 #r25,#r0,#r2
	ld	 #r13,#r25,20
	subu	 #r13,#r13,24
	or	 #r9,#r0,0
	subu	 #r13,#r13,#r25
	subu	 #r31,#r31,1024
	ext	 #r11,#r13,0<2>
	bcnd.n	 #le0,#r11,.L4
	or	 #r8,#r0,#r31
	addu	 #r10,#r25,24
.L6:
	ld	 #r13,#r10[#r9]
	st	 #r13,#r8[#r9]
	addu	 #r9,#r9,1
	cmp	 #r13,#r9,#r11
	bb1	 #lt,#r13,.L6
.L4:
	ld	 #r13,#r25,12
	cmp	 #r13,#r13,16
	bb1	 #ne,#r13,.L8
	ld	 #r12,#r25,8
.L8:
	ld	 #r2,#r25,24
	ld	 #r13,#r0,#r25
	ld	 #r3,#r25,28
	ld	 #r4,#r25,32
	ld	 #r5,#r25,36
	ld	 #r6,#r25,40
	ld	 #r7,#r25,44
	ld	 #r8,#r25,48
	jsr.n	 #r13
	ld	 #r9,#r25,52
	ld	 #r11,#r25,12
	cmp	 #r13,#r11,1
	bb0.n	 #ne,#r13,.L10
	or	 #r9,#r0,#r2
	bcnd.n	 #eq0,#r11,.L60
	cmp	 #r13,#r11,2
	bb0.n	 #ne,#r13,.L61
	cmp	 #r13,#r11,3
	bb0.n	 #ne,#r13,.L61
	cmp	 #r13,#r11,4
	bb0.n	 #ne,#r13,.L61
	cmp	 #r13,#r11,5
	bb0.n	 #ne,#r13,.L62
	cmp	 #r13,#r11,6
	bb0.n	 #ne,#r13,.L62
	cmp	 #r13,#r11,7
	bb0.n	 #ne,#r13,.L60
	cmp	 #r13,#r11,8
	bb0.n	 #ne,#r13,.L60
	cmp	 #r13,#r11,9
	bb0.n	 #ne,#r13,.L60
	cmp	 #r13,#r11,10
	bb0.n	 #ne,#r13,.L60
	subu	 #r13,#r11,11
	cmp	 #r13,#r13,1
	bb0	 #ls,#r13,.L31
	ld	 #r13,#r25,8
	st	 #r9,#r0,#r13
	ld	 #r11,#r25,8
	br.n	 .L10
	st	 #r3,#r11,4
	align	 4
.L31:
	cmp	 #r13,#r11,13
	bb1.n	 #ne,#r13,.L33
	cmp	 #r13,#r11,14
	ld	 #r13,#r25,8
	br.n	 .L10
	st	 #r2,#r0,#r13
	align	 4
.L33:
	bb1.n	 #ne,#r13,.L35
	cmp	 #r13,#r11,15
	ld	 #r13,#r25,8
	br.n	 .L10
	st.d	 #r2,#r0,#r13
	align	 4
.L35:
	bb0.n	 #ne,#r13,.L60
	cmp	 #r13,#r11,16
	bb0	 #eq,#r13,.L10
	ld	 #r13,#r25,4
	bb0	 (31-31),#r13,.L40
	ld	 #r11,#r25,16
	cmp	 #r13,#r11,1
	bb1.n	 #ne,#r13,.L41
	cmp	 #r13,#r11,2
	ld	 #r11,#r25,8
	ld.bu	 #r13,#r0,#r9
	br.n	 .L10
	st.b	 #r13,#r0,#r11
	align	 4
.L41:
	bb1.n	 #ne,#r13,.L43
	cmp	 #r13,#r11,4
	ld	 #r11,#r25,8
	ld.hu	 #r13,#r0,#r9
	br.n	 .L10
	st.h	 #r13,#r0,#r11
	align	 4
.L43:
	bb1.n	 #ne,#r13,.L45
	cmp	 #r13,#r11,8
	ld	 #r11,#r25,8
	ld	 #r13,#r0,#r9
	br.n	 .L10
	st	 #r13,#r0,#r11
	align	 4
.L45:
	bb1.n	 #ne,#r13,.L47
	addu	 #r13,#r11,3
	ld	 #r11,#r25,8
	ld	 #r13,#r0,#r9
	st	 #r13,#r0,#r11
	ld	 #r10,#r25,8
	ld	 #r13,#r9,4
	br.n	 .L10
	st	 #r13,#r10,4
	align	 4
.L47:
	extu	 #r10,#r13,0<2>
	subu	 #r10,#r10,1
	bcnd	 #lt0,#r10,.L10
.L51:
	ld	 #r11,#r25,8
	ld	 #r13,#r9[#r10]
	st	 #r13,#r11[#r10]
	subu	 #r10,#r10,1
	bcnd	 #ge0,#r10,.L51
	addu	 #r31,#r31,1024
	br	 .L63
	align	 4
.L40:
	bb0	 (31-30),#r13,.L10
	ld	 #r11,#r25,16
	cmp	 #r13,#r11,1
	bb1.n	 #ne,#r13,.L55
	cmp	 #r13,#r11,2
.L61:
	ld	 #r13,#r25,8
	br.n	 .L10
	st.b	 #r9,#r0,#r13
	align	 4
.L55:
	bb1.n	 #ne,#r13,.L57
	cmp	 #r13,#r11,4
.L62:
	ld	 #r13,#r25,8
	br.n	 .L10
	st.h	 #r9,#r0,#r13
	align	 4
.L57:
	bb1	 #ne,#r13,.L10
.L60:
	ld	 #r13,#r25,8
	st	 #r9,#r0,#r13
.L10:
	addu	 #r31,#r31,1024
.L63:
.Lte0:
	ld	 #r1,#r31,36
	or	 #r2,#r0,0
	ld	 #r25,#r31,32
	jmp.n	 #r1
	addu	 #r31,#r31,48

section	 .tdesc,"a"
	word	 66,1,.Ltb0,.Lte0,0x100103f,0x30,0xfffffff4,0xfffffff0
text
.Lfe1:
	size	 __builtin_avcall,.Lfe1-__builtin_avcall
