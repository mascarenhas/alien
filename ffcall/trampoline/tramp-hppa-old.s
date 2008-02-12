; Trampoline for hppa CPU

; Copyright 1995 Bruno Haible, <bruno@clisp.org>
;
; This is free software distributed under the GNU General Public Licence
; described in the file COPYING. Contact the author if you don't have this
; or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
; on this software.

; Available registers: %r19, %r20, %r21, %r22.

	.SPACE $PRIVATE$
	.SUBSPA $DATA$,QUAD=1,ALIGN=8,ACCESS=31
	.SUBSPA $BSS$,QUAD=1,ALIGN=8,ACCESS=31,ZERO,SORT=82
	.SPACE $TEXT$
	.SUBSPA $LIT$,QUAD=0,ALIGN=8,ACCESS=44
	.SUBSPA $CODE$,QUAD=0,ALIGN=8,ACCESS=44,CODE_ONLY

	.SPACE $TEXT$
	.SUBSPA $CODE$

	.align 4
	.EXPORT tramp
tramp
	.PROC
	.CALLINFO
	.ENTRY
; Move <data> into <variable>
	ldil L'0x73554711,%r20
	ldil L'0x12345678,%r19
	ldo R'0x73554711(%r20),%r20
	stw %r20,R'0x12345678(%r19)
; Get <function>
	ldil L'0xbabebec0,%r21
	ldo R'0xbabebec0(%r21),%r21
; Jump to %r21, just like the gcc-2.6.3 trampoline does it:
	bb,>=,n %r21,30,tramp2	; check bit 1 of %r21
	depi 0,31,2,%r21	; if set, clear bits 1..0
	ldw 4(0,%r21),%r19	; ... dereference the function struct
	ldw 0(0,%r21),%r21	; ... to get the actual code address
tramp2
	ldsid (0,%r21),%r1
	mtsp %r1,%sr0		; set segment register
	be,n 0(%sr0,%r21)	; now do an inter-module jump
	nop
	.EXIT
	.PROCEND
