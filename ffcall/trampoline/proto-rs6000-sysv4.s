	.file	"proto.c"
gcc2_compiled.:
	.section	".text"
	.align 2
	.globl tramp
	.type	 tramp,@function
tramp:
	.extern __mulh
	.extern __mull
	.extern __divss
	.extern __divus
	.extern __quoss
	.extern __quous
	stwu 1,-16(1)
	mflr 0
	stw 0,20(1)
	lis 3,0xbabe
	ori 3,3,48832
	mtlr 3
	lis 9,0x1234
	lis 0,0x7355
	ori 9,9,22136
	ori 0,0,18193
	stw 0,0(9)
	blrl
	lwz 0,20(1)
	mtlr 0
	la 1,16(1)
	blr
.Lfe1:
	.size	 tramp,.Lfe1-tramp
	.align 2
	.globl jump
	.type	 jump,@function
jump:
	lis 0,0xbabe
	ori 0,0,48832
	mtctr 0
	bctr
.Lfe2:
	.size	 jump,.Lfe2-jump
	.ident	"GCC: (GNU) 2.95.2 19991024 (release)"
