.text
	.align 2
	.globl ___TR_clear_cache
___TR_clear_cache:
	icbi 0,r3; dcbf 0,r3
	addi r0,r3,4
	icbi 0,r0; dcbf 0,r0
	addi r9,r3,8
	icbi 0,r9; dcbf 0,r9
	addi r0,r3,12
	icbi 0,r0; dcbf 0,r0
	addi r9,r3,16
	icbi 0,r9; dcbf 0,r9
	addi r0,r3,20
	icbi 0,r0; dcbf 0,r0
	addi r9,r3,24
	icbi 0,r9; dcbf 0,r9
	addi r0,r3,28
	icbi 0,r0; dcbf 0,r0
	addi r3,r3,32
	icbi 0,r3; dcbf 0,r3
	sync; isync
	blr
