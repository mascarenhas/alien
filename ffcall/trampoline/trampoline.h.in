#ifndef _TRAMPOLINE_H
#define _TRAMPOLINE_H

/*
 * Copyright 1995-1999 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

#ifdef __cplusplus
typedef int (*__TR_function) (...);
#else
typedef int (*__TR_function) ();
#endif
#if defined(__STDC__) || defined(__GNUC__) || defined(__cplusplus)
extern __TR_function alloc_trampoline (__TR_function, void*, void*);
extern void free_trampoline (__TR_function);
extern int is_trampoline (void*);
extern __TR_function trampoline_address (void*);
extern void* trampoline_variable (void*);
extern void* trampoline_data (void*);
#else
extern __TR_function alloc_trampoline ();
extern void free_trampoline ();
extern int is_trampoline ();
extern __TR_function trampoline_address ();
extern void* trampoline_variable ();
extern void* trampoline_data ();
#endif

#endif /* _TRAMPOLINE_H */
