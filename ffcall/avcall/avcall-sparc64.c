#ifndef _avcall_sparc64_c				/*-*- C -*-*/
#define _avcall_sparc64_c
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

  Foreign function interface for a Sparc v9 in 64-bit mode with gcc.

  This calls a C function with an argument list built up using macros
  defined in av_call.h.

  Sparc 64-bit Argument Passing Conventions

  The argument registers are laid out as an array of 16 elements
  and arguments are added sequentially.  The first 6 int args and up to the
  first 16 fp args (depending on size) are passed in regs.

  Slot    Stack   Integral   Float   Float in structure   Double   Long Double
  ----    -----   --------   -----   ------------------   ------   -----------
   15   [SP+248]              %f31       %f30,%f31         %d30
   14   [SP+240]              %f29       %f28,%f29         %d28       %q28
   13   [SP+232]              %f27       %f26,%f27         %d26
   12   [SP+224]              %f25       %f24,%f25         %d24       %q24
   11   [SP+216]              %f23       %f22,%f23         %d22
   10   [SP+208]              %f21       %f20,%f21         %d20       %q20
    9   [SP+200]              %f19       %f18,%f19         %d18
    8   [SP+192]              %f17       %f16,%f17         %d16       %q16
    7   [SP+184]              %f15       %f14,%f15         %d14
    6   [SP+176]              %f13       %f12,%f13         %d12       %q12
    5   [SP+168]     %o5      %f11       %f10,%f11         %d10
    4   [SP+160]     %o4       %f9        %f8,%f9           %d8        %q8
    3   [SP+152]     %o3       %f7        %f6,%f7           %d6
    2   [SP+144]     %o2       %f5        %f4,%f5           %d4        %q4
    1   [SP+136]     %o1       %f3        %f2,%f3           %d2
    0   [SP+128]     %o0       %f1        %f0,%f1           %d0        %q0

  Here SP = %sp if -mno-stack-bias or %sp+stack_bias otherwise.

  Integral arguments are always passed as 64 bit quantities appropriately
  extended.

  Passing of floating point values is handled as follows.
  If a prototype is in scope:
    If the value is in a named argument (i.e. not a stdarg function or a
    value not part of the `...') then the value is passed in the appropriate
    fp reg.
    If the value is part of the `...' and is passed in one of the first 6
    slots then the value is passed in the appropriate int reg.
    If the value is part of the `...' and is not passed in one of the first 6
    slots then the value is passed in memory.
  If a prototype is not in scope:
    If the value is one of the first 6 arguments the value is passed in the
    appropriate integer reg and the appropriate fp reg.
    If the value is not one of the first 6 arguments the value is passed in
    the appropriate fp reg and in memory.

  Remaining arguments are pushed onto the stack starting at a fixed offset
  Space is left on the stack frame for temporary storage of the register
  arguments as well.

  Integers shorter than `long' are always promoted to word-length
  (zero-extended or sign-extended, according to their type). Structures
  <= 16 bytes are passed embedded in the argument sequence; bigger structures
  are passed by reference.

  Integers and pointers are returned in o0, floats in f0, doubles in
  f0/f1.  If the function returns a structure a pointer to space
  allocated by the caller is pushed onto the stack immediately
  before the function arguments. Structures <= 32 bytes are returned in
  registers (integer/float/double registers, as appropriate).

  Long doubles are 16-byte aligned, but we don't deal with this here, so
  we assume 8-byte alignment for everything.

  ----------------------------------------------------------------------*/
#include "avcall.h.in"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))
#define OFFSETOF(struct,member) ((int)&(((struct*)0)->member))

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
  register __avword* sp	__asm__("%sp");  /* C names for registers */
  register float fret	__asm__("%f0");  /* %f0 */
  register double dret	__asm__("%f0");  /* %f0,%f1 */

  __avword trampoline[6];		/* room for a trampoline */
  __avword space[__AV_ALIST_WORDS];	/* space for callee's stack frame */
  __avword *argframe = sp + 17;		/* stack offset for argument list */
  int arglen = l->aptr - l->args;
  __avword i;

  if (l->farg_mask) {
    /* push leading float args */
    if (l->farg_mask & (1<<0))
      __asm__("ld %1(%0),%%f1" : : "p" (l), "i" OFFSETOF(av_alist,args[0]));
    if (l->farg_mask & (1<<1))
      __asm__("ld %1(%0),%%f3" : : "p" (l), "i" OFFSETOF(av_alist,args[1]));
    if (l->farg_mask & (1<<2))
      __asm__("ld %1(%0),%%f5" : : "p" (l), "i" OFFSETOF(av_alist,args[2]));
    if (l->farg_mask & (1<<3))
      __asm__("ld %1(%0),%%f7" : : "p" (l), "i" OFFSETOF(av_alist,args[3]));
    if (l->farg_mask & (1<<4))
      __asm__("ld %1(%0),%%f9" : : "p" (l), "i" OFFSETOF(av_alist,args[4]));
    if (l->farg_mask & (1<<5))
      __asm__("ld %1(%0),%%f11" : : "p" (l), "i" OFFSETOF(av_alist,args[5]));
    if (l->farg_mask & (1<<6))
      __asm__("ld %1(%0),%%f13" : : "p" (l), "i" OFFSETOF(av_alist,args[6]));
    if (l->farg_mask & (1<<7))
      __asm__("ld %1(%0),%%f15" : : "p" (l), "i" OFFSETOF(av_alist,args[7]));
    if (l->farg_mask & (1<<8))
      __asm__("ld %1(%0),%%f17" : : "p" (l), "i" OFFSETOF(av_alist,args[8]));
    if (l->farg_mask & (1<<9))
      __asm__("ld %1(%0),%%f19" : : "p" (l), "i" OFFSETOF(av_alist,args[9]));
    if (l->farg_mask & (1<<10))
      __asm__("ld %1(%0),%%f21" : : "p" (l), "i" OFFSETOF(av_alist,args[10]));
    if (l->farg_mask & (1<<11))
      __asm__("ld %1(%0),%%f23" : : "p" (l), "i" OFFSETOF(av_alist,args[11]));
    if (l->farg_mask & (1<<12))
      __asm__("ld %1(%0),%%f25" : : "p" (l), "i" OFFSETOF(av_alist,args[12]));
    if (l->farg_mask & (1<<13))
      __asm__("ld %1(%0),%%f27" : : "p" (l), "i" OFFSETOF(av_alist,args[13]));
    if (l->farg_mask & (1<<14))
      __asm__("ld %1(%0),%%f29" : : "p" (l), "i" OFFSETOF(av_alist,args[14]));
    if (l->farg_mask & (1<<15))
      __asm__("ld %1(%0),%%f31" : : "p" (l), "i" OFFSETOF(av_alist,args[15]));
  }
  if (l->darg_mask) {
    /* push leading double args */
    if (l->darg_mask & (1<<0))
      __asm__("ldd %1(%0),%%f0" : : "p" (l), "i" OFFSETOF(av_alist,args[0]));
    if (l->darg_mask & (1<<1))
      __asm__("ldd %1(%0),%%f2" : : "p" (l), "i" OFFSETOF(av_alist,args[1]));
    if (l->darg_mask & (1<<2))
      __asm__("ldd %1(%0),%%f4" : : "p" (l), "i" OFFSETOF(av_alist,args[2]));
    if (l->darg_mask & (1<<3))
      __asm__("ldd %1(%0),%%f6" : : "p" (l), "i" OFFSETOF(av_alist,args[3]));
    if (l->darg_mask & (1<<4))
      __asm__("ldd %1(%0),%%f8" : : "p" (l), "i" OFFSETOF(av_alist,args[4]));
    if (l->darg_mask & (1<<5))
      __asm__("ldd %1(%0),%%f10" : : "p" (l), "i" OFFSETOF(av_alist,args[5]));
    if (l->darg_mask & (1<<6))
      __asm__("ldd %1(%0),%%f12" : : "p" (l), "i" OFFSETOF(av_alist,args[6]));
    if (l->darg_mask & (1<<7))
      __asm__("ldd %1(%0),%%f14" : : "p" (l), "i" OFFSETOF(av_alist,args[7]));
    if (l->darg_mask & (1<<8))
      __asm__("ldd %1(%0),%%f16" : : "p" (l), "i" OFFSETOF(av_alist,args[8]));
    if (l->darg_mask & (1<<9))
      __asm__("ldd %1(%0),%%f18" : : "p" (l), "i" OFFSETOF(av_alist,args[9]));
    if (l->darg_mask & (1<<10))
      __asm__("ldd %1(%0),%%f20" : : "p" (l), "i" OFFSETOF(av_alist,args[10]));
    if (l->darg_mask & (1<<11))
      __asm__("ldd %1(%0),%%f22" : : "p" (l), "i" OFFSETOF(av_alist,args[11]));
    if (l->darg_mask & (1<<12))
      __asm__("ldd %1(%0),%%f24" : : "p" (l), "i" OFFSETOF(av_alist,args[12]));
    if (l->darg_mask & (1<<13))
      __asm__("ldd %1(%0),%%f26" : : "p" (l), "i" OFFSETOF(av_alist,args[13]));
    if (l->darg_mask & (1<<14))
      __asm__("ldd %1(%0),%%f28" : : "p" (l), "i" OFFSETOF(av_alist,args[14]));
    if (l->darg_mask & (1<<15))
      __asm__("ldd %1(%0),%%f30" : : "p" (l), "i" OFFSETOF(av_alist,args[15]));
  }

  {
    int i;
    for (i = 6; i < arglen; i++)	/* push excess function args */
      argframe[i] = l->args[i];
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
          if (l->rsize >= 8 && l->rsize <= 32) {
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
              ((unsigned char *)l->raddr)[8+0] = (unsigned char)(o1>>56);
            } else
            if (l->rsize == 10) {
              ((unsigned char *)l->raddr)[8+0] = (unsigned char)(o1>>56);
              ((unsigned char *)l->raddr)[8+1] = (unsigned char)(o1>>48);
            } else
            if (l->rsize == 11) {
              ((unsigned char *)l->raddr)[8+0] = (unsigned char)(o1>>56);
              ((unsigned char *)l->raddr)[8+1] = (unsigned char)(o1>>48);
              ((unsigned char *)l->raddr)[8+2] = (unsigned char)(o1>>40);
            } else
            if (l->rsize == 12) {
              ((unsigned char *)l->raddr)[8+0] = (unsigned char)(o1>>56);
              ((unsigned char *)l->raddr)[8+1] = (unsigned char)(o1>>48);
              ((unsigned char *)l->raddr)[8+2] = (unsigned char)(o1>>40);
              ((unsigned char *)l->raddr)[8+3] = (unsigned char)(o1>>32);
            } else
            if (l->rsize == 13) {
              ((unsigned char *)l->raddr)[8+0] = (unsigned char)(o1>>56);
              ((unsigned char *)l->raddr)[8+1] = (unsigned char)(o1>>48);
              ((unsigned char *)l->raddr)[8+2] = (unsigned char)(o1>>40);
              ((unsigned char *)l->raddr)[8+3] = (unsigned char)(o1>>32);
              ((unsigned char *)l->raddr)[8+4] = (unsigned char)(o1>>24);
            } else
            if (l->rsize == 14) {
              ((unsigned char *)l->raddr)[8+0] = (unsigned char)(o1>>56);
              ((unsigned char *)l->raddr)[8+1] = (unsigned char)(o1>>48);
              ((unsigned char *)l->raddr)[8+2] = (unsigned char)(o1>>40);
              ((unsigned char *)l->raddr)[8+3] = (unsigned char)(o1>>32);
              ((unsigned char *)l->raddr)[8+4] = (unsigned char)(o1>>24);
              ((unsigned char *)l->raddr)[8+5] = (unsigned char)(o1>>16);
            } else
            if (l->rsize == 15) {
              ((unsigned char *)l->raddr)[8+0] = (unsigned char)(o1>>56);
              ((unsigned char *)l->raddr)[8+1] = (unsigned char)(o1>>48);
              ((unsigned char *)l->raddr)[8+2] = (unsigned char)(o1>>40);
              ((unsigned char *)l->raddr)[8+3] = (unsigned char)(o1>>32);
              ((unsigned char *)l->raddr)[8+4] = (unsigned char)(o1>>24);
              ((unsigned char *)l->raddr)[8+5] = (unsigned char)(o1>>16);
              ((unsigned char *)l->raddr)[8+6] = (unsigned char)(o1>>8);
            } else
            if (l->rsize >= 16 && l->rsize <= 32) {
              ((unsigned char *)l->raddr)[8+0] = (unsigned char)(o1>>56);
              ((unsigned char *)l->raddr)[8+1] = (unsigned char)(o1>>48);
              ((unsigned char *)l->raddr)[8+2] = (unsigned char)(o1>>40);
              ((unsigned char *)l->raddr)[8+3] = (unsigned char)(o1>>32);
              ((unsigned char *)l->raddr)[8+4] = (unsigned char)(o1>>24);
              ((unsigned char *)l->raddr)[8+5] = (unsigned char)(o1>>16);
              ((unsigned char *)l->raddr)[8+6] = (unsigned char)(o1>>8);
              ((unsigned char *)l->raddr)[8+7] = (unsigned char)(o1);
              if (l->rsize == 16) {
              } else
              if (l->rsize == 17) {
                ((unsigned char *)l->raddr)[16+0] = (unsigned char)(o2>>56);
              } else
              if (l->rsize == 18) {
                ((unsigned char *)l->raddr)[16+0] = (unsigned char)(o2>>56);
                ((unsigned char *)l->raddr)[16+1] = (unsigned char)(o2>>48);
              } else
              if (l->rsize == 19) {
                ((unsigned char *)l->raddr)[16+0] = (unsigned char)(o2>>56);
                ((unsigned char *)l->raddr)[16+1] = (unsigned char)(o2>>48);
                ((unsigned char *)l->raddr)[16+2] = (unsigned char)(o2>>40);
              } else
              if (l->rsize == 20) {
                ((unsigned char *)l->raddr)[16+0] = (unsigned char)(o2>>56);
                ((unsigned char *)l->raddr)[16+1] = (unsigned char)(o2>>48);
                ((unsigned char *)l->raddr)[16+2] = (unsigned char)(o2>>40);
                ((unsigned char *)l->raddr)[16+3] = (unsigned char)(o2>>32);
              } else
              if (l->rsize == 21) {
                ((unsigned char *)l->raddr)[16+0] = (unsigned char)(o2>>56);
                ((unsigned char *)l->raddr)[16+1] = (unsigned char)(o2>>48);
                ((unsigned char *)l->raddr)[16+2] = (unsigned char)(o2>>40);
                ((unsigned char *)l->raddr)[16+3] = (unsigned char)(o2>>32);
                ((unsigned char *)l->raddr)[16+4] = (unsigned char)(o2>>24);
              } else
              if (l->rsize == 22) {
                ((unsigned char *)l->raddr)[16+0] = (unsigned char)(o2>>56);
                ((unsigned char *)l->raddr)[16+1] = (unsigned char)(o2>>48);
                ((unsigned char *)l->raddr)[16+2] = (unsigned char)(o2>>40);
                ((unsigned char *)l->raddr)[16+3] = (unsigned char)(o2>>32);
                ((unsigned char *)l->raddr)[16+4] = (unsigned char)(o2>>24);
                ((unsigned char *)l->raddr)[16+5] = (unsigned char)(o2>>16);
              } else
              if (l->rsize == 23) {
                ((unsigned char *)l->raddr)[16+0] = (unsigned char)(o2>>56);
                ((unsigned char *)l->raddr)[16+1] = (unsigned char)(o2>>48);
                ((unsigned char *)l->raddr)[16+2] = (unsigned char)(o2>>40);
                ((unsigned char *)l->raddr)[16+3] = (unsigned char)(o2>>32);
                ((unsigned char *)l->raddr)[16+4] = (unsigned char)(o2>>24);
                ((unsigned char *)l->raddr)[16+5] = (unsigned char)(o2>>16);
                ((unsigned char *)l->raddr)[16+6] = (unsigned char)(o2>>8);
              } else
              if (l->rsize >= 24 && l->rsize <= 32) {
                ((unsigned char *)l->raddr)[16+0] = (unsigned char)(o2>>56);
                ((unsigned char *)l->raddr)[16+1] = (unsigned char)(o2>>48);
                ((unsigned char *)l->raddr)[16+2] = (unsigned char)(o2>>40);
                ((unsigned char *)l->raddr)[16+3] = (unsigned char)(o2>>32);
                ((unsigned char *)l->raddr)[16+4] = (unsigned char)(o2>>24);
                ((unsigned char *)l->raddr)[16+5] = (unsigned char)(o2>>16);
                ((unsigned char *)l->raddr)[16+6] = (unsigned char)(o2>>8);
                ((unsigned char *)l->raddr)[16+7] = (unsigned char)(o2);
                if (l->rsize == 24) {
                } else
                if (l->rsize == 25) {
                  ((unsigned char *)l->raddr)[24+0] = (unsigned char)(o3>>56);
                } else
                if (l->rsize == 26) {
                  ((unsigned char *)l->raddr)[24+0] = (unsigned char)(o3>>56);
                  ((unsigned char *)l->raddr)[24+1] = (unsigned char)(o3>>48);
                } else
                if (l->rsize == 27) {
                  ((unsigned char *)l->raddr)[24+0] = (unsigned char)(o3>>56);
                  ((unsigned char *)l->raddr)[24+1] = (unsigned char)(o3>>48);
                  ((unsigned char *)l->raddr)[24+2] = (unsigned char)(o3>>40);
                } else
                if (l->rsize == 28) {
                  ((unsigned char *)l->raddr)[24+0] = (unsigned char)(o3>>56);
                  ((unsigned char *)l->raddr)[24+1] = (unsigned char)(o3>>48);
                  ((unsigned char *)l->raddr)[24+2] = (unsigned char)(o3>>40);
                  ((unsigned char *)l->raddr)[24+3] = (unsigned char)(o3>>32);
                } else
                if (l->rsize == 29) {
                  ((unsigned char *)l->raddr)[24+0] = (unsigned char)(o3>>56);
                  ((unsigned char *)l->raddr)[24+1] = (unsigned char)(o3>>48);
                  ((unsigned char *)l->raddr)[24+2] = (unsigned char)(o3>>40);
                  ((unsigned char *)l->raddr)[24+3] = (unsigned char)(o3>>32);
                  ((unsigned char *)l->raddr)[24+4] = (unsigned char)(o3>>24);
                } else
                if (l->rsize == 30) {
                  ((unsigned char *)l->raddr)[24+0] = (unsigned char)(o3>>56);
                  ((unsigned char *)l->raddr)[24+1] = (unsigned char)(o3>>48);
                  ((unsigned char *)l->raddr)[24+2] = (unsigned char)(o3>>40);
                  ((unsigned char *)l->raddr)[24+3] = (unsigned char)(o3>>32);
                  ((unsigned char *)l->raddr)[24+4] = (unsigned char)(o3>>24);
                  ((unsigned char *)l->raddr)[24+5] = (unsigned char)(o3>>16);
                } else
                if (l->rsize == 31) {
                  ((unsigned char *)l->raddr)[24+0] = (unsigned char)(o3>>56);
                  ((unsigned char *)l->raddr)[24+1] = (unsigned char)(o3>>48);
                  ((unsigned char *)l->raddr)[24+2] = (unsigned char)(o3>>40);
                  ((unsigned char *)l->raddr)[24+3] = (unsigned char)(o3>>32);
                  ((unsigned char *)l->raddr)[24+4] = (unsigned char)(o3>>24);
                  ((unsigned char *)l->raddr)[24+5] = (unsigned char)(o3>>16);
                  ((unsigned char *)l->raddr)[24+6] = (unsigned char)(o3>>8);
                } else
                if (l->rsize == 32) {
                  ((unsigned char *)l->raddr)[24+0] = (unsigned char)(o3>>56);
                  ((unsigned char *)l->raddr)[24+1] = (unsigned char)(o3>>48);
                  ((unsigned char *)l->raddr)[24+2] = (unsigned char)(o3>>40);
                  ((unsigned char *)l->raddr)[24+3] = (unsigned char)(o3>>32);
                  ((unsigned char *)l->raddr)[24+4] = (unsigned char)(o3>>24);
                  ((unsigned char *)l->raddr)[24+5] = (unsigned char)(o3>>16);
                  ((unsigned char *)l->raddr)[24+6] = (unsigned char)(o3>>8);
                  ((unsigned char *)l->raddr)[24+7] = (unsigned char)(o3);
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

#endif /*_avcall_sparc64_c */
