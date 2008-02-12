	.file	"avcall-s390.c"
	.version	"01.01"
gcc2_compiled.:
.text
	.align 4
.globl __builtin_avcall
	.type	 __builtin_avcall,@function
__builtin_avcall:
#	leaf function           0
#	automatics              1032
#	outgoing args           0
#	need frame pointer      0
#	call alloca             0
#	has varargs             0
#	incoming args (stack)   0
#	function length         702
#	register live           0111111000001011000000000000000001
	stm	%r6,%r15,24(%r15)
	lr	%r1,%r15
	ahi	%r15,-1128
	st	%r1,0(%r15)
	lr	%r12,%r2
	la	%r2,96(%r15)
	l	%r3,20(%r12)
	ahi	%r3,-40
	sr	%r3,%r12
	sra	%r3,2
	l	%r5,1068(%r12)
	ahi	%r5,-1072
	sr	%r5,%r12
	sra	%r5,2
	lr	%r1,%r3
	s	%r1,1064(%r12)
	chi	%r1,5
	jle	.L3
	lhi	%r1,5
.L3:
	lr	%r4,%r1
	cr	%r4,%r3
	jnl	.L5
	la	%r6,40(%r12)
.L7:
	lr	%r1,%r4
	sll	%r1,2
	l	%r1,0(%r6,%r1)
	st	%r1,0(%r2)
	ahi	%r2,4
	ahi	%r4,1
	cr	%r4,%r3
	jl	.L7
.L5:
	chi	%r5,1
	jne	.L9
	icm	%r1,15,1084(%r12)
	je	.L10
	le	%f0,1072(%r12)
	j	.L12
.L10:
	ld	%f0,1096(%r12)
	j	.L12
.L9:
	chi	%r5,2
	jne	.L12
	icm	%r1,15,1084(%r12)
	je	.L14
	icm	%r2,15,1088(%r12)
	je	.L14
	le	%f0,1072(%r12)
	le	%f2,1076(%r12)
	j	.L12
.L14:
	ltr	%r1,%r1
	je	.L16
	icm	%r5,15,1088(%r12)
	jne	.L16
	le	%f0,1072(%r12)
	j	.L74
.L16:
	ltr	%r1,%r1
	jne	.L18
	icm	%r2,15,1088(%r12)
	je	.L18
	ld	%f0,1096(%r12)
	le	%f2,1076(%r12)
	j	.L12
.L18:
	ltr	%r1,%r1
	jne	.L12
	icm	%r5,15,1088(%r12)
	jne	.L12
	ld	%f0,1096(%r12)
.L74:
	ld	%f2,1104(%r12)
.L12:
	l	%r1,0(%r12)
	l	%r2,40(%r12)
	l	%r3,44(%r12)
	l	%r4,48(%r12)
	l	%r5,52(%r12)
	l	%r6,56(%r12)
	basr	%r14,%r1
	lr	%r4,%r2
	l	%r1,12(%r12)
	chi	%r1,1
	je	.L22
	ltr	%r1,%r1
	je	.L75
	chi	%r1,2
	je	.L76
	chi	%r1,3
	je	.L76
	chi	%r1,4
	je	.L76
	chi	%r1,5
	je	.L77
	chi	%r1,6
	je	.L77
	chi	%r1,7
	je	.L75
	chi	%r1,8
	je	.L75
	chi	%r1,9
	je	.L75
	chi	%r1,10
	je	.L75
	l	%r2,12(%r12)
	lr	%r1,%r2
	ahi	%r1,-11
	lhi	%r5,1
	clr	%r1,%r5
	jle	.L78
	chi	%r2,13
	jne	.L45
	l	%r1,8(%r12)
	ste	%f0,0(%r1)
	j	.L22
.L45:
	chi	%r2,14
	jne	.L47
	l	%r1,8(%r12)
	std	%f0,0(%r1)
	j	.L22
.L47:
	chi	%r2,15
	je	.L75
	chi	%r2,16
	jne	.L22
	l	%r1,4(%r12)
	tml	%r1,0x1
	je	.L52
	l	%r1,16(%r12)
	chi	%r1,1
	jne	.L53
	l	%r1,8(%r12)
	ic	%r4,0(%r4)
	stc	%r4,0(%r1)
	j	.L22
.L53:
	chi	%r1,2
	jne	.L55
	l	%r1,8(%r12)
	lh	%r4,0(%r4)
	sth	%r4,0(%r1)
	j	.L22
.L55:
	chi	%r1,4
	jne	.L57
	l	%r1,8(%r12)
	mvc	0(4,%r1),0(%r4)
	j	.L22
.L57:
	chi	%r1,8
	jne	.L59
	l	%r1,8(%r12)
	mvc	0(4,%r1),0(%r4)
	l	%r2,8(%r12)
	mvc	4(4,%r2),4(%r4)
	j	.L22
.L59:
	lr	%r3,%r1
	ahi	%r3,3
	srl	%r3,2
	ahi	%r3,-1
	ltr	%r3,%r3
	jnhe	.L22
	lr	%r2,%r3
	sll	%r2,2
.L63:
	lr	%r1,%r2
	a	%r1,8(%r12)
	l	%r5,0(%r2,%r4)
	st	%r5,0(%r1)
	ahi	%r2,-4
	ahi	%r3,-1
	ltr	%r3,%r3
	jhe	.L63
	j	.L22
.L52:
	tml	%r1,0x200
	je	.L22
	l	%r1,16(%r12)
	chi	%r1,1
	jne	.L67
.L76:
	l	%r1,8(%r12)
	stc	%r4,0(%r1)
	j	.L22
.L67:
	chi	%r1,2
	jne	.L69
.L77:
	l	%r1,8(%r12)
	sth	%r4,0(%r1)
	j	.L22
.L69:
	chi	%r1,4
	jne	.L71
.L75:
	l	%r1,8(%r12)
	st	%r4,0(%r1)
	j	.L22
.L71:
	chi	%r1,8
	jne	.L22
.L78:
	l	%r1,8(%r12)
	st	%r4,0(%r1)
	l	%r2,8(%r12)
	st	%r3,4(%r2)
.L22:
	lhi	%r2,0
	l	%r4,1184(%r15)
	lm	%r6,%r15,1152(%r15)
	br	%r4
.Lfe1:
	.size	 __builtin_avcall,.Lfe1-__builtin_avcall
	.ident	"GCC: (GNU) 2.95.4  (Debian prerelease)"
