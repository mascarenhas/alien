/* Sample prototype for a trampoline. */

/*
 * Copyright 1995-1999, 2001, 2004 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

#define function  (int (*) ()) 0xbabebec0dea0ffabL
#define data      (void*)      0x7355471143622155L

#ifdef __mips64__
register void* env __asm__("$2");
#endif
#ifdef __sparc64__
register void* env __asm__("%g5");
#endif
#ifdef __alpha__
register void* env __asm__("$1");
#endif
#ifdef __ia64__
register void* env __asm__("r15");
#endif
#ifdef __x86_64__
register void* env __asm__("r10");
#endif

int tramp ()
{ env = data;
  return (*function)();
}

int jump ()
{ goto *function; }

