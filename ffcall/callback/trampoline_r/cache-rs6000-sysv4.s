	.file	"cache-rs6000.c"
gcc2_compiled.:
	.section	".text"
	.align 2
	.globl __TR_clear_cache
	.type	 __TR_clear_cache,@function
__TR_clear_cache:
	.extern __mulh
	.extern __mull
	.extern __divss
	.extern __divus
	.extern __quoss
	.extern __quous
	icbi 0,3; dcbf 0,3
	addi 0,3,4
	icbi 0,0; dcbf 0,0
	addi 9,3,8
	icbi 0,9; dcbf 0,9
	addi 0,3,12
	icbi 0,0; dcbf 0,0
	addi 9,3,16
	icbi 0,9; dcbf 0,9
	addi 0,3,20
	icbi 0,0; dcbf 0,0
	addi 9,3,24
	icbi 0,9; dcbf 0,9
	addi 0,3,28
	icbi 0,0; dcbf 0,0
	addi 3,3,32
	icbi 0,3; dcbf 0,3
	sync; isync
	blr
.Lfe1:
	.size	 __TR_clear_cache,.Lfe1-__TR_clear_cache
	.ident	"GCC: (GNU) 2.95.2 19991024 (release)"
