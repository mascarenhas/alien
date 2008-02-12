#ifndef _TRAMPOLINE_R_H
#define _TRAMPOLINE_R_H

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
extern __TR_function alloc_trampoline_r (__TR_function, void*, void*);
extern void free_trampoline_r (__TR_function);
extern int is_trampoline_r (void*);
extern __TR_function trampoline_r_address (void*);
extern void* trampoline_r_data0 (void*);
extern void* trampoline_r_data1 (void*);
#else
extern __TR_function alloc_trampoline_r ();
extern void free_trampoline_r ();
extern int is_trampoline_r ();
extern __TR_function trampoline_r_address ();
extern void* trampoline_r_data0 ();
extern void* trampoline_r_data1 ();
#endif

#endif /* _TRAMPOLINE_R_H */
