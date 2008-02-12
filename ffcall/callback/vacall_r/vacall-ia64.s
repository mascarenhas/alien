	.file	"vacall-ia64.c"
	.version	"01.01"
.text
	.align 16
	.global __vacall_r#
	.proc __vacall_r#
__vacall_r:
	alloc r44 = ar.pfs, 8, 5, 2, 0
	adds r12 = -208, r12
	mov r43 = b0
	;;
	adds r16 = 208, r12
	adds r14 = 224, r12
	adds r17 = 208, r12
	;;
	adds r22 = -112, r16
	adds r21 = -64, r14
	adds r23 = 208, r12
	adds r16 = -56, r14
	;;
	stfd [r22] = f8
	st8 [r21] = r32
	adds r14 = -104, r17
	st8 [r16] = r33
	adds r18 = 224, r12
	;;
	stfd [r14] = f9
	adds r17 = -96, r17
	adds r16 = -48, r18
	;;
	stfd [r17] = f10
	adds r14 = -88, r23
	st8 [r16] = r34
	;;
	stfd [r14] = f11
	adds r18 = -40, r18
	adds r17 = 224, r12
	adds r14 = 224, r12
	;;
	st8 [r18] = r35
	adds r42 = -176, r23
	adds r16 = -32, r14
	addl r18 = 0, r0
	adds r41 = -192, r23
	adds r14 = -80, r23
	;;
	st8 [r16] = r36
	st8 [r42] = r18
	stfd [r14] = f12
	adds r16 = -24, r17
	adds r40 = -168, r23
	adds r14 = -72, r23
	;;
	st8 [r16] = r37
	adds r17 = -16, r17
	stfd [r14] = f13
	adds r16 = -64, r23
	;;
	st8 [r17] = r38
	adds r14 = 208, r12
	stfd [r16] = f14
	adds r23 = 224, r12
	;;
	adds r19 = -56, r14
	adds r20 = -184, r14
	adds r18 = 208, r12
	adds r14 = -128, r14
	adds r17 = -8, r23
	;;
	adds r16 = -120, r18
	st8 [r14] = r21
	st8 [r17] = r39
	;;
	st8 [r16] = r22
	addl r23 = 0, r0
	mov r14 = r15
	adds r18 = -136, r18
	;;
	st8 [r18] = r8
	st4 [r40] = r23
	ld8 r16 = [r14], 8
	stfd [r19] = f15
	st8 [r20] = r21
	st4 [r41] = r23
	;;
	ld8 r17 = [r16], 8
	ld8 r45 = [r14]
	mov r46 = r41
	;;
	ld8 r1 = [r16]
	mov b6 = r17
	;;
	br.call.sptk.many b0 = b6 ;;
	ld4 r40 = [r40]
	;;
	cmp4.ne p6, p7 = 0, r40
	(p7) br.cond.dpnt .L4
	;;
	cmp4.ne p6, p7 = 1, r40
	(p6) br.cond.dptk .L5
	adds r16 = 208, r12
	;;
	adds r14 = -152, r16
	br .L69
.L5:
	cmp4.ne p6, p7 = 2, r40
	(p6) br.cond.dptk .L7
	adds r17 = 208, r12
	;;
	adds r14 = -152, r17
	;;
.L69:
	ld1 r16 = [r14]
	;;
	sxt1 r8 = r16
	br .L4
.L7:
	cmp4.ne p6, p7 = 3, r40
	(p6) br.cond.dptk .L9
	adds r18 = 208, r12
	;;
	adds r14 = -152, r18
	;;
	ld1 r8 = [r14]
	br .L4
.L9:
	cmp4.ne p6, p7 = 4, r40
	(p6) br.cond.dptk .L11
	adds r23 = 208, r12
	;;
	adds r14 = -152, r23
	;;
	ld2 r16 = [r14]
	;;
	sxt2 r8 = r16
	br .L4
.L11:
	cmp4.ne p6, p7 = 5, r40
	(p6) br.cond.dptk .L13
	adds r16 = 208, r12
	;;
	adds r14 = -152, r16
	;;
	ld2 r8 = [r14]
	br .L4
.L13:
	cmp4.ne p6, p7 = 6, r40
	(p6) br.cond.dptk .L15
	adds r17 = 208, r12
	;;
	adds r14 = -152, r17
	;;
	ld4 r16 = [r14]
	;;
	sxt4 r8 = r16
	br .L4
.L15:
	cmp4.ne p6, p7 = 7, r40
	(p6) br.cond.dptk .L17
	adds r18 = 208, r12
	;;
	adds r14 = -152, r18
	;;
	ld4 r8 = [r14]
	br .L4
.L17:
	cmp4.ne p6, p7 = 8, r40
	(p6) br.cond.dptk .L19
	adds r23 = 208, r12
	;;
	adds r14 = -152, r23
	;;
	ld8 r8 = [r14]
	br .L4
.L19:
	cmp4.ne p6, p7 = 9, r40
	(p6) br.cond.dptk .L21
	adds r16 = 208, r12
	;;
	adds r14 = -152, r16
	;;
	ld8 r8 = [r14]
	br .L4
.L21:
	cmp4.ne p6, p7 = 10, r40
	(p7) br.cond.dpnt .L70
	;;
	cmp4.ne p6, p7 = 11, r40
	(p6) br.cond.dptk .L25
	adds r18 = 208, r12
	;;
	adds r14 = -152, r18
	;;
	ld8 r8 = [r14]
	br .L4
.L25:
	cmp4.ne p6, p7 = 12, r40
	(p6) br.cond.dptk .L27
	adds r23 = 208, r12
	;;
	adds r14 = -152, r23
	;;
	ldfs f8 = [r14]
	br .L4
.L27:
	cmp4.ne p6, p7 = 13, r40
	(p6) br.cond.dptk .L29
	adds r16 = 208, r12
	;;
	adds r14 = -152, r16
	;;
	ldfd f8 = [r14]
	br .L4
.L29:
	cmp4.ne p6, p7 = 14, r40
	(p6) br.cond.dptk .L31
.L70:
	adds r17 = 208, r12
	;;
	adds r14 = -152, r17
	;;
	ld8 r8 = [r14]
	br .L4
.L31:
	cmp4.ne p6, p7 = 15, r40
	(p6) br.cond.dptk .L4
	ld4 r16 = [r41]
	;;
	and r14 = 1, r16
	;;
	cmp4.eq p6, p7 = 0, r14
	(p6) br.cond.dptk .L34
	ld8 r8 = [r42]
	br .L4
.L34:
	addl r14 = 1024, r0
	;;
	and r14 = r14, r16
	;;
	cmp4.eq p6, p7 = 0, r14
	(p6) br.cond.dptk .L4
	adds r18 = 208, r12
	;;
	adds r14 = -160, r18
	;;
	ld8 r18 = [r14]
	;;
	adds r16 = -1, r18
	;;
	cmp.ltu p6, p7 = 31, r16
	(p6) br.cond.dptk .L4
	ld8 r17 = [r42]
	;;
	cmp.geu p6, p7 = 1, r18
	ld1 r8 = [r17]
	(p6) br.cond.dptk .L38
	adds r16 = 1, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 8
	;;
	or r8 = r14, r8
.L38:
	cmp.geu p6, p7 = 2, r18
	(p6) br.cond.dptk .L39
	adds r16 = 2, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 16
	;;
	or r8 = r14, r8
.L39:
	cmp.geu p6, p7 = 3, r18
	(p6) br.cond.dptk .L40
	adds r16 = 3, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 24
	;;
	or r8 = r14, r8
.L40:
	cmp.geu p6, p7 = 4, r18
	(p6) br.cond.dptk .L41
	adds r16 = 4, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 32
	;;
	or r8 = r14, r8
.L41:
	cmp.geu p6, p7 = 5, r18
	(p6) br.cond.dptk .L42
	adds r16 = 5, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 40
	;;
	or r8 = r14, r8
.L42:
	cmp.geu p6, p7 = 6, r18
	(p6) br.cond.dptk .L43
	adds r16 = 6, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 48
	;;
	or r8 = r14, r8
.L43:
	cmp.geu p6, p7 = 7, r18
	(p6) br.cond.dptk .L44
	adds r16 = 7, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 56
	;;
	or r8 = r14, r8
.L44:
	cmp.geu p6, p7 = 8, r18
	(p6) br.cond.dptk .L4
	adds r14 = 8, r17
	;;
	cmp.geu p6, p7 = 9, r18
	ld1 r9 = [r14]
	(p6) br.cond.dptk .L46
	adds r16 = 9, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 8
	;;
	or r9 = r14, r9
.L46:
	cmp.geu p6, p7 = 10, r18
	(p6) br.cond.dptk .L47
	adds r16 = 10, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 16
	;;
	or r9 = r14, r9
.L47:
	cmp.geu p6, p7 = 11, r18
	(p6) br.cond.dptk .L48
	adds r16 = 11, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 24
	;;
	or r9 = r14, r9
.L48:
	cmp.geu p6, p7 = 12, r18
	(p6) br.cond.dptk .L49
	adds r16 = 12, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 32
	;;
	or r9 = r14, r9
.L49:
	cmp.geu p6, p7 = 13, r18
	(p6) br.cond.dptk .L50
	adds r16 = 13, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 40
	;;
	or r9 = r14, r9
.L50:
	cmp.geu p6, p7 = 14, r18
	(p6) br.cond.dptk .L51
	adds r16 = 14, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 48
	;;
	or r9 = r14, r9
.L51:
	cmp.geu p6, p7 = 15, r18
	(p6) br.cond.dptk .L52
	adds r16 = 15, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 56
	;;
	or r9 = r14, r9
.L52:
	cmp.geu p6, p7 = 16, r18
	(p6) br.cond.dptk .L4
	adds r14 = 16, r17
	;;
	cmp.geu p6, p7 = 17, r18
	ld1 r10 = [r14]
	(p6) br.cond.dptk .L54
	adds r16 = 17, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 8
	;;
	or r10 = r14, r10
.L54:
	cmp.geu p6, p7 = 18, r18
	(p6) br.cond.dptk .L55
	adds r16 = 18, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 16
	;;
	or r10 = r14, r10
.L55:
	cmp.geu p6, p7 = 19, r18
	(p6) br.cond.dptk .L56
	adds r16 = 19, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 24
	;;
	or r10 = r14, r10
.L56:
	cmp.geu p6, p7 = 20, r18
	(p6) br.cond.dptk .L57
	adds r16 = 20, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 32
	;;
	or r10 = r14, r10
.L57:
	cmp.geu p6, p7 = 21, r18
	(p6) br.cond.dptk .L58
	adds r16 = 21, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 40
	;;
	or r10 = r14, r10
.L58:
	cmp.geu p6, p7 = 22, r18
	(p6) br.cond.dptk .L59
	adds r16 = 22, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 48
	;;
	or r10 = r14, r10
.L59:
	cmp.geu p6, p7 = 23, r18
	(p6) br.cond.dptk .L60
	adds r16 = 23, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 56
	;;
	or r10 = r14, r10
.L60:
	cmp.geu p6, p7 = 24, r18
	(p6) br.cond.dptk .L4
	adds r14 = 24, r17
	;;
	cmp.geu p6, p7 = 25, r18
	ld1 r11 = [r14]
	(p6) br.cond.dptk .L62
	adds r16 = 25, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 8
	;;
	or r11 = r14, r11
.L62:
	cmp.geu p6, p7 = 26, r18
	(p6) br.cond.dptk .L63
	adds r16 = 26, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 16
	;;
	or r11 = r14, r11
.L63:
	cmp.geu p6, p7 = 27, r18
	(p6) br.cond.dptk .L64
	adds r16 = 27, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 24
	;;
	or r11 = r14, r11
.L64:
	cmp.geu p6, p7 = 28, r18
	(p6) br.cond.dptk .L65
	adds r16 = 28, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 32
	;;
	or r11 = r14, r11
.L65:
	cmp.geu p6, p7 = 29, r18
	(p6) br.cond.dptk .L66
	adds r16 = 29, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 40
	;;
	or r11 = r14, r11
.L66:
	cmp.geu p6, p7 = 30, r18
	(p6) br.cond.dptk .L67
	adds r16 = 30, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 48
	;;
	or r11 = r14, r11
.L67:
	cmp.geu p6, p7 = 31, r18
	(p6) br.cond.dptk .L4
	adds r16 = 31, r17
	;;
	ld1 r14 = [r16]
	;;
	shl r14 = r14, 56
	;;
	or r11 = r14, r11
.L4:
	adds r12 = 208, r12
	mov ar.pfs = r44
	mov b0 = r43
	br.ret.sptk.many b0
	.endp __vacall_r#
	.ident	"GCC: (GNU) 2.9-ia64-000216 snap-000324"
