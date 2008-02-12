;NO_APP
.fpmode native
gcc2_compiled.:
___gnu_compiled_c:
.text
.text
.align 2
.globl ___builtin_avcall
	ds.b "g263"
	ds.b "+01\0"
___builtin_avcall:
	sub.w #1032,sp
	ld.w (ap),a4
	ld.w 20(a4),s1
	mov a4,s3
	add.w #-32,s1
	sub.w s3,s1
	cvtw.l s1,s2
	shf #-2,s2
	ld.w #0,s1
	lt.w s1,s2
	jbrs.f L2
	mov sp,a2
	mov a4,a3
	mov s2,a1
	shf #2,a1
	add.w sp,a1
L4:
	ld.w 32(a3),s1
	add.w #4,a3
	st.w s1,(a2)
	add.w #4,a2
	lt.w a2,a1
	jbra.t L4
L2:
	ld.w (a4),a1
	st.w a4,-1028(fp)
	mov sp,ap
	calls (a1)
	ld.w 12(fp),ap
	ld.w -1028(fp),a4
	ld.w 12(a4),s1
	mov s0,a3
	eq.w #1,s1
	jbrs.t L7
	eq.w #0,s1
	jbrs.t L61
	eq.w #2,s1
	jbrs.t L62
	eq.w #3,s1
	jbrs.t L62
	eq.w #4,s1
	jbrs.t L62
	eq.w #5,s1
	jbrs.t L63
	eq.w #6,s1
	jbrs.t L63
	eq.w #7,s1
	jbrs.t L61
	eq.w #8,s1
	jbrs.t L61
	eq.w #9,s1
	jbrs.t L61
	eq.w #10,s1
	jbrs.t L61
	ld.w 12(a4),s1
	eq.w #11,s1
	jbrs.t L64
	eq.w #12,s1
	jbrs.t L64
	eq.w #13,s1
	jbrs.f L32
	ld.w 8(a4),a1
	st.s s0,(a1)
	jbr L7
L32:
	eq.w #14,s1
	jbrs.f L34
	ld.w 8(a4),a1
	st.d s0,(a1)
	jbr L7
L34:
	eq.w #15,s1
	jbrs.t L61
	eq.w #16,s1
	jbrs.f L7
	ld.w 4(a4),s2
	mov.w s2,s1
	and #1,s1
	eq.w #0,s1
	jbrs.t L39
	ld.w 16(a4),s1
	eq.w #1,s1
	jbrs.f L40
	ld.w 8(a4),a1
	ld.b (a3),s1
	st.b s1,(a1)
	jbr L7
L40:
	eq.w #2,s1
	jbrs.f L42
	ld.w 8(a4),a1
	ld.h (a3),s1
	st.h s1,(a1)
	jbr L7
L42:
	eq.w #4,s1
	jbrs.f L44
	ld.w 8(a4),a1
	ld.w (a3),s1
	st.w s1,(a1)
	jbr L7
L44:
	eq.w #8,s1
	jbrs.f L46
	ld.w 8(a4),a1
	ld.w (a3),s1
	st.w s1,(a1)
	ld.w 8(a4),a1
	ld.w 4(a3),s1
	st.w s1,4(a1)
	jbr L7
L46:
	add.w #3,s1
	shf.w #-2,s1
	add.w #-1,s1
	le.w #0,s1
	jbrs.f L7
	shf.w #2,s1
	mov s1,a2
	add.w a3,a2
	mov.w s1,s2
L50:
	ld.w 8(a4),a1
	ld.w (a2),s1
	add.w #-4,a2
	add.w s2,a1
	add.w #-4,s2
	st.w s1,(a1)
	lt.w a2,a3
	jbra.f L50
	jbr L7
L39:
	mov.w s2,s1
	and #512,s1
	eq.w #0,s1
	jbrs.t L7
	ld.w 16(a4),s1
	eq.w #1,s1
	jbrs.f L54
L62:
	ld.w 8(a4),a1
	st.b a3,(a1)
	jbr L7
L54:
	eq.w #2,s1
	jbrs.f L56
L63:
	ld.w 8(a4),a1
	st.h a3,(a1)
	jbr L7
L56:
	eq.w #4,s1
	jbrs.f L58
L61:
	ld.w 8(a4),a1
	st.w a3,(a1)
	jbr L7
L58:
	eq.w #8,s1
	jbrs.f L7
L64:
	ld.w 8(a4),a1
	st.l s0,(a1)
L7:
	ld.w #0,s0
	rtn
	ds.h 0
