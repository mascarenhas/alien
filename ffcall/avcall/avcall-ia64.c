#ifndef _avcall_ia64_c				/*-*- C -*-*/
#define _avcall_ia64_c
/**
  Copyright 1993 Bill Triggs, <Bill.Triggs@inrialpes.fr>
  Copyright 1995-2001 Bruno Haible, <bruno@clisp.org>

  This is free software distributed under the GNU General Public
  Licence described in the file COPYING. Contact the author if
  you don't have this or can't live with it. There is ABSOLUTELY
  NO WARRANTY, explicit or implied, on this software.
**/
/*----------------------------------------------------------------------
  !!! THIS ROUTINE MUST BE COMPILED gcc -O !!!

  Foreign function interface for a Intel IA-64 in little-endian mode with gcc.

  This calls a C function with an argument list built up using macros
  defined in av_call.h.

  IA-64 64-bit Argument Passing Conventions:

  The argument sequence is mapped linearly on the registers r32,...,r39,
  and continued on the stack, in [r12+16], [r12+24], ...
  Items in this sequence are word-aligned. Structures larger than a single
  word are even two-word-aligned.
  Integer/pointer arguments are passed in the allocated slots (registers
  or stack slots). The first 8 float/double arguments are passed in
  registers f8,...,f15 instead, but their slots are kept allocated.
  Structure args are passed like multiple integer arguments; except that
  structures consisting only of floats or only of doubles are passed like
  multiple float arguments or multiple double arguments, respectively.

  Integers and pointers are returned in r8, floats and doubles in f8.
  Structures consisting only of at most 8 floats or only of at most 8 doubles
  are returned in f8,...,f15. Other than that, structures of size <= 32 bytes
  are returned in r8,...,r11, as if these were 4 contiguous words in memory.
  Larger structures are returned in memory; the caller passes the address
  of the target memory area in r8, and it is returned unmodified in r8.
  ----------------------------------------------------------------------*/
#include "avcall.h.in"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))

register __avword*	sret	__asm__("r8");  /* structure return pointer */
register __avword	iret	__asm__("r8");
register __avword	iret2	__asm__("r9");
register __avword	iret3	__asm__("r10");
register __avword	iret4	__asm__("r11");
/*register float	fret	__asm__("f8");*/
/*register double	dret	__asm__("f8");*/
register double		farg1	__asm__("f8");
register double		farg2	__asm__("f9");
register double		farg3	__asm__("f10");
register double		farg4	__asm__("f11");
register double		farg5	__asm__("f12");
register double		farg6	__asm__("f13");
register double		farg7	__asm__("f14");
register double		farg8	__asm__("f15");

int
__builtin_avcall(av_alist* l)
{
  register __avword*	sp	__asm__("r12"); /* C names for registers */

  __avword* argframe = (sp -= __AV_ALIST_WORDS) + 2; /* make room for argument list */
  int arglen = l->aptr - l->args;
  int farglen = l->faptr - l->fargs;
  __avword i;

  for (i = 8; i < arglen; i++)		/* push function args onto stack */
    argframe[i-8] = l->args[i];

  /* struct return address */
  if (l->rtype == __AVstruct)
    sret = l->raddr;

  /* put max. 8 double args in registers */
  if (farglen > 0) {
    farg1 = l->fargs[0];
    if (farglen > 1) {
      farg2 = l->fargs[1];
      if (farglen > 2) {
        farg3 = l->fargs[2];
        if (farglen > 3) {
          farg4 = l->fargs[3];
          if (farglen > 4) {
            farg5 = l->fargs[4];
            if (farglen > 5) {
              farg6 = l->fargs[5];
              if (farglen > 6) {
                farg7 = l->fargs[6];
                if (farglen > 7)
                  farg8 = l->fargs[7];
              }
            }
          }
        }
      }
    }
  }

  /* call function, pass 8 integer and 8 double args in registers */
  if (l->rtype == __AVfloat) {
    *(float*)l->raddr = (*(float(*)())l->func)(l->args[0], l->args[1],
					       l->args[2], l->args[3],
					       l->args[4], l->args[5],
					       l->args[6], l->args[7]);
  } else
  if (l->rtype == __AVdouble) {
    *(double*)l->raddr = (*(double(*)())l->func)(l->args[0], l->args[1],
						 l->args[2], l->args[3],
						 l->args[4], l->args[5],
						 l->args[6], l->args[7]);
  } else {
    i = (*l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
		   l->args[4], l->args[5], l->args[6], l->args[7]);

    /* save return value */
    if (l->rtype == __AVvoid) {
    } else
    if (l->rtype == __AVword) {
      RETURN(__avword, i);
    } else
    if (l->rtype == __AVchar) {
      RETURN(char, i);
    } else
    if (l->rtype == __AVschar) {
      RETURN(signed char, i);
    } else
    if (l->rtype == __AVuchar) {
      RETURN(unsigned char, i);
    } else
    if (l->rtype == __AVshort) {
      RETURN(short, i);
    } else
    if (l->rtype == __AVushort) {
      RETURN(unsigned short, i);
    } else
    if (l->rtype == __AVint) {
      RETURN(int, i);
    } else
    if (l->rtype == __AVuint) {
      RETURN(unsigned int, i);
    } else
    if (l->rtype == __AVlong || l->rtype == __AVlonglong) {
      RETURN(long, i);
    } else
    if (l->rtype == __AVulong || l->rtype == __AVulonglong) {
      RETURN(unsigned long, i);
    } else
  /* see above
    if (l->rtype == __AVfloat) {
    } else
    if (l->rtype == __AVdouble) {
    } else
  */
    if (l->rtype == __AVvoidp) {
      RETURN(void*, i);
    } else
    if (l->rtype == __AVstruct) {
      if (l->flags & __AV_PCC_STRUCT_RETURN) {
        /* pcc struct return convention: need a  *(TYPE*)l->raddr = *(TYPE*)i;  */
        if (l->rsize == sizeof(char)) {
          RETURN(char, *(char*)i);
        } else
        if (l->rsize == sizeof(short)) {
          RETURN(short, *(short*)i);
        } else
        if (l->rsize == sizeof(int)) {
          RETURN(int, *(int*)i);
        } else
        if (l->rsize == sizeof(long)) {
          RETURN(long, *(long*)i);
        } else {
          int n = (l->rsize + sizeof(__avword)-1)/sizeof(__avword);
          while (--n >= 0)
            ((__avword*)l->raddr)[n] = ((__avword*)i)[n];
        }
      } else {
        /* normal struct return convention */
        if (l->flags & __AV_REGISTER_STRUCT_RETURN) {
          /* Return structs of size <= 32 in registers. */
          if (l->rsize > 0 && l->rsize <= 32) {
            if (l->rsize >= 1)
              ((unsigned char *)l->raddr)[0] = (unsigned char)(i);
            if (l->rsize >= 2)
              ((unsigned char *)l->raddr)[1] = (unsigned char)(i>>8);
            if (l->rsize >= 3)
              ((unsigned char *)l->raddr)[2] = (unsigned char)(i>>16);
            if (l->rsize >= 4)
              ((unsigned char *)l->raddr)[3] = (unsigned char)(i>>24);
            if (l->rsize >= 5)
              ((unsigned char *)l->raddr)[4] = (unsigned char)(i>>32);
            if (l->rsize >= 6)
              ((unsigned char *)l->raddr)[5] = (unsigned char)(i>>40);
            if (l->rsize >= 7)
              ((unsigned char *)l->raddr)[6] = (unsigned char)(i>>48);
            if (l->rsize >= 8)
              ((unsigned char *)l->raddr)[7] = (unsigned char)(i>>56);
            if (l->rsize >= 9) {
              ((unsigned char *)l->raddr)[8] = (unsigned char)(iret2);
              if (l->rsize >= 10)
                ((unsigned char *)l->raddr)[9] = (unsigned char)(iret2>>8);
              if (l->rsize >= 11)
                ((unsigned char *)l->raddr)[10] = (unsigned char)(iret2>>16);
              if (l->rsize >= 12)
                ((unsigned char *)l->raddr)[11] = (unsigned char)(iret2>>24);
              if (l->rsize >= 13)
                ((unsigned char *)l->raddr)[12] = (unsigned char)(iret2>>32);
              if (l->rsize >= 14)
                ((unsigned char *)l->raddr)[13] = (unsigned char)(iret2>>40);
              if (l->rsize >= 15)
                ((unsigned char *)l->raddr)[14] = (unsigned char)(iret2>>48);
              if (l->rsize >= 16)
                ((unsigned char *)l->raddr)[15] = (unsigned char)(iret2>>56);
              if (l->rsize >= 17) {
                ((unsigned char *)l->raddr)[16] = (unsigned char)(iret3);
                if (l->rsize >= 18)
                  ((unsigned char *)l->raddr)[17] = (unsigned char)(iret3>>8);
                if (l->rsize >= 19)
                  ((unsigned char *)l->raddr)[18] = (unsigned char)(iret3>>16);
                if (l->rsize >= 20)
                  ((unsigned char *)l->raddr)[19] = (unsigned char)(iret3>>24);
                if (l->rsize >= 21)
                  ((unsigned char *)l->raddr)[20] = (unsigned char)(iret3>>32);
                if (l->rsize >= 22)
                  ((unsigned char *)l->raddr)[21] = (unsigned char)(iret3>>40);
                if (l->rsize >= 23)
                  ((unsigned char *)l->raddr)[22] = (unsigned char)(iret3>>48);
                if (l->rsize >= 24)
                  ((unsigned char *)l->raddr)[23] = (unsigned char)(iret3>>56);
                if (l->rsize >= 25) {
                  ((unsigned char *)l->raddr)[24] = (unsigned char)(iret4);
                  if (l->rsize >= 26)
                    ((unsigned char *)l->raddr)[25] = (unsigned char)(iret4>>8);
                  if (l->rsize >= 27)
                    ((unsigned char *)l->raddr)[26] = (unsigned char)(iret4>>16);
                  if (l->rsize >= 28)
                    ((unsigned char *)l->raddr)[27] = (unsigned char)(iret4>>24);
                  if (l->rsize >= 29)
                    ((unsigned char *)l->raddr)[28] = (unsigned char)(iret4>>32);
                  if (l->rsize >= 30)
                    ((unsigned char *)l->raddr)[29] = (unsigned char)(iret4>>40);
                  if (l->rsize >= 31)
                    ((unsigned char *)l->raddr)[30] = (unsigned char)(iret4>>48);
                  if (l->rsize >= 32)
                    ((unsigned char *)l->raddr)[31] = (unsigned char)(iret4>>56);
                }
              }
            }
          }
        }
      }
    }
  }
  return 0;
}

#endif /*_avcall_ia64_c */
