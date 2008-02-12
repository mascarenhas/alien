.text
	.align 2
	.globl _tramp
_tramp:
	mflr r0
	lis r11,0x7355
	stw r0,8(r1)
	ori r11,r11,18193
	lis r0,0xbabe
	stw r31,-4(r1)
	ori r0,r0,48832
	stwu r1,-80(r1)
	mtlr r0
	blrl
	addi r1,r1,80
	lwz r0,8(r1)
	lwz r31,-4(r1)
	mtlr r0
	blr
	.align 2
	.globl _jump
_jump:
	lis r0,0xbabe
	ori r0,r0,48832
	mtctr r0
	bctr
