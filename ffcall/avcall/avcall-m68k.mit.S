#include "asmm68k.h"
.text
	.even
.globl C(__builtin_avcall)
	DECLARE_FUNCTION(__builtin_avcall)
C(__builtin_avcall:)
	moveml #0x3030,$sp@-
	movel $sp@(20),$a2
	lea $sp@(-1024),$sp
	moveq #-32,$d0
	addl $a2@(20),$d0
	subl $a2,$d0
	asrl #2,$d0
	jle L4
	movel $sp,$a3
	lea $a2@(32),$a0
	movel $d0,$a1
	.even
L6:
	movel $a0@+,$a3@+
	subql #1,$a1
	tstl $a1
	jne L6
L4:
	moveq #16,$d0
	cmpl $a2@(12),$d0
	jne L8
	movel $a2@(8),$a1
L8:
	movel $a2@,$a0
	jbsr $a0@
	movel $d0,$a1
	movel $d1,$a3
	movel $a2@(12),$d2
	moveq #1,$d1
	cmpl $d2,$d1
	jeq L10
	tstl $d2
	jeq L69
	moveq #2,$d3
	cmpl $d2,$d3
	jeq L70
	moveq #3,$d3
	cmpl $d2,$d3
	jeq L70
	moveq #4,$d3
	cmpl $d2,$d3
	jne L17
L70:
	movel $a2@(8),$a0
	movew $a1,$d0
	moveb $d0,$a0@
	jra L10
	.even
L17:
	moveq #5,$d3
	cmpl $d2,$d3
	jeq L71
	moveq #6,$d3
	cmpl $d2,$d3
	jeq L71
	moveq #7,$d3
	cmpl $d2,$d3
	jeq L69
	moveq #8,$d3
	cmpl $d2,$d3
	jeq L69
	moveq #9,$d3
	cmpl $d2,$d3
	jeq L69
	moveq #10,$d3
	cmpl $d2,$d3
	jeq L69
	movel $a2@(12),$a0
	moveq #-11,$d2
	addl $a0,$d2
	moveq #1,$d3
	cmpl $d2,$d3
	jcc L72
	moveq #13,$d2
	cmpl $a0,$d2
	jne L33
	movel $a2@(4),$d2
	btst #6,$d2
	jeq L34
	movel $a2@(8),$a0
	fmoves $fp0,$a0@
	jra L10
	.even
L34:
	btst #5,$d2
	jeq L36
	movel $a2@(8),$a0
	movel $d1,$sp@-
	movel $d0,$sp@-
	fmoved $sp@+,$fp0
	fmoves $fp0,$a0@
	jra L10
	.even
L36:
	movel $a2@(8),$a0
	movel $d0,$a0@
	jra L10
	.even
L33:
	moveq #14,$d2
	cmpl $a0,$d2
	jne L39
	btst #6,$a2@(7)
	jeq L40
	movel $a2@(8),$a0
	fmoved $fp0,$a0@
	jra L10
	.even
L40:
	movel $a2@(8),$a0
	movel $d0,$a0@
	movel $d1,$a0@(4)
	jra L10
	.even
L39:
	moveq #15,$d3
	cmpl $a0,$d3
	jeq L69
	moveq #16,$d0
	cmpl $a0,$d0
	jne L10
	movel $a2@(4),$d0
	btst #9,$d0
	jeq L46
	movel $a2@(16),$d1
	moveq #1,$d2
	cmpl $d1,$d2
	jne L47
	movel $a2@(8),$a0
	movew $a1,$d3
	moveb $d3,$a0@
	jra L10
	.even
L47:
	moveq #2,$d2
	cmpl $d1,$d2
	jne L50
L71:
	movel $a2@(8),$a0
	movew $a1,$a0@
	jra L10
	.even
L50:
	moveq #4,$d3
	cmpl $d1,$d3
	jne L52
L69:
	movel $a2@(8),$a0
	movel $a1,$a0@
	jra L10
	.even
L52:
	moveq #8,$d2
	cmpl $d1,$d2
	jne L46
L72:
	movel $a2@(8),$a0
	movel $a1,$a0@
	movel $a2@(8),$a0
	movel $a3,$a0@(4)
	jra L10
	.even
L46:
	btst #0,$d0
	jeq L10
	movel $a2@(16),$d0
	moveq #1,$d3
	cmpl $d0,$d3
	jne L56
	movel $a2@(8),$a0
	moveb $a1@,$a0@
	jra L10
	.even
L56:
	moveq #2,$d1
	cmpl $d0,$d1
	jne L58
	movel $a2@(8),$a0
	movew $a1@,$a0@
	jra L10
	.even
L58:
	moveq #4,$d2
	cmpl $d0,$d2
	jne L60
	movel $a2@(8),$a0
	movel $a1@,$a0@
	jra L10
	.even
L60:
	moveq #8,$d3
	cmpl $d0,$d3
	jne L62
	movel $a2@(8),$a0
	movel $a1@,$a0@
	movel $a2@(8),$a0
	movel $a1@(4),$a0@(4)
	jra L10
	.even
L62:
	addql #3,$d0
	lsrl #2,$d0
	subql #1,$d0
	jmi L10
	lea $a1@($d0:l:4),$a1
	.even
L66:
	movel $a2@(8),$a0
	movel $a1@,$a0@($d0:l:4)
	subql #4,$a1
	dbra $d0,L66
	clrw $d0
	subql #1,$d0
	jcc L66
L10:
	lea $sp@(1024),$sp
	clrl $d0
	moveml $sp@+,#0xc0c
	rts
