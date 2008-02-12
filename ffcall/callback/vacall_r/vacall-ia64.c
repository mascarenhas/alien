/* vacall function for ia64 CPU */

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
         *		env	__asm__("r15");
#endif
register double		farg1	__asm__("f8");
register double		farg2	__asm__("f9");
register double		farg3	__asm__("f10");
register double		farg4	__asm__("f11");
register double		farg5	__asm__("f12");
register double		farg6	__asm__("f13");
register double		farg7	__asm__("f14");
register double		farg8	__asm__("f15");
register __vaword*	sret	__asm__("r8");
register __vaword	iret	__asm__("r8");
register __vaword	iret2	__asm__("r9");
register __vaword	iret3	__asm__("r10");
register __vaword	iret4	__asm__("r11");
register float		fret	__asm__("f8");
register double		dret	__asm__("f8");

void /* the return type is variable, not void! */
__vacall (__vaword word1, __vaword word2, __vaword word3, __vaword word4,
          __vaword word5, __vaword word6, __vaword word7, __vaword word8,
          __vaword firstword)
{
  /* The default scratch area right below firstword is only 2 words, but
     we need 8 words. */
  __vaword room[6]; /* FRAGILE! */
  __va_alist list;
  /* Move the arguments passed in registers to their stack locations. */
  (&firstword)[-8] = word1;
  (&firstword)[-7] = word2;
  (&firstword)[-6] = word3;
  (&firstword)[-5] = word4;
  (&firstword)[-4] = word5;
  (&firstword)[-3] = word6;
  (&firstword)[-2] = word7;
  (&firstword)[-1] = word8;
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
  list.aptr = (long)(&firstword - 8);
  list.saptr = &firstword - 8;
  list.memfargptr = &list.farg[0];
  list.raddr = (void*)0;
  list.rtype = __VAvoid;
  list.structraddr = sret;
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
        /* Return structs of size <= 32 in registers. */
        if (list.rsize > 0 && list.rsize <= 32) {
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
            if (list.rsize >= 17) {
              iret3 = (__vaword)((unsigned char *) list.raddr)[16];
              if (list.rsize >= 18)
                iret3 |= (__vaword)((unsigned char *) list.raddr)[17] << 8;
              if (list.rsize >= 19)
                iret3 |= (__vaword)((unsigned char *) list.raddr)[18] << 16;
              if (list.rsize >= 20)
                iret3 |= (__vaword)((unsigned char *) list.raddr)[19] << 24;
              if (list.rsize >= 21)
                iret3 |= (__vaword)((unsigned char *) list.raddr)[20] << 32;
              if (list.rsize >= 22)
                iret3 |= (__vaword)((unsigned char *) list.raddr)[21] << 40;
              if (list.rsize >= 23)
                iret3 |= (__vaword)((unsigned char *) list.raddr)[22] << 48;
              if (list.rsize >= 24)
                iret3 |= (__vaword)((unsigned char *) list.raddr)[23] << 56;
              if (list.rsize >= 25) {
                iret4 = (__vaword)((unsigned char *) list.raddr)[24];
                if (list.rsize >= 26)
                  iret4 |= (__vaword)((unsigned char *) list.raddr)[25] << 8;
                if (list.rsize >= 27)
                  iret4 |= (__vaword)((unsigned char *) list.raddr)[26] << 16;
                if (list.rsize >= 28)
                  iret4 |= (__vaword)((unsigned char *) list.raddr)[27] << 24;
                if (list.rsize >= 29)
                  iret4 |= (__vaword)((unsigned char *) list.raddr)[28] << 32;
                if (list.rsize >= 30)
                  iret4 |= (__vaword)((unsigned char *) list.raddr)[29] << 40;
                if (list.rsize >= 31)
                  iret4 |= (__vaword)((unsigned char *) list.raddr)[30] << 48;
                if (list.rsize >= 32)
                  iret4 |= (__vaword)((unsigned char *) list.raddr)[31] << 56;
              }
            }
          }
        }
      }
    }
  }
}
