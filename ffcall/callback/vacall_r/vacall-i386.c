/* vacall function for i386 CPU */

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
typedef struct { void (*vacall_function) (void*,va_alist); void* arg; } env_t;
#endif
register void*	sp	__asm__("%esp");
register void*	sret	__asm__("%ebx");
register int	iret	__asm__("%eax");
/*
 * Tell gcc to not use the call-saved registers %esi, %edi, %ebp.
 * This ensures that the return sequence does not need to restore registers
 * from the stack.
 */
register void*	dummy1	__asm__("%esi");
register void*	dummy2	__asm__("%edi");
register void*	dummy3	__asm__("%ebp");

void /* the return type is variable, not void! */
#ifdef REENTRANT
__vacall_r (env_t * env, __vaword firstword)
#else
__vacall (__vaword firstword)
#endif
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
    /* This code is EXTREMELY fragile!!                     */
    /* It depends on the register allocation chosen by gcc. */
    iret = ((__vaword *) &list.tmp._longlong)[0];
    asm volatile ("movl %0,%%edx" : : "g"(((__vaword *) &list.tmp._longlong)[1]));
  } else
  if (list.rtype == __VAfloat) {
    asm volatile ("flds %0": : "m"(list.tmp._float));
  } else
  if (list.rtype == __VAdouble) {
    asm volatile ("fldl %0": : "m"(list.tmp._double));
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
          /* This code is EXTREMELY fragile!!                     */
          /* It depends on the register allocation chosen by gcc. */
          iret = ((__vaword *) list.raddr)[0];
          asm volatile ("movl %0,%%edx" : : "g"(((__vaword *) list.raddr)[1]));
          goto done;
        }
      }
      if (!(list.flags & (__VA_NEXTGCC_STRUCT_RETURN | __VA_MSVC_STRUCT_RETURN))) {
        /* We have to pop the struct return address off the stack. */
        /* Callers compiled with -fomit-frame-pointer expect this. */
        /* Return via a "ret $4" instruction. */
        /* NOTE: This is EXTREMELY fragile. It depends on the fact that
         * no registers have to be restored from the stack. Look at the
         * assembly code!
         */
        sp = __builtin_frame_address(0);
#ifndef REENTRANT
        asm volatile ("ret $4");
#else
        /* Also pop env off the stack. */
        asm volatile ("ret $8");
#endif
        /*NOTREACHED*/
      }
      if (list.flags & __VA_MSVC_STRUCT_RETURN) {
        /* on MSVC, must put the structure address into %eax */
        iret = (long) list.raddr;
      }
      done: ;
    }
  }
  if (list.flags & __VA_STDCALL_CLEANUP) {
    /* Return, and at the same time pop the arguments off the stack. */
    /* Normally done through a "ret $n" instruction. */
    /* Be careful not to clobber %eax and %edx. Only %ecx can be used. */
    /* Use *__builtin_frame_address(0), since __builtin_return_address(0)
     * is buggy in gcc-2.7.2. */
    asm volatile ("movl %0,%%ecx" : : "g" (*(void**)__builtin_frame_address(0)));
    sp = (void*)list.aptr;
    asm volatile ("jmp *%ecx");
    /*NOTREACHED*/
  }
#ifdef REENTRANT
  /* Pop env off the stack. */
  /* Callers compiled with -fomit-frame-pointer expect this. */
  sp = __builtin_frame_address(0);
  asm volatile ("ret $4");
#endif
}
