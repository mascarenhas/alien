	.file	"vacall-x86_64.c"
	.text
	.p2align 4,,15
.globl __vacall_r
	.type	__vacall_r,@function
__vacall_r:
.LFB1:
	pushq	%r13
.LCFI0:
	pushq	%r12
.LCFI1:
	subq	$200, %rsp
.LCFI2:
	leaq	136(%rsp), %r12
	leaq	224(%rsp), %r11
	movq	%rdi, 136(%rsp)
	movq	%r12, 128(%rsp)
	movq	%rsi, 144(%rsp)
	movq	%r11, 8(%rsp)
	leaq	64(%rsp), %r12
	movq	$0, 16(%rsp)
	movq	%rdx, 152(%rsp)
	movq	%rcx, 160(%rsp)
	movq	%r8, 168(%rsp)
	movq	%r9, 176(%rsp)
	movsd	%xmm0, 64(%rsp)
	movsd	%xmm1, 72(%rsp)
	movsd	%xmm2, 80(%rsp)
	movsd	%xmm3, 88(%rsp)
	movsd	%xmm4, 96(%rsp)
	movsd	%xmm5, 104(%rsp)
	movsd	%xmm6, 112(%rsp)
	movsd	%xmm7, 120(%rsp)
	movl	$0, (%rsp)
	movl	$0, 24(%rsp)
	movq	%r12, 56(%rsp)
	movq	%rsp, %rsi
	movq	8(%r10), %rdi
	call	*(%r10)
	movl	24(%rsp), %r11d
	testl	%r11d, %r11d
	je	.L1
	cmpl	$1, %r11d
	je	.L53
	cmpl	$2, %r11d
	je	.L53
	cmpl	$3, %r11d
	je	.L54
	cmpl	$4, %r11d
	je	.L55
	cmpl	$5, %r11d
	je	.L56
	cmpl	$6, %r11d
	je	.L57
	cmpl	$7, %r11d
	je	.L58
	cmpl	$8, %r11d
	je	.L52
	cmpl	$9, %r11d
	je	.L52
	cmpl	$10, %r11d
	je	.L52
	cmpl	$11, %r11d
	je	.L52
	cmpl	$12, %r11d
	je	.L59
	cmpl	$13, %r11d
	je	.L60
	cmpl	$14, %r11d
	je	.L52
	cmpl	$15, %r11d
	je	.L61
	.p2align 4,,7
.L1:
	addq	$200, %rsp
	popq	%r12
	popq	%r13
	ret
.L61:
	movl	(%rsp), %r11d
	testl	$1, %r11d
	je	.L33
	movq	16(%rsp), %rax
	jmp	.L1
.L33:
	andl	$1024, %r11d
	je	.L1
	movq	32(%rsp), %r12
	leaq	-1(%r12), %r11
	cmpq	$15, %r11
	ja	.L1
	movq	16(%rsp), %r13
	cmpq	$1, %r12
	movzbq	(%r13), %rax
	jbe	.L37
	movzbq	1(%r13), %r11
	salq	$8, %r11
	orq	%r11, %rax
.L37:
	cmpq	$2, %r12
	jbe	.L38
	movzbq	2(%r13), %r11
	salq	$16, %r11
	orq	%r11, %rax
.L38:
	cmpq	$3, %r12
	jbe	.L39
	movzbq	3(%r13), %r11
	salq	$24, %r11
	orq	%r11, %rax
.L39:
	cmpq	$4, %r12
	jbe	.L40
	movzbq	4(%r13), %r11
	salq	$32, %r11
	orq	%r11, %rax
.L40:
	cmpq	$5, %r12
	jbe	.L41
	movzbq	5(%r13), %r11
	salq	$40, %r11
	orq	%r11, %rax
.L41:
	cmpq	$6, %r12
	jbe	.L42
	movzbq	6(%r13), %r11
	salq	$48, %r11
	orq	%r11, %rax
.L42:
	cmpq	$7, %r12
	jbe	.L43
	movzbq	7(%r13), %r11
	salq	$56, %r11
	orq	%r11, %rax
.L43:
	cmpq	$8, %r12
	jbe	.L1
	cmpq	$9, %r12
	movzbq	8(%r13), %rdx
	jbe	.L45
	movzbq	9(%r13), %r11
	salq	$8, %r11
	orq	%r11, %rdx
.L45:
	cmpq	$10, %r12
	jbe	.L46
	movzbq	10(%r13), %r11
	salq	$16, %r11
	orq	%r11, %rdx
.L46:
	cmpq	$11, %r12
	jbe	.L47
	movzbq	11(%r13), %r11
	salq	$24, %r11
	orq	%r11, %rdx
.L47:
	cmpq	$12, %r12
	jbe	.L48
	movzbq	12(%r13), %r11
	salq	$32, %r11
	orq	%r11, %rdx
.L48:
	cmpq	$13, %r12
	jbe	.L49
	movzbq	13(%r13), %r11
	salq	$40, %r11
	orq	%r11, %rdx
.L49:
	cmpq	$14, %r12
	jbe	.L50
	movzbq	14(%r13), %r11
	salq	$48, %r11
	orq	%r11, %rdx
.L50:
	cmpq	$15, %r12
	jbe	.L1
	movzbq	15(%r13), %r11
	salq	$56, %r11
	orq	%r11, %rdx
	jmp	.L1
	.p2align 4,,7
.L52:
	movq	40(%rsp), %rax
	jmp	.L1
.L60:
	movlpd	40(%rsp), %xmm0
	jmp	.L1
.L59:
	movss	40(%rsp), %xmm0
	jmp	.L1
.L58:
	mov	40(%rsp), %eax
	jmp	.L1
.L57:
	movslq	40(%rsp),%rax
	jmp	.L1
.L56:
	movzwq	40(%rsp), %rax
	jmp	.L1
.L55:
	movswq	40(%rsp),%rax
	jmp	.L1
.L54:
	movzbq	40(%rsp), %rax
	jmp	.L1
	.p2align 4,,7
.L53:
	movsbq	40(%rsp),%rax
	jmp	.L1
.LFE1:
.Lfe1:
	.size	__vacall_r,.Lfe1-__vacall_r
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
	.uleb128 0xe0
	.byte	0x8c
	.uleb128 0x3
	.byte	0x8d
	.uleb128 0x2
	.align 8
.LEFDE1:
	.ident	"GCC: (GNU) 3.2.2 (SuSE Linux)"
