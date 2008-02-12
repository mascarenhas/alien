/* vacall function for sparc64 CPU */

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
         *	env	__asm__("%g5");
#endif
register __vaword* fp	__asm__("%fp");	/* our %fp, caller's %sp */
register __vaword* ret	__asm__("%i7");	/* %i7+8 = return address */
register float	farg0	__asm__("%f1");
register float	farg1	__asm__("%f3");
register float	farg2	__asm__("%f5");
register float	farg3	__asm__("%f7");
register float	farg4	__asm__("%f9");
register float	farg5	__asm__("%f11");
register float	farg6	__asm__("%f13");
register float	farg7	__asm__("%f15");
register float	farg8	__asm__("%f17");
register float	farg9	__asm__("%f19");
register float	farg10	__asm__("%f21");
register float	farg11	__asm__("%f23");
register float	farg12	__asm__("%f25");
register float	farg13	__asm__("%f27");
register float	farg14	__asm__("%f29");
register float	farg15	__asm__("%f31");
register double	darg0	__asm__("%f0");
register double	darg1	__asm__("%f2");
register double	darg2	__asm__("%f4");
register double	darg3	__asm__("%f6");
register double	darg4	__asm__("%f8");
register double	darg5	__asm__("%f10");
register double	darg6	__asm__("%f12");
register double	darg7	__asm__("%f14");
register double	darg8	__asm__("%f16");
register double	darg9	__asm__("%f18");
register double	darg10	__asm__("%f20");
register double	darg11	__asm__("%f22");
register double	darg12	__asm__("%f24");
register double	darg13	__asm__("%f26");
register double	darg14	__asm__("%f28");
register double	darg15	__asm__("%f30");
register __vaword iret	__asm__("%i0");
register __vaword o1	__asm__("%i1");
register __vaword o2	__asm__("%i2");
register __vaword o3	__asm__("%i3");
register __vaword o4	__asm__("%i4");
register __vaword o5	__asm__("%i5");
register float	fret	__asm__("%f0");	/* %f0 */
register double	dret	__asm__("%f0");	/* %f0,%f1 */

void /* the return type is variable, not void! */
__vacall (__vaword word1, __vaword word2, __vaword word3, __vaword word4,
          __vaword word5, __vaword word6,
          __vaword firstword)
{
  __va_alist list;
  /* Move the arguments passed in registers to their stack locations. */
  (&firstword)[-6] = word1;
  (&firstword)[-5] = word2;
  (&firstword)[-4] = word3;
  (&firstword)[-3] = word4;
  (&firstword)[-2] = word5;
  (&firstword)[-1] = word6;
  list.darg[0] = darg0;
  list.darg[1] = darg1;
  list.darg[2] = darg2;
  list.darg[3] = darg3;
  list.darg[4] = darg4;
  list.darg[5] = darg5;
  list.darg[6] = darg6;
  list.darg[7] = darg7;
  list.darg[8] = darg8;
  list.darg[9] = darg9;
  list.darg[10] = darg10;
  list.darg[11] = darg11;
  list.darg[12] = darg12;
  list.darg[13] = darg13;
  list.darg[14] = darg14;
  list.darg[15] = darg15;
  list.farg[0] = farg0;
  list.farg[1] = farg1;
  list.farg[2] = farg2;
  list.farg[3] = farg3;
  list.farg[4] = farg4;
  list.farg[5] = farg5;
  list.farg[6] = farg6;
  list.farg[7] = farg7;
  list.farg[8] = farg8;
  list.farg[9] = farg9;
  list.farg[10] = farg10;
  list.farg[11] = farg11;
  list.farg[12] = farg12;
  list.farg[13] = farg13;
  list.farg[14] = farg14;
  list.farg[15] = farg15;
  /* Prepare the va_alist. */
  list.flags = 0;
  list.aptr = (long)(&firstword - 6);
  list.raddr = (void*)0;
  list.rtype = __VAvoid;
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
          if (list.rsize >= 8 && list.rsize <= 32) {
            iret =  ((__vaword)((unsigned char *) list.raddr)[0] << 56)
                  | ((__vaword)((unsigned char *) list.raddr)[1] << 48)
                  | ((__vaword)((unsigned char *) list.raddr)[2] << 40)
                  | ((__vaword)((unsigned char *) list.raddr)[3] << 32)
                  | ((__vaword)((unsigned char *) list.raddr)[4] << 24)
                  | ((__vaword)((unsigned char *) list.raddr)[5] << 16)
                  | ((__vaword)((unsigned char *) list.raddr)[6] << 8)
                  |  (__vaword)((unsigned char *) list.raddr)[7];
            if (list.rsize == 8) {
            } else
            if (list.rsize == 9) {
              o1 =   (__vaword)((unsigned char *) list.raddr)[8] << 56;
            } else
            if (list.rsize == 10) {
              o1 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                  | ((__vaword)((unsigned char *) list.raddr)[9] << 48);
            } else
            if (list.rsize == 11) {
              o1 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                  | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                  | ((__vaword)((unsigned char *) list.raddr)[10] << 40);
            } else
            if (list.rsize == 12) {
              o1 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                  | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                  | ((__vaword)((unsigned char *) list.raddr)[10] << 40)
                  | ((__vaword)((unsigned char *) list.raddr)[11] << 32);
            } else
            if (list.rsize == 13) {
              o1 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                  | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                  | ((__vaword)((unsigned char *) list.raddr)[10] << 40)
                  | ((__vaword)((unsigned char *) list.raddr)[11] << 32)
                  | ((__vaword)((unsigned char *) list.raddr)[12] << 24);
            } else
            if (list.rsize == 14) {
              o1 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                  | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                  | ((__vaword)((unsigned char *) list.raddr)[10] << 40)
                  | ((__vaword)((unsigned char *) list.raddr)[11] << 32)
                  | ((__vaword)((unsigned char *) list.raddr)[12] << 24)
                  | ((__vaword)((unsigned char *) list.raddr)[13] << 16);
            } else
            if (list.rsize == 15) {
              o1 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                  | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                  | ((__vaword)((unsigned char *) list.raddr)[10] << 40)
                  | ((__vaword)((unsigned char *) list.raddr)[11] << 32)
                  | ((__vaword)((unsigned char *) list.raddr)[12] << 24)
                  | ((__vaword)((unsigned char *) list.raddr)[13] << 16)
                  | ((__vaword)((unsigned char *) list.raddr)[14] << 8);
            } else
            if (list.rsize >= 16 && list.rsize <= 32) {
              o1 =  ((__vaword)((unsigned char *) list.raddr)[8] << 56)
                  | ((__vaword)((unsigned char *) list.raddr)[9] << 48)
                  | ((__vaword)((unsigned char *) list.raddr)[10] << 40)
                  | ((__vaword)((unsigned char *) list.raddr)[11] << 32)
                  | ((__vaword)((unsigned char *) list.raddr)[12] << 24)
                  | ((__vaword)((unsigned char *) list.raddr)[13] << 16)
                  | ((__vaword)((unsigned char *) list.raddr)[14] << 8)
                  |  (__vaword)((unsigned char *) list.raddr)[15];
              if (list.rsize == 16) {
              } else
              if (list.rsize == 17) {
                o2 =   (__vaword)((unsigned char *) list.raddr)[16] << 56;
              } else
              if (list.rsize == 18) {
                o2 =  ((__vaword)((unsigned char *) list.raddr)[16] << 56)
                    | ((__vaword)((unsigned char *) list.raddr)[17] << 48);
              } else
              if (list.rsize == 19) {
                o2 =  ((__vaword)((unsigned char *) list.raddr)[16] << 56)
                    | ((__vaword)((unsigned char *) list.raddr)[17] << 48)
                    | ((__vaword)((unsigned char *) list.raddr)[18] << 40);
              } else
              if (list.rsize == 20) {
                o2 =  ((__vaword)((unsigned char *) list.raddr)[16] << 56)
                    | ((__vaword)((unsigned char *) list.raddr)[17] << 48)
                    | ((__vaword)((unsigned char *) list.raddr)[18] << 40)
                    | ((__vaword)((unsigned char *) list.raddr)[19] << 32);
              } else
              if (list.rsize == 21) {
                o2 =  ((__vaword)((unsigned char *) list.raddr)[16] << 56)
                    | ((__vaword)((unsigned char *) list.raddr)[17] << 48)
                    | ((__vaword)((unsigned char *) list.raddr)[18] << 40)
                    | ((__vaword)((unsigned char *) list.raddr)[19] << 32)
                    | ((__vaword)((unsigned char *) list.raddr)[20] << 24);
              } else
              if (list.rsize == 22) {
                o2 =  ((__vaword)((unsigned char *) list.raddr)[16] << 56)
                    | ((__vaword)((unsigned char *) list.raddr)[17] << 48)
                    | ((__vaword)((unsigned char *) list.raddr)[18] << 40)
                    | ((__vaword)((unsigned char *) list.raddr)[19] << 32)
                    | ((__vaword)((unsigned char *) list.raddr)[20] << 24)
                    | ((__vaword)((unsigned char *) list.raddr)[21] << 16);
              } else
              if (list.rsize == 23) {
                o2 =  ((__vaword)((unsigned char *) list.raddr)[16] << 56)
                    | ((__vaword)((unsigned char *) list.raddr)[17] << 48)
                    | ((__vaword)((unsigned char *) list.raddr)[18] << 40)
                    | ((__vaword)((unsigned char *) list.raddr)[19] << 32)
                    | ((__vaword)((unsigned char *) list.raddr)[20] << 24)
                    | ((__vaword)((unsigned char *) list.raddr)[21] << 16)
                    | ((__vaword)((unsigned char *) list.raddr)[22] << 8);
              } else
              if (list.rsize >= 24 && list.rsize <= 32) {
                o2 =  ((__vaword)((unsigned char *) list.raddr)[16] << 56)
                    | ((__vaword)((unsigned char *) list.raddr)[17] << 48)
                    | ((__vaword)((unsigned char *) list.raddr)[18] << 40)
                    | ((__vaword)((unsigned char *) list.raddr)[19] << 32)
                    | ((__vaword)((unsigned char *) list.raddr)[20] << 24)
                    | ((__vaword)((unsigned char *) list.raddr)[21] << 16)
                    | ((__vaword)((unsigned char *) list.raddr)[22] << 8)
                    |  (__vaword)((unsigned char *) list.raddr)[23];
                if (list.rsize == 24) {
                } else
                if (list.rsize == 25) {
                  o3 =   (__vaword)((unsigned char *) list.raddr)[24] << 56;
                } else
                if (list.rsize == 26) {
                  o3 =  ((__vaword)((unsigned char *) list.raddr)[24] << 56)
                      | ((__vaword)((unsigned char *) list.raddr)[25] << 48);
                } else
                if (list.rsize == 27) {
                  o3 =  ((__vaword)((unsigned char *) list.raddr)[24] << 56)
                      | ((__vaword)((unsigned char *) list.raddr)[25] << 48)
                      | ((__vaword)((unsigned char *) list.raddr)[26] << 40);
                } else
                if (list.rsize == 28) {
                  o3 =  ((__vaword)((unsigned char *) list.raddr)[24] << 56)
                      | ((__vaword)((unsigned char *) list.raddr)[25] << 48)
                      | ((__vaword)((unsigned char *) list.raddr)[26] << 40)
                      | ((__vaword)((unsigned char *) list.raddr)[27] << 32);
                } else
                if (list.rsize == 29) {
                  o3 =  ((__vaword)((unsigned char *) list.raddr)[24] << 56)
                      | ((__vaword)((unsigned char *) list.raddr)[25] << 48)
                      | ((__vaword)((unsigned char *) list.raddr)[26] << 40)
                      | ((__vaword)((unsigned char *) list.raddr)[27] << 32)
                      | ((__vaword)((unsigned char *) list.raddr)[28] << 24);
                } else
                if (list.rsize == 30) {
                  o3 =  ((__vaword)((unsigned char *) list.raddr)[24] << 56)
                      | ((__vaword)((unsigned char *) list.raddr)[25] << 48)
                      | ((__vaword)((unsigned char *) list.raddr)[26] << 40)
                      | ((__vaword)((unsigned char *) list.raddr)[27] << 32)
                      | ((__vaword)((unsigned char *) list.raddr)[28] << 24)
                      | ((__vaword)((unsigned char *) list.raddr)[29] << 16);
                } else
                if (list.rsize == 31) {
                  o3 =  ((__vaword)((unsigned char *) list.raddr)[24] << 56)
                      | ((__vaword)((unsigned char *) list.raddr)[25] << 48)
                      | ((__vaword)((unsigned char *) list.raddr)[26] << 40)
                      | ((__vaword)((unsigned char *) list.raddr)[27] << 32)
                      | ((__vaword)((unsigned char *) list.raddr)[28] << 24)
                      | ((__vaword)((unsigned char *) list.raddr)[29] << 16)
                      | ((__vaword)((unsigned char *) list.raddr)[30] << 8);
                } else
                if (list.rsize == 32) {
                  o3 =  ((__vaword)((unsigned char *) list.raddr)[24] << 56)
                      | ((__vaword)((unsigned char *) list.raddr)[25] << 48)
                      | ((__vaword)((unsigned char *) list.raddr)[26] << 40)
                      | ((__vaword)((unsigned char *) list.raddr)[27] << 32)
                      | ((__vaword)((unsigned char *) list.raddr)[28] << 24)
                      | ((__vaword)((unsigned char *) list.raddr)[29] << 16)
                      | ((__vaword)((unsigned char *) list.raddr)[30] << 8)
                      |  (__vaword)((unsigned char *) list.raddr)[31];
                }
              }
            }
          }
        }
      }
    }
  }
}
