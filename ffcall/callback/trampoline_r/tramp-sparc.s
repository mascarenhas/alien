! Trampoline for sparc CPU

! Copyright 1995-1997 Bruno Haible, <bruno@clisp.org>
!
! This is free software distributed under the GNU General Public Licence
! described in the file COPYING. Contact the author if you don't have this
! or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
! on this software.

! Available registers: %g1, %g2, %g3.

	.global _tramp
	.proc	04
_tramp:
	sethi %hi(0x73554711),%g2
	sethi %hi(0xbabebec0),%g1
	jmp %g1+%lo(0xbabebec0)
	or %g2,%lo(0x73554711),%g2
