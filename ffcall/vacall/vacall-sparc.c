/* vacall function for sparc CPU */

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
         *	env	__asm__("%g2");
#endif
register __vaword* fp	__asm__("%fp");	/* our %fp, caller's %sp */
register __vaword* ret	__asm__("%i7");	/* %i7+8 = return address */
register int	iret	__asm__("%i0");
register int	iret2	__asm__("%i1");
register float	fret	__asm__("%f0");	/* %f0 */
register double	dret	__asm__("%f0");	/* %f0,%f1 */

void /* the return type is variable, not void! */
__vacall (__vaword word1, __vaword word2, __vaword word3, __vaword word4,
          __vaword word5, __vaword word6,
          __vaword firstword)
{
  __va_alist list;
  /* gcc-2.6.3 source says: When a parameter is passed in a register,
   * stack space is still allocated for it.
   */
  /* Move the arguments passed in registers to their stack locations. */
  (&firstword)[-6] = word1;
  (&firstword)[-5] = word2;
  (&firstword)[-4] = word3;
  (&firstword)[-3] = word4;
  (&firstword)[-2] = word5;
  (&firstword)[-1] = word6;
  /* Prepare the va_alist. */
  list.flags = 0;
  list.aptr = (long)(&firstword - 6);
  list.raddr = (void*)0;
  list.rtype = __VAvoid;
  list.structraddr = (void*)((&firstword)[-7]); /* = (void*) fp[16] */
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
  if (list.rtype == __VAlonglong || list.rtype == __VAulonglong) {
    iret  = ((__vaword *) &list.tmp._longlong)[0];
    iret2 = ((__vaword *) &list.tmp._longlong)[1];
  } else
  if (list.rtype == __VAfloat) {
    if (list.flags & __VA_SUNCC_FLOAT_RETURN) {
      dret = (double)list.tmp._float;
    } else {
      fret = list.tmp._float;
    }
  } else
  if (list.rtype == __VAdouble) {
    dret = list.tmp._double;
  } else
  if (list.rtype == __VAvoidp) {
    iret = (long)list.tmp._ptr;
  } else
  if (list.rtype == __VAstruct) {
    if (list.flags & (__VA_SUNCC_STRUCT_RETURN | __VA_SUNPROCC_STRUCT_RETURN)) {
      /* Sun cc struct return convention. */
      /* The desired struct return address was passed in fp[16], later on
       * list.raddr = list.structraddr = fp[16]. Now the result has
       * already been copied there. No need to copy the result once more.
       * The caller expects to receive the struct return address in %o0.
       */
      iret = (long) list.raddr;
      if ((list.rsize & 0xfff) == ret[2])
        ret++; /* skip the "unimp n" instruction at the return address */
        /* else the "unimp n" instruction will cause a core dump */
    } else {
      if (list.flags & __VA_PCC_STRUCT_RETURN) {
        /* pcc struct return convention */
        iret = (long) list.raddr;
      } else {
        /* normal struct return convention */
        if (list.flags & __VA_SMALL_STRUCT_RETURN) {
          if (list.rsize == sizeof(char)) {
            iret = *(unsigned char *) list.raddr;
            goto done;
          } else
          if (list.rsize == sizeof(short)) {
            iret = *(unsigned short *) list.raddr;
            goto done;
          } else
          if (list.rsize == sizeof(int)) {
            iret = *(unsigned int *) list.raddr;
            goto done;
          }
        }
        ret++; /* skip the "unimp n" instruction at the return address */
        done: ;
      }
    }
  }
}
