#ifndef _CALLBACK_H
#define _CALLBACK_H

/*
 * Copyright 1997-1999 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

#include "vacall_r.h"
#include "trampoline_r.h"

#if defined(__STDC__) || defined(__GNUC__) || defined(__cplusplus)
typedef void (*__VA_function) (void*, va_alist);
#else
typedef void (*__VA_function) ();
#endif

#if 0
extern __TR_function alloc_callback (__VA_function, void*);
extern void free_callback (__TR_function);
extern int is_callback (void*);
extern __VA_function callback_address (void*);
extern void* callback_data (void*);
#else
#define alloc_callback(address,data)  \
  alloc_trampoline_r((__TR_function)&__vacall_r,(void*)(__VA_function)(address),(void*)(data))
#define free_callback(function)  \
  free_trampoline_r(function)
#define is_callback(function)  \
  (is_trampoline_r(function)                                       \
   && trampoline_r_address(function) == (__TR_function)&__vacall_r \
  )
#define callback_address(function)  \
  (__VA_function)trampoline_r_data0(function)
#define callback_data(function)  \
  trampoline_r_data1(function)
#endif

#endif /* _CALLBACK_H */
