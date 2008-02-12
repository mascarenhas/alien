	.file	"proto.c"
	.version	"01.01"
gcc2_compiled.:
.text
	.align 4
.globl tramp
	.type	 tramp,@function
tramp:
#	leaf function           0
#	automatics              0
#	outgoing args           0
#	need frame pointer      0
#	call alloca             0
#	has varargs             0
#	incoming args (stack)   0
#	function length         16
#	register live           0110000000000010000000000000000000
	stm	%r13,%r15,52(%r15)
	bras	%r13,.LTN0_0
.LT0_0:
.LC0:
	.long	305419896
.LC1:
	.long	1934968593
.LC2:
	.long	-1161904448
.LTN0_0:
	lr	%r1,%r15
	ahi	%r15,-96
	st	%r1,0(%r15)
	l	%r1,.LC0-.LT0_0(%r13)
	l	%r2,.LC2-.LT0_0(%r13)
	mvc	0(4,%r1),.LC1-.LT0_0(%r13)
	basr	%r14,%r2
	l	%r4,152(%r15)
	lm	%r13,%r15,148(%r15)
	br	%r4
.Lfe1:
	.size	 tramp,.Lfe1-tramp
	.align 4
.globl jump
	.type	 jump,@function
jump:
#	leaf function
#	has varargs             0
#	incoming args (stack)   0
#	function length         6
#	register live           0100000000000000000000000000000000
	stm	%r13,%r13,52(%r15)
	bras	%r13,.LTN1_0
.LT1_0:
.LC3:
	.long	-1161904448
.LTN1_0:
	l	%r1,.LC3-.LT1_0(%r13)
	br	%r1
	lm	%r13,%r13,52(%r15)
	br	%r14
.Lfe2:
	.size	 jump,.Lfe2-jump
	.ident	"GCC: (GNU) 2.95.4 20011006 (Debian prerelease)"
