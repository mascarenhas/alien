#NO_APP
gcc2_compiled.:
___gnu_compiled_c:
.text
	.even
.globl ___builtin_avcall
___builtin_avcall:
	moveml #0x3020,sp@-
	movel sp@(16),a2
	lea sp@(-1076),sp
	moveq #-32,d0
	addl a2@(20),d0
	subl a2,d0
	asrl #2,d0
	jle L4
	movel sp,a1
	lea a2@(32),a0
	.even
L6:
	movel a0@+,a1@+
	subql #1,d0
	jne L6
L4:
	moveq #16,d0
	cmpl a2@(12),d0
	jne L8
	movel a2@(8),a2@(1092)
L8:
#APP
	moveml #32764,sp@(1024)
	movel #L9,sp@-
	movel a2@,sp@-
	moveml a2@(1056),#x7fff
	rts
#NO_APP
L9:
#APP
	moveml sp@(1024),#32764
#NO_APP
	lea sp@(1076),sp
	movel a2@(12),a0
	moveq #1,d2
	cmpl a0,d2
	jeq L11
	cmpw #0,a0
	jeq L66
	moveq #2,d3
	cmpl a0,d3
	jeq L67
	moveq #3,d2
	cmpl a0,d2
	jeq L67
	moveq #4,d3
	cmpl a0,d3
	jeq L67
	moveq #5,d2
	cmpl a0,d2
	jeq L68
	moveq #6,d3
	cmpl a0,d3
	jeq L68
	moveq #7,d2
	cmpl a0,d2
	jeq L66
	moveq #8,d3
	cmpl a0,d3
	jeq L66
	moveq #9,d2
	cmpl a0,d2
	jeq L66
	moveq #10,d3
	cmpl a0,d3
	jeq L66
	moveq #-11,d2
	addl a0,d2
	moveq #1,d3
	cmpl d2,d3
	jcc L69
	moveq #13,d2
	cmpl a0,d2
	jne L34
	btst #5,a2@(7)
	jeq L35
	movel a2@(8),a2
	movel d1,sp@-
	movel d0,sp@-
	jbsr ___truncdfsf2
	addql #8,sp
	movel d0,a2@
	jra L11
	.even
L35:
	movel a2@(8),a0
	movel d0,a0@
	jra L11
	.even
L34:
	moveq #14,d3
	cmpl a0,d3
	jne L38
	movel a2@(8),a0
	movel d0,a0@
	movel d1,a0@(4)
	jra L11
	.even
L38:
	moveq #15,d2
	cmpl a0,d2
	jeq L66
	moveq #16,d3
	cmpl a0,d3
	jne L11
	movel a2@(4),d2
	btst #9,d2
	jeq L43
	movel a2@(16),a0
	moveq #1,d3
	cmpl a0,d3
	jne L44
L67:
	movel a2@(8),a0
	moveb d0,a0@
	jra L11
	.even
L44:
	moveq #2,d3
	cmpl a0,d3
	jne L47
L68:
	movel a2@(8),a0
	movew d0,a0@
	jra L11
	.even
L47:
	moveq #4,d3
	cmpl a0,d3
	jne L49
L66:
	movel a2@(8),a0
	movel d0,a0@
	jra L11
	.even
L49:
	moveq #8,d3
	cmpl a0,d3
	jne L43
L69:
	movel a2@(8),a0
	movel d0,a0@
	movel a2@(8),a0
	movel d1,a0@(4)
	jra L11
	.even
L43:
	btst #0,d2
	jeq L11
	movel a2@(16),d1
	moveq #1,d2
	cmpl d1,d2
	jne L53
	movel a2@(8),a1
	movel d0,a0
	moveb a0@,a1@
	jra L11
	.even
L53:
	moveq #2,d3
	cmpl d1,d3
	jne L55
	movel a2@(8),a1
	movel d0,a0
	movew a0@,a1@
	jra L11
	.even
L55:
	moveq #4,d2
	cmpl d1,d2
	jne L57
	movel a2@(8),a1
	movel d0,a0
	movel a0@,a1@
	jra L11
	.even
L57:
	moveq #8,d3
	cmpl d1,d3
	jne L59
	movel a2@(8),a0
	movel d0,a1
	movel a1@,a0@
	movel a2@(8),a0
	moveq #4,d0
	movel a1@(d0:l),a0@(4)
	jra L11
	.even
L59:
	addql #3,d1
	lsrl #2,d1
	subql #1,d1
	jmi L11
	movel d1,a1
	movel a1,d2
	lsll #2,d2
	movel d2,a1
	.even
L63:
	movel a2@(8),a0
	movel a1@(d0:l),a0@(a1:l)
	subql #4,a1
	dbra d1,L63
	clrw d1
	subql #1,d1
	jcc L63
L11:
	moveq #0,d0
	moveml sp@+,#0x40c
	rts
