	.file	"avcall-ia64.c"
	.version	"01.01"
	.global __divdi3#
.text
	.align 16
	.global __builtin_avcall#
	.proc __builtin_avcall#
__builtin_avcall:
	alloc r37 = ar.pfs, 1, 5, 8, 0
	mov r34 = r32
	adds r12 = -16, r12
	mov r33 = r1
	;;
	adds r15 = 40, r34
	adds r12 = -2048, r12
	mov r36 = b0
	;;
	ld8 r14 = [r15]
	adds r35 = 16, r12
	addl r39 = 8, r0
	;;
	sub r14 = r14, r34
	;;
	adds r38 = -120, r14
	br.call.sptk.many b0 = __divdi3# ;;
	adds r15 = 48, r34
	mov r1 = r33
	addl r39 = 8, r0
	;;
	ld8 r14 = [r15]
	sxt4 r33 = r8
	;;
	sub r14 = r14, r34
	;;
	adds r38 = -56, r14
	br.call.sptk.many b0 = __divdi3# ;;
	addl r18 = 8, r0
	sxt4 r17 = r8
	;;
	cmp.gt p6, p7 = r33, r18
	(p7) br.cond.dpnt .L97
	adds r23 = 120, r34
	;;
	mov r19 = r23
.L6:
	shl r14 = r18, 3
	;;
	add r16 = r19, r14
	adds r18 = 1, r18
	add r14 = r35, r14
	;;
	ld8 r15 = [r16]
	cmp.gt p6, p7 = r33, r18
	adds r14 = -64, r14
	;;
	st8 [r14] = r15
	(p6) br.cond.dptk .L6
	br .L96
.L97:
	adds r23 = 120, r34
.L96:
	adds r33 = 24, r34
	;;
	ld4 r14 = [r33]
	;;
	cmp4.ne p6, p7 = 16, r14
	(p6) br.cond.dptk .L8
	adds r14 = 16, r34
	;;
	ld8 r8 = [r14]
.L8:
	cmp4.ge p6, p7 = 0, r17
	(p6) br.cond.dptk .L9
	adds r14 = 56, r34
	;;
	cmp4.ge p6, p7 = 1, r17
	ldfd f8 = [r14]
	(p6) br.cond.dptk .L9
	adds r14 = 64, r34
	;;
	cmp4.ge p6, p7 = 2, r17
	ldfd f9 = [r14]
	(p6) br.cond.dptk .L9
	adds r14 = 72, r34
	;;
	cmp4.ge p6, p7 = 3, r17
	ldfd f10 = [r14]
	(p6) br.cond.dptk .L9
	adds r14 = 80, r34
	;;
	cmp4.ge p6, p7 = 4, r17
	ldfd f11 = [r14]
	(p6) br.cond.dptk .L9
	adds r14 = 88, r34
	;;
	cmp4.ge p6, p7 = 5, r17
	ldfd f12 = [r14]
	(p6) br.cond.dptk .L9
	adds r14 = 96, r34
	;;
	cmp4.ge p6, p7 = 6, r17
	ldfd f13 = [r14]
	(p6) br.cond.dptk .L9
	adds r14 = 104, r34
	;;
	cmp4.ge p6, p7 = 7, r17
	ldfd f14 = [r14]
	(p6) br.cond.dptk .L9
	adds r14 = 112, r34
	;;
	ldfd f15 = [r14]
.L9:
	ld4 r14 = [r33]
	;;
	cmp4.ne p6, p7 = 13, r14
	(p6) br.cond.dptk .L17
	ld8 r21 = [r34]
	adds r14 = 144, r34
	adds r15 = 152, r34
	;;
	ld8 r22 = [r21], 8
	adds r19 = 128, r34
	adds r20 = 136, r34
	adds r16 = 160, r34
	adds r17 = 168, r34
	adds r18 = 176, r34
	ld8 r41 = [r14]
	ld8 r42 = [r15]
	ld8 r38 = [r23]
	;;
	ld8 r39 = [r19]
	ld8 r40 = [r20]
	ld8 r43 = [r16]
	ld8 r44 = [r17]
	ld8 r45 = [r18]
	ld8 r1 = [r21]
	mov b6 = r22
	;;
	br.call.sptk.many b0 = b6 ;;
	adds r14 = 16, r34
	;;
	ld8 r15 = [r14]
	;;
	stfs [r15] = f8
	br .L18
.L17:
	cmp4.ne p6, p7 = 14, r14
	(p6) br.cond.dptk .L19
	ld8 r21 = [r34]
	adds r14 = 144, r34
	adds r15 = 152, r34
	;;
	ld8 r22 = [r21], 8
	adds r19 = 128, r34
	adds r20 = 136, r34
	adds r16 = 160, r34
	adds r17 = 168, r34
	adds r18 = 176, r34
	ld8 r41 = [r14]
	ld8 r42 = [r15]
	ld8 r38 = [r23]
	;;
	ld8 r39 = [r19]
	ld8 r40 = [r20]
	ld8 r43 = [r16]
	ld8 r44 = [r17]
	ld8 r45 = [r18]
	ld8 r1 = [r21]
	mov b6 = r22
	;;
	br.call.sptk.many b0 = b6 ;;
	adds r14 = 16, r34
	;;
	ld8 r15 = [r14]
	;;
	stfd [r15] = f8
	br .L18
.L19:
	ld8 r21 = [r34]
	adds r14 = 144, r34
	adds r18 = 176, r34
	;;
	ld8 r22 = [r21], 8
	adds r19 = 128, r34
	adds r20 = 136, r34
	adds r15 = 152, r34
	adds r16 = 160, r34
	adds r17 = 168, r34
	ld8 r41 = [r14]
	ld8 r45 = [r18]
	ld8 r38 = [r23]
	;;
	ld8 r39 = [r19]
	ld8 r40 = [r20]
	ld8 r42 = [r15]
	ld8 r43 = [r16]
	ld8 r44 = [r17]
	ld8 r1 = [r21]
	mov b6 = r22
	;;
	br.call.sptk.many b0 = b6 ;;
	ld4 r14 = [r33]
	mov r18 = r8
	;;
	cmp4.ne p6, p7 = 1, r14
	(p7) br.cond.dpnt .L18
	;;
	cmp4.ne p6, p7 = 0, r14
	(p7) br.cond.dpnt .L98
	;;
	cmp4.ne p6, p7 = 2, r14
	(p7) br.cond.dpnt .L99
	;;
	cmp4.ne p6, p7 = 3, r14
	(p7) br.cond.dpnt .L99
	;;
	cmp4.ne p6, p7 = 4, r14
	(p6) br.cond.dptk .L29
.L99:
	adds r14 = 16, r34
	;;
	ld8 r15 = [r14]
	;;
	st1 [r15] = r18
	br .L18
.L29:
	cmp4.ne p6, p7 = 5, r14
	(p7) br.cond.dpnt .L100
	;;
	cmp4.ne p6, p7 = 6, r14
	(p6) br.cond.dptk .L33
.L100:
	adds r14 = 16, r34
	;;
	ld8 r15 = [r14]
	;;
	st2 [r15] = r18
	br .L18
.L33:
	cmp4.ne p6, p7 = 7, r14
	(p7) br.cond.dpnt .L101
	;;
	cmp4.ne p6, p7 = 8, r14
	(p6) br.cond.dptk .L37
.L101:
	adds r14 = 16, r34
	;;
	ld8 r15 = [r14]
	;;
	st4 [r15] = r18
	br .L18
.L37:
	mov r15 = r14
	;;
	cmp4.eq p6, p7 = 9, r15
	(p6) br.cond.dptk .L98
	;;
	cmp4.eq p6, p7 = 11, r15
	(p6) br.cond.dptk .L98
	;;
	cmp4.eq p6, p7 = 10, r15
	(p6) br.cond.dptk .L98
	;;
	cmp4.eq p6, p7 = 12, r15
	(p6) br.cond.dptk .L98
	;;
	cmp4.ne p6, p7 = 15, r15
	(p6) br.cond.dptk .L45
.L98:
	adds r14 = 16, r34
	;;
	ld8 r15 = [r14]
	;;
	st8 [r15] = r18
	br .L18
.L45:
	cmp4.ne p6, p7 = 16, r14
	(p6) br.cond.dptk .L18
	adds r15 = 8, r34
	;;
	ld4 r14 = [r15]
	;;
	and r14 = 1, r14
	;;
	cmp4.eq p6, p7 = 0, r14
	(p6) br.cond.dptk .L48
	adds r14 = 32, r34
	;;
	ld8 r14 = [r14]
	;;
	cmp.ne p6, p7 = 1, r14
	(p6) br.cond.dptk .L49
	adds r14 = 16, r34
	ld1 r16 = [r18]
	;;
	ld8 r15 = [r14]
	;;
	st1 [r15] = r16
	br .L18
.L49:
	cmp.ne p6, p7 = 2, r14
	(p6) br.cond.dptk .L51
	adds r14 = 16, r34
	ld2 r16 = [r18]
	;;
	ld8 r15 = [r14]
	;;
	st2 [r15] = r16
	br .L18
.L51:
	cmp.ne p6, p7 = 4, r14
	(p6) br.cond.dptk .L53
	adds r14 = 16, r34
	ld4 r16 = [r18]
	;;
	ld8 r15 = [r14]
	;;
	st4 [r15] = r16
	br .L18
.L53:
	cmp.ne p6, p7 = 8, r14
	(p6) br.cond.dptk .L55
	adds r14 = 16, r34
	ld8 r16 = [r18]
	;;
	ld8 r15 = [r14]
	;;
	st8 [r15] = r16
	br .L18
.L55:
	adds r14 = 7, r14
	;;
	shr.u r14 = r14, 3
	;;
	adds r14 = -1, r14
	;;
	cmp4.le p6, p7 = 0, r14
	sxt4 r17 = r14
	(p7) br.cond.dpnt .L18
	adds r14 = 16, r34
	;;
	ld8 r19 = [r14]
.L59:
	shl r14 = r17, 3
	adds r17 = -1, r17
	;;
	add r16 = r18, r14
	add r14 = r19, r14
	cmp4.le p6, p7 = 0, r17
	;;
	ld8 r15 = [r16]
	sxt4 r17 = r17
	;;
	st8 [r14] = r15
	(p6) br.cond.dptk .L59
	br .L18
.L48:
	ld4 r14 = [r15]
	addl r15 = 512, r0
	;;
	and r14 = r15, r14
	;;
	cmp4.eq p6, p7 = 0, r14
	(p6) br.cond.dptk .L18
	adds r22 = 32, r34
	;;
	ld8 r15 = [r22]
	;;
	adds r14 = -1, r15
	;;
	cmp.ltu p6, p7 = 31, r14
	(p6) br.cond.dptk .L18
	;;
	cmp.eq p6, p7 = 0, r15
	(p6) br.cond.dptk .L64
	adds r14 = 16, r34
	;;
	ld8 r15 = [r14]
	;;
	st1 [r15] = r18
	ld8 r15 = [r22]
	;;
.L64:
	cmp.geu p6, p7 = 1, r15
	(p6) br.cond.dptk .L65
	adds r14 = 16, r34
	shr r16 = r18, 8
	;;
	ld8 r15 = [r14]
	;;
	adds r15 = 1, r15
	;;
	st1 [r15] = r16
	ld8 r15 = [r22]
	;;
.L65:
	cmp.geu p6, p7 = 2, r15
	(p6) br.cond.dptk .L66
	adds r14 = 16, r34
	shr r16 = r18, 16
	;;
	ld8 r15 = [r14]
	;;
	adds r15 = 2, r15
	;;
	st1 [r15] = r16
	ld8 r15 = [r22]
	;;
.L66:
	cmp.geu p6, p7 = 3, r15
	(p6) br.cond.dptk .L67
	adds r14 = 16, r34
	shr r16 = r18, 24
	;;
	ld8 r15 = [r14]
	;;
	adds r15 = 3, r15
	;;
	st1 [r15] = r16
	ld8 r15 = [r22]
	;;
.L67:
	cmp.geu p6, p7 = 4, r15
	(p6) br.cond.dptk .L68
	adds r14 = 16, r34
	shr r16 = r18, 32
	;;
	ld8 r15 = [r14]
	;;
	adds r15 = 4, r15
	;;
	st1 [r15] = r16
	ld8 r15 = [r22]
	;;
.L68:
	cmp.geu p6, p7 = 5, r15
	(p6) br.cond.dptk .L69
	adds r14 = 16, r34
	shr r16 = r18, 40
	;;
	ld8 r15 = [r14]
	;;
	adds r15 = 5, r15
	;;
	st1 [r15] = r16
	ld8 r15 = [r22]
	;;
.L69:
	cmp.geu p6, p7 = 6, r15
	(p6) br.cond.dptk .L70
	adds r14 = 16, r34
	shr r16 = r18, 48
	;;
	ld8 r15 = [r14]
	;;
	adds r15 = 6, r15
	;;
	st1 [r15] = r16
	ld8 r15 = [r22]
	;;
.L70:
	cmp.geu p6, p7 = 7, r15
	(p6) br.cond.dptk .L71
	adds r14 = 16, r34
	shr r16 = r18, 56
	;;
	ld8 r15 = [r14]
	;;
	adds r15 = 7, r15
	;;
	st1 [r15] = r16
	ld8 r15 = [r22]
	;;
.L71:
	cmp.geu p6, p7 = 8, r15
	(p6) br.cond.dptk .L18
	adds r16 = 16, r34
	;;
	ld8 r14 = [r16]
	;;
	adds r14 = 8, r14
	;;
	st1 [r14] = r9
	ld8 r15 = [r22]
	;;
	cmp.geu p6, p7 = 9, r15
	(p6) br.cond.dptk .L73
	ld8 r14 = [r16]
	shr r15 = r9, 8
	;;
	adds r14 = 9, r14
	;;
	st1 [r14] = r15
	ld8 r15 = [r22]
	;;
.L73:
	cmp.geu p6, p7 = 10, r15
	(p6) br.cond.dptk .L74
	ld8 r14 = [r16]
	shr r15 = r9, 16
	;;
	adds r14 = 10, r14
	;;
	st1 [r14] = r15
.L74:
	ld8 r14 = [r22]
	;;
	cmp.geu p6, p7 = 11, r14
	(p6) br.cond.dptk .L75
	ld8 r14 = [r16]
	shr r15 = r9, 24
	;;
	adds r14 = 11, r14
	;;
	st1 [r14] = r15
	ld8 r14 = [r22]
	;;
.L75:
	cmp.geu p6, p7 = 12, r14
	(p6) br.cond.dptk .L76
	ld8 r14 = [r16]
	shr r15 = r9, 32
	;;
	adds r14 = 12, r14
	;;
	st1 [r14] = r15
	ld8 r14 = [r22]
	;;
.L76:
	cmp.geu p6, p7 = 13, r14
	(p6) br.cond.dptk .L77
	ld8 r14 = [r16]
	shr r15 = r9, 40
	;;
	adds r14 = 13, r14
	;;
	st1 [r14] = r15
	ld8 r14 = [r22]
	;;
.L77:
	cmp.geu p6, p7 = 14, r14
	(p6) br.cond.dptk .L78
	ld8 r14 = [r16]
	shr r15 = r9, 48
	;;
	adds r14 = 14, r14
	;;
	st1 [r14] = r15
	ld8 r14 = [r22]
	;;
.L78:
	cmp.geu p6, p7 = 15, r14
	(p6) br.cond.dptk .L79
	ld8 r14 = [r16]
	shr r15 = r9, 56
	;;
	adds r14 = 15, r14
	;;
	st1 [r14] = r15
	ld8 r14 = [r22]
	;;
.L79:
	cmp.geu p6, p7 = 16, r14
	(p6) br.cond.dptk .L18
	ld8 r14 = [r16]
	;;
	adds r14 = 16, r14
	;;
	st1 [r14] = r10
	ld8 r14 = [r22]
	;;
	cmp.geu p6, p7 = 17, r14
	(p6) br.cond.dptk .L81
	ld8 r14 = [r16]
	shr r15 = r10, 8
	;;
	adds r14 = 17, r14
	;;
	st1 [r14] = r15
	ld8 r14 = [r22]
	;;
.L81:
	cmp.geu p6, p7 = 18, r14
	(p6) br.cond.dptk .L82
	ld8 r14 = [r16]
	shr r15 = r10, 16
	;;
	adds r14 = 18, r14
	;;
	st1 [r14] = r15
	ld8 r14 = [r22]
	;;
.L82:
	cmp.geu p6, p7 = 19, r14
	(p6) br.cond.dptk .L83
	ld8 r14 = [r16]
	shr r15 = r10, 24
	;;
	adds r14 = 19, r14
	;;
	st1 [r14] = r15
	ld8 r14 = [r22]
	;;
.L83:
	cmp.geu p6, p7 = 20, r14
	(p6) br.cond.dptk .L84
	ld8 r14 = [r16]
	shr r15 = r10, 32
	;;
	adds r14 = 20, r14
	;;
	st1 [r14] = r15
	ld8 r14 = [r22]
	;;
.L84:
	cmp.geu p6, p7 = 21, r14
	(p6) br.cond.dptk .L85
	ld8 r14 = [r16]
	shr r15 = r10, 40
	;;
	adds r14 = 21, r14
	;;
	st1 [r14] = r15
.L85:
	ld8 r14 = [r22]
	;;
	cmp.geu p6, p7 = 22, r14
	(p6) br.cond.dptk .L86
	ld8 r14 = [r16]
	shr r15 = r10, 48
	;;
	adds r14 = 22, r14
	;;
	st1 [r14] = r15
	ld8 r14 = [r22]
	;;
.L86:
	cmp.geu p6, p7 = 23, r14
	(p6) br.cond.dptk .L87
	ld8 r14 = [r16]
	shr r15 = r10, 56
	;;
	adds r14 = 23, r14
	;;
	st1 [r14] = r15
	ld8 r14 = [r22]
	;;
.L87:
	cmp.geu p6, p7 = 24, r14
	(p6) br.cond.dptk .L18
	ld8 r14 = [r16]
	;;
	adds r14 = 24, r14
	;;
	st1 [r14] = r11
	ld8 r14 = [r22]
	;;
	cmp.geu p6, p7 = 25, r14
	(p6) br.cond.dptk .L89
	ld8 r14 = [r16]
	shr r15 = r11, 8
	;;
	adds r14 = 25, r14
	;;
	st1 [r14] = r15
	ld8 r14 = [r22]
	;;
.L89:
	cmp.geu p6, p7 = 26, r14
	(p6) br.cond.dptk .L90
	ld8 r14 = [r16]
	shr r15 = r11, 16
	;;
	adds r14 = 26, r14
	;;
	st1 [r14] = r15
	ld8 r14 = [r22]
	;;
.L90:
	cmp.geu p6, p7 = 27, r14
	(p6) br.cond.dptk .L91
	ld8 r14 = [r16]
	shr r15 = r11, 24
	;;
	adds r14 = 27, r14
	;;
	st1 [r14] = r15
	ld8 r14 = [r22]
	;;
.L91:
	cmp.geu p6, p7 = 28, r14
	(p6) br.cond.dptk .L92
	ld8 r14 = [r16]
	shr r15 = r11, 32
	;;
	adds r14 = 28, r14
	;;
	st1 [r14] = r15
	ld8 r14 = [r22]
	;;
.L92:
	cmp.geu p6, p7 = 29, r14
	(p6) br.cond.dptk .L93
	ld8 r14 = [r16]
	shr r15 = r11, 40
	;;
	adds r14 = 29, r14
	;;
	st1 [r14] = r15
	ld8 r14 = [r22]
	;;
.L93:
	cmp.geu p6, p7 = 30, r14
	(p6) br.cond.dptk .L94
	ld8 r14 = [r16]
	shr r15 = r11, 48
	;;
	adds r14 = 30, r14
	;;
	st1 [r14] = r15
	ld8 r14 = [r22]
	;;
.L94:
	cmp.geu p6, p7 = 31, r14
	(p6) br.cond.dptk .L18
	ld8 r14 = [r16]
	shr r15 = r11, 56
	;;
	adds r14 = 31, r14
	;;
	st1 [r14] = r15
.L18:
	addl r8 = 0, r0
	adds r12 = 16, r12
	mov ar.pfs = r37
	mov b0 = r36
	br.ret.sptk.many b0
	.endp __builtin_avcall#
	.ident	"GCC: (GNU) 2.9-ia64-000216 snap-000324"
