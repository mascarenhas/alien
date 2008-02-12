/* vacall function for x86_64 CPU */

/*
 * Copyright 1995-2004 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

#ifndef REENTRANT
#include "vacall.h.in"
#else /* REENTRANT */
#include "vacall_r.h.in"
#endif

#ifdef REENTRANT
#define __vacall __vacall_r
register struct { void (*vacall_function) (void*,va_alist); void* arg; }
         *		env	__asm__("r10");
#endif

register __vaword iarg1 __asm__("rdi");
register __vaword iarg2 __asm__("rsi");
register __vaword iarg3 __asm__("rdx");
register __vaword iarg4 __asm__("rcx");
register __vaword iarg5 __asm__("r8");
register __vaword iarg6 __asm__("r9");

register double farg1 __asm__("xmm0");
register double farg2 __asm__("xmm1");
register double farg3 __asm__("xmm2");
register double farg4 __asm__("xmm3");
register double farg5 __asm__("xmm4");
register double farg6 __asm__("xmm5");
register double farg7 __asm__("xmm6");
register double farg8 __asm__("xmm7");

register __vaword iret  __asm__("rax");
register __vaword iret2 __asm__("rdx");
register float  fret __asm__("xmm0");
register double dret __asm__("xmm0");

/*
 * Tell gcc to not use the call-saved registers %rbx, %rbp.
 * This ensures that the return sequence does not need to restore registers
 * from the stack.
 */
register void*	dummy1	__asm__("%rbx");
register void*	dummy2	__asm__("%rbp");

void /* the return type is variable, not void! */
__vacall (__vaword word1, __vaword word2, __vaword word3, __vaword word4,
          __vaword word5, __vaword word6,
          __vaword firstword)
{
  __va_alist list;
  /* Move the arguments passed in registers to temp storage. */
  list.iarg[0] = iarg1;
  list.iarg[1] = iarg2;
  list.iarg[2] = iarg3;
  list.iarg[3] = iarg4;
  list.iarg[4] = iarg5;
  list.iarg[5] = iarg6;
  list.farg[0] = farg1;
  list.farg[1] = farg2;
  list.farg[2] = farg3;
  list.farg[3] = farg4;
  list.farg[4] = farg5;
  list.farg[5] = farg6;
  list.farg[6] = farg7;
  list.farg[7] = farg8;
  /* Prepare the va_alist. */
  list.flags = 0;
  list.aptr = (long)&firstword;
  list.raddr = (void*)0;
  list.rtype = __VAvoid;
  list.memiargptr = &list.iarg[0];
  list.memfargptr = &list.farg[0];
  /* Call vacall_function. The macros do all the rest. */
#ifndef REENTRANT
  (*vacall_function) (&list);
#else /* REENTRANT */
  (*env->vacall_function) (env->arg,&list);
#endif
  /* Put return value into proper register. */
  if (list.rtype == __VAvoid) {
  } else
  if (list.rtype == __VAchar) {
    iret = list.tmp._char;
  } else
  if (list.rtype == __VAschar) {
    iret = list.tmp._schar;
  } else
  if (list.rtype == __VAuchar) {
    iret = list.tmp._uchar;
  } else
  if (list.rtype == __VAshort) {
    iret = list.tmp._short;
  } else
  if (list.rtype == __VAushort) {
    iret = list.tmp._ushort;
  } else
  if (list.rtype == __VAint) {
    iret = list.tmp._int;
  } else
  if (list.rtype == __VAuint) {
    iret = list.tmp._uint;
  } else
  if (list.rtype == __VAlong) {
    iret = list.tmp._long;
  } else
  if (list.rtype == __VAulong) {
    iret = list.tmp._ulong;
  } else
  if (list.rtype == __VAlonglong) {
    iret = list.tmp._long;
  } else
  if (list.rtype == __VAulonglong) {
    iret = list.tmp._ulong;
  } else
  if (list.rtype == __VAfloat) {
    fret = list.tmp._float;
  } else
  if (list.rtype == __VAdouble) {
    dret = list.tmp._double;
  } else
  if (list.rtype == __VAvoidp) {
    iret = (long)list.tmp._ptr;
  } else
  if (list.rtype == __VAstruct) {
    if (list.flags & __VA_PCC_STRUCT_RETURN) {
      /* pcc struct return convention */
      iret = (long) list.raddr;
    } else {
      /* normal struct return convention */
      if (list.flags & __VA_REGISTER_STRUCT_RETURN) {
        /* Return structs of size <= 16 in registers. */
        if (list.rsize > 0 && list.rsize <= 16) {
          iret = (__vaword)((unsigned char *) list.raddr)[0];
          if (list.rsize >= 2)
            iret |= (__vaword)((unsigned char *) list.raddr)[1] << 8;
          if (list.rsize >= 3)
            iret |= (__vaword)((unsigned char *) list.raddr)[2] << 16;
          if (list.rsize >= 4)
            iret |= (__vaword)((unsigned char *) list.raddr)[3] << 24;
          if (list.rsize >= 5)
            iret |= (__vaword)((unsigned char *) list.raddr)[4] << 32;
          if (list.rsize >= 6)
            iret |= (__vaword)((unsigned char *) list.raddr)[5] << 40;
          if (list.rsize >= 7)
            iret |= (__vaword)((unsigned char *) list.raddr)[6] << 48;
          if (list.rsize >= 8)
            iret |= (__vaword)((unsigned char *) list.raddr)[7] << 56;
          if (list.rsize >= 9) {
            iret2 = (__vaword)((unsigned char *) list.raddr)[8];
            if (list.rsize >= 10)
              iret2 |= (__vaword)((unsigned char *) list.raddr)[9] << 8;
            if (list.rsize >= 11)
              iret2 |= (__vaword)((unsigned char *) list.raddr)[10] << 16;
            if (list.rsize >= 12)
              iret2 |= (__vaword)((unsigned char *) list.raddr)[11] << 24;
            if (list.rsize >= 13)
              iret2 |= (__vaword)((unsigned char *) list.raddr)[12] << 32;
            if (list.rsize >= 14)
              iret2 |= (__vaword)((unsigned char *) list.raddr)[13] << 40;
            if (list.rsize >= 15)
              iret2 |= (__vaword)((unsigned char *) list.raddr)[14] << 48;
            if (list.rsize >= 16)
              iret2 |= (__vaword)((unsigned char *) list.raddr)[15] << 56;
          }
        }
      }
    }
  }
}
