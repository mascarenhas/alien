#ifndef _avcall_hppa_c				/*-*- C -*-*/
#define _avcall_hppa_c
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

  Foreign function interface for a HP Precision Architecture 1.0 with gcc

  This calls a C function with an argument list built up using macros
  defined in av_call.h.

  HPPA Argument Passing Conventions:

  All arguments, except the first 4 words, are passed on the stack
  - growing down! - with word alignment. Doubles take two words and force
  double alignment. Small structures args are passed as true structures
  embedded in the argument stack. They force double alignment and - if they
  don't fit entirely in the 4 register words - are passed in memory.
  The first 2 words are passed like this:
    %r26 = first integer arg, %r25 = second integer arg, or
    %r26 = high word of double arg, %r25 = low word of double arg.
  Similarly for the next 2 words, passed in %r24 and %r23.
  Note that other calling conventions would be in effect if we would call
  an explicitly named function!

  To return a structure, the called function copies the return value to
  the address supplied in register "%r28".

  It is forbidden to modify the stack pointer.

  Compile this routine with gcc -O2 -fomit-frame-pointer to get the right
  register variables, then replace the -120 in the second save statement
  "stw %r3,-120(0,%r30)" by -1060, or use the assembler version.
  ----------------------------------------------------------------------*/
#include "avcall.h.in"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))

/* This declaration tells gcc not to modify %r28. */
register __avword*	sret	__asm__("%r28");  /* structure return pointer */

int
__builtin_avcall(av_alist* l)
{
  register __avword*	sp	__asm__("%r30");  /* C names for registers */
  register float	fret	__asm__("%fr4");
  register double	dret	__asm__("%fr4");
/*register __avword	iret1	__asm__("%r28"); */
  register __avword	iret2	__asm__("%r29");

  __avword space[__AV_ALIST_WORDS];	/* space for callee's stack frame */
  __avword* argframe = sp - 8;		/* stack offset for argument list */
  int arglen = &l->args[__AV_ALIST_WORDS] - l->aptr;
  __avword i;

  {
    int i;
    for (i = -arglen; i < -4; i++)	/* push function args onto stack */
      argframe[i] = l->args[__AV_ALIST_WORDS+i];
  }

  if (l->rtype == __AVstruct)		/* push struct return address */
    sret = l->raddr;

				/* call function, pass 4 args in registers */
  i = (*l->func)(l->args[__AV_ALIST_WORDS-1], l->args[__AV_ALIST_WORDS-2],
		 l->args[__AV_ALIST_WORDS-3], l->args[__AV_ALIST_WORDS-4]);

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
  if (l->rtype == __AVlonglong || l->rtype == __AVulonglong) {
    ((__avword*)l->raddr)[0] = i;
    ((__avword*)l->raddr)[1] = iret2;
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
      if (l->rsize == sizeof(double)) {
        ((int*)l->raddr)[0] = ((int*)i)[0];
        ((int*)l->raddr)[1] = ((int*)i)[1];
      } else {
        int n = (l->rsize + sizeof(__avword)-1)/sizeof(__avword);
        while (--n >= 0)
          ((__avword*)l->raddr)[n] = ((__avword*)i)[n];
      }
    } else {
      /* normal struct return convention */
      if (l->flags & __AV_SMALL_STRUCT_RETURN) {
        if (l->flags & __AV_OLDGCC_STRUCT_RETURN) {
          /* gcc <= 2.6.3 returns structs of size 1,2,4 in registers. */
          if (l->rsize == sizeof(char)) {
            RETURN(char, i);
          } else
          if (l->rsize == sizeof(short)) {
            RETURN(short, i);
          } else
          if (l->rsize == sizeof(int)) {
            RETURN(int, i);
          }
        } else {
          /* cc, c89 and gcc >= 2.7 return structs of size <= 8 in registers. */
          if (l->rsize == 1) {
            ((unsigned char *)l->raddr)[0] = (unsigned char)(i);
          } else
          if (l->rsize == 2) {
            ((unsigned char *)l->raddr)[0] = (unsigned char)(i>>8);
            ((unsigned char *)l->raddr)[1] = (unsigned char)(i);
          } else
          if (l->rsize == 3) {
            ((unsigned char *)l->raddr)[0] = (unsigned char)(i>>16);
            ((unsigned char *)l->raddr)[1] = (unsigned char)(i>>8);
            ((unsigned char *)l->raddr)[2] = (unsigned char)(i);
          } else
          if (l->rsize == 4) {
            ((unsigned char *)l->raddr)[0] = (unsigned char)(i>>24);
            ((unsigned char *)l->raddr)[1] = (unsigned char)(i>>16);
            ((unsigned char *)l->raddr)[2] = (unsigned char)(i>>8);
            ((unsigned char *)l->raddr)[3] = (unsigned char)(i);
          } else
          if (l->rsize == 5) {
            ((unsigned char *)l->raddr)[0] = (unsigned char)(i>>24);
            ((unsigned char *)l->raddr)[1] = (unsigned char)(i>>16);
            ((unsigned char *)l->raddr)[2] = (unsigned char)(i>>8);
            ((unsigned char *)l->raddr)[3] = (unsigned char)(i);
            ((unsigned char *)l->raddr)[4] = (unsigned char)(iret2);
          } else
          if (l->rsize == 6) {
            ((unsigned char *)l->raddr)[0] = (unsigned char)(i>>24);
            ((unsigned char *)l->raddr)[1] = (unsigned char)(i>>16);
            ((unsigned char *)l->raddr)[2] = (unsigned char)(i>>8);
            ((unsigned char *)l->raddr)[3] = (unsigned char)(i);
            ((unsigned char *)l->raddr)[4] = (unsigned char)(iret2>>8);
            ((unsigned char *)l->raddr)[5] = (unsigned char)(iret2);
          } else
          if (l->rsize == 7) {
            ((unsigned char *)l->raddr)[0] = (unsigned char)(i>>24);
            ((unsigned char *)l->raddr)[1] = (unsigned char)(i>>16);
            ((unsigned char *)l->raddr)[2] = (unsigned char)(i>>8);
            ((unsigned char *)l->raddr)[3] = (unsigned char)(i);
            ((unsigned char *)l->raddr)[4] = (unsigned char)(iret2>>16);
            ((unsigned char *)l->raddr)[5] = (unsigned char)(iret2>>8);
            ((unsigned char *)l->raddr)[6] = (unsigned char)(iret2);
          } else
          if (l->rsize == 8) {
            ((unsigned char *)l->raddr)[0] = (unsigned char)(i>>24);
            ((unsigned char *)l->raddr)[1] = (unsigned char)(i>>16);
            ((unsigned char *)l->raddr)[2] = (unsigned char)(i>>8);
            ((unsigned char *)l->raddr)[3] = (unsigned char)(i);
            ((unsigned char *)l->raddr)[4] = (unsigned char)(iret2>>24);
            ((unsigned char *)l->raddr)[5] = (unsigned char)(iret2>>16);
            ((unsigned char *)l->raddr)[6] = (unsigned char)(iret2>>8);
            ((unsigned char *)l->raddr)[7] = (unsigned char)(iret2);
          }
        }
      }
    }
  }
  return 0;
}

#endif /*_avcall_hppa_c */
