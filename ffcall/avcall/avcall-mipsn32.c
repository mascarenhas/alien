#ifndef _avcall_mipsn32_c				/*-*- C -*-*/
#define _avcall_mipsn32_c
/**
  Copyright 1993 Bill Triggs, <Bill.Triggs@inrialpes.fr>
  Copyright 1995-1999 Bruno Haible, <bruno@clisp.org>

  This is free software distributed under the GNU General Public
  Licence described in the file COPYING. Contact the author if
  you don't have this or can't live with it. There is ABSOLUTELY
  NO WARRANTY, explicit or implied, on this software.
**/
/*----------------------------------------------------------------------
  !!! THIS ROUTINE MUST BE COMPILED gcc -O !!!

  Foreign function interface for an SGI 32-bit MIPS III with "cc -n32",
  or gcc configured as mips-sgi-irix6.

  This calls a C function with an argument list built up using macros
  defined in av_call.h.

  SGI MIPS new 32-bit Argument Passing Conventions

  - The entire argument list forms a structure with all the appropriate
    holes & alignments, and space for this is allocated in the stack frame.
  - Shorter integers are promoted to long long length (sizeof(long long)=8).
  - Doubles are 1 longword.
  - Structure arguments are copies embedded in the arglist structure.
  - The first 8 longwords of the structure are passed in registers $4...$11,
    except that float arguments are passed in registers $f12...$f19, and
    that double arguments and structure elements of type double are passed
    in registers $f12...$f19. (But varargs functions may expect them in the
    integer registers and we can't tell whether the function is varargs so
    we pass them both ways.)
    Remaining longwords are passed on the stack. No stack space is allocated
    for the first 8 longwords of the structure.
  - Structure returns of structures > 16 bytes: pointers to caller-allocated
    space are passed in as the first argument of the list.
  - Structure returns of structures <= 16 bytes: in the registers $2 (for the
    first 8 bytes) and $3 (for the next 8 bytes).
    A structure of 1 or 2 floats or doubles is returned in $f0 and $f2:
    the first float or double in $f0, the second float or double in $f2.
  - Integer/pointer returns are in $2, float/double returns in $f0.
  - The called function expects to see its own address in $25.

  This file needs to be compiled with gcc for the asm extensions, but the
  assembly version of it and the header file seem to work with SGI cc.
  ----------------------------------------------------------------------*/
#include "avcall.h.in"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))
#define OFFSETOF(struct,member) ((int)&(((struct*)0)->member))

typedef __avword (*func_pointer)();
register func_pointer	t9	__asm__("$25");

int
__builtin_avcall(av_alist* l)
{
  register __avword*	sp	__asm__("$sp");  /* C names for registers */
  register float	fret	__asm__("$f0");
  register double	dret	__asm__("$f0");
/*register __avword	iret1	__asm__("$2"); */
  register __avword	iret2	__asm__("$3");
  __avword space[__AV_ALIST_WORDS];	/* big space for child's stack frame */
  __avword *argframe = (__avword*)sp;	/* stack offset for argument list is 0 */
  int arglen = l->aptr - l->args;
  __avword i;

  if (l->farg_mask)
    { /* push leading float args */
      if (l->farg_mask & (1<<0))
        __asm__("lwc1 $f12,%1(%0)" : : "p" (l), "i" OFFSETOF(av_alist,farg[0]));
      if (l->farg_mask & (1<<1))
        __asm__("lwc1 $f13,%1(%0)" : : "p" (l), "i" OFFSETOF(av_alist,farg[1]));
      if (l->farg_mask & (1<<2))
        __asm__("lwc1 $f14,%1(%0)" : : "p" (l), "i" OFFSETOF(av_alist,farg[2]));
      if (l->farg_mask & (1<<3))
        __asm__("lwc1 $f15,%1(%0)" : : "p" (l), "i" OFFSETOF(av_alist,farg[3]));
      if (l->farg_mask & (1<<4))
        __asm__("lwc1 $f16,%1(%0)" : : "p" (l), "i" OFFSETOF(av_alist,farg[4]));
      if (l->farg_mask & (1<<5))
        __asm__("lwc1 $f17,%1(%0)" : : "p" (l), "i" OFFSETOF(av_alist,farg[5]));
      if (l->farg_mask & (1<<6))
        __asm__("lwc1 $f18,%1(%0)" : : "p" (l), "i" OFFSETOF(av_alist,farg[6]));
      if (l->farg_mask & (1<<7))
        __asm__("lwc1 $f19,%1(%0)" : : "p" (l), "i" OFFSETOF(av_alist,farg[7]));
    }
  if (l->darg_mask)
    { /* push leading double args */
      if (l->darg_mask & (1<<0))
        __asm__("ldc1 $f12,%1(%0)" : : "p" (l), "i" OFFSETOF(av_alist,args[0]));
      if (l->darg_mask & (1<<1))
        __asm__("ldc1 $f13,%1(%0)" : : "p" (l), "i" OFFSETOF(av_alist,args[1]));
      if (l->darg_mask & (1<<2))
        __asm__("ldc1 $f14,%1(%0)" : : "p" (l), "i" OFFSETOF(av_alist,args[2]));
      if (l->darg_mask & (1<<3))
        __asm__("ldc1 $f15,%1(%0)" : : "p" (l), "i" OFFSETOF(av_alist,args[3]));
      if (l->darg_mask & (1<<4))
        __asm__("ldc1 $f16,%1(%0)" : : "p" (l), "i" OFFSETOF(av_alist,args[4]));
      if (l->darg_mask & (1<<5))
        __asm__("ldc1 $f17,%1(%0)" : : "p" (l), "i" OFFSETOF(av_alist,args[5]));
      if (l->darg_mask & (1<<6))
        __asm__("ldc1 $f18,%1(%0)" : : "p" (l), "i" OFFSETOF(av_alist,args[6]));
      if (l->darg_mask & (1<<7))
        __asm__("ldc1 $f19,%1(%0)" : : "p" (l), "i" OFFSETOF(av_alist,args[7]));
    }

  for (i = 8; i < arglen; i++)		/* push excess function args */
    argframe[i-8] = l->args[i];

					/* call function with 1st 8 args */
  __asm__ __volatile__ ("ld $4,%0" : : "m" (l->args[0]) : "$4"); /* arg1 = l->args[0]; */
  __asm__ __volatile__ ("ld $5,%0" : : "m" (l->args[1]) : "$5"); /* arg1 = l->args[1]; */
  __asm__ __volatile__ ("ld $6,%0" : : "m" (l->args[2]) : "$6"); /* arg1 = l->args[2]; */
  __asm__ __volatile__ ("ld $7,%0" : : "m" (l->args[3]) : "$7"); /* arg1 = l->args[3]; */
  __asm__ __volatile__ ("ld $8,%0" : : "m" (l->args[4]) : "$8"); /* arg1 = l->args[4]; */
  __asm__ __volatile__ ("ld $9,%0" : : "m" (l->args[5]) : "$9"); /* arg1 = l->args[5]; */
  __asm__ __volatile__ ("ld $10,%0" : : "m" (l->args[6]) : "$10"); /* arg1 = l->args[6]; */
  __asm__ __volatile__ ("ld $11,%0" : : "m" (l->args[7]) : "$11"); /* arg1 = l->args[7]; */
  i = (*(t9 = l->func))();

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
  if (l->rtype == __AVlong) {
    RETURN(long, i);
  } else
  if (l->rtype == __AVulong) {
    RETURN(unsigned long, i);
  } else
  if (l->rtype == __AVlonglong) {
    RETURN(long long, i);
  } else
  if (l->rtype == __AVulonglong) {
    RETURN(unsigned long long, i);
  } else
  if (l->rtype == __AVfloat) {
    RETURN(float, fret);
  } else
  if (l->rtype == __AVdouble) {
    RETURN(double, dret);
  } else
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
      if (l->rsize == sizeof(long long)) {
        RETURN(long, *(long long*)i);
      } else {
        int n = (l->rsize + sizeof(__avword)-1)/sizeof(__avword);
        while (--n >= 0)
          ((__avword*)l->raddr)[n] = ((__avword*)i)[n];
      }
    } else {
      /* normal struct return convention */
      if (l->flags & __AV_REGISTER_STRUCT_RETURN) {
        if (l->flags & __AV_GCC_STRUCT_RETURN) {
          /* gcc returns structs of size 1,2,4,8 in registers. */
          if (l->rsize == sizeof(char)) {
            RETURN(char, i);
          } else
          if (l->rsize == sizeof(short)) {
            RETURN(short, i);
          } else
          if (l->rsize == sizeof(int)) {
            RETURN(int, i);
          } else
          if (l->rsize == sizeof(long long)) {
            RETURN(long long, i);
          }
        } else {
          /* cc returns structs of size <= 16 in registers. */
          if (l->rsize > 0 && l->rsize <= 16) {
            if (l->rsize == 1) {
              ((unsigned char *)l->raddr)[0] = (unsigned char)(i>>56);
            } else
            if (l->rsize == 2) {
              ((unsigned char *)l->raddr)[0] = (unsigned char)(i>>56);
              ((unsigned char *)l->raddr)[1] = (unsigned char)(i>>48);
            } else
            if (l->rsize == 3) {
              ((unsigned char *)l->raddr)[0] = (unsigned char)(i>>56);
              ((unsigned char *)l->raddr)[1] = (unsigned char)(i>>48);
              ((unsigned char *)l->raddr)[2] = (unsigned char)(i>>40);
            } else
            if (l->rsize == 4) {
              ((unsigned char *)l->raddr)[0] = (unsigned char)(i>>56);
              ((unsigned char *)l->raddr)[1] = (unsigned char)(i>>48);
              ((unsigned char *)l->raddr)[2] = (unsigned char)(i>>40);
              ((unsigned char *)l->raddr)[3] = (unsigned char)(i>>32);
            } else
            if (l->rsize == 5) {
              ((unsigned char *)l->raddr)[0] = (unsigned char)(i>>56);
              ((unsigned char *)l->raddr)[1] = (unsigned char)(i>>48);
              ((unsigned char *)l->raddr)[2] = (unsigned char)(i>>40);
              ((unsigned char *)l->raddr)[3] = (unsigned char)(i>>32);
              ((unsigned char *)l->raddr)[4] = (unsigned char)(i>>24);
            } else
            if (l->rsize == 6) {
              ((unsigned char *)l->raddr)[0] = (unsigned char)(i>>56);
              ((unsigned char *)l->raddr)[1] = (unsigned char)(i>>48);
              ((unsigned char *)l->raddr)[2] = (unsigned char)(i>>40);
              ((unsigned char *)l->raddr)[3] = (unsigned char)(i>>32);
              ((unsigned char *)l->raddr)[4] = (unsigned char)(i>>24);
              ((unsigned char *)l->raddr)[5] = (unsigned char)(i>>16);
            } else
            if (l->rsize == 7) {
              ((unsigned char *)l->raddr)[0] = (unsigned char)(i>>56);
              ((unsigned char *)l->raddr)[1] = (unsigned char)(i>>48);
              ((unsigned char *)l->raddr)[2] = (unsigned char)(i>>40);
              ((unsigned char *)l->raddr)[3] = (unsigned char)(i>>32);
              ((unsigned char *)l->raddr)[4] = (unsigned char)(i>>24);
              ((unsigned char *)l->raddr)[5] = (unsigned char)(i>>16);
              ((unsigned char *)l->raddr)[6] = (unsigned char)(i>>8);
            } else
            if (l->rsize >= 8 && l->rsize <= 16) {
              ((unsigned char *)l->raddr)[0] = (unsigned char)(i>>56);
              ((unsigned char *)l->raddr)[1] = (unsigned char)(i>>48);
              ((unsigned char *)l->raddr)[2] = (unsigned char)(i>>40);
              ((unsigned char *)l->raddr)[3] = (unsigned char)(i>>32);
              ((unsigned char *)l->raddr)[4] = (unsigned char)(i>>24);
              ((unsigned char *)l->raddr)[5] = (unsigned char)(i>>16);
              ((unsigned char *)l->raddr)[6] = (unsigned char)(i>>8);
              ((unsigned char *)l->raddr)[7] = (unsigned char)(i);
              if (l->rsize == 8) {
              } else
              if (l->rsize == 9) {
                ((unsigned char *)l->raddr)[8+0] = (unsigned char)(iret2>>56);
              } else
              if (l->rsize == 10) {
                ((unsigned char *)l->raddr)[8+0] = (unsigned char)(iret2>>56);
                ((unsigned char *)l->raddr)[8+1] = (unsigned char)(iret2>>48);
              } else
              if (l->rsize == 11) {
                ((unsigned char *)l->raddr)[8+0] = (unsigned char)(iret2>>56);
                ((unsigned char *)l->raddr)[8+1] = (unsigned char)(iret2>>48);
                ((unsigned char *)l->raddr)[8+2] = (unsigned char)(iret2>>40);
              } else
              if (l->rsize == 12) {
                ((unsigned char *)l->raddr)[8+0] = (unsigned char)(iret2>>56);
                ((unsigned char *)l->raddr)[8+1] = (unsigned char)(iret2>>48);
                ((unsigned char *)l->raddr)[8+2] = (unsigned char)(iret2>>40);
                ((unsigned char *)l->raddr)[8+3] = (unsigned char)(iret2>>32);
              } else
              if (l->rsize == 13) {
                ((unsigned char *)l->raddr)[8+0] = (unsigned char)(iret2>>56);
                ((unsigned char *)l->raddr)[8+1] = (unsigned char)(iret2>>48);
                ((unsigned char *)l->raddr)[8+2] = (unsigned char)(iret2>>40);
                ((unsigned char *)l->raddr)[8+3] = (unsigned char)(iret2>>32);
                ((unsigned char *)l->raddr)[8+4] = (unsigned char)(iret2>>24);
              } else
              if (l->rsize == 14) {
                ((unsigned char *)l->raddr)[8+0] = (unsigned char)(iret2>>56);
                ((unsigned char *)l->raddr)[8+1] = (unsigned char)(iret2>>48);
                ((unsigned char *)l->raddr)[8+2] = (unsigned char)(iret2>>40);
                ((unsigned char *)l->raddr)[8+3] = (unsigned char)(iret2>>32);
                ((unsigned char *)l->raddr)[8+4] = (unsigned char)(iret2>>24);
                ((unsigned char *)l->raddr)[8+5] = (unsigned char)(iret2>>16);
              } else
              if (l->rsize == 15) {
                ((unsigned char *)l->raddr)[8+0] = (unsigned char)(iret2>>56);
                ((unsigned char *)l->raddr)[8+1] = (unsigned char)(iret2>>48);
                ((unsigned char *)l->raddr)[8+2] = (unsigned char)(iret2>>40);
                ((unsigned char *)l->raddr)[8+3] = (unsigned char)(iret2>>32);
                ((unsigned char *)l->raddr)[8+4] = (unsigned char)(iret2>>24);
                ((unsigned char *)l->raddr)[8+5] = (unsigned char)(iret2>>16);
                ((unsigned char *)l->raddr)[8+6] = (unsigned char)(iret2>>8);
              } else
              if (l->rsize == 16) {
                ((unsigned char *)l->raddr)[8+0] = (unsigned char)(iret2>>56);
                ((unsigned char *)l->raddr)[8+1] = (unsigned char)(iret2>>48);
                ((unsigned char *)l->raddr)[8+2] = (unsigned char)(iret2>>40);
                ((unsigned char *)l->raddr)[8+3] = (unsigned char)(iret2>>32);
                ((unsigned char *)l->raddr)[8+4] = (unsigned char)(iret2>>24);
                ((unsigned char *)l->raddr)[8+5] = (unsigned char)(iret2>>16);
                ((unsigned char *)l->raddr)[8+6] = (unsigned char)(iret2>>8);
                ((unsigned char *)l->raddr)[8+7] = (unsigned char)(iret2);
              }
            }
          }
        }
      }
    }
  }
  return 0;
}

#endif /*_avcall_mipsn32_c */
