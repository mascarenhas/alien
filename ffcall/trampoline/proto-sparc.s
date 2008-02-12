gcc2_compiled.:
___gnu_compiled_c:
.text
	.align 4
	.global _tramp
	.proc	04
_tramp:
	!#PROLOGUE# 0
	save	%sp, -104, %sp
	!#PROLOGUE# 1
	sethi	%hi(305419264), %o2
	sethi	%hi(1934967808), %o1
	or	%o2, 632, %o2
	or	%o1, 785, %o1
	sethi	%hi(-1161905152), %o0
	or	%o0, 704, %o0
	call	%o0, 0
	st	%o1, [%o2]
	ret
	restore %g0, %o0, %o0
	.align 4
	.global _jump
	.proc	04
_jump:
	!#PROLOGUE# 0
	!#PROLOGUE# 1
	sethi	%hi(-1161905152), %g2
	or	%g2, 704, %g2
	jmp	%g2
	 nop
