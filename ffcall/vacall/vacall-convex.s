;NO_APP
.fpmode native
gcc2_compiled.:
___gnu_compiled_c:
.text
.text
.align 2
.globl ___vacall
	ds.b "g263"
	ds.b "+01\0"
___vacall:
	sub.w #32,sp
	ld.w #0,s1
	st.w s1,-28(fp)
	st.w ap,-24(fp)
	st.w s1,-20(fp)
	st.w s1,-16(fp)
	add.w #-4,sp
	pshea -28(fp)
	ld.w _vacall_function,a1
	mov sp,ap
	calls (a1)
	ld.w 12(fp),ap
	add.w #8,sp
	ld.w -16(fp),s1
	eq.w #0,s1
	jbrs.t L2
	eq.w #1,s1
	jbrs.t L42
	eq.w #2,s1
	jbrs.f L5
L42:
	ld.b -8(fp),s1
	cvtb.w s1,s0
	rtn
L5:
	eq.w #3,s1
	jbrs.f L7
	ld.b -8(fp),s1
	jbr L43
L7:
	eq.w #4,s1
	jbrs.f L9
	ld.h -8(fp),s1
	cvth.w s1,s0
	rtn
L9:
	eq.w #5,s1
	jbrs.f L11
	ld.h -8(fp),s1
	jbr L44
L11:
	eq.w #6,s1
	jbrs.t L45
	eq.w #7,s1
	jbrs.t L45
	eq.w #8,s1
	jbrs.t L45
	eq.w #9,s1
	jbrs.t L45
	eq.w #10,s1
	jbrs.t L46
	ld.w -16(fp),s1
	eq.w #11,s1
	jbrs.f L23
L46:
	ld.w -4(fp),s0
	rtn
L23:
	eq.w #12,s1
	jbrs.f L25
	ld.s -8(fp),s0
	rtn
L25:
	eq.w #13,s1
	jbrs.f L27
	ld.d -8(fp),s0
	rtn
L27:
	eq.w #14,s1
	jbrs.f L29
L45:
	ld.w -8(fp),s0
	rtn
L29:
	eq.w #15,s1
	jbrs.f L2
	ld.w -28(fp),s2
	mov.w s2,s1
	and #1,s1
	eq.w #0,s1
	jbrs.t L32
	ld.w -20(fp),s0
	rtn
L32:
	mov.w s2,s1
	and #1024,s1
	eq.w #0,s1
	jbrs.t L2
	ld.w -12(fp),s1
	eq.w #1,s1
	jbrs.f L35
	ld.w -20(fp),a1
	ld.b (a1),s1
L43:
	mov.w s1,s0
	and #0xff,s0
	rtn
L35:
	eq.w #2,s1
	jbrs.f L37
	ld.w -20(fp),a1
	ld.h (a1),s1
L44:
	mov.w s1,s0
	and #0xffff,s0
	rtn
L37:
	eq.w #4,s1
	jbrs.f L39
	ld.w -20(fp),a1
	ld.w (a1),s0
	rtn
L39:
	eq.w #8,s1
	jbrs.f L2
	ld.w -20(fp),a1
	ld.l (a1),s0
L2:
	rtn
	ds.h 0
