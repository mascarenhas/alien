/* Instruction cache flushing for hppa */

/*
 * Copyright 1995-1997 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

/*
 * This assumes that the range [first_addr..last_addr] lies in at most two
 * cache lines.
 */
void __TR_clear_cache (char* first_addr, char* last_addr)
{
  register int tmp1;
  register int tmp2;
  /* Flush the relevant data cache lines. (Yes, this is needed. I tried it.) */
  asm volatile ("fdc 0(0,%0)"
         "\n\t" "fdc 0(0,%1)"
         "\n\t" "sync"
                :
                : "r" (first_addr), "r" (last_addr)
               );
  /* Flush the relevant instruction cache lines. */
  asm volatile ("mfsp %%sr0,%1"
         "\n\t" "ldsid (0,%4),%0"
         "\n\t" "mtsp %0,%%sr0"
         "\n\t" "fic 0(%%sr0,%2)"
         "\n\t" "fic 0(%%sr0,%3)"
         "\n\t" "sync"
         "\n\t" "mtsp %1,%%sr0"
         "\n\t" "nop"
         "\n\t" "nop"
         "\n\t" "nop"
         "\n\t" "nop"
         "\n\t" "nop"
         "\n\t" "nop"
                : "=r" (tmp1), "=r" (tmp2)
                : "r" (first_addr), "r" (last_addr), "r" (first_addr)
               );
}
