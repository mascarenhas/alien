/* vacall function for m68k CPU */

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
         *	env	__asm__("a0");
#endif
register void*	sret	__asm__("a1");
register int	iret	__asm__("d0");
register int	iret2	__asm__("d1");
register int	pret	__asm__("a0");	/* some compilers return pointers in a0 */
register float	fret	__asm__("d0");	/* d0 */
register double	dret	__asm__("d0");	/* d0,d1 */
register float	fp_fret	__asm__("fp0");
register double	fp_dret	__asm__("fp0");

void /* the return type is variable, not void! */
__vacall (__vaword firstword)
{
  __va_alist list;
  /* Prepare the va_alist. */
  list.flags = 0;
  list.aptr = (long)&firstword;
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
  if (list.rtype == __VAlonglong || list.rtype == __VAulonglong) {
    iret  = ((__vaword *) &list.tmp._longlong)[0];
    iret2 = ((__vaword *) &list.tmp._longlong)[1];
  } else
  if (list.rtype == __VAfloat) {
    if (list.flags & __VA_FREG_FLOAT_RETURN) {
      fp_fret = list.tmp._float;
    } else {
      if (list.flags & __VA_SUNCC_FLOAT_RETURN) {
        dret = (double)list.tmp._float;
      } else {
        fret = list.tmp._float;
      }
    }
  } else
  if (list.rtype == __VAdouble) {
    if (list.flags & __VA_FREG_FLOAT_RETURN) {
      fp_dret = list.tmp._double;
    } else {
      dret = list.tmp._double;
    }
  } else
  if (list.rtype == __VAvoidp) {
    pret = iret = (long)list.tmp._ptr;
  } else
  if (list.rtype == __VAstruct) {
    /* NB: On m68k, all structure sizes are divisible by 2. */
    if (list.flags & __VA_REGISTER_STRUCT_RETURN) {
      if (list.rsize == sizeof(char)) { /* can't occur */
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
      } else
      if (list.rsize == 2*sizeof(__vaword)) {
        iret  = ((__vaword *) list.raddr)[0];
        iret2 = ((__vaword *) list.raddr)[1];
        goto done;
      }
    }
    if (list.flags & __VA_PCC_STRUCT_RETURN) {
      /* pcc struct return convention */
      pret = iret = (long) list.raddr;
    } else {
      /* normal struct return convention */
    }
    done: ;
  }
}
