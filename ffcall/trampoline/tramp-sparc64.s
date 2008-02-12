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
	rd %pc,%g1		! Put the address of _tramp into %g1
	ldx [%g1+(_variable-_tramp)],%g2
	ldx [%g1+(_data-_tramp)],%g3
	ldx [%g1+(_function-_tramp)],%g1
	jmp %g1
	 stx %g3,[%g2]
_variable:
	.long 0x12345678
	.long 0x13578765
_data:
	.long 0x73554711
	.long 0x43622155
_function:
	.long 0xbabebec0
	.long 0xdea0ffab
