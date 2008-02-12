/* Trampoline test */

/*
 * Copyright 1995-1999, 2002 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

#include <stdio.h>
#include <stdlib.h>

#include "trampoline.h"

#define MAGIC1  0x9db9af42
#define MAGIC2  0x614a13c9

static int magic = MAGIC1;

#ifdef __cplusplus
typedef int (*function)(...);
#else
typedef int (*function)();
#endif

void* function_data;

#if defined(__STDC__) || defined(__GNUC__) || defined(__cplusplus)
int f (int x)
#else
int f (x)
  int x;
#endif
{ return *(int*)function_data + x; }

int main ()
{
  function cf = alloc_trampoline((function)&f, &function_data, &magic);
  /* calling cf shall set  function_data = &magic  and then call f(x),
   * thus returning  magic + x.
   */
  if (((*cf)(MAGIC2) == MAGIC1+MAGIC2) && (function_data == &magic))
    { free_trampoline(cf); printf("Works, test1 passed.\n"); exit(0); }
  else
    { printf("Doesn't work!\n"); exit(1); }
}
