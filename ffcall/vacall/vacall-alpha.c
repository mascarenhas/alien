/* vacall function for alpha CPU */

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
         *		env	__asm__("$1");
#endif
register long		arg1	__asm__("$16");
register long		arg2	__asm__("$17");
register long		arg3	__asm__("$18");
register long		arg4	__asm__("$19");
register long		arg5	__asm__("$20");
register long		arg6	__asm__("$21");
register double		farg1	__asm__("$f16");
register double		farg2	__asm__("$f17");
register double		farg3	__asm__("$f18");
register double		farg4	__asm__("$f19");
register double		farg5	__asm__("$f20");
register double		farg6	__asm__("$f21");
register __vaword	iret	__asm__("$0");
register __vaword	iret2	__asm__("$1");
register float		fret	__asm__("$f0");
register double		dret	__asm__("$f0");

void /* the return type is variable, not void! */
__vacall (__vaword word1, __vaword word2, __vaword word3, __vaword word4,
          __vaword word5, __vaword word6,
          __vaword firstword)
{
  __va_alist list;
  struct { double farg1, farg2, farg3, farg4, farg5, farg6;
           long arg1, arg2, arg3, arg4, arg5, arg6;
         }
    args;
  /* MAGIC ALERT! This is the last struct on the stack, so that
   * &args + 1 == &firstword. Look at the assembly code to convince yourself.
   */
  /* Move the arguments passed in registers to their stack locations. */
  /* args.arg1 = */ (&firstword)[-6] = word1;
  /* args.arg2 = */ (&firstword)[-5] = word2;
  /* args.arg3 = */ (&firstword)[-4] = word3;
  /* args.arg4 = */ (&firstword)[-3] = word4;
  /* args.arg5 = */ (&firstword)[-2] = word5;
  /* args.arg6 = */ (&firstword)[-1] = word6;
  args.farg1 = farg1;
  args.farg2 = farg2;
  args.farg3 = farg3;
  args.farg4 = farg4;
  args.farg5 = farg5;
  args.farg6 = farg6;
  /* Prepare the va_alist. */
  list.flags = 0;
  list.aptr = (long)(&firstword - 6);
  list.raddr = (void*)0;
  list.rtype = __VAvoid;
  list.memargptr = (long)&firstword;
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
        if (list.rsize == sizeof(char)) {
          iret = *(unsigned char *) list.raddr;
        } else
        if (list.rsize == sizeof(short)) {
          iret = *(unsigned short *) list.raddr;
        } else
        if (list.rsize == sizeof(int)) {
          iret = *(unsigned int *) list.raddr;
        } else
        if (list.rsize == sizeof(long)) {
          iret = *(unsigned long *) list.raddr;
        } else
        if (list.rsize == 2*sizeof(__vaword)) {
          iret  = ((__vaword *) list.raddr)[0];
          iret2 = ((__vaword *) list.raddr)[1];
        }
      }
    }
  }
}
