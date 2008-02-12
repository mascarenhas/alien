/* vacall function for S/390 CPU */

/*
 * Copyright 1995-2004 Bruno Haible, <bruno@clisp.org>
 * Copyright 2000 Adam Fedor, <fedor@gnu.org>
 * Copyright 2001 Gerhard Tonn, <gt@debian.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

#ifndef REENTRANT
#include "vacall.h.in"
#else /* REENTRANT */
#include "vacall_r.h"
#endif

#ifdef REENTRANT
#define __vacall __vacall_r
register struct { void (*vacall_function) (void*,va_alist); void* arg; }
         *		env	__asm__("r0");
#endif
register float 		farg1	__asm__("f0");
register float		farg2	__asm__("f2");
register double		darg1	__asm__("f0");
register double		darg2	__asm__("f2");
register __vaword	iret	__asm__("%r2");
register __vaword	iret2	__asm__("%r3");
register float		fret	__asm__("%f0");
register double		dret	__asm__("%f0");

void /* the return type is variable, not void! */
__vacall (__vaword word1, __vaword word2, __vaword word3, __vaword word4,
          __vaword word5,
          __vaword firstword)
{
  __va_alist list;
  /* Move the arguments passed in registers to temp storage, since
     moving them to the stack would mess up the stack */
  list.regarg[0] = word1;
  list.regarg[1] = word2;
  list.regarg[2] = word3;
  list.regarg[3] = word4;
  list.regarg[4] = word5;

  list.darg[1] = darg2;
  list.darg[0] = darg1;

  list.farg[1] = farg2;
  list.farg[0] = farg1;

  /* Prepare the va_alist. */
  list.flags = 0;
  list.aptr = (long)(&list.regarg[0]);
  list.saptr = (long)(&firstword);
  list.onstack = 0;
  list.raddr = (void*)0;
  list.rtype = __VAvoid;
  list.memfargptr = &list.farg[0];
  list.memdargptr = &list.darg[0];
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
        if (list.rsize == sizeof(char)) {
          iret = *(unsigned char *) list.raddr;
        } else
        if (list.rsize == sizeof(short)) {
          iret = *(unsigned short *) list.raddr;
        } else
        if (list.rsize == sizeof(int)) {
          iret = *(unsigned int *) list.raddr;
        } else
        if (list.rsize == 2*sizeof(__vaword)) {
          iret  = ((__vaword *) list.raddr)[0];
          iret2 = ((__vaword *) list.raddr)[1];
        }
      }
    }
  }
}
