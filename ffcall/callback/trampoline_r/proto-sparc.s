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
	sethi	%hi(1934967808), %o1
	sethi	%hi(-1161905152), %o0
	or	%o0, 704, %o0
	call	%o0, 0
	or	%o1, 785, %g2
	ret
	restore %g0, %o0, %o0
	.align 4
	.global _jump
	.proc	04
_jump:
	!#PROLOGUE# 0
	!#PROLOGUE# 1
	sethi	%hi(-1161905152), %g3
	or	%g3, 704, %g3
	jmp	%g3
	 nop
