	.file	"vacall-m68k.c"
	.version	"01.01"
gcc2_compiled.:
.text
	.align 	2
.globl __vacall
	.type	 __vacall,@function
__vacall:
	link.w %a6,#-32
	movm.l #0x3020,-(%sp)
	clr.l -32(%a6)
	lea (8,%a6),%a2
	move.l %a2,-28(%a6)
	clr.l -24(%a6)
	clr.l -20(%a6)
	move.l %a1,-4(%a6)
	pea -32(%a6)
	move.l vacall_function,%a2
	jbsr (%a2)
	addq.l #4,%sp
	move.l -20(%a6),%d2
	jbeq .L4
	moveq.l #1,%d3
	cmp.l %d2,%d3
	jbeq .L49
	moveq.l #2,%d3
	cmp.l %d2,%d3
	jbne .L7
.L49:
	move.b -12(%a6),%d0
	extb.l %d0
	jbra .L4
	.align 	2
.L7:
	moveq.l #3,%d3
	cmp.l %d2,%d3
	jbne .L9
	clr.l %d0
	move.b -12(%a6),%d0
	jbra .L4
	.align 	2
.L9:
	moveq.l #4,%d3
	cmp.l %d2,%d3
	jbne .L11
	move.w -12(%a6),%d0
	ext.l %d0
	jbra .L4
	.align 	2
.L11:
	moveq.l #5,%d3
	cmp.l %d2,%d3
	jbne .L13
	clr.l %d0
	move.w -12(%a6),%d0
	jbra .L4
	.align 	2
.L13:
	moveq.l #6,%d3
	cmp.l %d2,%d3
	jbeq .L50
	moveq.l #7,%d3
	cmp.l %d2,%d3
	jbeq .L50
	moveq.l #8,%d3
	cmp.l %d2,%d3
	jbeq .L50
	moveq.l #9,%d3
	cmp.l %d2,%d3
	jbne .L21
.L50:
	move.l -12(%a6),%d0
	jbra .L4
	.align 	2
.L21:
	moveq.l #-10,%d3
	add.l %d3,%d2
	moveq.l #1,%d3
	cmp.l %d2,%d3
	jbcs .L23
	move.l -12(%a6),%d0
	move.l -8(%a6),%d1
	jbra .L4
	.align 	2
.L23:
	move.l -20(%a6),%d2
	moveq.l #12,%d3
	cmp.l %d2,%d3
	jbne .L25
	move.l -32(%a6),%d2
	btst #6,%d2
	jbeq .L26
	fmove.s -12(%a6),%fp0
	jbra .L4
	.align 	2
.L26:
	btst #5,%d2
	jbeq .L28
	fmove.s -12(%a6),%fp1
	fmove.d %fp1,-(%sp)
	move.l (%sp)+,%d0
	move.l (%sp)+,%d1
	jbra .L4
	.align 	2
.L28:
	move.l -12(%a6),%d0
	jbra .L4
	.align 	2
.L25:
	moveq.l #13,%d3
	cmp.l %d2,%d3
	jbne .L31
	btst #6,-29(%a6)
	jbeq .L32
	fmove.d -12(%a6),%fp0
	jbra .L4
	.align 	2
.L32:
	move.l -12(%a6),%d0
	move.l -8(%a6),%d1
	jbra .L4
	.align 	2
.L31:
	moveq.l #14,%d3
	cmp.l %d2,%d3
	jbne .L35
	move.l -12(%a6),%d0
	jbra .L51
	.align 	2
.L35:
	moveq.l #15,%d3
	cmp.l %d2,%d3
	jbne .L4
	move.l -32(%a6),%d2
	btst #10,%d2
	jbeq .L38
	move.l -16(%a6),%a2
	moveq.l #1,%d3
	cmp.l %a2,%d3
	jbne .L39
	move.l -24(%a6),%a2
	clr.l %d0
	move.b (%a2),%d0
	jbra .L4
	.align 	2
.L39:
	moveq.l #2,%d3
	cmp.l %a2,%d3
	jbne .L42
	move.l -24(%a6),%a2
	clr.l %d0
	move.w (%a2),%d0
	jbra .L4
	.align 	2
.L42:
	moveq.l #4,%d3
	cmp.l %a2,%d3
	jbne .L44
	move.l -24(%a6),%a2
	move.l (%a2),%d0
	jbra .L4
	.align 	2
.L44:
	moveq.l #8,%d3
	cmp.l %a2,%d3
	jbne .L38
	move.l -24(%a6),%a2
	move.l (%a2),%d0
	move.l 4(%a2),%d1
	jbra .L4
	.align 	2
.L38:
	btst #0,%d2
	jbeq .L4
	move.l -24(%a6),%d0
.L51:
	move.l %d0,%a0
.L4:
	movm.l -44(%a6),#0x40c
	unlk %a6
	rts
.Lfe1:
	.size	 __vacall,.Lfe1-__vacall
	.ident	"GCC: (GNU) 2.95.2 19991024 (release)"
