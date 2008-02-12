; Trampoline for hppa CPU

;
; Copyright 1997 Bruno Haible, <bruno@clisp.org>
;
; This is free software distributed under the GNU General Public Licence
; described in the file COPYING. Contact the author if you don't have this
; or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
; on this software.
;

	.code
	.IMPORT $global$,DATA
	.IMPORT $$dyncall,MILLICODE
	.code

	.align 4
	.EXPORT tramp,ENTRY,PRIV_LEV=3,ARGW0=GR,ARGW1=GR
	.label tramp
	.PROC
	.CALLINFO FRAME=0,NO_CALLS
	.ENTRY
; The closure pointer is already in register %r19.
; Move <variable> into register %r20.
	ldw 0(0,%r19),%r20
; Move <data> into register %r22
	ldw 4(0,%r19),%r22
; Move <address> into register %r21.
	ldw 8(0,%r19),%r21
; Store <data> into <variable>.
	stw %r22,0(0,%r20)
; Jump to %r21.
	bb,>=,n %r21,30,tramp_2
	depi 0,31,2,%r21
	ldw 4(0,%r21),%r19
	ldw 0(0,%r21),%r21
	.label tramp_2
	ldsid (0,%r21),%r1
	mtsp %r1,%sr0
	be,n 0(%sr0,%r21)
	nop
	.EXIT
	.PROCEND
