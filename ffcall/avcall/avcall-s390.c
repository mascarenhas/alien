#ifndef _avcall_s390_c				/*-*- C -*-*/
#define _avcall_s390_c
/**
  Copyright 1993 Bill Triggs, <Bill.Triggs@inrialpes.fr>
  Copyright 1995-1999 Bruno Haible, <bruno@clisp.org>
  Copyright 2001 Gerhard Tonn, <gt@debian.org>

  This is free software distributed under the GNU General Public
  Licence described in the file COPYING. Contact the author if
  you don't have this or can't live with it. There is ABSOLUTELY
  NO WARRANTY, explicit or implied, on this software.
**/
/*----------------------------------------------------------------------

  Foreign function interface for an IBM S/390 with gcc

  This calls a C function with an argument list built up using macros
  defined in av_call.h.

  S390 Argument Passing Conventions:

  All arguments, except the first 5 words, are passed on the stack with
  word alignment. Doubles take two words. The first 2 doubles and floats
  are also passed in floating-point-registers.
  To return a structure, the called function copies the value to space
  pointed to by its first argument, and all other arguments are shifted
  down by one.

  Compile this routine with gcc -O2 to get the right register variables.
  For other compilers use the pre-compiled assembler version.
  ----------------------------------------------------------------------*/
#include "avcall.h"

#define STACK_OFFSET 24

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))

register float  farg1	__asm__("f0");
register float  farg2	__asm__("f2");
register double darg1	__asm__("f0");
register double darg2	__asm__("f2");

int
__builtin_avcall(av_alist* l)
{
  register __avword*	sp	__asm__("r15");  /* C names for registers */
/*register __avword	iret	__asm__("r2"); */
  register __avword	iret2	__asm__("r3");
  register float	fret	__asm__("f0");
  register double	dret	__asm__("f0");

  __avword space[__AV_ALIST_WORDS];	/* space for callee's stack frame */
  __avword* argframe = sp + STACK_OFFSET;/* stack offset for argument list */
  int arglen = l->aptr - l->args;
  int farglen = l->faptr - l->fargs;
  int iargwords = (arglen-l->fargwords)<5?arglen-l->fargwords:5;
  __avword i;

  for (i = iargwords; i < arglen; i++) /* push function args onto stack */
   argframe[i-iargwords] = l->args[i];

  /* pass first 2 floating-point args in registers */
  if (farglen == 1) {
    if(l->fargsused[0])  farg1 = l->fargs[0]; else darg1 = l->dargs[0];
   }
  else if (farglen == 2) {
    if(l->fargsused[0] && l->fargsused[1]) {
       farg1 = l->fargs[0]; farg2 = l->fargs[1];
    }
    else if(l->fargsused[0] && !l->fargsused[1]) {
       farg1 = l->fargs[0]; darg2 = l->dargs[1];
    }
    else if(!l->fargsused[0] && l->fargsused[1]) {
       darg1 = l->dargs[0]; farg2 = l->fargs[1];
    }
    else if(!l->fargsused[0] && !l->fargsused[1]) {
       darg1 = l->dargs[0]; darg2 = l->dargs[1];
    }
  }

				/* call function, pass 5 args in registers */
  i = (*l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
		 l->args[4]);

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
      if (l->flags & __AV_REGISTER_STRUCT_RETURN) {
        if (l->rsize == sizeof(char)) {
          RETURN(char, i);
        } else
        if (l->rsize == sizeof(short)) {
          RETURN(short, i);
        } else
        if (l->rsize == sizeof(int)) {
          RETURN(int, i);
        } else
        if (l->rsize == 2*sizeof(__avword)) {
          ((__avword*)l->raddr)[0] = i;
          ((__avword*)l->raddr)[1] = iret2;
        }
      }
    }
  }
  return 0;
}

#endif /*_avcall_s390_c */
