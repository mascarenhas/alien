	.file	"avcall-x86_64.c"
	.text
	.p2align 4,,15
.globl __builtin_avcall
	.type	__builtin_avcall,@function
__builtin_avcall:
.LFB1:
	pushq	%r12
.LCFI0:
	xorl	%r11d, %r11d
	pushq	%rbp
.LCFI1:
	pushq	%rbx
.LCFI2:
	movq	104(%rdi), %rax
	movq	40(%rdi), %r10
	subq	$2048, %rsp
	movq	%rdi, %rbx
	movq	%rsp, %rbp
	subq	%rdi, %r10
	subq	%rdi, %rax
	subq	$176, %r10
	subq	$112, %rax
	shrq	$3, %r10
	movq	%rax, %r12
	movslq	%r10d,%r10
	shrq	$3, %r12
	cmpq	%r10, %r11
	jge	.L113
	.p2align 4,,7
.L6:
	movq	176(%rbx,%r11,8), %rax
	movq	%rax, (%rbp,%r11,8)
	incq	%r11
	cmpq	%r10, %r11
	jl	.L6
.L113:
	movl	24(%rbx), %eax
	movq	56(%rbx), %rdi
	movq	64(%rbx), %rsi
	movq	72(%rbx), %rdx
	movq	80(%rbx), %rcx
	movq	88(%rbx), %r8
	cmpl	$13, %eax
	movq	96(%rbx), %r9
	je	.L119
	cmpl	$14, %eax
	je	.L120
	cmpl	$7, %r12d
	xorpd	%xmm15, %xmm15
	jle	.L44
	movlpd	168(%rbx), %xmm15
.L44:
	cmpl	$6, %r12d
	xorpd	%xmm14, %xmm14
	jle	.L46
	movlpd	160(%rbx), %xmm14
.L46:
	cmpl	$5, %r12d
	xorpd	%xmm13, %xmm13
	jle	.L48
	movlpd	152(%rbx), %xmm13
.L48:
	cmpl	$4, %r12d
	xorpd	%xmm12, %xmm12
	jle	.L50
	movlpd	144(%rbx), %xmm12
.L50:
	cmpl	$3, %r12d
	xorpd	%xmm11, %xmm11
	jle	.L52
	movlpd	136(%rbx), %xmm11
.L52:
	cmpl	$2, %r12d
	xorpd	%xmm10, %xmm10
	jle	.L54
	movlpd	128(%rbx), %xmm10
.L54:
	cmpl	$1, %r12d
	xorpd	%xmm9, %xmm9
	jle	.L56
	movlpd	120(%rbx), %xmm9
.L56:
	testl	%r12d, %r12d
	xorpd	%xmm8, %xmm8
	jle	.L58
	movlpd	112(%rbx), %xmm8
.L58:
	movsd	%xmm15, %xmm7
	movsd	%xmm14, %xmm6
	movsd	%xmm13, %xmm5
	movsd	%xmm12, %xmm4
	movsd	%xmm11, %xmm3
	movsd	%xmm10, %xmm2
	movsd	%xmm9, %xmm1
	movsd	%xmm8, %xmm0
	movl	$8, %eax
	call	*(%rbx)
	movq	%rax, %r11
	movl	24(%rbx), %eax
	cmpl	$1, %eax
	je	.L24
	testl	%eax, %eax
	je	.L115
	cmpl	$2, %eax
	je	.L118
	cmpl	$3, %eax
	je	.L118
	cmpl	$4, %eax
	je	.L118
	cmpl	$5, %eax
	je	.L117
	cmpl	$6, %eax
	je	.L117
	cmpl	$7, %eax
	je	.L116
	cmpl	$8, %eax
	je	.L116
	cmpl	$9, %eax
	je	.L115
	cmpl	$10, %eax
	je	.L115
	cmpl	$11, %eax
	je	.L115
	cmpl	$12, %eax
	je	.L115
	cmpl	$15, %eax
	je	.L115
	cmpl	$16, %eax
	je	.L121
	.p2align 4,,7
.L24:
	addq	$2048, %rsp
	xorl	%eax, %eax
	popq	%rbx
	popq	%rbp
	popq	%r12
	ret
.L121:
	movl	8(%rbx), %eax
	testl	$1, %eax
	je	.L88
	movq	32(%rbx), %rax
	cmpq	$1, %rax
	je	.L122
	cmpq	$2, %rax
	je	.L123
	cmpq	$4, %rax
	je	.L124
	cmpq	$8, %rax
	je	.L125
	addq	$7, %rax
	movq	%rax, %rbp
	shrq	$3, %rbp
	decl	%ebp
	js	.L24
	movq	16(%rbx), %rbx
.L100:
	movslq	%ebp,%r10
	decl	%ebp
	movq	(%r11,%r10,8), %rax
	movq	%rax, (%rbx,%r10,8)
	jns	.L100
	jmp	.L24
.L125:
	movq	16(%rbx), %r10
	movq	(%r11), %rax
	movq	%rax, (%r10)
	jmp	.L24
.L124:
	movq	16(%rbx), %r10
	movl	(%r11), %eax
	movl	%eax, (%r10)
	jmp	.L24
.L123:
	movzwl	(%r11), %eax
	movq	16(%rbx), %r10
	movw	%ax, (%r10)
	jmp	.L24
.L122:
	movzbl	(%r11), %eax
	movq	16(%rbx), %r10
	movb	%al, (%r10)
	jmp	.L24
	.p2align 4,,7
.L88:
	testl	$512, %eax
	je	.L24
	movq	32(%rbx), %rax
	cmpq	$1, %rax
	je	.L118
	cmpq	$2, %rax
	je	.L117
	cmpq	$4, %rax
	je	.L116
	cmpq	$8, %rax
	je	.L115
	cmpq	$16, %rax
	jne	.L24
	movq	16(%rbx), %rax
	movq	%r11, (%rax)
	movq	%rdx, 8(%rax)
	jmp	.L24
	.p2align 4,,7
.L115:
	movq	16(%rbx), %rax
	movq	%r11, (%rax)
	jmp	.L24
.L116:
	movq	16(%rbx), %rax
	movl	%r11d, (%rax)
	jmp	.L24
.L117:
	movq	16(%rbx), %rax
	movw	%r11w, (%rax)
	jmp	.L24
.L118:
	movq	16(%rbx), %rax
	movb	%r11b, (%rax)
	jmp	.L24
.L120:
	cmpl	$7, %r12d
	xorpd	%xmm15, %xmm15
	jle	.L27
	movlpd	168(%rbx), %xmm15
.L27:
	cmpl	$6, %r12d
	xorpd	%xmm14, %xmm14
	jle	.L29
	movlpd	160(%rbx), %xmm14
.L29:
	cmpl	$5, %r12d
	xorpd	%xmm13, %xmm13
	jle	.L31
	movlpd	152(%rbx), %xmm13
.L31:
	cmpl	$4, %r12d
	xorpd	%xmm12, %xmm12
	jle	.L33
	movlpd	144(%rbx), %xmm12
.L33:
	cmpl	$3, %r12d
	xorpd	%xmm11, %xmm11
	jle	.L35
	movlpd	136(%rbx), %xmm11
.L35:
	cmpl	$2, %r12d
	xorpd	%xmm10, %xmm10
	jle	.L37
	movlpd	128(%rbx), %xmm10
.L37:
	cmpl	$1, %r12d
	xorpd	%xmm9, %xmm9
	jle	.L39
	movlpd	120(%rbx), %xmm9
.L39:
	testl	%r12d, %r12d
	xorpd	%xmm8, %xmm8
	jle	.L41
	movlpd	112(%rbx), %xmm8
.L41:
	movl	$8, %eax
	movsd	%xmm15, %xmm7
	movsd	%xmm14, %xmm6
	movsd	%xmm13, %xmm5
	movsd	%xmm12, %xmm4
	movsd	%xmm11, %xmm3
	movsd	%xmm10, %xmm2
	movsd	%xmm9, %xmm1
	movsd	%xmm8, %xmm0
	call	*(%rbx)
	movq	16(%rbx), %rax
	movsd	%xmm0, (%rax)
	jmp	.L24
.L119:
	cmpl	$7, %r12d
	xorpd	%xmm15, %xmm15
	jle	.L9
	movlpd	168(%rbx), %xmm15
.L9:
	cmpl	$6, %r12d
	xorpd	%xmm14, %xmm14
	jle	.L11
	movlpd	160(%rbx), %xmm14
.L11:
	cmpl	$5, %r12d
	xorpd	%xmm13, %xmm13
	jle	.L13
	movlpd	152(%rbx), %xmm13
.L13:
	cmpl	$4, %r12d
	xorpd	%xmm12, %xmm12
	jle	.L15
	movlpd	144(%rbx), %xmm12
.L15:
	cmpl	$3, %r12d
	xorpd	%xmm11, %xmm11
	jle	.L17
	movlpd	136(%rbx), %xmm11
.L17:
	cmpl	$2, %r12d
	xorpd	%xmm10, %xmm10
	jle	.L19
	movlpd	128(%rbx), %xmm10
.L19:
	cmpl	$1, %r12d
	xorpd	%xmm9, %xmm9
	jle	.L21
	movlpd	120(%rbx), %xmm9
.L21:
	testl	%r12d, %r12d
	xorpd	%xmm8, %xmm8
	jle	.L23
	movlpd	112(%rbx), %xmm8
.L23:
	movl	$8, %eax
	movsd	%xmm15, %xmm7
	movsd	%xmm14, %xmm6
	movsd	%xmm13, %xmm5
	movsd	%xmm12, %xmm4
	movsd	%xmm11, %xmm3
	movsd	%xmm10, %xmm2
	movsd	%xmm9, %xmm1
	movsd	%xmm8, %xmm0
	call	*(%rbx)
	movq	16(%rbx), %rax
	movss	%xmm0, (%rax)
	jmp	.L24
.LFE1:
.Lfe1:
	.size	__builtin_avcall,.Lfe1-__builtin_avcall
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
	.byte	0x4
	.long	.LCFI1-.LCFI0
	.byte	0xe
	.uleb128 0x18
	.byte	0x4
	.long	.LCFI2-.LCFI1
	.byte	0xe
	.uleb128 0x20
	.byte	0x83
	.uleb128 0x4
	.byte	0x86
	.uleb128 0x3
	.byte	0x8c
	.uleb128 0x2
	.align 8
.LEFDE1:
	.ident	"GCC: (GNU) 3.2.2 (SuSE Linux)"
