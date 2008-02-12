	.file	"avcall-m68k.c"
	.version	"01.01"
gcc2_compiled.:
.text
	.align 	2
.globl __builtin_avcall
	.type	 __builtin_avcall,@function
__builtin_avcall:
	movm.l #0x3030,-(%sp)
	move.l 20(%sp),%a2
	lea (-1024,%sp),%sp
	moveq.l #-32,%d0
	add.l 20(%a2),%d0
	sub.l %a2,%d0
	asr.l #2,%d0
	jble .L4
	move.l %sp,%a3
	lea (32,%a2),%a0
	move.l %d0,%a1
	.align 	2
.L6:
	move.l (%a0)+,(%a3)+
	subq.l #1,%a1
	tst.l %a1
	jbne .L6
.L4:
	moveq.l #16,%d0
	cmp.l 12(%a2),%d0
	jbne .L8
#APP
	move.l 8(%a2),%a1
#NO_APP
.L8:
	move.l (%a2),%a0
	jbsr (%a0)
	move.l %d0,%a1
	move.l %d1,%a3
	move.l 12(%a2),%d2
	moveq.l #1,%d1
	cmp.l %d2,%d1
	jbeq .L10
	tst.l %d2
	jbeq .L69
	moveq.l #2,%d3
	cmp.l %d2,%d3
	jbeq .L70
	moveq.l #3,%d3
	cmp.l %d2,%d3
	jbeq .L70
	moveq.l #4,%d3
	cmp.l %d2,%d3
	jbne .L17
.L70:
	move.l 8(%a2),%a0
	move.w %a1,%d0
	move.b %d0,(%a0)
	jbra .L10
	.align 	2
.L17:
	moveq.l #5,%d3
	cmp.l %d2,%d3
	jbeq .L71
	moveq.l #6,%d3
	cmp.l %d2,%d3
	jbeq .L71
	moveq.l #7,%d3
	cmp.l %d2,%d3
	jbeq .L69
	moveq.l #8,%d3
	cmp.l %d2,%d3
	jbeq .L69
	moveq.l #9,%d3
	cmp.l %d2,%d3
	jbeq .L69
	moveq.l #10,%d3
	cmp.l %d2,%d3
	jbeq .L69
	move.l 12(%a2),%a0
	moveq.l #-11,%d2
	add.l %a0,%d2
	moveq.l #1,%d3
	cmp.l %d2,%d3
	jbcc .L72
	moveq.l #13,%d2
	cmp.l %a0,%d2
	jbne .L33
	move.l 4(%a2),%d2
	btst #6,%d2
	jbeq .L34
	move.l 8(%a2),%a0
	fmove.s %fp0,(%a0)
	jbra .L10
	.align 	2
.L34:
	btst #5,%d2
	jbeq .L36
	move.l 8(%a2),%a0
	move.l %d1,-(%sp)
	move.l %d0,-(%sp)
	fmove.d (%sp)+,%fp0
	fmove.s %fp0,(%a0)
	jbra .L10
	.align 	2
.L36:
	move.l 8(%a2),%a0
	move.l %d0,(%a0)
	jbra .L10
	.align 	2
.L33:
	moveq.l #14,%d2
	cmp.l %a0,%d2
	jbne .L39
	btst #6,7(%a2)
	jbeq .L40
	move.l 8(%a2),%a0
	fmove.d %fp0,(%a0)
	jbra .L10
	.align 	2
.L40:
	move.l 8(%a2),%a0
	move.l %d0,(%a0)
	move.l %d1,4(%a0)
	jbra .L10
	.align 	2
.L39:
	moveq.l #15,%d3
	cmp.l %a0,%d3
	jbeq .L69
	moveq.l #16,%d0
	cmp.l %a0,%d0
	jbne .L10
	move.l 4(%a2),%d0
	btst #9,%d0
	jbeq .L46
	move.l 16(%a2),%d1
	moveq.l #1,%d2
	cmp.l %d1,%d2
	jbne .L47
	move.l 8(%a2),%a0
	move.w %a1,%d3
	move.b %d3,(%a0)
	jbra .L10
	.align 	2
.L47:
	moveq.l #2,%d2
	cmp.l %d1,%d2
	jbne .L50
.L71:
	move.l 8(%a2),%a0
	move.w %a1,(%a0)
	jbra .L10
	.align 	2
.L50:
	moveq.l #4,%d3
	cmp.l %d1,%d3
	jbne .L52
.L69:
	move.l 8(%a2),%a0
	move.l %a1,(%a0)
	jbra .L10
	.align 	2
.L52:
	moveq.l #8,%d2
	cmp.l %d1,%d2
	jbne .L46
.L72:
	move.l 8(%a2),%a0
	move.l %a1,(%a0)
	move.l 8(%a2),%a0
	move.l %a3,4(%a0)
	jbra .L10
	.align 	2
.L46:
	btst #0,%d0
	jbeq .L10
	move.l 16(%a2),%d0
	moveq.l #1,%d3
	cmp.l %d0,%d3
	jbne .L56
	move.l 8(%a2),%a0
	move.b (%a1),(%a0)
	jbra .L10
	.align 	2
.L56:
	moveq.l #2,%d1
	cmp.l %d0,%d1
	jbne .L58
	move.l 8(%a2),%a0
	move.w (%a1),(%a0)
	jbra .L10
	.align 	2
.L58:
	moveq.l #4,%d2
	cmp.l %d0,%d2
	jbne .L60
	move.l 8(%a2),%a0
	move.l (%a1),(%a0)
	jbra .L10
	.align 	2
.L60:
	moveq.l #8,%d3
	cmp.l %d0,%d3
	jbne .L62
	move.l 8(%a2),%a0
	move.l (%a1),(%a0)
	move.l 8(%a2),%a0
	move.l 4(%a1),4(%a0)
	jbra .L10
	.align 	2
.L62:
	addq.l #3,%d0
	lsr.l #2,%d0
	subq.l #1,%d0
	jbmi .L10
	lea (%a1,%d0.l*4),%a1
	.align 	2
.L66:
	move.l 8(%a2),%a0
	move.l (%a1),(%a0,%d0.l*4)
	subq.l #4,%a1
	dbra %d0,.L66
	clr.w %d0
	subq.l #1,%d0
	jbcc .L66
.L10:
	lea (1024,%sp),%sp
	clr.l %d0
	movm.l (%sp)+,#0xc0c
	rts
.Lfe1:
	.size	 __builtin_avcall,.Lfe1-__builtin_avcall
	.ident	"GCC: (GNU) 2.95.2 19991024 (release)"
