;NO_APP
.fpmode native
gcc2_compiled.:
___gnu_compiled_c:
.text
.text
.align 2
.globl _tramp
	ds.b "g263"
	ds.b "+00\0"
_tramp:
	ld.w #1934968593,s0
	mov sp,ap
	calls -1161904448
	ld.w 12(fp),ap
	rtn
	ds.h 0
.text
.align 2
.globl _jump
	ds.b "g263"
	ds.b "+00\0"
_jump:
	jmp -1161904448
	ds.h 0
