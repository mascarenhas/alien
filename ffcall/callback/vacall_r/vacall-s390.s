	.file	"vacall-s390.c"
	.version	"01.01"
gcc2_compiled.:
.text
	.align 4
.globl __vacall_r
	.type	 __vacall_r,@function
__vacall_r:
#	leaf function           0
#	automatics              120
#	outgoing args           0
#	need frame pointer      1
#	call alloca             0
#	has varargs             0
#	incoming args (stack)   8
#	function length         646
#	register live           1111111000010110110000000000000011
	stm	%r6,%r15,24(%r15)
	bras	%r13,.LTN0_0
.LT0_0:
.LC0:
	.long	0
.LTN0_0:
	lr	%r1,%r15
	ahi	%r15,-216
	st	%r1,0(%r15)
	lr	%r11,%r15
	st	%r2,96(%r11)
	st	%r3,100(%r11)
	st	%r4,104(%r11)
	st	%r5,108(%r11)
	st	%r6,112(%r11)
	mvc	184(4,%r11),96(%r11)
	mvc	188(4,%r11),100(%r11)
	mvc	192(4,%r11),104(%r11)
	mvc	196(4,%r11),108(%r11)
	mvc	200(4,%r11),112(%r11)
	std	%f2,176(%r11)
	std	%f0,168(%r11)
	ste	%f2,164(%r11)
	ste	%f0,160(%r11)
	lhi	%r1,0
	st	%r1,120(%r11)
	lr	%r1,%r11
	ahi	%r1,120
	lr	%r4,%r1
	ahi	%r4,64
	st	%r4,124(%r11)
	la	%r1,312(%r11)
	st	%r1,204(%r11)
	lhi	%r1,0
	st	%r1,208(%r11)
	lhi	%r1,0
	st	%r1,128(%r11)
	lhi	%r1,0
	st	%r1,132(%r11)
	lr	%r1,%r11
	ahi	%r1,120
	lr	%r4,%r1
	ahi	%r4,40
	st	%r4,152(%r11)
	lr	%r1,%r11
	ahi	%r1,120
	lr	%r4,%r1
	ahi	%r4,48
	st	%r4,156(%r11)
	lr	%r1,%r0
	lr	%r4,%r0
	lr	%r5,%r11
	ahi	%r5,120
	l	%r1,0(%r1)
	l	%r2,4(%r4)
	lr	%r3,%r5
	basr	%r14,%r1
	l	%r1,132(%r11)
	ltr	%r1,%r1
	jne	.L3
	j	.L4
.L3:
	l	%r1,132(%r11)
	chi	%r1,1
	jne	.L5
	sr	%r2,%r2
	ic	%r2,144(%r11)
	j	.L4
.L5:
	l	%r1,132(%r11)
	chi	%r1,2
	jne	.L7
	icm	%r2,8,144(%r11)
	sra	%r2,24
	j	.L4
.L7:
	l	%r1,132(%r11)
	chi	%r1,3
	jne	.L9
	sr	%r2,%r2
	ic	%r2,144(%r11)
	j	.L4
.L9:
	l	%r1,132(%r11)
	chi	%r1,4
	jne	.L11
	lh	%r2,144(%r11)
	j	.L4
.L11:
	l	%r1,132(%r11)
	chi	%r1,5
	jne	.L13
	icm	%r2,12,144(%r11)
	srl	%r2,16
	j	.L4
.L13:
	l	%r1,132(%r11)
	chi	%r1,6
	jne	.L15
	l	%r2,144(%r11)
	j	.L4
.L15:
	l	%r1,132(%r11)
	chi	%r1,7
	jne	.L17
	l	%r2,144(%r11)
	j	.L4
.L17:
	l	%r1,132(%r11)
	chi	%r1,8
	jne	.L19
	l	%r2,144(%r11)
	j	.L4
.L19:
	l	%r1,132(%r11)
	chi	%r1,9
	jne	.L21
	l	%r2,144(%r11)
	j	.L4
.L21:
	l	%r1,132(%r11)
	chi	%r1,10
	je	.L24
	l	%r1,132(%r11)
	chi	%r1,11
	je	.L24
	j	.L23
.L24:
	l	%r2,144(%r11)
	l	%r3,148(%r11)
	j	.L4
.L23:
	l	%r1,132(%r11)
	chi	%r1,12
	jne	.L26
	le	%f0,144(%r11)
	j	.L4
.L26:
	l	%r1,132(%r11)
	chi	%r1,13
	jne	.L28
	ld	%f0,144(%r11)
	j	.L4
.L28:
	l	%r1,132(%r11)
	chi	%r1,14
	jne	.L30
	l	%r2,144(%r11)
	j	.L4
.L30:
	l	%r1,132(%r11)
	chi	%r1,15
	jne	.L4
	lhi	%r4,1
	l	%r1,120(%r11)
	nr	%r1,%r4
	ltr	%r1,%r1
	je	.L33
	l	%r2,128(%r11)
	j	.L4
.L33:
	lhi	%r4,1024
	l	%r1,120(%r11)
	nr	%r1,%r4
	ltr	%r1,%r1
	je	.L4
	l	%r1,136(%r11)
	chi	%r1,1
	jne	.L36
	l	%r1,128(%r11)
	sr	%r2,%r2
	ic	%r2,0(%r1)
	j	.L4
.L36:
	l	%r1,136(%r11)
	chi	%r1,2
	jne	.L38
	l	%r1,128(%r11)
	icm	%r2,12,0(%r1)
	srl	%r2,16
	j	.L4
.L38:
	l	%r1,136(%r11)
	chi	%r1,4
	jne	.L40
	l	%r1,128(%r11)
	l	%r2,0(%r1)
	j	.L4
.L40:
	l	%r1,136(%r11)
	chi	%r1,8
	jne	.L4
	l	%r1,128(%r11)
	l	%r2,0(%r1)
	l	%r4,128(%r11)
	lr	%r1,%r4
	ahi	%r1,4
	l	%r3,0(%r1)
.L42:
.L41:
.L39:
.L37:
.L35:
.L34:
.L32:
.L31:
.L29:
.L27:
.L25:
.L22:
.L20:
.L18:
.L16:
.L14:
.L12:
.L10:
.L8:
.L6:
.L4:
.L2:
	l	%r4,272(%r11)
	lm	%r6,%r15,240(%r11)
	br	%r4
.Lfe1:
	.size	 __vacall_r,.Lfe1-__vacall_r
	.ident	"GCC: (GNU) 2.95.4 20011006 (Debian prerelease)"
