#ifndef _avcall_m68k_c				/*-*- C -*-*/
#define _avcall_m68k_c
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

  Foreign function interface for a m68k Sun3 with gcc/sun-cc.

  This calls a C function with an argument list built up using macros
  defined in av_call.h.

  M68k Argument Passing Conventions:

  All arguments are passed on the stack with word alignment. Doubles take
  two words. Structure args are passed as true structures embedded in the
  argument stack. To return a structure, the called function copies the
  return value to the address supplied in register "a1". Gcc without
  -fpcc-struct-return returns <= 4 byte structures as integers.

  Compile this routine with gcc -O (or -O2 or -g -O) to get the right
  register variables, or use the assembler version.
  ----------------------------------------------------------------------*/
#include "avcall.h.in"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))

int
__builtin_avcall(av_alist* l)
{
  register __avword*	sp	__asm__("sp");  /* C names for registers */
  register __avword*	sret	__asm__("a1");	/* structure return pointer */
/*register __avword	iret	__asm__("d0"); */
  register __avword	iret2	__asm__("d1");
  register float	fret	__asm__("d0");	/* d0 */
  register double	dret	__asm__("d0");	/* d0,d1 */
  register float	fp_fret	__asm__("fp0");
  register double	fp_dret	__asm__("fp0");

  __avword* argframe = (sp -= __AV_ALIST_WORDS); /* make room for argument list */
  int arglen = l->aptr - l->args;
  __avword i;
  __avword i2;

  for (i = 0; i < arglen; i++)		/* push function args onto stack */
    argframe[i] = l->args[i];

  if (l->rtype == __AVstruct)		/* push struct return address */
    __asm__("move%.l %0,%/a1" : : "g" (l->raddr));

  i = (*l->func)();			/* call function */
  i2 = iret2;

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
    ((__avword*)l->raddr)[1] = i2;
  } else
  if (l->rtype == __AVfloat) {
    if (l->flags & __AV_FREG_FLOAT_RETURN) {
      RETURN(float, fp_fret);
    } else {
      if (l->flags & __AV_SUNCC_FLOAT_RETURN) {
        RETURN(float, (float)dret);
      } else {
        RETURN(float, fret);
      }
    }
  } else
  if (l->rtype == __AVdouble) {
    if (l->flags & __AV_FREG_FLOAT_RETURN) {
      RETURN(double, fp_dret);
    } else {
      RETURN(double, dret);
    }
  } else
  if (l->rtype == __AVvoidp) {
    RETURN(void*, i);
  } else
  if (l->rtype == __AVstruct) {
    /* NB: On m68k, all structure sizes are divisible by 2. */
    if (l->flags & __AV_REGISTER_STRUCT_RETURN) {
      if (l->rsize == sizeof(char)) { /* can't occur */
        RETURN(char, i);
        goto done;
      } else
      if (l->rsize == sizeof(short)) {
        RETURN(short, i);
        goto done;
      } else
      if (l->rsize == sizeof(int)) {
        RETURN(int, i);
        goto done;
      } else
      if (l->rsize == 2*sizeof(__avword)) {
        ((__avword*)l->raddr)[0] = i;
        ((__avword*)l->raddr)[1] = i2;
        goto done;
      }
    }
    if (l->flags & __AV_PCC_STRUCT_RETURN) {
      /* pcc struct return convention: need a  *(TYPE*)l->raddr = *(TYPE*)i;  */
      if (l->rsize == sizeof(char)) { /* can't occur */
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
    }
    done: ;
  }
  sp += __AV_ALIST_WORDS;
  return 0;
}

#endif /*_avcall_m68k_c */
