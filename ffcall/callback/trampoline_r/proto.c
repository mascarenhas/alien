/* Sample prototype for a trampoline. */

/*
 * Copyright 1995-1998 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

#define function  (int (*) ()) 0xbabebec0
#define data      (void*)      0x73554711

#ifdef __i386__
register void* env __asm__("%ecx");
#endif
#ifdef __m68k__
register void* env __asm__("a0");
#endif
#if defined(__mips__) || defined(__mipsn32__) || defined(__mips64__)
register void* env __asm__("$2");
#endif
#ifdef __sparc__
register void* env __asm__("%g2");
#endif
#ifdef __alpha__
register void* env __asm__("$1");
#endif
#ifdef __hppa__
register void* env __asm__("%r29");
#endif
#ifdef __arm__
register void* env __asm__("r12");
#endif
#ifdef __rs6000__
register void* env __asm__("r11");
#endif
#ifdef __m88k__
register void* env __asm__("r11");
#endif
#ifdef __convex__
register void* env __asm__("s0");
#endif
#ifdef __s390__
register void* env __asm__("r0");
#endif

int tramp ()
{ env = data;
  return (*function)();
}

#ifdef __i386__
int tramp2 ()
{ return (*function)(data); }
#endif

int jump ()
{ goto *function; }

