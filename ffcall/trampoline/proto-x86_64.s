	.file	"proto64.c"
	.text
	.p2align 4,,15
.globl tramp
	.type	tramp,@function
tramp:
.LFB1:
	movabsq	$8310626826852639061, %rax
	subq	$8, %rsp
.LCFI0:
	movabsq	$-4990341601501839445, %rdx
	movabsq	%rax, 1311768465192224613
	xorl	%eax, %eax
	call	*%rdx
	addq	$8, %rsp
	ret
.LFE1:
.Lfe1:
	.size	tramp,.Lfe1-tramp
	.p2align 4,,15
.globl jump
	.type	jump,@function
jump:
.LFB2:
	movabsq	$-4990341601501839445, %rax
	jmp	*%rax
.LFE2:
.Lfe2:
	.size	jump,.Lfe2-jump
	.section	.eh_frame,"aw",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0x0
	.byte	0x1
	.string	""
	.uleb128 0x1
	.sleb128 -8
	.byte	0x10
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x90
	.uleb128 0x1
	.align 8
.LECIE1:
.LSFDE1:
	.long	.LEFDE1-.LASFDE1
.LASFDE1:
	.long	.LASFDE1-.Lframe1
	.quad	.LFB1
	.quad	.LFE1-.LFB1
	.byte	0x4
	.long	.LCFI0-.LFB1
	.byte	0xe
	.uleb128 0x10
	.align 8
.LEFDE1:
.LSFDE3:
	.long	.LEFDE3-.LASFDE3
.LASFDE3:
	.long	.LASFDE3-.Lframe1
	.quad	.LFB2
	.quad	.LFE2-.LFB2
	.align 8
.LEFDE3:
	.ident	"GCC: (GNU) 3.2.2 (SuSE Linux)"
