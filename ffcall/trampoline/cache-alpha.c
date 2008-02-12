/* Instruction cache flushing for alpha */

/*
 * Copyright 1997 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

void __TR_clear_cache (void)
{
  /* Taken from gforth-0.3.0. */
  asm volatile ("call_pal 0x86"); /* imb (instruction-memory barrier) */
}
