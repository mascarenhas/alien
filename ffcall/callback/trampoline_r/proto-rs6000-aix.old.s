	.file	"proto.c"
.toc
.csect .text[PR]
gcc2_compiled.:
__gnu_compiled_c:
	.align 2
	.globl tramp
	.globl .tramp
.csect tramp[DS]
tramp:
	.long .tramp, TOC[tc0], 0
.csect .text[PR]
.tramp:
	.extern __mulh
	.extern __mull
	.extern __divss
	.extern __divus
	.extern __quoss
	.extern __quous
	mflr 0
	st 0,8(1)
	stu 1,-56(1)
	liu 11,0x7355
	liu 9,0xbabe
	oril 11,11,18193
	oril 9,9,48832
	st 2,20(1)
	l 0,0(9)
	l 2,4(9)
	mtlr 0
	l 11,8(9)
	brl
	l 2,20(1)
	cal 1,56(1)
	l 0,8(1)
	mtlr 0
	br
LT..tramp:
	.long 0
	.byte 0,0,32,65,128,0,0,0
	.long LT..tramp-.tramp
	.short 5
	.byte "tramp"
	.align 2
	.globl jump
	.globl .jump
.csect jump[DS]
jump:
	.long .jump, TOC[tc0], 0
.csect .text[PR]
.jump:
	liu 0,0xbabe
	oril 0,0,48832
	mtctr 0
	bctr
LT..jump:
	.long 0
	.byte 0,0,32,64,0,0,0,0
	.long LT..jump-.jump
	.short 4
	.byte "jump"
_section_.text:
.csect .data[RW],3
	.long _section_.text
