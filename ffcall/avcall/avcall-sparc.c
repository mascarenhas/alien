#ifndef _avcall_sparc_c				/*-*- C -*-*/
#define _avcall_sparc_c
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

  Foreign function interface for a Sun4 Sparc with gcc/sun-cc.

  This calls a C function with an argument list built up using macros
  defined in av_call.h.

  Sparc Argument Passing Conventions

  The first 6 words of arguments are passed in integer registers o0-o5
  regardless of type or alignment.  (Registers are windowed: o0-o5 become
  i0-i5 if the called function executes a `save' instruction.)  Remaining
  arguments are pushed onto the stack starting at a fixed offset
  ("argframe"). Space is left on the stack frame for temporary storage of
  the register arguments as well.

  Doubles may be cut in half and misaligned.  Shorter integers are
  always promoted to word-length.  Functions with K&R-style declarations
  and float args pass them as doubles and truncate them on function entry.
  Structures are passed as pointers to a local copy of the structure made
  by the caller.

  Integers and pointers are returned in o0, floats in f0, doubles in
  f0/f1.  If the function returns a structure a pointer to space
  allocated by the caller is pushed onto the stack immediately
  before the function arguments. Gcc without -fpcc-struct-return returns
  <= 4 byte structures as integers.

  Sun cc allocates temporary space for a returned structure just below
  the current frame pointer $fp (the $sp of the caller), and the caller
  must copy them from there. It also returns the temp address in $o0, but
  that gets nuked in the return in the code below so we can't use it.
  **The Sun cc struct return stuff below is a kludge**, but seems to work
  on the test cases...

  Compile this routine with gcc for the __asm__ extensions and with
  optimisation on (-O or -O2 or -g -O) so that argframe is set to the
  correct offset. (%sp is used differently in non-optimized code).
  For Sun cc, use the pre-compiled assembler version of this routine.
  ----------------------------------------------------------------------*/
#include "avcall.h.in"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))

register void* callee	__asm__("%g2");  /* any global or local register */
register __avword o0	__asm__("%o0");
register __avword o1	__asm__("%o1");
register __avword o2	__asm__("%o2");
register __avword o3	__asm__("%o3");
register __avword o4	__asm__("%o4");
register __avword o5	__asm__("%o5");

int
__builtin_avcall(av_alist* l)
{
  /*?? We probably need to make space for Sun cc
    struct return somewhere here. */
  register __avword* sp	__asm__("%sp");  /* C names for registers */
  register float fret	__asm__("%f0");  /* %f0 */
  register double dret	__asm__("%f0");  /* %f0,%f1 */

  __avword trampoline[6];		/* room for a trampoline */
  __avword space[__AV_ALIST_WORDS];	/* space for callee's stack frame */
  __avword *argframe = sp + 17;		/* stack offset for argument list */
  int arglen = l->aptr - l->args;
  __avword i;

  if ((l->rtype == __AVstruct) && !(l->flags & __AV_SUNCC_STRUCT_RETURN))
    argframe[-1] = (__avword)l->raddr;	/* push struct return address */

  {
    int i;
    for (i = 6; i < arglen; i++)	/* push excess function args */
      argframe[i] = l->args[i];
  }

  if ((l->rtype == __AVstruct) && (l->flags & __AV_SUNPROCC_STRUCT_RETURN))
    /* SUNWspro cc compiled functions don't copy the structure to the area
     * pointed to by argframe[-1] unless the caller has a proper "unimp n"
     * instruction. We generate the calling instructions on the stack. */
    {
      trampoline[0] = 0x9FC08000;	/* call %g2	*/
      trampoline[1] = 0x01000000;	/* nop		*/
      trampoline[2] = l->rsize & 0xFFF;	/* unimp n	*/
      trampoline[3] = 0xB0102000;       /* mov 0,%i0    */
      trampoline[4] = 0x81C7E008;       /* ret          */
      trampoline[5] = 0x81E80000;       /* restore      */
      __asm__ __volatile__ ("iflush %0" : : "r" (&trampoline[0]));
      __asm__ __volatile__ ("iflush %0" : : "r" (&trampoline[2]));
      __asm__ __volatile__ ("iflush %0" : : "r" (&trampoline[4]));
      __asm__ __volatile__ ("iflush %0" : : "r" (&trampoline[5]));
      o0 = l->args[0]; o1 = l->args[1]; o2 = l->args[2];
      o3 = l->args[3]; o4 = l->args[4]; o5 = l->args[5];
      callee = l->func;
      goto *(void*)trampoline;
    }

					/* call function with 1st 6 args */
  i = ({ __avword iret;	/* %o0 */
         iret = (*l->func)(l->args[0], l->args[1], l->args[2],
			   l->args[3], l->args[4], l->args[5]);
         asm ("nop");	/* struct returning functions skip this instruction */
         iret;
       });

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
    ((__avword*)l->raddr)[1] = o1;
  } else
  if (l->rtype == __AVfloat) {
    /* old Sun cc returns floats as doubles */
    if (l->flags & __AV_SUNCC_FLOAT_RETURN) {
      RETURN(float, (float)dret);
    } else {
      RETURN(float, fret);
    }
  } else
  if (l->rtype == __AVdouble) {
    RETURN(double, dret);
  } else
  if (l->rtype == __AVvoidp) {
    RETURN(void*, i);
  } else
  if (l->rtype == __AVstruct) {
    /* This is a kludge for old Sun cc and is probably fragile. */
    if (l->flags & __AV_SUNCC_STRUCT_RETURN) {
      /* Sun cc struct return convention */
      if (l->rsize == sizeof(char)) {
        RETURN(char, ((char*)sp)[-1]);
      } else
      if (l->rsize == sizeof(short)) {
        RETURN(short, ((short*)sp)[-1]);
      } else
      if (l->rsize == sizeof(int)) {
        RETURN(int, ((int*)sp)[-1]);
      } else
      if (l->rsize == sizeof(double)) {
        ((int*)l->raddr)[0] = ((int*)sp)[-2];
        ((int*)l->raddr)[1] = ((int*)sp)[-1];
      } else
      if (l->rsize % 4) {
        char* dstaddr = (char*)l->raddr;
        char* srcaddr = (char*)((long)sp - l->rsize);
        unsigned int count = l->rsize;
        if (count > 4)
          srcaddr = (char*)((long)srcaddr & -4);
        while (count > 0) {
          *dstaddr++ = *srcaddr++;
          count--;
        }
      } else {
        __avword* dstaddr = (__avword*)l->raddr;
        __avword* srcaddr = (__avword*)((long)sp - l->rsize);
        while (srcaddr < sp)
          *dstaddr++ = *srcaddr++;
      }
    } else {
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
          if (l->rsize == sizeof(char)) {
            RETURN(char, i);
          } else
          if (l->rsize == sizeof(short)) {
            RETURN(short, i);
          } else
          if (l->rsize == sizeof(int)) {
            RETURN(int, i);
          }
        }
      }
    }
  }
  return 0;
}

#endif /*_avcall_sparc_c */
