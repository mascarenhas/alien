	.file	"vacall-ia64.c"
	.version	"01.01"
.text
	.align 16
	.global __vacall#
	.proc __vacall#
__vacall:
	alloc r44 = ar.pfs, 8, 5, 1, 0
	adds r12 = -208, r12
	mov r43 = b0
	;;
	adds r15 = 208, r12
	adds r14 = 224, r12
	adds r16 = 208, r12
	;;
	adds r22 = -112, r15
	adds r20 = -64, r14
	adds r23 = 208, r12
	adds r15 = -56, r14
	;;
	stfd [r22] = f8
	st8 [r20] = r32
	adds r14 = -104, r16
	st8 [r15] = r33
	adds r17 = 224, r12
	;;
	stfd [r14] = f9
	adds r16 = -96, r16
	adds r15 = -48, r17
	;;
	stfd [r16] = f10
	adds r14 = -88, r23
	st8 [r15] = r34
	;;
	stfd [r14] = f11
	adds r17 = -40, r17
	adds r16 = 224, r12
	adds r14 = 224, r12
	;;
	st8 [r17] = r35
	adds r42 = -176, r23
	adds r15 = -32, r14
	adds r17 = 224, r12
	adds r14 = -80, r23
	;;
	st8 [r15] = r36
	stfd [r14] = f12
	adds r15 = -24, r16
	adds r14 = -72, r23
	;;
	st8 [r15] = r37
	addl r16 = @ltoff(vacall_function#), gp
	stfd [r14] = f13
	adds r15 = -16, r17
	adds r14 = -64, r23
	;;
	st8 [r15] = r38
	addl r23 = 0, r0
	stfd [r14] = f14
	;;
	st8 [r42] = r23
	adds r14 = 208, r12
	ld8 r21 = [r16]
	;;
	adds r41 = -192, r14
	adds r40 = -168, r14
	adds r16 = -8, r17
	adds r18 = -56, r14
	adds r19 = -184, r14
	adds r17 = 208, r12
	adds r14 = -128, r14
	;;
	st8 [r16] = r39
	adds r15 = -120, r17
	st8 [r14] = r20
	st4 [r40] = r23
	adds r17 = -136, r17
	;;
	st8 [r15] = r22
	stfd [r18] = f15
	st8 [r19] = r20
	st8 [r17] = r8
	st4 [r41] = r23
	ld8 r14 = [r21]
	mov r45 = r41
	;;
	ld8 r15 = [r14], 8
	;;
	ld8 r1 = [r14]
	mov b6 = r15
	;;
	br.call.sptk.many b0 = b6 ;;
	ld4 r40 = [r40]
	;;
	cmp4.ne p6, p7 = 0, r40
	(p7) br.cond.dpnt .L4
	;;
	cmp4.ne p6, p7 = 1, r40
	(p6) br.cond.dptk .L5
	adds r15 = 208, r12
	;;
	adds r14 = -152, r15
	br .L69
.L5:
	cmp4.ne p6, p7 = 2, r40
	(p6) br.cond.dptk .L7
	adds r16 = 208, r12
	;;
	adds r14 = -152, r16
	;;
.L69:
	ld1 r15 = [r14]
	;;
	sxt1 r8 = r15
	br .L4
.L7:
	cmp4.ne p6, p7 = 3, r40
	(p6) br.cond.dptk .L9
	adds r17 = 208, r12
	;;
	adds r14 = -152, r17
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
	ld2 r15 = [r14]
	;;
	sxt2 r8 = r15
	br .L4
.L11:
	cmp4.ne p6, p7 = 5, r40
	(p6) br.cond.dptk .L13
	adds r15 = 208, r12
	;;
	adds r14 = -152, r15
	;;
	ld2 r8 = [r14]
	br .L4
.L13:
	cmp4.ne p6, p7 = 6, r40
	(p6) br.cond.dptk .L15
	adds r16 = 208, r12
	;;
	adds r14 = -152, r16
	;;
	ld4 r15 = [r14]
	;;
	sxt4 r8 = r15
	br .L4
.L15:
	cmp4.ne p6, p7 = 7, r40
	(p6) br.cond.dptk .L17
	adds r17 = 208, r12
	;;
	adds r14 = -152, r17
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
	adds r15 = 208, r12
	;;
	adds r14 = -152, r15
	;;
	ld8 r8 = [r14]
	br .L4
.L21:
	cmp4.ne p6, p7 = 10, r40
	(p7) br.cond.dpnt .L70
	;;
	cmp4.ne p6, p7 = 11, r40
	(p6) br.cond.dptk .L25
	adds r17 = 208, r12
	;;
	adds r14 = -152, r17
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
	adds r15 = 208, r12
	;;
	adds r14 = -152, r15
	;;
	ldfd f8 = [r14]
	br .L4
.L29:
	cmp4.ne p6, p7 = 14, r40
	(p6) br.cond.dptk .L31
.L70:
	adds r16 = 208, r12
	;;
	adds r14 = -152, r16
	;;
	ld8 r8 = [r14]
	br .L4
.L31:
	cmp4.ne p6, p7 = 15, r40
	(p6) br.cond.dptk .L4
	ld4 r15 = [r41]
	;;
	and r14 = 1, r15
	;;
	cmp4.eq p6, p7 = 0, r14
	(p6) br.cond.dptk .L34
	ld8 r8 = [r42]
	br .L4
.L34:
	addl r14 = 1024, r0
	;;
	and r14 = r14, r15
	;;
	cmp4.eq p6, p7 = 0, r14
	(p6) br.cond.dptk .L4
	adds r17 = 208, r12
	;;
	adds r14 = -160, r17
	;;
	ld8 r17 = [r14]
	;;
	adds r15 = -1, r17
	;;
	cmp.ltu p6, p7 = 31, r15
	(p6) br.cond.dptk .L4
	ld8 r16 = [r42]
	;;
	cmp.geu p6, p7 = 1, r17
	ld1 r8 = [r16]
	(p6) br.cond.dptk .L38
	adds r15 = 1, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 8
	;;
	or r8 = r14, r8
.L38:
	cmp.geu p6, p7 = 2, r17
	(p6) br.cond.dptk .L39
	adds r15 = 2, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 16
	;;
	or r8 = r14, r8
.L39:
	cmp.geu p6, p7 = 3, r17
	(p6) br.cond.dptk .L40
	adds r15 = 3, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 24
	;;
	or r8 = r14, r8
.L40:
	cmp.geu p6, p7 = 4, r17
	(p6) br.cond.dptk .L41
	adds r15 = 4, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 32
	;;
	or r8 = r14, r8
.L41:
	cmp.geu p6, p7 = 5, r17
	(p6) br.cond.dptk .L42
	adds r15 = 5, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 40
	;;
	or r8 = r14, r8
.L42:
	cmp.geu p6, p7 = 6, r17
	(p6) br.cond.dptk .L43
	adds r15 = 6, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 48
	;;
	or r8 = r14, r8
.L43:
	cmp.geu p6, p7 = 7, r17
	(p6) br.cond.dptk .L44
	adds r15 = 7, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 56
	;;
	or r8 = r14, r8
.L44:
	cmp.geu p6, p7 = 8, r17
	(p6) br.cond.dptk .L4
	adds r14 = 8, r16
	;;
	cmp.geu p6, p7 = 9, r17
	ld1 r9 = [r14]
	(p6) br.cond.dptk .L46
	adds r15 = 9, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 8
	;;
	or r9 = r14, r9
.L46:
	cmp.geu p6, p7 = 10, r17
	(p6) br.cond.dptk .L47
	adds r15 = 10, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 16
	;;
	or r9 = r14, r9
.L47:
	cmp.geu p6, p7 = 11, r17
	(p6) br.cond.dptk .L48
	adds r15 = 11, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 24
	;;
	or r9 = r14, r9
.L48:
	cmp.geu p6, p7 = 12, r17
	(p6) br.cond.dptk .L49
	adds r15 = 12, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 32
	;;
	or r9 = r14, r9
.L49:
	cmp.geu p6, p7 = 13, r17
	(p6) br.cond.dptk .L50
	adds r15 = 13, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 40
	;;
	or r9 = r14, r9
.L50:
	cmp.geu p6, p7 = 14, r17
	(p6) br.cond.dptk .L51
	adds r15 = 14, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 48
	;;
	or r9 = r14, r9
.L51:
	cmp.geu p6, p7 = 15, r17
	(p6) br.cond.dptk .L52
	adds r15 = 15, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 56
	;;
	or r9 = r14, r9
.L52:
	cmp.geu p6, p7 = 16, r17
	(p6) br.cond.dptk .L4
	adds r14 = 16, r16
	;;
	cmp.geu p6, p7 = 17, r17
	ld1 r10 = [r14]
	(p6) br.cond.dptk .L54
	adds r15 = 17, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 8
	;;
	or r10 = r14, r10
.L54:
	cmp.geu p6, p7 = 18, r17
	(p6) br.cond.dptk .L55
	adds r15 = 18, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 16
	;;
	or r10 = r14, r10
.L55:
	cmp.geu p6, p7 = 19, r17
	(p6) br.cond.dptk .L56
	adds r15 = 19, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 24
	;;
	or r10 = r14, r10
.L56:
	cmp.geu p6, p7 = 20, r17
	(p6) br.cond.dptk .L57
	adds r15 = 20, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 32
	;;
	or r10 = r14, r10
.L57:
	cmp.geu p6, p7 = 21, r17
	(p6) br.cond.dptk .L58
	adds r15 = 21, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 40
	;;
	or r10 = r14, r10
.L58:
	cmp.geu p6, p7 = 22, r17
	(p6) br.cond.dptk .L59
	adds r15 = 22, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 48
	;;
	or r10 = r14, r10
.L59:
	cmp.geu p6, p7 = 23, r17
	(p6) br.cond.dptk .L60
	adds r15 = 23, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 56
	;;
	or r10 = r14, r10
.L60:
	cmp.geu p6, p7 = 24, r17
	(p6) br.cond.dptk .L4
	adds r14 = 24, r16
	;;
	cmp.geu p6, p7 = 25, r17
	ld1 r11 = [r14]
	(p6) br.cond.dptk .L62
	adds r15 = 25, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 8
	;;
	or r11 = r14, r11
.L62:
	cmp.geu p6, p7 = 26, r17
	(p6) br.cond.dptk .L63
	adds r15 = 26, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 16
	;;
	or r11 = r14, r11
.L63:
	cmp.geu p6, p7 = 27, r17
	(p6) br.cond.dptk .L64
	adds r15 = 27, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 24
	;;
	or r11 = r14, r11
.L64:
	cmp.geu p6, p7 = 28, r17
	(p6) br.cond.dptk .L65
	adds r15 = 28, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 32
	;;
	or r11 = r14, r11
.L65:
	cmp.geu p6, p7 = 29, r17
	(p6) br.cond.dptk .L66
	adds r15 = 29, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 40
	;;
	or r11 = r14, r11
.L66:
	cmp.geu p6, p7 = 30, r17
	(p6) br.cond.dptk .L67
	adds r15 = 30, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 48
	;;
	or r11 = r14, r11
.L67:
	cmp.geu p6, p7 = 31, r17
	(p6) br.cond.dptk .L4
	adds r15 = 31, r16
	;;
	ld1 r14 = [r15]
	;;
	shl r14 = r14, 56
	;;
	or r11 = r14, r11
.L4:
	adds r12 = 208, r12
	mov ar.pfs = r44
	mov b0 = r43
	br.ret.sptk.many b0
	.endp __vacall#
	.ident	"GCC: (GNU) 2.9-ia64-000216 snap-000324"
