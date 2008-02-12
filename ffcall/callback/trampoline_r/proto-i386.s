	.file	"proto.c"
gcc2_compiled.:
___gnu_compiled_c:
.text
	.align 2
.globl _tramp
_tramp:
	movl $1934968593,%ecx
	call -1161904448
	ret
	.align 2
.globl _tramp2
_tramp2:
	pushl $1934968593
	call -1161904448
	addl $4,%esp
	ret
	.align 2
.globl _jump
_jump:
	movl $-1161904448,%eax
	jmp *%eax
	.align 2,0x90
