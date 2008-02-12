/* Instruction cache flushing for rs6000, not on AIX */

/*
 * Copyright 1997-1999 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

void __TR_clear_cache (char* first_addr)
{
  /* Taken from egcs-1.1.2/gcc/config/rs6000/tramp.asm. */
  asm volatile ("icbi 0,%0; dcbf 0,%0" : : "r" (first_addr));
  asm volatile ("icbi 0,%0; dcbf 0,%0" : : "r" (first_addr+4));
  asm volatile ("icbi 0,%0; dcbf 0,%0" : : "r" (first_addr+8));
  asm volatile ("icbi 0,%0; dcbf 0,%0" : : "r" (first_addr+12));
  asm volatile ("icbi 0,%0; dcbf 0,%0" : : "r" (first_addr+16));
  asm volatile ("icbi 0,%0; dcbf 0,%0" : : "r" (first_addr+20));
  asm volatile ("icbi 0,%0; dcbf 0,%0" : : "r" (first_addr+24));
  asm volatile ("icbi 0,%0; dcbf 0,%0" : : "r" (first_addr+28));
  asm volatile ("icbi 0,%0; dcbf 0,%0" : : "r" (first_addr+32));
  asm volatile ("sync; isync");
}
