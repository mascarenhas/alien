	.file	"proto64.c"
	.version	"01.01"
.text
	.align 16
	.global tramp#
	.proc tramp#
tramp:
	alloc r33 = ar.pfs, 0, 2, 0, 0
	movl r14 = 0x1234567813578765
	mov r32 = b0
	adds r12 = -16, r12
	movl r15 = 0x7355471143622155
	;;
	st8 [r14] = r15
	movl r16 = 0xbabebec0dea0ffab
	movl r15 = 0xbabebec0dea0ffb3
	;;
	ld8 r8 = [r16]
	ld8 r1 = [r15]
	;;
	mov b6 = r8
	br.call.sptk.many b0 = b6 ;;
	adds r12 = 16, r12
	;;
	mov ar.pfs = r33
	mov b0 = r32
	br.ret.sptk.many b0
	.endp tramp#
	.align 16
	.global jump#
	.proc jump#
jump:
	movl r14 = 0xbabebec0dea0ffab
	;;
	mov b6 = r14
	br b6
	.endp jump#
	.ident	"GCC: (GNU) 2.9-ia64-000216 snap-000324"
