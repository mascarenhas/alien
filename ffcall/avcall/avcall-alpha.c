#ifndef _avcall_alpha_c				/*-*- C -*-*/
#define _avcall_alpha_c
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

  Foreign function interface for a DEC Alpha with gcc.

  This calls a C function with an argument list built up using macros
  defined in av_call.h.

  Alpha Argument Passing Conventions

  The first 6 arguments are passed in registers $16-$21 for integers,
  in registers $f16-$f21 for floats. From then on, everything is passed
  on the stack.

  Everything on the stack is word-aligned.

  Integers and pointers are returned in $0, floats and doubles in $f0.
  To return a structure, the called function copies the value to space
  pointed to by its first argument, and all other arguments are shifted
  down by one.

  Compile this routine with gcc for the __asm__ extensions and with
  optimisation on (-O or -O2 or -g -O) so that argframe is set to the
  correct offset.
  ----------------------------------------------------------------------*/
#include "avcall.h.in"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))

int
__builtin_avcall(av_alist* l)
{
  register __avword*	sp	__asm__("$30");  /* C names for registers */
  register long		arg1	__asm__("$16");
  register long		arg2	__asm__("$17");
  register long		arg3	__asm__("$18");
  register long		arg4	__asm__("$19");
  register long		arg5	__asm__("$20");
  register long		arg6	__asm__("$21");
  register double	fret	__asm__("$f0");
  register double	farg1	__asm__("$f16");
  register double	farg2	__asm__("$f17");
  register double	farg3	__asm__("$f18");
  register double	farg4	__asm__("$f19");
  register double	farg5	__asm__("$f20");
  register double	farg6	__asm__("$f21");
/*register __avword	iret	__asm__("$0"); */
  register __avword	iret2	__asm__("$1");

  __avword* argframe = (sp -= __AV_ALIST_WORDS); /* make room for argument list */
  int arglen = ((unsigned long) l->aptr - (unsigned long) l->args) >> 3;
  __avword i, i2;

  for (i = 6; i < arglen; i++)		/* push excess function args */
    argframe[i-6] = l->args[i];

					/* call function with 1st 6 args */
  /* we pass the args both in the integer registers and the floating point
     registers, so we don't have to store the argument types. */
  __asm__ __volatile__ ("ldq $16,%0" : : "m" (l->args[0])); /* arg1 = l->args[0]; */
  __asm__ __volatile__ ("ldt $f16,%0" : : "m" (l->args[0])); /* farg1 = *(double*) &l->args[0]; */
  __asm__ __volatile__ ("ldq $17,%0" : : "m" (l->args[1])); /* arg2 = l->args[1]; */
  __asm__ __volatile__ ("ldt $f17,%0" : : "m" (l->args[1])); /* farg2 = *(double*) &l->args[1]; */
  __asm__ __volatile__ ("ldq $18,%0" : : "m" (l->args[2])); /* arg3 = l->args[2]; */
  __asm__ __volatile__ ("ldt $f18,%0" : : "m" (l->args[2])); /* farg3 = *(double*) &l->args[2]; */
  __asm__ __volatile__ ("ldq $19,%0" : : "m" (l->args[3])); /* arg4 = l->args[3]; */
  __asm__ __volatile__ ("ldt $f19,%0" : : "m" (l->args[3])); /* farg4 = *(double*) &l->args[3]; */
  __asm__ __volatile__ ("ldq $20,%0" : : "m" (l->args[4])); /* arg5 = l->args[4]; */
  __asm__ __volatile__ ("ldt $f20,%0" : : "m" (l->args[4])); /* farg5 = *(double*) &l->args[4]; */
  __asm__ __volatile__ ("ldq $21,%0" : : "m" (l->args[5])); /* arg6 = l->args[5]; */
  __asm__ __volatile__ ("ldt $f21,%0" : : "m" (l->args[5])); /* farg6 = *(double*) &l->args[5]; */
  i = (*l->func)();
  i2 = iret2;
  sp += __AV_ALIST_WORDS;	/* remove argument list from the stack */
  /* this is apparently not needed, but better safe than sorry... */
  __asm__ __volatile__ ("" : : :
			/* clobber */ "$16", "$17", "$18", "$19", "$20", "$21",
				     "$f16","$f17","$f18","$f19","$f20","$f21");

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
    RETURN(double, fret);
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
        if (l->rsize == sizeof(char)) {
          RETURN(char, i);
        } else
        if (l->rsize == sizeof(short)) {
          RETURN(short, i);
        } else
        if (l->rsize == sizeof(int)) {
          RETURN(int, i);
        } else
        if (l->rsize == sizeof(long)) {
          RETURN(long, i);
        } else
        if (l->rsize == 2*sizeof(__avword)) {
          ((__avword*)l->raddr)[0] = i;
          ((__avword*)l->raddr)[1] = i2;
        }
      }
    }
  }
  return 0;
}

#endif /*_avcall_alpha_c */
