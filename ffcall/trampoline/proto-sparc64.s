	.file	"proto64.c"
	.version	"01.01"
.section	".text"
	.align 4
	.global tramp
	.type	 tramp,#function
	.proc	04
tramp:
	!#PROLOGUE# 0
	save	%sp, -192, %sp
	!#PROLOGUE# 1
	sethi	%hi(1934967808), %o0
	sethi	%hi(1130504192), %o1
	or	%o0, 785, %o0
	or	%o1, 341, %o1
	sllx	%o0, 32, %o0
	sethi	%hi(305419264), %o4
	add	%o0, %o1, %o0
	or	%o4, 632, %o4
	sethi	%hi(324502528), %o3
	sethi	%hi(0xbabebc00), %o2
	sllx	%o4, 32, %o4
	or	%o3, 869, %o3
	or	%o2, 704, %o2
	sethi	%hi(0xdea0fc00), %o1
	sllx	%o2, 32, %o2
	or	%o1, 939, %o1
	call	%o2+%o1, 0
	stx	%o0, [%o4+%o3]
	ret
	restore %g0, %o0, %o0
.LLfe1:
	.size	 tramp,.LLfe1-tramp
	.align 4
	.global jump
	.type	 jump,#function
	.proc	04
jump:
	!#PROLOGUE# 0
	!#PROLOGUE# 1
	sethi	%hi(0xbabebc00), %g2
	sethi	%hi(0xdea0fc00), %g3
	or	%g2, 704, %g2
	or	%g3, 939, %g3
	sllx	%g2, 32, %g2
	jmp	%g2+%g3
	 nop
.LLfe2:
	.size	 jump,.LLfe2-jump
	.ident	"GCC: (GNU) 2.95.2 19991024 (release)"
