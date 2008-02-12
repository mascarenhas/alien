| Trampoline for m68k CPU

| Copyright 1995 Bruno Haible, <bruno@clisp.org>
|
| This is free software distributed under the GNU General Public Licence
| described in the file COPYING. Contact the author if you don't have this
| or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
| on this software.

| Available registers: d0, d1, a0, a1.

.globl _tramp
_tramp:
	movel #0x73554711,0x12345678
	jmp 0xbabebec0
	nop
