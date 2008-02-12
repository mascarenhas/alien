/* vacall function for mips CPU */

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

#ifndef REENTRANT
typedef void (*func_pointer)(va_alist);
#else /* REENTRANT */
#define __vacall __vacall_r
typedef void (*func_pointer)(void*,va_alist);
register struct { func_pointer vacall_function; void* arg; }
         *		env	__asm__("$2");
#endif
register func_pointer	t9	__asm__("$25");
register void*		sp	__asm__("$sp");
register __vaword	iarg0	__asm__("$4");
register __vaword	iarg1	__asm__("$5");
register __vaword	iarg2	__asm__("$6");
register __vaword	iarg3	__asm__("$7");
register __vaword	iarg4	__asm__("$8");
register __vaword	iarg5	__asm__("$9");
register __vaword	iarg6	__asm__("$10");
register __vaword	iarg7	__asm__("$11");
register float		farg0	__asm__("$f12");
register float		farg1	__asm__("$f13");
register float		farg2	__asm__("$f14");
register float		farg3	__asm__("$f15");
register float		farg4	__asm__("$f16");
register float		farg5	__asm__("$f17");
register float		farg6	__asm__("$f18");
register float		farg7	__asm__("$f19");
register double		darg0	__asm__("$f12");
register double		darg1	__asm__("$f13");
register double		darg2	__asm__("$f14");
register double		darg3	__asm__("$f15");
register double		darg4	__asm__("$f16");
register double		darg5	__asm__("$f17");
register double		darg6	__asm__("$f18");
register double		darg7	__asm__("$f19");
register __vaword	iret	__asm__("$2");
register __vaword	iret2	__asm__("$3");
register float		fret	__asm__("$f0");
register float		fret2	__asm__("$f2");
register double		dret	__asm__("$f0");
register double		dret2	__asm__("$f2");

void /* the return type is variable, not void! */
__vacall (__vaword word1, __vaword word2, __vaword word3, __vaword word4,
          __vaword word5, __vaword word6, __vaword word7, __vaword word8,
          __vaword firstword)
{
  /* gcc-2.95 does not allocate stack space for word1,...,word8. */
  /* The following account for the stack frame increase from 192 to 256 bytes
   * done by postprocessing. */
#define firstword (*(&firstword+8))
  /* Move the arguments passed in registers to their stack locations. */
  (&firstword)[-8] = iarg0; /* word1 */
  (&firstword)[-7] = iarg1; /* word2 */
  (&firstword)[-6] = iarg2; /* word3 */
  (&firstword)[-5] = iarg3; /* word4 */
  (&firstword)[-4] = iarg4; /* word5 */
  (&firstword)[-3] = iarg5; /* word6 */
  (&firstword)[-2] = iarg6; /* word7 */
  (&firstword)[-1] = iarg7; /* word8 */
 {__va_alist list;
  list.darg[0] = darg0;
  list.darg[1] = darg1;
  list.darg[2] = darg2;
  list.darg[3] = darg3;
  list.darg[4] = darg4;
  list.darg[5] = darg5;
  list.darg[6] = darg6;
  list.darg[7] = darg7;
  list.farg[0] = farg0;
  list.farg[1] = farg1;
  list.farg[2] = farg2;
  list.farg[3] = farg3;
  list.farg[4] = farg4;
  list.farg[5] = farg5;
  list.farg[6] = farg6;
  list.farg[7] = farg7;
  /* Prepare the va_alist. */
  list.flags = 0;
  list.aptr = (long)(&firstword - 8);
  list.raddr = (void*)0;
  list.rtype = __VAvoid;
  list.memargptr = (long)&firstword;
  list.anum = 0;
  /* Call vacall_function. The macros do all the rest. */
#ifndef REENTRANT
  (*(t9 = vacall_function)) (&list);
#else /* REENTRANT */
  (*(t9 = env->vacall_function)) (env->arg,&list);
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
    iret = list.tmp._longlong;
  } else
  if (list.rtype == __VAulonglong) {
    iret = list.tmp._ulonglong;
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
      iret = (__vaword) list.raddr;
    } else {
      /* normal struct return convention */
      if (list.flags & __VA_REGISTER_STRUCT_RETURN) {
        if (list.flags & __VA_GCC_STRUCT_RETURN) {
          /* gcc returns structs of size 1,2,4,8 in registers. */
          if (list.rsize == sizeof(char)) {
            iret = *(unsigned char *) list.raddr;
          } else
          if (list.rsize == sizeof(short)) {
            iret = *(unsigned short *) list.raddr;
          } else
          if (list.rsize == sizeof(int)) {
            iret = *(unsigned int *) list.raddr;
          } else
          if (list.rsize == sizeof(long long)) {
            iret = *(unsigned long long *) list.raddr;
          }
        } else {
          /* cc returns structs of size <= 16 in registers. */
          /* Maybe this big if cascade could be replaced with
           * if (list.rsize > 0 && list.rsize <= 16)
           *   __asm__ ("ldl $2,%0 ; ldr $2,%1"
           *            : : "m" (((unsigned char *) list.raddr)[0]),
           *                "m" (((unsigned char *) list.raddr)[7]));
           */
          if (list.rsize > 0 && list.rsize <= 16) {
            if (list.rsize == 1) {
              iret =   (__vaword)((unsigned char *) list.raddr)[0] << 56;
            } else
            if (list.rsize == 2) {
              iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
                    | ((__vaword)((unsigned char *) list.raddr)[1] << 48);
            } else
            if (list.rsize == 3) {
              iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
                    | ((__vaword)((unsigned char *) list.raddr)[1] << 48)
                    | ((__vaword)((unsigned char *) list.raddr)[2] << 40);
            } else
            if (list.rsize == 4) {
              iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
                    | ((__vaword)((unsigned char *) list.raddr)[1] << 48)
                    | ((__vaword)((unsigned char *) list.raddr)[2] << 40)
                    | ((__vaword)((unsigned char *) list.raddr)[3] << 32);
            } else
            if (list.rsize == 5) {
              iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
                    | ((__vaword)((unsigned char *) list.raddr)[1] << 48)
                    | ((__vaword)((unsigned char *) list.raddr)[2] << 40)
                    | ((__vaword)((unsigned char *) list.raddr)[3] << 32)
                    | ((__vaword)((unsigned char *) list.raddr)[4] << 24);
            } else
            if (list.rsize == 6) {
              iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
                    | ((__vaword)((unsigned char *) list.raddr)[1] << 48)
                    | ((__vaword)((unsigned char *) list.raddr)[2] << 40)
                    | ((__vaword)((unsigned char *) list.raddr)[3] << 32)
                    | ((__vaword)((unsigned char *) list.raddr)[4] << 24)
                    | ((__vaword)((unsigned char *) list.raddr)[5] << 16);
            } else
            if (list.rsize == 7) {
              iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
                    | ((__vaword)((unsigned char *) list.raddr)[1] << 48)
                    | ((__vaword)((unsigned char *) list.raddr)[2] << 40)
                    | ((__vaword)((unsigned char *) list.raddr)[3] << 32)
                    | ((__vaword)((unsigned char *) list.raddr)[4] << 24)
                    | ((__vaword)((unsigned char *) list.raddr)[5] << 16)
                    | ((__vaword)((unsigned char *) list.raddr)[6] << 8);
            } else
            if (list.rsize >= 8 && list.rsize <= 16) {
              iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
                    | ((__vaword)((unsigned char *) list.raddr)[1] << 48)
                    | ((__vaword)((unsigned char *) list.raddr)[2] << 40)
                    | ((__vaword)((unsigned char *) list.raddr)[3] << 32)
                    | ((__vaword)((unsigned char *) list.raddr)[4] << 24)
                    | ((__vaword)((unsigned char *) list.raddr)[5] << 16)
                    | ((__vaword)((unsigned char *) list.raddr)[6] << 8)
                    |  (__vaword)((unsigned char *) list.raddr)[7];
              /* Maybe this big if cascade could be replaced with
               * if (list.rsize > 8 && list.rsize <= 16)
               *   __asm__ ("ldl $3,%0 ; ldr $3,%1"
               *            : : "m" (((unsigned char *) list.raddr)[8]),
               *                "m" (((unsigned char *) list.raddr)[15]));
               */
              if (list.rsize == 8) {
              } else
              if (list.rsize == 9) {
                iret2 =   (__vaword)((unsigned char *) list.raddr)[8] << 56;
              } else
              if (list.rsize == 10) {
                iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                       | ((__vaword)((unsigned char *) list.raddr)[9] << 48);
              } else
              if (list.rsize == 11) {
                iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                       | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                       | ((__vaword)((unsigned char *) list.raddr)[10] << 40);
              } else
              if (list.rsize == 12) {
                iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                       | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                       | ((__vaword)((unsigned char *) list.raddr)[10] << 40)
                       | ((__vaword)((unsigned char *) list.raddr)[11] << 32);
              } else
              if (list.rsize == 13) {
                iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                       | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                       | ((__vaword)((unsigned char *) list.raddr)[10] << 40)
                       | ((__vaword)((unsigned char *) list.raddr)[11] << 32)
                       | ((__vaword)((unsigned char *) list.raddr)[12] << 24);
              } else
              if (list.rsize == 14) {
                iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                       | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                       | ((__vaword)((unsigned char *) list.raddr)[10] << 40)
                       | ((__vaword)((unsigned char *) list.raddr)[11] << 32)
                       | ((__vaword)((unsigned char *) list.raddr)[12] << 24)
                       | ((__vaword)((unsigned char *) list.raddr)[13] << 16);
              } else
              if (list.rsize == 15) {
                iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                       | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                       | ((__vaword)((unsigned char *) list.raddr)[10] << 40)
                       | ((__vaword)((unsigned char *) list.raddr)[11] << 32)
                       | ((__vaword)((unsigned char *) list.raddr)[12] << 24)
                       | ((__vaword)((unsigned char *) list.raddr)[13] << 16)
                       | ((__vaword)((unsigned char *) list.raddr)[14] << 8);
              } else
              if (list.rsize == 16) {
                iret2 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                       | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                       | ((__vaword)((unsigned char *) list.raddr)[10] << 40)
                       | ((__vaword)((unsigned char *) list.raddr)[11] << 32)
                       | ((__vaword)((unsigned char *) list.raddr)[12] << 24)
                       | ((__vaword)((unsigned char *) list.raddr)[13] << 16)
                       | ((__vaword)((unsigned char *) list.raddr)[14] << 8)
                       |  (__vaword)((unsigned char *) list.raddr)[15];
              }
            }
          }
          if (list.flags & __VA_REGISTER_FLOATSTRUCT_RETURN) {
            if (list.rsize == sizeof(float)) {
              fret = *(float*)list.raddr;
            } else
            if (list.rsize == 2*sizeof(float)) {
              fret = *(float*)list.raddr;
              fret2 = *(float*)((char*)list.raddr + 4);
            }
          }
          if (list.flags & __VA_REGISTER_DOUBLESTRUCT_RETURN) {
            if (list.rsize == sizeof(double)) {
              dret = *(double*)list.raddr;
            } else
            if (list.rsize == 2*sizeof(double)) {
              dret = *(double*)list.raddr;
              dret2 = *(double*)((char*)list.raddr + 8);
            }
          }
        }
      }
    }
  }
}}
