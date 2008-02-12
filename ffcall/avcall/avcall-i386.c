#ifndef _avcall_i386_c				/*-*- C -*-*/
#define _avcall_i386_c
/**
  Copyright 1993 Bill Triggs, <Bill.Triggs@inrialpes.fr>
  Copyright 1995-1999 Bruno Haible, <bruno@clisp.org>

  This is free software distributed under the GNU General Public
  Licence described in the file COPYING. Contact the author if
  you don't have this or can't live with it. There is ABSOLUTELY
  NO WARRANTY, explicit or implied, on this software.
**/
/*----------------------------------------------------------------------
  !!! THIS ROUTINE MUST BE COMPILED gcc -O -fno-omit-frame-pointer !!!

  Foreign function interface for a Linux i386/486 with gcc.

  This calls a C function with an argument list built up using macros
  defined in av_call.h.

  i386 Argument Passing Conventions:

  All arguments are passed on the stack with word alignment. Doubles take
  two words. Structure args are passed as true structures embedded in the
  argument stack. Float and double returns often come from FPU registers.

  To return a structure, the called function copies the value to space
  pointed to by its first argument, and all other arguments are shifted
  down by one. On NeXTstep, however, the called function copies the return
  value to the address supplied in register "%ebx". Gcc without
  -fpcc-struct-return returns <= 4 byte structures as integers.

  Compile this routine with gcc -O (or -O2 -fno-omit-frame-pointer or -g -O)
  to get the right register variables. For other compilers use the
  pre-compiled assembler version.

  -fomit-frame-pointer is forbidden because when calling structure returning
  functions (the "i = (*l->func)();" line below) the called functions pops
  the return value container pointer from the stack: "ret $4" instead of
  "ret". (See gcc-2.6.3 macro RETURN_POPS_ARGS.) From our point of view, %esp
  gets magically incremented. A workaround would be to push the return value
  container pointer using an __asm__("pushl %0" : : : ...) instruction.
  Similarly, when calling functions with `stdcall' linkage, %esp also gets
  incremented: all arguments (including the return value container pointer)
  are popped from the stack.
  ----------------------------------------------------------------------*/
#include "avcall.h.in"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))

int
__builtin_avcall(av_alist* l)
{
  register __avword*	sp	__asm__("sp");	/* C names for registers */
/*register __avword	iret	__asm__("eax"); */
  register __avword	iret2	__asm__("edx");

  __avword* argframe = (sp -= __AV_ALIST_WORDS); /* make room for argument list */
  int arglen = l->aptr - l->args;
  __avword i;

  for (i = 0; i < arglen; i++)		/* push function args onto stack */
    argframe[i] = l->args[i];

  /* struct return address */
  if ((l->flags & __AV_NEXTGCC_STRUCT_RETURN) && (l->rtype == __AVstruct))
    __asm__("movl %0,%%ebx" : : "g" (l->raddr) : "bx" /* %ebx */);

  /* call function */
  if (l->rtype == __AVfloat) {
    *(float*)l->raddr = (*(float(*)())l->func)();
  } else
  if (l->rtype == __AVdouble) {
    *(double*)l->raddr = (*(double(*)())l->func)();
  } else {
    i = (*l->func)();

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
  }
  return 0;
}

#endif /*_avcall_i386_c */
