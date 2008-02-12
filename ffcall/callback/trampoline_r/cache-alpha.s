	.set noreorder
	.set volatile
	.set noat
	.file	1 "cache-alpha.c"
gcc2_compiled.:
__gnu_compiled_c:
.text
	.align 3
	.globl __TR_clear_cache
	.ent __TR_clear_cache
__TR_clear_cache:
__TR_clear_cache..ng:
	.frame $30,0,$26,0
	.prologue 0
	call_pal 0x86
	ret $31,($26),1
	.end __TR_clear_cache
