/* Trampoline accessor test */

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

#ifdef __cplusplus
typedef int (*function)(...);
#else
typedef int (*function)();
#endif

#if defined(__STDC__) || defined(__GNUC__) || defined(__cplusplus)
int f (int x)
#else
int f (x)
  int x;
#endif
{ return x; }

void* variable;

static int data;

int main ()
{
  function cf = alloc_trampoline((function)&f, &variable, &data);
  if (is_trampoline((void*)&main))
    { printf("is_trampoline(&main) returns true!\n"); exit(1); }
  if (!is_trampoline((void*)cf))
    { printf("is_trampoline() returns false!\n"); exit(1); }
  if (trampoline_address((void*)cf) != (function)&f)
    { printf("trampoline_address() doesn't work!\n"); exit(1); }
  if (trampoline_variable((void*)cf) != &variable)
    { printf("trampoline_variable() doesn't work!\n"); exit(1); }
  if (trampoline_data((void*)cf) != &data)
    { printf("trampoline_data() doesn't work!\n"); exit(1); }
  printf("test2 passed.\n");
  exit(0);
}
