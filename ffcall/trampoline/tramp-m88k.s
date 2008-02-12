; Trampoline for m88k CPU

; Copyright 1995 Bruno Haible, <bruno@clisp.org>
;
; This is free software distributed under the GNU General Public Licence
; described in the file COPYING. Contact the author if you don't have this
; or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
; on this software.

; Available registers: r13, r10, maybe r11.

text
	align	8
	global	tramp
;	type	tramp,#function
tramp:
	or.u	r13,r0,0x1234
	or	r13,r13,0x5678
	or.u	r10,r0,0x7355
	or	r10,r10,0x4711
	st	r10,r0,r13
	or.u	r13,r0,0xbabe
	or	r13,r13,0xbec0
	jmp	r13
.Lfe1:
;	size	tramp,.Lfe1-tramp
