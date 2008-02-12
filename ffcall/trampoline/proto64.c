/* Sample prototype for a trampoline. */

/*
 * Copyright 1995-1996 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

#define function  (int (*) ()) 0xbabebec0dea0ffabL
#define variable  *(void**)    0x1234567813578765L
#define data      (void*)      0x7355471143622155L

int tramp ()
{ variable = data;
  return (*function)();
}

int jump ()
{ goto *function; }

