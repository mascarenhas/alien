#include "asmm68k.h"
.text
	.even
.globl C(__vacall_r)
	DECLARE_FUNCTION(__vacall_r)
C(__vacall_r:)
	link $a6,#-32
	moveml #0x3020,$sp@-
	clrl $a6@(-32)
	lea $a6@(8),$a2
	movel $a2,$a6@(-28)
	clrl $a6@(-24)
	clrl $a6@(-20)
	movel $a1,$a6@(-4)
	pea $a6@(-32)
	movel $a0@(4),$sp@-
	movel $a0@,$a2
	jbsr $a2@
	addql #8,$sp
	movel $a6@(-20),$d2
	jeq L4
	moveq #1,$d3
	cmpl $d2,$d3
	jeq L49
	moveq #2,$d3
	cmpl $d2,$d3
	jne L7
L49:
	moveb $a6@(-12),$d0
	extbl $d0
	jra L4
	.even
L7:
	moveq #3,$d3
	cmpl $d2,$d3
	jne L9
	clrl $d0
	moveb $a6@(-12),$d0
	jra L4
	.even
L9:
	moveq #4,$d3
	cmpl $d2,$d3
	jne L11
	movew $a6@(-12),$d0
	extl $d0
	jra L4
	.even
L11:
	moveq #5,$d3
	cmpl $d2,$d3
	jne L13
	clrl $d0
	movew $a6@(-12),$d0
	jra L4
	.even
L13:
	moveq #6,$d3
	cmpl $d2,$d3
	jeq L50
	moveq #7,$d3
	cmpl $d2,$d3
	jeq L50
	moveq #8,$d3
	cmpl $d2,$d3
	jeq L50
	moveq #9,$d3
	cmpl $d2,$d3
	jne L21
L50:
	movel $a6@(-12),$d0
	jra L4
	.even
L21:
	moveq #-10,$d3
	addl $d3,$d2
	moveq #1,$d3
	cmpl $d2,$d3
	jcs L23
	movel $a6@(-12),$d0
	movel $a6@(-8),$d1
	jra L4
	.even
L23:
	movel $a6@(-20),$d2
	moveq #12,$d3
	cmpl $d2,$d3
	jne L25
	movel $a6@(-32),$d2
	btst #6,$d2
	jeq L26
	fmoves $a6@(-12),$fp0
	jra L4
	.even
L26:
	btst #5,$d2
	jeq L28
	fmoves $a6@(-12),$fp1
	fmoved $fp1,$sp@-
	movel $sp@+,$d0
	movel $sp@+,$d1
	jra L4
	.even
L28:
	movel $a6@(-12),$d0
	jra L4
	.even
L25:
	moveq #13,$d3
	cmpl $d2,$d3
	jne L31
	btst #6,$a6@(-29)
	jeq L32
	fmoved $a6@(-12),$fp0
	jra L4
	.even
L32:
	movel $a6@(-12),$d0
	movel $a6@(-8),$d1
	jra L4
	.even
L31:
	moveq #14,$d3
	cmpl $d2,$d3
	jne L35
	movel $a6@(-12),$d0
	jra L51
	.even
L35:
	moveq #15,$d3
	cmpl $d2,$d3
	jne L4
	movel $a6@(-32),$d2
	btst #10,$d2
	jeq L38
	movel $a6@(-16),$a2
	moveq #1,$d3
	cmpl $a2,$d3
	jne L39
	movel $a6@(-24),$a2
	clrl $d0
	moveb $a2@,$d0
	jra L4
	.even
L39:
	moveq #2,$d3
	cmpl $a2,$d3
	jne L42
	movel $a6@(-24),$a2
	clrl $d0
	movew $a2@,$d0
	jra L4
	.even
L42:
	moveq #4,$d3
	cmpl $a2,$d3
	jne L44
	movel $a6@(-24),$a2
	movel $a2@,$d0
	jra L4
	.even
L44:
	moveq #8,$d3
	cmpl $a2,$d3
	jne L38
	movel $a6@(-24),$a2
	movel $a2@,$d0
	movel $a2@(4),$d1
	jra L4
	.even
L38:
	btst #0,$d2
	jeq L4
	movel $a6@(-24),$d0
L51:
	movel $d0,$a0
L4:
	moveml $a6@(-44),#0x40c
	unlk $a6
	rts
