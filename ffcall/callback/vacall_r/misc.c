/*
 * Copyright 1995-1999 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

#include <stdio.h>
#include <stdlib.h>

#include "vacall_r.h"
#include "config.h"

/* Room for returning structs according to the pcc non-reentrant struct return convention. */
__va_struct_buffer_t __va_struct_buffer;

int /* no return type, since this never returns */
#if defined(__STDC__) || defined(__GNUC__) || defined(__cplusplus)
__va_error1 (enum __VAtype start_type, enum __VAtype return_type)
#else
__va_error1 (start_type, return_type)
  enum __VAtype start_type;
  enum __VAtype return_type;
#endif
{
  /* If you see this, fix your code. */
  fprintf (stderr, "vacall: va_start type %d and va_return type %d disagree.\n",
                   (int)start_type, (int)return_type);
  abort();
#if defined(__cplusplus)
  return 0;
#endif
}

int /* no return type, since this never returns */
#if defined(__STDC__) || defined(__GNUC__) || defined(__cplusplus)
__va_error2 (unsigned int size)
#else
__va_error2 (size)
  unsigned int size;
#endif
{
  /* If you see this, increase __VA_ALIST_WORDS: */
  fprintf (stderr, "vacall: struct of size %u too large for pcc struct return.\n",
                   size);
  abort();
#if defined(__cplusplus)
  return 0;
#endif
}
