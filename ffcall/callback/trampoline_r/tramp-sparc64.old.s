! Trampoline for sparc64 CPU

! Copyright 1999 Bruno Haible, <bruno@clisp.org>
!
! This is free software distributed under the GNU General Public Licence
! described in the file COPYING. Contact the author if you don't have this
! or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
! on this software.

! Available registers: %g1, %g2, %g3.

	.global _tramp
	.proc	04
_tramp:
	call _getpc,0		! Put the address of _tramp into %o7
	 mov %o7,%g1		! But save the previous %o7 in %g1
_getpc:
	ldx [%o7+(_data-_tramp)],%g5
	ldx [%o7+(_function-_tramp)],%g2
	jmp %g2
	 mov %g1,%o7
_data:
	.long 0x73554711
	.long 0x43622155
_function:
	.long 0xbabebec0
	.long 0xdea0ffab
