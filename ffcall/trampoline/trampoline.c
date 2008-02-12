/* Trampoline construction */

/*
 * Copyright 1995-1999, 2001-2004 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */


#include "config.h"
#include "trampoline.h"

#if defined(__hppa__)
#if 0
#define __hppaold__  /* Old trampoline, real machine code. */
#else
#define __hppanew__  /* New trampoline, just a closure. */
#endif
#endif
#if defined(__rs6000__)
#if !defined(_AIX)
#define __rs6000sysv4__  /* SysV.4 ABI, real machine code. */
#else
#define __rs6000aix__  /* AIX ABI, just a closure. */
#endif
#endif
#if defined(__hppanew__)
/*
 * A function pointer is a biased pointer to a data area whose first word
 * contains the actual address of the function.
 */
extern void tramp (); /* trampoline prototype */
/* We don't need to take any special measures to make the code executable
 * since the actual instructions are in the text segment.
 */
#ifndef CODE_EXECUTABLE
#define CODE_EXECUTABLE
#endif
#endif
#if defined(__rs6000aix__) || defined(__ia64__)
/*
 * A function pointer is a pointer to a data area whose first word contains
 * the actual address of the function.
 */
extern void (*tramp) (); /* trampoline prototype */
/* We don't need to take any special measures to make the code executable
 * since the actual instructions are in the text segment.
 */
#ifndef CODE_EXECUTABLE
#define CODE_EXECUTABLE
#endif
#endif
#if defined(__m68k__)
#if defined(AMIGA) /* Amiga running AmigaOS, not Linux */
#ifndef CODE_EXECUTABLE /* configure guesses wrong?? */
#define CODE_EXECUTABLE
#endif
#endif
#endif

#ifndef CODE_EXECUTABLE
/* How do we make the trampoline's code executable? */
#if defined(HAVE_MACH_VM) || defined(__convex__) || defined(HAVE_WORKING_MPROTECT) || defined(HAVE_SYS_M88KBCS_H)
/* mprotect() [or equivalent] the malloc'ed area. */
#define EXECUTABLE_VIA_MPROTECT
#else
#ifdef HAVE_MMAP
/* Use an mmap'ed page. */
#define EXECUTABLE_VIA_MMAP
#ifdef HAVE_MMAP_ANONYMOUS
/* Use mmap with the MAP_ANONYMOUS or MAP_ANON flag. */
#define EXECUTABLE_VIA_MMAP_ANONYMOUS
#else
/* Use mmap on /dev/zero. */
#define EXECUTABLE_VIA_MMAP_DEVZERO
#endif
#else
#ifdef HAVE_SHM
/* Use an shmat'ed page. */
#define EXECUTABLE_VIA_SHM
#else
??
#endif
#endif
#endif
#endif

#include <stdio.h> /* declares fprintf() */

#include <sys/types.h>
#include <stdlib.h> /* declares abort(), malloc(), free() */
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

/* Declare getpagesize(). */
#ifdef HAVE_GETPAGESIZE
#ifdef __cplusplus
extern "C" RETGETPAGESIZETYPE getpagesize (void);
#elif defined(__STDC__)
extern RETGETPAGESIZETYPE getpagesize (void);
#else
extern RETGETPAGESIZETYPE getpagesize ();
#endif
#else
#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#else
/* Not Unix, e.g. mingw32 */
#define PAGESIZE 4096
#endif
#define getpagesize() PAGESIZE
#endif

/* Declare mprotect() or equivalent. */
#ifdef EXECUTABLE_VIA_MPROTECT
#ifdef HAVE_MACH_VM
#include <sys/resource.h>
#include <mach/mach_interface.h>
#ifdef NeXT
#include <mach/mach_init.h>
#endif
#ifdef __osf__
#include <mach_init.h>
#endif
#include <mach/machine/vm_param.h>
#else
#ifdef HAVE_SYS_M88KBCS_H
#include <sys/m88kbcs.h>
#define getpagesize()  4096  /* ?? */
#else
#include <sys/types.h>
#include <sys/mman.h>
#endif
#endif
#endif

/* Declare mmap(). */
#ifdef EXECUTABLE_VIA_MMAP
#include <sys/types.h>
#include <sys/mman.h>
#if !defined(PROT_EXEC) && defined(PROT_EXECUTE) /* Irix 4.0.5 needs this */
#define PROT_EXEC PROT_EXECUTE
#endif
#endif

/* Declare open(). */
#ifdef EXECUTABLE_VIA_MMAP_DEVZERO
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#ifdef OPEN_NEEDS_SYS_FILE_H
#include <sys/file.h>
#endif
#endif

/* Declare shmget(), shmat(), shmctl(). */
#ifdef EXECUTABLE_VIA_SHM
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#ifdef HAVE_SYS_SYSMACROS_H
#include <sys/sysmacros.h>
#endif
#endif

/* Support for instruction cache flush. */
#ifdef __i386__
#if defined(_WIN32) /* WindowsNT or Windows95 */
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#endif
#endif
#ifdef __m68k__
#if defined(AMIGA) /* Amiga running AmigaOS, not Linux */
#include <exec/types.h>
#include <exec/execbase.h>
#include <proto/exec.h>
#endif
#ifdef hpux
#include <sys/cache.h>
#endif
#endif
#if defined(__mips__) || defined(__mipsn32__) || defined(__mips64__)
#ifdef ultrix
#include <mips/cachectl.h>
#else
#ifdef linux
#include <asm/cachectl.h>
#else
#ifdef HAVE_SYS_CACHECTL_H
#include <sys/cachectl.h>
#endif
#endif
#endif
#endif
#ifdef __m88k__
#include <sys/syslocal.h>
#endif
/* Inline assembly function for instruction cache flush. */
#if defined(__sparc__) || defined(__sparc64__) || defined(__alpha__) || defined(__hppaold__) || defined(__rs6000sysv4__) || defined(__convex__)
#ifdef __GNUC__
extern inline
#if defined(__sparc__) || defined(__sparc64__)
#include "cache-sparc.c"
#endif
#ifdef __alpha__
#include "cache-alpha.c"
#endif
#ifdef __hppa__
#include "cache-hppa.c"
#endif
#ifdef __rs6000__
#include "cache-rs6000.c"
#endif
#ifdef __convex__
#include "cache-convex.c"
#endif
#else
#if defined(__sparc__) || defined(__sparc64__)
extern void __TR_clear_cache_4();
#else
extern void __TR_clear_cache();
#endif
#endif
#endif

/* Length and alignment of trampoline */
#ifdef __i386__
#define TRAMP_LENGTH 15
#define TRAMP_ALIGN 16  /* 4 for a i386, 16 for a i486 */
#endif
#ifdef __m68k__
#define TRAMP_LENGTH 18
#define TRAMP_ALIGN 16
#endif
#if defined(__mips__) && !defined(__mipsn32__)
#define TRAMP_LENGTH 32
#define TRAMP_ALIGN 4
#endif
#ifdef __mipsn32__
#define TRAMP_LENGTH 36
#define TRAMP_ALIGN 4
#endif
#ifdef __mips64old__
#define TRAMP_LENGTH 84
#define TRAMP_ALIGN 4
#endif
#ifdef __mips64__
#define TRAMP_LENGTH 48
#define TRAMP_ALIGN 8
#endif
#if defined(__sparc__) && !defined(__sparc64__)
#define TRAMP_LENGTH 28
#define TRAMP_ALIGN 16
#endif
#ifdef __sparc64__
#define TRAMP_LENGTH 48
#define TRAMP_ALIGN 16
#endif
#ifdef __alpha__
#define TRAMP_LENGTH 48
#define TRAMP_ALIGN 8
#endif
#ifdef __hppaold__
#define TRAMP_LENGTH 56
#define TRAMP_ALIGN 16
#endif
#ifdef __hppanew__
#define TRAMP_LENGTH 20
#define TRAMP_ALIGN 16
#define TRAMP_BIAS 2
#endif
#ifdef __arm__
#define TRAMP_LENGTH 44
#define TRAMP_ALIGN 4
#endif
#ifdef __rs6000sysv4__
#define TRAMP_LENGTH 36
#define TRAMP_ALIGN 4
#endif
#ifdef __rs6000aix__
#define TRAMP_LENGTH 24
#define TRAMP_ALIGN 4
#endif
#ifdef __m88k__
#define TRAMP_LENGTH 32
#define TRAMP_ALIGN 8
#endif
#ifdef __convex__
#define TRAMP_LENGTH 20
#define TRAMP_ALIGN 4
#endif
#ifdef __ia64__
#define TRAMP_LENGTH 40
#define TRAMP_ALIGN 16
#endif
#ifdef __x86_64__
#define TRAMP_LENGTH 32
#define TRAMP_ALIGN 16
#endif
#ifdef __s390__
#define TRAMP_LENGTH 36
#define TRAMP_ALIGN 2
#endif

#ifndef TRAMP_BIAS
#define TRAMP_BIAS 0
#endif

#if !defined(CODE_EXECUTABLE) && !defined(EXECUTABLE_VIA_MPROTECT)
/* AIX doesn't support mprotect() in malloc'ed memory. Must get pages of
 * memory with execute permission via mmap(). Then keep a free list of
 * free trampolines.
 */
static char* freelist = NULL;
#endif

#if defined(__STDC__) || defined(__GNUC__) || defined(__cplusplus)
__TR_function alloc_trampoline (__TR_function address, void* variable, void* data)
#else
__TR_function alloc_trampoline (address, variable, data)
  __TR_function address;
  void* variable;
  void* data;
#endif
{
  char* function;

#if !defined(CODE_EXECUTABLE)
  static long pagesize = 0;
#if defined(EXECUTABLE_VIA_MMAP_DEVZERO)
  static int zero_fd;
#endif
  /* First, get the page size once and for all. */
  if (!pagesize)
    {
#if defined(HAVE_MACH_VM)
      pagesize = vm_page_size;
#else
      pagesize = getpagesize();
#endif
#if defined(EXECUTABLE_VIA_MMAP_DEVZERO)
      zero_fd = open("/dev/zero",O_RDONLY,0644);
      if (zero_fd < 0)
        { fprintf(stderr,"trampoline: Cannot open /dev/zero!\n"); abort(); }
#endif
    }
#endif

  /* 1. Allocate room */

#if !defined(CODE_EXECUTABLE) && !defined(EXECUTABLE_VIA_MPROTECT)
  if (freelist == NULL)
    { /* Get a new page. */
      char* page;
#ifdef EXECUTABLE_VIA_MMAP_ANONYMOUS
      page = mmap(0, pagesize, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_VARIABLE, -1, 0);
#endif
#ifdef EXECUTABLE_VIA_MMAP_DEVZERO
      page = mmap(0, pagesize, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, zero_fd, 0);
#endif
#ifdef EXECUTABLE_VIA_SHM
      int shmid = shmget(IPC_PRIVATE, pagesize, 0700|IPC_CREAT);
      if (shmid<0)
        { page = (char*)(-1); }
      else
        { page = shmat(shmid, 0, 0); shmctl(shmid, IPC_RMID, 0); }
#endif
      if (page == (char*)(-1))
        { fprintf(stderr,"trampoline: Out of virtual memory!\n"); abort(); }
      /* Fill it with free trampolines. */
      { char** last = &freelist;
        char* page_end = page + pagesize;
        while (page+TRAMP_LENGTH <= page_end)
          { *last = page; last = (char**)page; page += TRAMP_LENGTH; }
        *last = NULL;
    } }
  function = freelist; freelist = *(char**)freelist;
#else
  { char* room = (char*) malloc(sizeof(void*) + TRAMP_LENGTH + TRAMP_ALIGN-1);
    if (!room)
      { fprintf(stderr,"trampoline: Out of virtual memory!\n"); abort(); }
    function = (char*)(((long)room + sizeof(void*) + TRAMP_ALIGN-1) & -TRAMP_ALIGN);
    ((char**)function)[-1] = room; /* backpointer for free_trampoline() */
  }
#endif

  /* 2. Fill out the trampoline */
#ifdef __i386__
  /* function:
   *    movl $<data>,<variable>		C7 05 <variable> <data>
   *    jmp <address>			E9 <address>-<here>
   * here:
   */
  *(short *) (function + 0) = 0x05C7;
  *(long *)  (function + 2) = (long) variable;
  *(long *)  (function + 6) = (long) data;
  *(char *)  (function +10) = 0xE9;
  *(long *)  (function +11) = (long) address - (long) (function + 15);
#define is_tramp(function)  \
  *(unsigned short *) (function + 0) == 0x05C7 && \
  *(unsigned char *)  (function +10) == 0xE9
#define tramp_address(function)  \
  *(long *)  (function +11) + (long) (function + 15)
#define tramp_variable(function)  \
  *(long *)  (function + 2)
#define tramp_data(function)  \
  *(long *)  (function + 6)
#endif
#ifdef __m68k__
  /* function:
   *    movel #<data>,<variable>	23 FC <data> <variable>
   *    jmp <address>			4E F9 <address>
   *    nop				4E 71
   */
  *(short *) (function + 0) = 0x23FC;
  *(long *)  (function + 2) = (long) data;
  *(long *)  (function + 6) = (long) variable;
  *(short *) (function +10) = 0x4EF9;
  *(long *)  (function +12) = (long) address;
  *(short *) (function +16) = 0x4E71;
#define is_tramp(function)  \
  *(unsigned short *) (function + 0) == 0x23FC && \
  *(unsigned short *) (function +10) == 0x4EF9 && \
  *(unsigned short *) (function +16) == 0x4E71
#define tramp_address(function)  \
  *(long *)  (function +12)
#define tramp_variable(function)  \
  *(long *)  (function + 6)
#define tramp_data(function)  \
  *(long *)  (function + 2)
#endif
#if defined(__mips__) && !defined(__mipsn32__)
  /* function:
   *    li $2,<data>&0xffff0000		3C 02 hi16(<data>)
   *    ori $2,$2,<data>&0xffff		34 42 lo16(<data>)
   *    sw $2,<variable>		3C 01 hi16(<variable>)
   *    				AC 22 lo16(<variable>)
   *    li $25,<address>&0xffff0000	3C 19 hi16(<address>)
   *    ori $25,$25,<address>&0xffff	37 39 lo16(<address>)
   *    j $25				03 20 00 08
   *    nop				00 00 00 00
   */
  /* What about big endian / little endian ?? */
  *(short *) (function + 0) = 0x3C02;
  *(short *) (function + 2) = (unsigned long) data >> 16;
  *(short *) (function + 4) = 0x3442;
  *(short *) (function + 6) = (unsigned long) data & 0xffff;
  *(short *) (function + 8) = 0x3C01;
  *(short *) (function +10) = (unsigned long) variable >> 16;
  *(short *) (function +12) = 0xAC22;
  *(short *) (function +14) = (unsigned long) variable & 0xffff;
  *(short *) (function +16) = 0x3C19;
  *(short *) (function +18) = (unsigned long) address >> 16;
  *(short *) (function +20) = 0x3739;
  *(short *) (function +22) = (unsigned long) address & 0xffff;
  *(long *)  (function +24) = 0x03200008;
  *(long *)  (function +28) = 0x00000000;
#define is_tramp(function)  \
  *(unsigned short *) (function + 0) == 0x3C02 && \
  *(unsigned short *) (function + 4) == 0x3442 && \
  *(unsigned short *) (function + 8) == 0x3C01 && \
  *(unsigned short *) (function +12) == 0xAC22 && \
  *(unsigned short *) (function +16) == 0x3C19 && \
  *(unsigned short *) (function +20) == 0x3739 && \
  *(unsigned long *)  (function +24) == 0x03200008 && \
  *(unsigned long *)  (function +28) == 0x00000000
#define hilo(hiword,loword)  \
  (((unsigned long) (hiword) << 16) | (unsigned long) (loword))
#define tramp_address(function)  \
  hilo(*(unsigned short *) (function +18), *(unsigned short *) (function +22))
#define tramp_variable(function)  \
  hilo(*(unsigned short *) (function +10), *(unsigned short *) (function +14))
#define tramp_data(function)  \
  hilo(*(unsigned short *) (function + 2), *(unsigned short *) (function + 6))
#endif
#ifdef __mipsn32__
  /* function:
   *    lw $2,24($25)			8F 22 00 18
   *    lw $3,28($25)			8F 23 00 1C
   *    sw $3,0($2)			AC 43 00 00
   *    lw $25,32($25)			8F 39 00 20
   *    j $25				03 20 00 08
   *    nop				00 00 00 00
   *    .word <variable>		<variable>
   *    .word <data>			<data>
   *    .word <address>			<address>
   */
  /* What about big endian / little endian ?? */
  *(unsigned int *) (function + 0) = 0x8F220018;
  *(unsigned int *) (function + 4) = 0x8F23001C;
  *(unsigned int *) (function + 8) = 0xAC430000;
  *(unsigned int *) (function +12) = 0x8F390020;
  *(unsigned int *) (function +16) = 0x03200008;
  *(unsigned int *) (function +20) = 0x00000000;
  *(unsigned int *) (function +24) = (unsigned int) variable;
  *(unsigned int *) (function +28) = (unsigned int) data;
  *(unsigned int *) (function +32) = (unsigned int) address;
#define is_tramp(function)  \
  *(int *)          (function + 0) == 0x8F220018 && \
  *(int *)          (function + 4) == 0x8F23001C && \
  *(int *)          (function + 8) == 0xAC430000 && \
  *(int *)          (function +12) == 0x8F390020 && \
  *(int *)          (function +16) == 0x03200008 && \
  *(int *)          (function +20) == 0x00000000
#define tramp_address(function)  \
  *(unsigned int *) (function +32)
#define tramp_variable(function)  \
  *(unsigned int *) (function +24)
#define tramp_data(function)  \
  *(unsigned int *) (function +28)
#endif
#ifdef __mips64old__
  /* function:
   *    dli $2,<variable>		3C 02 hi16(hi32(<variable>))
   *					34 42 lo16(hi32(<variable>))
   *					00 02 14 38
   *					34 42 hi16(lo32(<variable>))
   *					00 02 14 38
   *					34 42 lo16(lo32(<variable>))
   *    dli $3,<data>			3C 03 hi16(hi32(<data>))
   *					34 63 lo16(hi32(<data>))
   *					00 03 1C 38
   *					34 63 hi16(lo32(<data>))
   *					00 03 1C 38
   *					34 63 lo16(lo32(<data>))
   *    sd $3,0($2)			FC 43 00 00
   *    dli $25,<address>		3C 19 hi16(hi32(<address>))
   *					37 39 lo16(hi32(<address>))
   *					00 19 CC 38
   *					37 39 hi16(lo32(<address>))
   *					00 19 CC 38
   *					37 39 lo16(lo32(<address>))
   *    j $25				03 20 00 08
   *    nop				00 00 00 00
   */
  /* What about big endian / little endian ?? */
  *(short *) (function + 0) = 0x3C02;
  *(short *) (function + 2) = (unsigned long) variable >> 48;
  *(short *) (function + 4) = 0x3442;
  *(short *) (function + 6) = ((unsigned long) variable >> 32) & 0xffff;
  *(int *)   (function + 8) = 0x00021438;
  *(short *) (function +12) = 0x3442;
  *(short *) (function +14) = ((unsigned long) variable >> 16) & 0xffff;
  *(int *)   (function +16) = 0x00021438;
  *(short *) (function +20) = 0x3442;
  *(short *) (function +22) = (unsigned long) variable & 0xffff;
  *(short *) (function +24) = 0x3C03;
  *(short *) (function +26) = (unsigned long) data >> 48;
  *(short *) (function +28) = 0x3463;
  *(short *) (function +30) = ((unsigned long) data >> 32) & 0xffff;
  *(int *)   (function +32) = 0x00031C38;
  *(short *) (function +36) = 0x3463;
  *(short *) (function +38) = ((unsigned long) data >> 16) & 0xffff;
  *(int *)   (function +40) = 0x00031C38;
  *(short *) (function +44) = 0x3463;
  *(short *) (function +46) = (unsigned long) data & 0xffff;
  *(int *)   (function +48) = 0xFC430000;
  *(short *) (function +52) = 0x3C19;
  *(short *) (function +54) = (unsigned long) address >> 48;
  *(short *) (function +56) = 0x3739;
  *(short *) (function +58) = ((unsigned long) address >> 32) & 0xffff;
  *(int *)   (function +60) = 0x0019CC38;
  *(short *) (function +64) = 0x3739;
  *(short *) (function +66) = ((unsigned long) address >> 16) & 0xffff;
  *(int *)   (function +68) = 0x0019CC38;
  *(short *) (function +72) = 0x3739;
  *(short *) (function +74) = (unsigned long) address & 0xffff;
  *(int *)   (function +76) = 0x03200008;
  *(int *)   (function +80) = 0x00000000;
#define is_tramp(function)  \
  *(unsigned short *) (function + 0) == 0x3C02 && \
  *(unsigned short *) (function + 4) == 0x3442 && \
  *(unsigned int *)   (function + 8) == 0x00021438 && \
  *(unsigned short *) (function +12) == 0x3442 && \
  *(unsigned int *)   (function +16) == 0x00021438 && \
  *(unsigned short *) (function +20) == 0x3442 && \
  *(unsigned short *) (function +24) == 0x3C03 && \
  *(unsigned short *) (function +28) == 0x3463 && \
  *(unsigned int *)   (function +32) == 0x00031C38 && \
  *(unsigned short *) (function +36) == 0x3463 && \
  *(unsigned int *)   (function +40) == 0x00031C38 && \
  *(unsigned short *) (function +44) == 0x3463 && \
  *(unsigned int *)   (function +48) == 0xFC430000 && \
  *(unsigned short *) (function +52) == 0x3C19 && \
  *(unsigned short *) (function +56) == 0x3739 && \
  *(unsigned int *)   (function +60) == 0x0019CC38 && \
  *(unsigned short *) (function +64) == 0x3739 && \
  *(unsigned int *)   (function +68) == 0x0019CC38 && \
  *(unsigned short *) (function +72) == 0x3739 && \
  *(unsigned int *)   (function +76) == 0x03200008 && \
  *(unsigned int *)   (function +80) == 0x00000000
#define hilo(word3,word2,word1,word0)  \
  (((unsigned long) (word3) << 48) | ((unsigned long) (word2) << 32) | \
   ((unsigned long) (word1) << 16) | (unsigned long) (word0))
#define tramp_address(function)  \
  hilo(*(unsigned short *) (function +54), \
       *(unsigned short *) (function +58), \
       *(unsigned short *) (function +66), \
       *(unsigned short *) (function +74))
#define tramp_variable(function)  \
  hilo(*(unsigned short *) (function + 2), \
       *(unsigned short *) (function + 6), \
       *(unsigned short *) (function +14), \
       *(unsigned short *) (function +22))
#define tramp_data(function)  \
  hilo(*(unsigned short *) (function +26), \
       *(unsigned short *) (function +30), \
       *(unsigned short *) (function +38), \
       *(unsigned short *) (function +46))
#endif
#ifdef __mips64__
  /* function:
   *    ld $2,24($25)			DF 22 00 18
   *    ld $3,32($25)			DF 23 00 20
   *    sd $3,0($2)			FC 43 00 00
   *    ld $25,40($25)			DF 39 00 28
   *    j $25				03 20 00 08
   *    nop				00 00 00 00
   *    .dword <variable>		<variable>
   *    .dword <data>			<data>
   *    .dword <address>		<address>
   */
  /* What about big endian / little endian ?? */
  *(long *)          (function + 0) = 0xDF220018DF230020L;
  *(long *)          (function + 8) = 0xFC430000DF390028L;
  *(long *)          (function +16) = 0x0320000800000000L;
  *(unsigned long *) (function +24) = (unsigned long) variable;
  *(unsigned long *) (function +32) = (unsigned long) data;
  *(unsigned long *) (function +40) = (unsigned long) address;
#define is_tramp(function)  \
  *(long *)          (function + 0) == 0xDF220018DF230020L && \
  *(long *)          (function + 8) == 0xFC430000DF390028L && \
  *(long *)          (function +16) == 0x0320000800000000L
#define tramp_address(function)  \
  *(unsigned long *) (function +40)
#define tramp_variable(function)  \
  *(unsigned long *) (function +24)
#define tramp_data(function)  \
  *(unsigned long *) (function +32)
#endif
#if defined(__sparc__) && !defined(__sparc64__)
  /* function:
   *    sethi %hi(<variable>),%g1	03000000 | (<variable> >> 10)
   *    sethi %hi(<data>),%g2		05000000 | (<data> >> 10)
   *    or %g2,%lo(<data>),%g2		8410A000 | (<data> & 0x3ff)
   *    st %g2,[%g1+%lo(<variable>)]	C4206000 | (<variable> & 0x3ff)
   *    sethi %hi(<address>),%g1	03000000 | (<address> >> 10)
   *    jmp %g1+%lo(<address>)		81C06000 | (<address> & 0x3ff)
   *    nop				01000000
   */
#define hi(word)  ((unsigned long) (word) >> 10)
#define lo(word)  ((unsigned long) (word) & 0x3ff)
  *(long *) (function + 0) = 0x03000000 | hi(variable);
  *(long *) (function + 4) = 0x05000000 | hi(data);
  *(long *) (function + 8) = 0x8410A000 | lo(data);
  *(long *) (function +12) = 0xC4206000 | lo(variable);
  *(long *) (function +16) = 0x03000000 | hi(address);
  *(long *) (function +20) = 0x81C06000 | lo(address);
  *(long *) (function +24) = 0x01000000;
#define is_tramp(function)  \
  (*(long *) (function + 0) & 0xffc00000) == 0x03000000 && \
  (*(long *) (function + 4) & 0xffc00000) == 0x05000000 && \
  (*(long *) (function + 8) & 0xfffffc00) == 0x8410A000 && \
  (*(long *) (function +12) & 0xfffffc00) == 0xC4206000 && \
  (*(long *) (function +16) & 0xffc00000) == 0x03000000 && \
  (*(long *) (function +20) & 0xfffffc00) == 0x81C06000 && \
   *(long *) (function +24)               == 0x01000000
#define hilo(hiword,loword)  (((hiword) << 10) | ((loword) & 0x3ff))
#define tramp_address(function)  \
  hilo(*(long *) (function +16), *(long *) (function +20))
#define tramp_variable(function)  \
  hilo(*(long *) (function + 0), *(long *) (function +12))
#define tramp_data(function)  \
  hilo(*(long *) (function + 4), *(long *) (function + 8))
#endif
#ifdef __sparc64__
  /* function:
   *    rd %pc,%g1			83414000
   *    ldx [%g1+24],%g2		C4586018
   *    ldx [%g1+32],%g3		C6586020
   *    ldx [%g1+40],%g1		C2586028
   *    jmp %g1				81C04000
   *    stx %g3,[%g2]			C6708000
   *    .long high32(<variable>)	<variable> >> 32
   *    .long low32(<variable>)		<variable> & 0xffffffff
   *    .long high32(<data>)		<data> >> 32
   *    .long low32(<data>)		<data> & 0xffffffff
   *    .long high32(<address>)		<address> >> 32
   *    .long low32(<address>)		<address> & 0xffffffff
   */
  *(int *)  (function + 0) = 0x83414000;
  *(int *)  (function + 4) = 0xC4586018;
  *(int *)  (function + 8) = 0xC6586020;
  *(int *)  (function +12) = 0xC2586028;
  *(int *)  (function +16) = 0x81C04000;
  *(int *)  (function +20) = 0xC6708000;
  *(long *) (function +24) = (long) variable;
  *(long *) (function +32) = (long) data;
  *(long *) (function +40) = (long) address;
#define is_tramp(function)  \
  *(int *)  (function + 0) == 0x83414000 && \
  *(int *)  (function + 4) == 0xC4586018 && \
  *(int *)  (function + 8) == 0xC6586020 && \
  *(int *)  (function +12) == 0xC2586028 && \
  *(int *)  (function +16) == 0x81C04000 && \
  *(int *)  (function +20) == 0xC6708000
#define tramp_address(function)  \
  *(long *) (function +40)
#define tramp_variable(function)  \
  *(long *) (function +24)
#define tramp_data(function)  \
  *(long *) (function +32)
#endif
#ifdef __alpha__
  /* function:
   *    br $1,function..ng	00 00 20 C0
   * function..ng:
   *    ldq $2,20($1)		14 00 41 A4
   *    ldq $3,28($1)		1C 00 61 A4
   *    ldq $27,36($1)		24 00 61 A7
   *    stq $2,0($3)		00 00 43 B4
   *    jmp $31,($27),0		00 00 FB 6B
   *    .quad <data>		<data>
   *    .quad <variable>	<variable>
   *    .quad <address>		<address>
   */
  { static int code [6] =
      { 0xC0200000, 0xA4410014, 0xA461001C, 0xA7610024, 0xB4430000, 0x6BFB0000 };
    int i;
    for (i=0; i<6; i++) { ((int *) function)[i] = code[i]; }
    ((long *) function)[3] = (long) data;
    ((long *) function)[4] = (long) variable;
    ((long *) function)[5] = (long) address;
  }
#define is_tramp(function)  \
  ((int *) function)[0] == 0xC0200000 && \
  ((int *) function)[1] == 0xA4410014 && \
  ((int *) function)[2] == 0xA461001C && \
  ((int *) function)[3] == 0xA7610024 && \
  ((int *) function)[4] == 0xB4430000 && \
  ((int *) function)[5] == 0x6BFB0000
#define tramp_address(function)  \
  ((long *) function)[5]
#define tramp_variable(function)  \
  ((long *) function)[4]
#define tramp_data(function)  \
  ((long *) function)[3]
#endif
#ifdef __hppaold__
  /* function:
   *    ldil L'<data>,%r20		22800000 | hi(<data>)
   *    ldil L'<variable>,%r19		22600000 | hi(<variable>)
   *    ldo R'<data>(%r20),%r20		36940000 | lo(<data>)
   *    stw %r20,R'<variable>(%r19)	6A740000 | lo(<variable>)
   *    ldil L'<address>,%r21		22A00000 | hi(<address>)
   *    ldo R'<address>(%r21),%r21	36B50000 | lo(<address>)
   *    bb,>=,n %r21,30,function2	C7D5C012
   *    depi 0,31,2,%r21		D6A01C1E
   *    ldw 4(0,%r21),%r19		4AB30008
   *    ldw 0(0,%r21),%r21		4AB50000
   * function2:
   *    ldsid (0,%r21),%r1		02A010A1
   *    mtsp %r1,%sr0			00011820
   *    be,n 0(%sr0,%r21)		E2A00002
   *    nop				08000240
   */
  /* When decoding a 21-bit argument in an instruction, the hppa performs
   * the following bit manipulation:
   * assemble21: x[20]...x[0]
   *       --> x[0] x[11]...x[1] x[15]..x[14] x[20]...x[16] x[13]..x[12]
   * When encoding a 21-bit argument into an instruction, we need the
   * to perform the reverse permutation:
   * permute21:  y[20]...y[0]
   *       --> y[6]...y[2] y[8]..y[7] y[1]..y[0] y[19]...y[9] y[20]
   */
#define assemble21(x)  \
  ((((x) & 0x1) << 20) | (((x) & 0xFFE) << 8) | \
   (((x) & 0xC000) >> 7) | (((x) & 0x1F0000) >> 14) | (((x) & 0x3000) >> 12))
#define permute21(y)  \
  ((((y) & 0x7C) << 14) | (((y) & 0x180) << 7) | (((y) & 0x3) << 12) | \
   (((y) & 0xFFE00) >> 8) | (((y) & 0x100000) >> 20))
#define hi(word)  permute21((unsigned long) (word) >> 11)
#define lo(word)  (((unsigned long) (word) & 0x7FF) << 1)
  *(long *) (function + 0) = 0x22800000 | hi(data);
  *(long *) (function + 4) = 0x22600000 | hi(variable);
  *(long *) (function + 8) = 0x36940000 | lo(data);
  *(long *) (function +12) = 0x6A740000 | lo(variable);
  *(long *) (function +16) = 0x22A00000 | hi(address);
  *(long *) (function +20) = 0x36B50000 | lo(address);
  *(long *) (function +24) = 0xC7D5C012;
  *(long *) (function +28) = 0xD6A01C1E;
  *(long *) (function +32) = 0x4AB30008;
  *(long *) (function +36) = 0x4AB50000;
  *(long *) (function +40) = 0x02A010A1;
  *(long *) (function +44) = 0x00011820;
  *(long *) (function +48) = 0xE2A00002;
  *(long *) (function +52) = 0x08000240;
#define is_tramp(function)  \
  ((long) function & 3) == 0 && \
  (*(long *) (function + 0) & 0xffe00000) == 0x22800000 && \
  (*(long *) (function + 4) & 0xffe00000) == 0x22600000 && \
  (*(long *) (function + 8) & 0xfffff000) == 0x36940000 && \
  (*(long *) (function +12) & 0xfffff000) == 0x6A740000 && \
  (*(long *) (function +16) & 0xffe00000) == 0x22A00000 && \
  (*(long *) (function +20) & 0xfffff000) == 0x36B50000 && \
  *(long *) (function +24) == 0xC7D5C012 && \
  *(long *) (function +28) == 0xD6A01C1E && \
  *(long *) (function +32) == 0x4AB30008 && \
  *(long *) (function +36) == 0x4AB50000 && \
  *(long *) (function +40) == 0x02A010A1 && \
  *(long *) (function +44) == 0x00011820 && \
  *(long *) (function +48) == 0xE2A00002 && \
  *(long *) (function +52) == 0x08000240
#define hilo(hiword,loword)  \
  ((assemble21((unsigned long) (hiword)) << 11) | \
   (((unsigned long) (loword) & 0xFFE) >> 1) \
  )
#define tramp_address(function)  \
  hilo(*(long *) (function +16), *(long *) (function +20))
#define tramp_variable(function)  \
  hilo(*(long *) (function + 4), *(long *) (function +12))
#define tramp_data(function)  \
  hilo(*(long *) (function + 0), *(long *) (function + 8))
#endif
#ifdef __hppanew__
  /* function:
   *    .long   tramp
   *    .long   closure
   * closure:
   *    .long   <variable>
   *    .long   <data>
   *    .long   <address>
   */
  { /* work around a bug in gcc 3.* */
    void* tramp_address = &tramp;
    *(long *) (function + 0) = ((long *) ((char*)tramp_address-2))[0];
    *(long *) (function + 4) = (long) (function + 8);
    *(long *) (function + 8) = (long) variable;
    *(long *) (function +12) = (long) data;
    *(long *) (function +16) = (long) address;
  }
#define is_tramp(function)  \
  ((long *) function)[0] == ((long *) ((char*)tramp_address-2))[0]
#define tramp_address(function)  \
  ((long *) function)[4]
#define tramp_variable(function)  \
  ((long *) function)[2]
#define tramp_data(function)  \
  ((long *) function)[3]
#endif
#ifdef __arm__
  /* function:
   *    stmfd   sp!,{r0}			E92D0001
   *    ldr     r0,[pc,#_data-.-8]		E59F0014
   *    ldr     ip,[r0,#0]			E590C000
   *    ldr     r0,[pc,#_variable-.-8]		E59F0010
   *    str     ip,[r0,#0]			E580C000
   *    ldmfd   sp!,{r0}^			E8FD0001
   *    ldr     ip,[pc,#_function-.-8]		E59FC008
   *    ldr     pc,[ip,#0]			E59CF000
   * _data:
   *    .word   <data>				<data>
   * _variable:
   *    .word   <variable>			<variable>
   * _function:
   *    .word   <address>			<address>
   */
  { static long code [8] =
      { 0xE92D0001, 0xE59F0014, 0xE590C000, 0xE59F0010,
        0xE580C000, 0xE8FD0001, 0xE59FC008, 0xE59CF000
      };
    int i;
    for (i=0; i<8; i++) { ((long *) function)[i] = code[i]; }
    ((long *) function)[8] = (long) data;
    ((long *) function)[9] = (long) variable;
    ((long *) function)[10] = (long) address;
  }
#define is_tramp(function)  \
  ((long *) function)[0] == 0xE92D0001 && \
  ((long *) function)[1] == 0xE59F0014 && \
  ((long *) function)[2] == 0xE590C000 && \
  ((long *) function)[3] == 0xE59F0010 && \
  ((long *) function)[4] == 0xE580C000 && \
  ((long *) function)[5] == 0xE8FD0001 && \
  ((long *) function)[6] == 0xE59FC008 && \
  ((long *) function)[7] == 0xE59CF000
#define tramp_address(function)  \
  ((long *) function)[10]
#define tramp_variable(function)  \
  ((long *) function)[9]
#define tramp_data(function)  \
  ((long *) function)[8]
#endif
#ifdef __rs6000sysv4__
  /* function:
   *    {liu|lis} 11,hi16(<variable>)		3D 60 hi16(<variable>)
   *    {oril|ori} 11,11,lo16(<variable>)	61 6B lo16(<variable>)
   *    {liu|lis} 12,hi16(<data>)		3D 80 hi16(<data>)
   *    {oril|ori} 12,12,lo16(<data>)		61 8C lo16(<data>)
   *    {st|stw} 12,0(11)			91 8B 00 00
   *    {liu|lis} 0,hi16(<address>)		3C 00 hi16(<address>)
   *    {oril|ori} 0,0,lo16(<address>)		60 00 lo16(<address>)
   *    mtctr 0					7C 09 03 A6
   *    bctr					4E 80 04 20
   */
  *(short *) (function + 0) = 0x3D60;
  *(short *) (function + 2) = (unsigned long) variable >> 16;
  *(short *) (function + 4) = 0x616B;
  *(short *) (function + 6) = (unsigned long) variable & 0xffff;
  *(short *) (function + 8) = 0x3D80;
  *(short *) (function +10) = (unsigned long) data >> 16;
  *(short *) (function +12) = 0x618C;
  *(short *) (function +14) = (unsigned long) data & 0xffff;
  *(long *)  (function +16) = 0x918B0000;
  *(short *) (function +20) = 0x3C00;
  *(short *) (function +22) = (unsigned long) address >> 16;
  *(short *) (function +24) = 0x6000;
  *(short *) (function +26) = (unsigned long) address & 0xffff;
  *(long *)  (function +28) = 0x7C0903A6;
  *(long *)  (function +32) = 0x4E800420;
#define is_tramp(function)  \
  *(unsigned short *) (function + 0) == 0x3D60 && \
  *(unsigned short *) (function + 4) == 0x616B && \
  *(unsigned short *) (function + 8) == 0x3D80 && \
  *(unsigned short *) (function +12) == 0x618C && \
  *(unsigned long *)  (function +16) == 0x918B0000 && \
  *(unsigned short *) (function +20) == 0x3C00 && \
  *(unsigned short *) (function +24) == 0x6000 && \
  *(unsigned long *)  (function +28) == 0x7C0903A6 && \
  *(unsigned long *)  (function +32) == 0x4E800420
#define hilo(hiword,loword)  \
  (((unsigned long) (hiword) << 16) | (unsigned long) (loword))
#define tramp_address(function)  \
  hilo(*(unsigned short *) (function +22), *(unsigned short *) (function +26))
#define tramp_variable(function)  \
  hilo(*(unsigned short *) (function + 2), *(unsigned short *) (function + 6))
#define tramp_data(function)  \
  hilo(*(unsigned short *) (function +10), *(unsigned short *) (function +14))
#endif
#ifdef __rs6000aix__
  /* function:
   *    .long .tramp
   *    .long .mytoc
   *    .long 0
   * .mytoc:
   *    .long <variable>
   *    .long <data>
   *    .long <address>
   */
  *(long *)  (function + 0) = ((long *) &tramp)[0];
  *(long *)  (function + 4) = (long) (function + 12);
  *(long *)  (function + 8) = 0;
  *(long *)  (function +12) = (long) variable;
  *(long *)  (function +16) = (long) data;
  *(long *)  (function +20) = (long) address;
#define is_tramp(function)  \
  ((long *) function)[0] == ((long *) &tramp)[0]
#define tramp_address(function)  \
  ((long *) function)[5]
#define tramp_variable(function)  \
  ((long *) function)[3]
#define tramp_data(function)  \
  ((long *) function)[4]
#endif
#ifdef __m88k__
  /* function:
   *    or.u    #r13,#r0,hi16(<variable>)	5D A0 hi16(<variable>)
   *    or      #r13,#r13,lo16(<variable>)	59 AD lo16(<variable>)
   *    or.u    #r10,#r0,hi16(<data>)		5D 40 hi16(<data>)
   *    or      #r10,#r10,lo16(<data>)		59 4A lo16(<data>)
   *    st      #r10,#r0,#r13			F5 40 24 0D
   *    or.u    #r13,#r0,hi16(<address>)	5D A0 hi16(<address>)
   *    or      #r13,#r13,lo16(<address>)	59 AD lo16(<address>)
   *    jmp     #r13				F4 00 C0 0D
   */
  *(short *) (function + 0) = 0x5DA0;
  *(short *) (function + 2) = (unsigned long) variable >> 16;
  *(short *) (function + 4) = 0x59AD;
  *(short *) (function + 6) = (unsigned long) variable & 0xffff;
  *(short *) (function + 8) = 0x5D40;
  *(short *) (function +10) = (unsigned long) data >> 16;
  *(short *) (function +12) = 0x594A;
  *(short *) (function +14) = (unsigned long) data & 0xffff;
  *(long *)  (function +16) = 0xF540240D;
  *(short *) (function +20) = 0x5DA0;
  *(short *) (function +22) = (unsigned long) address >> 16;
  *(short *) (function +24) = 0x59AD;
  *(short *) (function +26) = (unsigned long) address & 0xffff;
  *(long *)  (function +28) = 0xF400C00D;
#define is_tramp(function)  \
  *(unsigned short *) (function + 0) == 0x5DA0 && \
  *(unsigned short *) (function + 4) == 0x59AD && \
  *(unsigned short *) (function + 8) == 0x5D40 && \
  *(unsigned short *) (function +12) == 0x594A && \
  *(unsigned long *)  (function +16) == 0xF540240D && \
  *(unsigned short *) (function +20) == 0x5DA0 && \
  *(unsigned short *) (function +24) == 0x59AD && \
  *(unsigned long *)  (function +28) == 0xF400C00D
#define hilo(hiword,loword)  \
  (((unsigned long) (hiword) << 16) | (unsigned long) (loword))
#define tramp_address(function)  \
  hilo(*(unsigned short *) (function +22), *(unsigned short *) (function +26))
#define tramp_variable(function)  \
  hilo(*(unsigned short *) (function + 2), *(unsigned short *) (function + 6))
#define tramp_data(function)  \
  hilo(*(unsigned short *) (function +10), *(unsigned short *) (function +14))
#endif
#ifdef __convex__
  /* function:
   *    ld.w #<data>,s1				11C9 <data>
   *    st.w s1,<variable>			3641 <variable>
   *    jmp <address>				0140 <address>
   *    ds.h 0					0000
   */
  *(short *) (function + 0) = 0x11C9;
  *(long *)  (function + 2) = (unsigned long) data;
  *(short *) (function + 6) = 0x3641;
  *(long *)  (function + 8) = (unsigned long) variable;
  *(short *) (function +12) = 0x0140;
  *(long *)  (function +14) = (unsigned long) address;
  *(short *) (function +18) = 0x0000;
#define is_tramp(function)  \
  *(unsigned short *) (function + 0) == 0x11C9 && \
  *(unsigned short *) (function + 6) == 0x3641 && \
  *(unsigned short *) (function +12) == 0x0140 && \
  *(unsigned short *) (function +18) == 0x0000
#define tramp_address(function)  \
  *(long *)  (function +14)
#define tramp_variable(function)  \
  *(long *)  (function + 8)
#define tramp_data(function)  \
  *(long *)  (function + 2)
#endif
#ifdef __ia64__
  /* function:
   *    data8   tramp
   *    data8   closure
   * closure:
   *    data8   <address>
   *    data8   <variable>
   *    data8   <data>
   */
  *(long *) (function + 0) = (long) &tramp;
  *(long *) (function + 8) = (long) (function + 16);
  *(long *) (function +16) = (long) address;
  *(long *) (function +24) = (long) variable;
  *(long *) (function +32) = (long) data;
#define is_tramp(function)  \
  ((long *) function)[0] == (long) &tramp
#define tramp_address(function)  \
  ((long *) function)[2]
#define tramp_variable(function)  \
  ((long *) function)[3]
#define tramp_data(function)  \
  ((long *) function)[4]
#endif
#ifdef __x86_64__
  /* function:
   *    movabsq $<data>,%rax		48 B8 <data>
   *    movabsq %rax, <variable>	48 A3 <variable>
   *    movabsq $<address>,%rax		48 B8 <address>
   *    jmp *%rax			FF E0
   */
  *(short *) (function + 0) = 0xB848;
  *(short *) (function + 2) = (unsigned long) data & 0xffff;
  *(int *)   (function + 4) = ((unsigned long) data >> 16) & 0xffffffff;
  *(short *) (function + 8) = ((unsigned long) data >> 48) & 0xffff;
  *(short *) (function +10) = 0xA348;
  *(int *)   (function +12) = (unsigned long) variable & 0xffffffff;
  *(int *)   (function +16) = ((unsigned long) variable >> 32) & 0xffffffff;
  *(short *) (function +20) = 0xB848;
  *(short *) (function +22) = (unsigned long) address & 0xffff;
  *(int *)   (function +24) = ((unsigned long) address >> 16) & 0xffffffff;
  *(short *) (function +28) = ((unsigned long) address >> 48) & 0xffff;
  *(short *) (function +30) = 0xE0FF;
#define is_tramp(function)  \
  *(unsigned short *) (function + 0) == 0xB848 && \
  *(unsigned short *) (function +10) == 0xA348 && \
  *(unsigned short *) (function +20) == 0xB848 && \
  *(unsigned short *) (function +30) == 0xE0FF
#define hilo(hiword,loword)  \
  (((unsigned long) (hiword) << 32) | (unsigned long) (loword))
#define himidlo(hishort,midword,loshort)  \
  (((unsigned long) (hishort) << 48) | (unsigned long) (midword) << 16 \
   | (unsigned long) (loshort))
#define tramp_address(function)  \
  himidlo(*(unsigned short *) (function +28), \
          *(unsigned int *)   (function +24), \
          *(unsigned short *) (function +22))
#define tramp_variable(function)  \
  hilo(*(unsigned int *) (function +16), *(unsigned int *) (function +12))
#define tramp_data(function)  \
  himidlo(*(unsigned short *) (function + 8), \
          *(unsigned int *)   (function + 4), \
          *(unsigned short *) (function + 2))
#endif
#ifdef __s390__
  /* function:

        lr      %r0,%r13
        bras    %r13,.LTN0_0
.LT0_0:
.LC0:
        .long   0x73554711
.LC1:
        .long   0x12345678
.LC2:
        .long   0xbabebec0
.LTN0_0:
        l       %r1,.LC0-.LT0_0(%r13)
        mvc     0(4,%r1),.LC1-.LT0_0(%r13)
        l       %r1,.LC2-.LT1_0(%r13)
        lr      %r13,%r0
        br      %r1
  */
  /* What about big endian / little endian ?? */
  *(unsigned short *) (function + 0) = 0x180D;
  *(unsigned int *)   (function + 2) = 0xA7D50008;
  *(unsigned int *)   (function + 6) = (unsigned int) variable;
  *(unsigned int *)   (function +10) = (unsigned int) data;
  *(unsigned int *)   (function +14) = (unsigned int) address;
  *(unsigned int *)   (function +18) = 0x5810D000;
  *(unsigned int *)   (function +22) = 0xD2031000;
  *(unsigned short *) (function +26) = 0xD004;
  *(unsigned int *)   (function +28) = 0x5810D008;
  *(unsigned short *) (function +32) = 0x18D0;
  *(unsigned short *) (function +34) = 0x07f1;
#define is_tramp(function)  \
  *(short *)          (function + 0) == 0x180D && \
  *(int *)            (function + 2) == 0xA7D50008 && \
  *(int *)            (function +18) == 0x5810D000 && \
  *(int *)            (function +22) == 0xD2031000 && \
  *(short *)          (function +26) == 0xD004 && \
  *(int *)            (function +28) == 0x5810D008 && \
  *(short *)          (function +32) == 0x18D0 && \
  *(short *)          (function +34) == 0x07f1
#define tramp_address(function)  \
  *(unsigned int *) (function +14)
#define tramp_variable(function)  \
  *(unsigned int *) (function +6)
#define tramp_data(function)  \
  *(unsigned int *) (function +10)
#endif

  /* 3. Set memory protection to "executable" */

#if !defined(CODE_EXECUTABLE) && defined(EXECUTABLE_VIA_MPROTECT)
  /* Call mprotect on the pages that contain the range. */
  { unsigned long start_addr = (unsigned long) function;
    unsigned long end_addr = (unsigned long) (function + TRAMP_LENGTH);
    start_addr = start_addr & -pagesize;
    end_addr = (end_addr + pagesize-1) & -pagesize;
   {unsigned long len = end_addr - start_addr;
#if defined(HAVE_MACH_VM)
    if (vm_protect(task_self(),start_addr,len,0,VM_PROT_READ|VM_PROT_WRITE|VM_PROT_EXECUTE) != KERN_SUCCESS)
#else
#if defined(__convex__)
    /* Convex OS calls it `mremap()'. */
    mremap(start_addr, &len, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE);
    if (0)
#else
#if defined(HAVE_SYS_M88KBCS_H)
    if (memctl(start_addr, len, MCT_TEXT) == -1)
#else
    if (mprotect((void*)start_addr, len, PROT_READ|PROT_WRITE|PROT_EXEC) < 0)
#endif
#endif
#endif
      { fprintf(stderr,"trampoline: cannot make memory executable\n"); abort(); }
  }}
#endif

  /* 4. Flush instruction cache */
  /* We need this because some CPUs have separate data cache and instruction
   * cache. The freshly built trampoline is visible to the data cache, but not
   * maybe not to the instruction cache. This is hairy.
   */
#if !(defined(__hppanew__) || defined(__rs6000aix__) || defined(__ia64__))
  /* Only needed if we really set up machine instructions. */
#ifdef __i386__
#if defined(_WIN32)
  while (!FlushInstructionCache(GetCurrentProcess(),function,TRAMP_LENGTH))
    continue;
#endif
#endif
#ifdef __m68k__
#if defined(NeXT) && defined(__GNUC__)
  __asm__ __volatile__ ("trap #2");
#endif
#if defined(AMIGA)
  CacheClearE(function,TRAMP_LENGTH,CACRF_ClearI|CACRF_ClearD);
#endif
#if defined(apollo)
  cache_$clear();
#endif
#if defined(hpux)
  cachectl(CC_IPURGE,function,TRAMP_LENGTH);
#endif
#if defined(__NetBSD__) && defined(__GNUC__)
  { register unsigned long _beg __asm__ ("%a1") = (unsigned long) function;
    register unsigned long _len __asm__ ("%d1") = TRAMP_LENGTH;
    __asm__ __volatile__ (
      "move%.l %#0x80000004,%/d0\n\t" /* CC_EXTPURGE | C_IPURGE */
      "trap #12"                      /* kernel call `cachectl' */
      :
      : "a" (_beg), "d" (_len)
      : "%a0", "%a1", "%d0", "%d1"    /* call-used registers */
      );
  }
#endif
#if defined(__linux__) && defined(__GNUC__)
  { register unsigned long _beg __asm__ ("%d1") = (unsigned long) function;
    register unsigned long _len __asm__ ("%d4") = TRAMP_LENGTH + 32;
    __asm__ __volatile__ (
      "move%.l %#123,%/d0\n\t"
      "move%.l %#1,%/d2\n\t"
      "move%.l %#3,%/d3\n\t"
      "trap %#0"
      :
      : "d" (_beg), "d" (_len)
      : "%d0", "%d2", "%d3"
      );
  }
#endif
#if defined(AUX) && defined(__GNUC__)
  /* sysm68k(105, addr, scope, cache, len) */
  __asm__ __volatile__ (
    "move%.l %1,%/sp@-\n\t"
    "move%.l %#3,%/sp@-\n\t"
    "move%.l %#1,%/sp@-\n\t"
    "move%.l %0,%/sp@-\n\t"
    "move%.l %#105,%/sp@-\n\t"
    "move%.l %#0,%/sp@-\n\t"
    "move%.l %#38,%/sp@-\n\t"
    "trap %#0\n\t"
    "add%.l %#24,%/sp"
    :
    : "r" (function), "g" ((int)TRAMP_LENGTH)
    : "%d0"
    );
#endif
#endif
#if defined(__mips__) || defined(__mipsn32__) || defined(__mips64__)
  cacheflush(function,TRAMP_LENGTH,ICACHE);
  /* gforth-0.3.0 uses BCACHE instead of ICACHE. Why?? */
#endif
#if defined(__sparc__) || defined(__sparc64__)
  /* This assumes that the trampoline fits in at most four cache lines. */
  __TR_clear_cache_4(function,function+TRAMP_LENGTH-1);
#endif
#ifdef __alpha__
  __TR_clear_cache();
#endif
#ifdef __hppa__
  /* This assumes that the trampoline fits in at most two cache lines. */
  __TR_clear_cache(function,function+TRAMP_LENGTH-1);
#endif
#ifdef __arm__
  /* This CPU does not have a separate instruction cache. (I think.) */
#endif
#ifdef __rs6000__
  __TR_clear_cache(function);
#endif
#ifdef __m88k__
  sysmot(S88CACHEFLUSHPAGE, (unsigned long)function & -pagesize);
#endif
#ifdef __convex__
  __TR_clear_cache();
#endif
#endif

  /* 5. Return. */
  return (__TR_function) (function + TRAMP_BIAS);
}

#if defined(__STDC__) || defined(__GNUC__) || defined(__cplusplus)
void free_trampoline (__TR_function function)
#else
void free_trampoline (function)
  __TR_function function;
#endif
{
#if TRAMP_BIAS
  function = (__TR_function)((char*)function - TRAMP_BIAS);
#endif
#if !defined(CODE_EXECUTABLE) && !defined(EXECUTABLE_VIA_MPROTECT)
  *(char**)function = freelist; freelist = (char*)function;
  /* It is probably not worth calling munmap() for entirely freed pages. */
#else
  free(((char**)function)[-1]);
#endif
}

#if defined(__STDC__) || defined(__GNUC__) || defined(__cplusplus)
int is_trampoline (void* function)
#else
int is_trampoline (function)
  void* function;
#endif
{
#ifdef is_tramp
#ifdef __hppanew__
  void* tramp_address = &tramp;
  if (!(((long)function & 3) == (TRAMP_BIAS & 3))) return 0;
#endif
  return ((is_tramp(((char*)function - TRAMP_BIAS))) ? 1 : 0);
#else
  abort();
#endif
}

#if defined(__STDC__) || defined(__GNUC__) || defined(__cplusplus)
__TR_function trampoline_address (void* function)
#else
__TR_function trampoline_address (function)
  void* function;
#endif
{
#ifdef tramp_address
  return (__TR_function)(tramp_address(((char*)function - TRAMP_BIAS)));
#else
  abort();
#endif
}

#if defined(__STDC__) || defined(__GNUC__) || defined(__cplusplus)
void* trampoline_variable (void* function)
#else
void* trampoline_variable (function)
  void* function;
#endif
{
#ifdef tramp_variable
  return (void*)(tramp_variable(((char*)function - TRAMP_BIAS)));
#else
  abort();
#endif
}

#if defined(__STDC__) || defined(__GNUC__) || defined(__cplusplus)
void* trampoline_data (void* function)
#else
void* trampoline_data (function)
  void* function;
#endif
{
#ifdef tramp_data
  return (void*)(tramp_data(((char*)function - TRAMP_BIAS)));
#else
  abort();
#endif
}
