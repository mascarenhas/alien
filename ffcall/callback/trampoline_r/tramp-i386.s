/* Trampoline for i386 CPU */

/*
 * Copyright 1995-1999 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

/* Available registers: %eax, %edx, %ecx. */
/*
 * On Solaris 2.6, when the function being jumped to is an external symbol of
 * a shared library, the jump actually points to an ELF indirect jump:
 *   jmp *PTR
 * where PTR initially contains the address of some resolving routine which
 * will replace the PTR contents with the actual code address of the function
 * and then jump to the function.
 * Unfortunately, this resolving routine clobbers all three registers:
 * %eax, %edx, %ecx. Must pass the additional data via the stack.
 * A simple "pushl $<data>" is not sufficient: it causes trouble if the called
 * function is compiled with -fomit-frame-pointer.
 */
 
.globl _tramp
_tramp:
	popl %ecx
	pushl $0x73554711
	pushl %ecx
	jmp 0xbabebec0
