#ifndef _avcall_h				/*-*- C -*-*/
#define _avcall_h
/**
  Copyright 1993 Bill Triggs, <Bill.Triggs@inrialpes.fr>

  Copyright 1995-2004 Bruno Haible, <bruno@clisp.org>

  This is free software distributed under the GNU General Public
  Licence described in the file COPYING. Contact the author if
  you don't have this or can't live with it. There is ABSOLUTELY
  NO WARRANTY, explicit or implied, on this software.
**/
/*----------------------------------------------------------------------
  av_call() foreign function interface.

  Varargs-style macros to build a C argument list incrementally
  and call a function on it.
 ----------------------------------------------------------------------*/


/* These definitions are adjusted by `configure' automatically. */

/* CPU */
#ifndef __i386__
#define __i386__ 1
#endif
#ifndef __m68k__
#undef __m68k__
#endif
#ifndef __mips__
#undef __mips__
#endif
#ifndef __mipsn32__
#undef __mipsn32__
#endif
#ifndef __mips64__
#undef __mips64__
#endif
#ifndef __sparc__
#undef __sparc__
#endif
#ifndef __sparc64__
#undef __sparc64__
#endif
#ifndef __alpha__
#undef __alpha__
#endif
#ifndef __hppa__
#undef __hppa__
#endif
#ifndef __arm__
#undef __arm__
#endif
#ifndef __rs6000__
#undef __rs6000__
#endif
#ifndef __s390__
#undef __s390__
#endif
#ifndef __m88k__
#undef __m88k__
#endif
#ifndef __convex__
#undef __convex__
#endif
#ifndef __ia64__
#undef __ia64__
#endif
#ifndef __x86_64__
#undef __x86_64__
#endif

/* Calling convention */
/* Define if using pcc non-reentrant struct return convention */
#undef __PCC_STRUCT_RETURN__
/* Define if small structs are returned in registers */
#define __SMALL_STRUCT_RETURN__ 1
/* Define if floating-point results are returned in the integer registers */
#undef __IREG_FLOAT_RETURN__

/* CL_LONGLONG */
/* Define if your compiler supports the `long long' type. */
#undef HAVE_LONGLONG

/* End of definitions adjusted by `configure'. */


/* Max # words in argument-list and temporary structure storage.
 */
#ifndef __AV_ALIST_WORDS
#define __AV_ALIST_WORDS  256
#endif

/* Determine the alignment of a type at compile time.
 */
#if defined(__GNUC__)
#define __AV_alignof __alignof__
#else
#if defined(__mips__) || defined(__mipsn32__) || defined(__mips64__) /* SGI compiler */
#define __AV_alignof __builtin_alignof
#else
#define __AV_offsetof(type,ident)  ((unsigned long)&(((type*)0)->ident))
#define __AV_alignof(type)  __AV_offsetof(struct { char __slot1; type __slot2; }, __slot2)
#endif
#endif

/* C builtin types.
 */
#if defined(__mipsn32__)
typedef long long __avword;
#else
typedef long __avword;
#endif

enum __AVtype
{
  __AVword,
  __AVvoid,
  __AVchar,
  __AVschar,
  __AVuchar,
  __AVshort,
  __AVushort,
  __AVint,
  __AVuint,
  __AVlong,
  __AVulong,
  __AVlonglong,
  __AVulonglong,
  __AVfloat,
  __AVdouble,
  __AVvoidp,
  __AVstruct
};

enum __AV_alist_flags
{

  /* how to return structs */
  /* There are basically 3 ways to return structs:
   * a. The called function returns a pointer to static data. Not reentrant.
   * b. The caller passes the return structure address in a dedicated register
   *    or as a first (or last), invisible argument. The called function stores
   *    its result there.
   * c. Like b, and the called function also returns the return structure
   *    address in the return value register. (This is not very distinguishable
   *    from b.)
   * Independently of this,
   * r. small structures (<= 4 or <= 8 bytes) may be returned in the return
   *    value register(s), or
   * m. even small structures are passed in memory.
   */
  /* gcc-2.6.3 employs the following strategy:
   *   - If PCC_STATIC_STRUCT_RETURN is defined in the machine description
   *     it uses method a, else method c.
   *   - If flag_pcc_struct_return is set (either by -fpcc-struct-return or if
   *     DEFAULT_PCC_STRUCT_RETURN is defined to 1 in the machine description)
   *     it uses method m, else (either by -freg-struct-return or if
   *     DEFAULT_PCC_STRUCT_RETURN is defined to 0 in the machine description)
   *     method r.
   */
  __AV_PCC_STRUCT_RETURN	= 1<<0,	/* a: need to copy the struct */
  __AV_SMALL_STRUCT_RETURN	= 1<<1,	/* r: special case for small structs */
  __AV_GCC_STRUCT_RETURN	= 1<<2,	/* consider 8 byte structs as small */
#if defined(__sparc__) && !defined(__sparc64__)
  __AV_SUNCC_STRUCT_RETURN	= 1<<3,
  __AV_SUNPROCC_STRUCT_RETURN	= 1<<4,
#endif
#if defined(__i386__)
  __AV_NEXTGCC_STRUCT_RETURN	= 1<<3,
  __AV_MSVC_STRUCT_RETURN	= 1<<4,
#endif
#if defined(__hppa__)
  __AV_OLDGCC_STRUCT_RETURN	= 1<<3,
#endif
  /* the default way to return structs */
  /* This choice here is based on the assumption that the function you are
   * going to call has been compiled with the same compiler you are using to
   * include this file.
   * If you want to call functions with another struct returning convention,
   * just  #define __AV_STRUCT_RETURN ...
   * before or after #including <avcall.h>.
   */
#ifndef __AV_STRUCT_RETURN
  __AV_STRUCT_RETURN		=
#if defined(__sparc__) && !defined(__sparc64__) && defined(sun) && defined(__SUNPRO_C) /* SUNWspro cc */
				  __AV_SUNPROCC_STRUCT_RETURN,
#else
#if defined(__PCC_STRUCT_RETURN__) /* defined through configure, see above */
				  __AV_PCC_STRUCT_RETURN |
#if defined(__sparc__) && !defined(__sparc64__) && defined(sun) && !(defined(__STDC__) || defined(__GNUC__)) /* sun cc */
  				  __AV_SUNCC_STRUCT_RETURN,
#else
  				  0,
#endif
#else
#if defined(__SMALL_STRUCT_RETURN__) || defined(__mipsn32__) || defined(__mips64__) /* defined through configure, see above */
				  __AV_SMALL_STRUCT_RETURN |
#endif
#if defined(__GNUC__)
				  __AV_GCC_STRUCT_RETURN |
#endif
#if defined(__i386__) && defined(NeXT) && defined(__GNUC__) /* NeXT gcc-2.5.8 */
				  __AV_NEXTGCC_STRUCT_RETURN |
#endif
#if defined(__i386__) && defined(_MSC_VER) /* MSVC 4.0 */
				  __AV_MSVC_STRUCT_RETURN |
#endif
#if defined(__hppa__) && defined(__GNUC__) && (__GNUC__ < 3) && (__GNUC_MINOR__ < 7)
				  __AV_OLDGCC_STRUCT_RETURN |
#endif
  				  0,
#endif
#endif
#endif

  /* how to return floats */
#if defined(__m68k__) || (defined(__sparc__) && !defined(__sparc64__))
  __AV_SUNCC_FLOAT_RETURN	= 1<<5,
#endif
#if defined(__m68k__)
  __AV_FREG_FLOAT_RETURN	= 1<<6,
#endif
  /* the default way to return floats */
  /* This choice here is based on the assumption that the function you are
   * going to call has been compiled with the same compiler you are using to
   * include this file.
   * If you want to call functions with another float returning convention,
   * just  #define __AV_FLOAT_RETURN ...
   * before or after #including <avcall.h>.
   */
#ifndef __AV_FLOAT_RETURN
#if (defined(__m68k__) || (defined(__sparc__) && !defined(__sparc64__))) && !defined(__GNUC__) && defined(sun) && !defined(__SUNPRO_C)  /* sun cc */
  __AV_FLOAT_RETURN		= __AV_SUNCC_FLOAT_RETURN,
#elif (defined(__m68k__) && !defined(__IREG_FLOAT_RETURN__))
  __AV_FLOAT_RETURN		= __AV_FREG_FLOAT_RETURN,
#else
  __AV_FLOAT_RETURN		= 0,
#endif
#endif

  /* how to pass structs */
#if defined(__mips__) || defined(__mipsn32__) || defined(__mips64__)
  __AV_SGICC_STRUCT_ARGS	= 1<<7,
#endif
#if defined(__rs6000__)
  __AV_AIXCC_STRUCT_ARGS	= 1<<7,
#endif
  /* the default way to pass floats */
  /* This choice here is based on the assumption that the function you are
   * going to call has been compiled with the same compiler you are using to
   * include this file.
   * If you want to call functions with another float passing convention,
   * just  #define __AV_STRUCT_ARGS ...
   * before or after #including <avcall.h>.
   */
#ifndef __AV_STRUCT_ARGS
#if (defined(__mips__) || defined(__mipsn32__) || defined(__mips64__)) && !defined(__GNUC__) /* SGI mips cc */
  __AV_STRUCT_ARGS		= __AV_SGICC_STRUCT_ARGS,
#else
#if defined(__rs6000__) && defined(_AIX) && !defined(__GNUC__) /* AIX cc, xlc */
  __AV_STRUCT_ARGS		= __AV_AIXCC_STRUCT_ARGS,
#else
  __AV_STRUCT_ARGS		= 0,
#endif
#endif
#endif

  /* how to pass floats */
  /* ANSI C compilers and GNU gcc pass floats as floats.
   * K&R C compilers pass floats as doubles.
   * (Except some compilers like SGI MIPS "cc" and "cc -cckr" if a prototype is
   * known for the called functions. But to compile a program with prototypes,
   * "cc -ansi" is better anyway.
   */
  __AV_ANSI_FLOAT_ARGS		= 0,    /* pass floats as floats */
  __AV_TRADITIONAL_FLOAT_ARGS	= 1<<8, /* pass floats as doubles */
  /* the default way to pass floats */
  /* This choice here is based on the assumption that the function you are
   * going to call has been compiled with the same compiler you are using to
   * include this file.
   * If you want to call functions with another float passing convention,
   * just  #define __AV_FLOAT_ARGS ...
   * before or after #including <avcall.h>.
   */
#ifndef __AV_FLOAT_ARGS
#if defined(__STDC__) || defined(__GNUC__) /* what about hppa "cc -Aa" ?? */
  __AV_FLOAT_ARGS		= __AV_ANSI_FLOAT_ARGS,
#else
  __AV_FLOAT_ARGS		= __AV_TRADITIONAL_FLOAT_ARGS,
#endif
#endif

  /* how to pass and return small integer arguments */
  __AV_ANSI_INTEGERS		= 0, /* no promotions */
  __AV_TRADITIONAL_INTEGERS	= 0, /* promote [u]char, [u]short to [u]int */
  /* Fortunately these two methods are compatible. Our macros work with both. */
  /* the default way to pass and return small integer arguments */
  /* This choice here is based on the assumption that the function you are
   * going to call has been compiled with the same compiler you are using to
   * include this file.
   * If you want to call functions with another float passing convention,
   * just  #define __AV_INTEGERS ...
   * before or after #including <avcall.h>.
   */
#ifndef __AV_INTEGERS
#if defined(__STDC__) || defined(__GNUC__)
  __AV_INTEGERS			= __AV_ANSI_INTEGERS,
#else
  __AV_INTEGERS			= __AV_TRADITIONAL_INTEGERS,
#endif
#endif

  /* stack cleanup policy */
  __AV_CDECL_CLEANUP		= 0, /* caller pops args after return */
  __AV_STDCALL_CLEANUP		= 0, /* callee pops args before return */
				     /* currently only supported on __i386__ */
#ifndef __AV_CLEANUP
  __AV_CLEANUP			= __AV_CDECL_CLEANUP,
#endif

  /* These are for internal use only */
#if defined(__i386__) || defined(__m68k__) || defined(__mipsn32__) || defined(__mips64__) || defined(__sparc64__) || defined(__alpha__) || defined(__arm__) || defined(__rs6000__) || defined(__convex__) || defined(__ia64__) || defined(__x86_64__) || defined(__s390__)
  __AV_REGISTER_STRUCT_RETURN	= 1<<9,
#endif
#if defined(__mips__) && !defined(__mipsn32__)
  __AV_FLOAT_1			= 1<<10,
  __AV_FLOAT_2			= 1<<11,
#endif

  __AV_flag_for_broken_compilers_that_dont_like_trailing_commas
};

typedef struct
{
  /* function to be called */
  __avword		(*func)();
  /* some av_... macros need these flags */
  int			flags;
  /* return type, address for the result */
  void*			raddr;
  enum __AVtype		rtype;
  unsigned long		rsize;
  /* current pointer into the args[] array */
  __avword*		aptr;
#if defined(__sparc__) || defined(__sparc64__) || defined(__hppa__) || (defined(__rs6000__) && !defined(_AIX) && !(defined(__MACH__) && defined(__APPLE__))) || defined(__s390__)
  /* limit pointer into the args[] array */
  __avword*		eptr;
#endif
#if defined(__i386__) && 0
  /* Filler word, needed if the numbers of words up to now in this structure */
  /* is odd (because on MSVC, alignof(double) = 8, normally = 4).            */
  __avword		filler1;
#endif
#if defined(__i386__) || defined(__m68k__) || (defined(__sparc__) && !defined(__sparc64__)) || defined(__hppa__) || defined(__arm__) || defined(__rs6000__) || defined(__convex__) || defined(__s390__)
  /* temporary storage, used to split doubles into two words */
  union {
    double	_double;
#if defined(__sparc__) && !defined(__sparc64__) && defined(HAVE_LONGLONG)
    long long	_longlong;
#endif
    __avword	words[2];
  }			tmp;
#endif
#if defined(__x86_64__)
  /* store the integer arguments in an extra array */
  __avword*		iaptr;
  __avword		iargs[6];
#endif
#if defined(__mips__) && !defined(__mipsn32__)
  /* store the floating-point arguments in an extra array */
  int			anum;
  double		floatarg[2];
#endif
#if defined(__mipsn32__) || defined(__mips64__)
  /* store the floating-point arguments in an extra array */
  int			anum;		/* redundant: (LIST).aptr = &(LIST).args[(LIST).anum] */
  unsigned int		farg_mask;	/* bitmask of those entries in farg[] which have a value */
  unsigned int		darg_mask;	/* bitmask of those entries in args[] which have a double value */
  float			farg[8];
#endif
#if defined(__sparc64__)
  /* store the floating-point arguments in an extra array */
  int			anum;		/* redundant: (LIST).aptr = &(LIST).args[(LIST).anum] */
  unsigned int		farg_mask;	/* bitmask of those entries in farg[] which have a value */
  unsigned int		darg_mask;	/* bitmask of those entries in args[] which have a double value */
#endif
#if defined(__ia64__) || defined(__x86_64__)
  /* store the floating-point arguments in an extra array */
  double*		faptr;
  double		fargs[8];
#endif
  __avword		args[__AV_ALIST_WORDS]; /* sizeof(double)-aligned */
#if defined(__rs6000__)
  /* store the floating-point arguments in an extra array */
  double*		faptr;
  double		fargs[13];
#endif
#if defined(__s390__)
  /* store the floating-point arguments in an extra array */
  int   		fargwords;
  float*		faptr;
  float 		fargs[2];
  int*			fargsusedptr;
  int			fargsused[2];
  double*		daptr;
  double		dargs[2];
  int*			dargsusedptr;
  int			dargsused[2];
#endif
#if defined(AMIGA)
  /* store the arguments passed in registers in an extra array */
  __avword		regargs[8+7];
#endif
} av_alist;

/* The limit for the pointer into the args[] array. */
#if defined(__sparc__) || defined(__sparc64__) || defined(__hppa__) || (defined(__rs6000__) && !defined(_AIX) && !(defined(__MACH__) && defined(__APPLE__))) || defined(__s390)
#define __av_eptr(LIST)	((LIST).eptr)
#else
#define __av_eptr(LIST)	(&(LIST).args[__AV_ALIST_WORDS])
#endif

/* Delayed overflow detection */
#if defined(__hppa__)
#define av_overflown(LIST) ((LIST).aptr < __av_eptr(LIST))
#else
#define av_overflown(LIST) ((LIST).aptr > __av_eptr(LIST))
#endif


/*
 *  av_start_<type> macros which specify the return type
 */

#define __AV_START_FLAGS  \
  __AV_STRUCT_RETURN | __AV_FLOAT_RETURN | __AV_STRUCT_ARGS | __AV_FLOAT_ARGS | __AV_INTEGERS | __AV_CLEANUP

#define __av_start(LIST,FUNC,RADDR,RETTYPE)				\
  ((LIST).func = (__avword(*)())(FUNC),					\
   (LIST).raddr = (void*)(RADDR),					\
   (LIST).rtype = (RETTYPE),						\
   __av_start1(LIST)							\
   (LIST).flags = __AV_START_FLAGS)

#if defined(__i386__) || defined(__m68k__) || defined(__alpha__) || defined(__arm__) || defined(__m88k__) || defined(__convex__)
#define __av_start1(LIST)						\
   (LIST).aptr = &(LIST).args[0],
#endif
#if defined(__mips__) && !defined(__mipsn32__)
#define __av_start1(LIST)						\
   (LIST).anum = 0,							\
   (LIST).aptr = &(LIST).args[0],
#endif
#if defined(__mipsn32__) || defined(__mips64__)
#define __av_start1(LIST)						\
   (LIST).anum = 0,							\
   (LIST).farg_mask = 0,						\
   (LIST).darg_mask = 0,						\
   (LIST).aptr = &(LIST).args[0],
#endif
#if defined(__sparc__) && !defined(__sparc64__)
#define __av_start1(LIST)						\
   (LIST).aptr = &(LIST).args[0],					\
   (LIST).eptr = &(LIST).args[__AV_ALIST_WORDS],
#endif
#if defined(__sparc64__)
#define __av_start1(LIST)						\
   (LIST).anum = 0,							\
   (LIST).farg_mask = 0,						\
   (LIST).darg_mask = 0,						\
   (LIST).aptr = &(LIST).args[0],					\
   (LIST).eptr = &(LIST).args[__AV_ALIST_WORDS],
#endif
#if defined(__hppa__)
#define __av_start1(LIST)						\
   (LIST).aptr = &(LIST).args[__AV_ALIST_WORDS],			\
   (LIST).eptr = &(LIST).args[0],
#endif
#if defined(__rs6000__)
#if defined(_AIX) || (defined(__MACH__) && defined(__APPLE__))
#define __av_start1(LIST)						\
   (LIST).aptr = &(LIST).args[0],					\
   (LIST).faptr = &(LIST).fargs[0],
#else
#define __av_start1(LIST)						\
   (LIST).aptr = &(LIST).args[0],					\
   (LIST).faptr = &(LIST).fargs[0],                                     \
   (LIST).eptr = &(LIST).args[__AV_ALIST_WORDS],
#endif
#endif
#if defined(__s390__)
#define __av_start1(LIST)						\
   (LIST).aptr = &(LIST).args[0],					\
   (LIST).fargwords = 0,						\
   (LIST).faptr = &(LIST).fargs[0],                                     \
   (LIST).daptr = &(LIST).dargs[0],                                     \
   (LIST).fargsusedptr = &(LIST).fargsused[0],                          \
   (LIST).dargsusedptr = &(LIST).dargsused[0],                          \
   (LIST).eptr = &(LIST).args[__AV_ALIST_WORDS],
#endif
#if defined(__ia64__)
#define __av_start1(LIST)						\
   (LIST).aptr = &(LIST).args[0],					\
   (LIST).faptr = &(LIST).fargs[0],
#endif
#if defined(__x86_64__)
#define __av_start1(LIST)						\
   (LIST).aptr = &(LIST).args[0],					\
   (LIST).iaptr = &(LIST).iargs[0],					\
   (LIST).faptr = &(LIST).fargs[0],
#endif

#define av_start_void(LIST,FUNC)		__av_start(LIST,FUNC,0,    __AVvoid)
#define av_start_char(LIST,FUNC,RADDR)		__av_start(LIST,FUNC,RADDR,__AVchar)
#define av_start_schar(LIST,FUNC,RADDR)		__av_start(LIST,FUNC,RADDR,__AVschar)
#define av_start_uchar(LIST,FUNC,RADDR)		__av_start(LIST,FUNC,RADDR,__AVuchar)
#define av_start_short(LIST,FUNC,RADDR)		__av_start(LIST,FUNC,RADDR,__AVshort)
#define av_start_ushort(LIST,FUNC,RADDR)	__av_start(LIST,FUNC,RADDR,__AVushort)
#define av_start_int(LIST,FUNC,RADDR)		__av_start(LIST,FUNC,RADDR,__AVint)
#define av_start_uint(LIST,FUNC,RADDR)		__av_start(LIST,FUNC,RADDR,__AVuint)
#define av_start_long(LIST,FUNC,RADDR)		__av_start(LIST,FUNC,RADDR,__AVlong)
#define av_start_ulong(LIST,FUNC,RADDR)		__av_start(LIST,FUNC,RADDR,__AVulong)
#define av_start_longlong(LIST,FUNC,RADDR)	__av_start(LIST,FUNC,RADDR,__AVlonglong)
#define av_start_ulonglong(LIST,FUNC,RADDR)	__av_start(LIST,FUNC,RADDR,__AVulonglong)
#define av_start_float(LIST,FUNC,RADDR)		__av_start(LIST,FUNC,RADDR,__AVfloat)
#define av_start_double(LIST,FUNC,RADDR)	__av_start(LIST,FUNC,RADDR,__AVdouble)
#define av_start_ptr(LIST,FUNC,TYPE,RADDR)	__av_start(LIST,FUNC,RADDR,__AVvoidp)

#define av_start_struct(LIST,FUNC,TYPE,TYPE_SPLITTABLE,RADDR)		\
  _av_start_struct(LIST,FUNC,sizeof(TYPE),TYPE_SPLITTABLE,RADDR)
#define _av_start_struct(LIST,FUNC,TYPE_SIZE,TYPE_SPLITTABLE,RADDR)	\
  (__av_start(LIST,FUNC,RADDR,__AVstruct),				\
   (LIST).rsize = TYPE_SIZE,						\
   __av_start_struct1(LIST,TYPE_SIZE,TYPE_SPLITTABLE),			\
   0)

#define __av_start_struct1(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((LIST).flags & __AV_PCC_STRUCT_RETURN				\
   ? /* pcc struct return convention:					\
      * called function returns pointer to value, we'll copy its contents afterwards. \
      */								\
     0									\
   : __av_start_struct2(LIST,TYPE_SIZE,TYPE_SPLITTABLE)			\
  )
#if (defined(__sparc__) && !defined(__sparc64__)) || defined(__m88k__)
/* Return structure pointer is passed in a special register.
 */
#define __av_start_struct2(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  0
#else
#define __av_start_struct2(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  (((LIST).flags & __AV_SMALL_STRUCT_RETURN)				\
   && __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)		\
   ? /* <= Word-sized structures are returned in a register. */		\
     __av_start_struct3(LIST)						\
   : __av_start_struct4(LIST,TYPE_SIZE)					\
  )
/* Determines whether a structure is returned in registers,
 * depending on its size and its word-splittable flag.
 */
#if (defined(__i386__) && defined(_WIN32))
#define __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4		\
   || ((TYPE_SIZE) == 8							\
       && (((LIST).flags & __AV_MSVC_STRUCT_RETURN)			\
           || ((TYPE_SPLITTABLE)					\
               && ((LIST).flags & __AV_GCC_STRUCT_RETURN)		\
  )   )   )   )
/* Turn on __AV_REGISTER_STRUCT_RETURN if __AV_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __av_start_struct3(LIST)  \
  ((LIST).flags |= __AV_REGISTER_STRUCT_RETURN, 0)
#endif
#if (defined(__i386__) && !defined(_WIN32)) || defined(__m68k__) || defined(__arm__) || defined(__rs6000__) || defined(__convex__) || defined(__s390__)
#define __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4		\
   || ((TYPE_SIZE) == 8 && (TYPE_SPLITTABLE)				\
       && ((LIST).flags & __AV_GCC_STRUCT_RETURN)			\
  )   )
/* Turn on __AV_REGISTER_STRUCT_RETURN if __AV_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __av_start_struct3(LIST)  \
  ((LIST).flags |= __AV_REGISTER_STRUCT_RETURN, 0)
#endif
#if defined(__alpha__)
#define __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4 || (TYPE_SIZE) == 8	\
   || ((TYPE_SIZE) == 16 && (TYPE_SPLITTABLE)				\
       && ((LIST).flags & __AV_GCC_STRUCT_RETURN)			\
  )   )
/* Turn on __AV_REGISTER_STRUCT_RETURN if __AV_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __av_start_struct3(LIST)  \
  ((LIST).flags |= __AV_REGISTER_STRUCT_RETURN, 0)
#endif
#if defined(__hppa__)
#define __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((LIST).flags & __AV_OLDGCC_STRUCT_RETURN				\
   ? ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4)		\
   : ((TYPE_SIZE) <= 8)							\
  )
/* Test both __AV_OLDGCC_STRUCT_RETURN and __AV_SMALL_STRUCT_RETURN at run time. */
#define __av_start_struct3(LIST)  \
  0
#endif
#if defined(__mips__) && !defined(__mipsn32__)
#define __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4)
/* Test __AV_SMALL_STRUCT_RETURN instead of __AV_REGISTER_STRUCT_RETURN. */
#define __av_start_struct3(LIST)  \
  0
#endif
#if defined(__mipsn32__) || defined(__mips64__)
#define __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((LIST).flags & __AV_GCC_STRUCT_RETURN				\
   ? ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4 || (TYPE_SIZE) == 8) \
   : ((TYPE_SIZE) <= 16)						\
  )
/* Turn on __AV_REGISTER_STRUCT_RETURN if __AV_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __av_start_struct3(LIST)  \
  ((LIST).flags |= __AV_REGISTER_STRUCT_RETURN, 0)
#endif
#if defined(__sparc64__) || defined(__ia64__)
#define __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) <= 32)
/* Turn on __AV_REGISTER_STRUCT_RETURN if __AV_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __av_start_struct3(LIST)  \
  ((LIST).flags |= __AV_REGISTER_STRUCT_RETURN, 0)
#endif
#if defined(__x86_64__)
#define __av_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) <= 16)
/* Turn on __AV_REGISTER_STRUCT_RETURN if __AV_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __av_start_struct3(LIST)  \
  ((LIST).flags |= __AV_REGISTER_STRUCT_RETURN, 0)
#endif
#if defined(__i386__)
/* Return structure pointer is passed in a special register or as first arg. */
#define __av_start_struct4(LIST,TYPE_SIZE)				\
  ((LIST).flags & __AV_NEXTGCC_STRUCT_RETURN				\
   ? 0						 /* special register */	\
   : (*(LIST).aptr++ = (__avword)((LIST).raddr), 0)	/* first arg */	\
  )
#endif
#if defined(__m68k__) || defined(__hppa__) || defined(__ia64__)
/* Return structure pointer is passed in a special register.
 */
#define __av_start_struct4(LIST,TYPE_SIZE)  0
#endif
/* Return structure pointer is passed as first arg.
 */
#if defined(__alpha__) || defined(__arm__) || defined(__rs6000__) || defined(__convex__) || defined(__s390__)
#define __av_start_struct4(LIST,TYPE_SIZE)				\
   (*(LIST).aptr++ = (__avword)((LIST).raddr), 0)
#endif
#if defined(__mips__) || defined(__mipsn32__) || defined(__mips64__) || defined(__sparc64__)
#define __av_start_struct4(LIST,TYPE_SIZE)				\
   (*(LIST).aptr++ = (__avword)((LIST).raddr),				\
    (LIST).anum++,							\
    0									\
   )
#endif
#if defined(__x86_64__)
#define __av_start_struct4(LIST,TYPE_SIZE)				\
   (*(LIST).iaptr++ = (__avword)((LIST).raddr), 0)
#endif
#endif


/*
 * av_<type> macros which specify the argument and its type
 */

/*
 * scalar argument types
 */

#if defined(__i386__) || defined(__m68k__) || (defined(__sparc__) && !defined(__sparc64__)) || defined(__alpha__) || defined(__arm__) || defined(__rs6000__) || defined(__m88k__) || defined(__convex__) || defined(__ia64__) || defined(__x86_64__) || defined(__s390__)
/* Floats and all integer types are passed as words,
 * doubles as two words.
 */
#define __av_word(LIST,VAL)						\
  (++(LIST).aptr > __av_eptr(LIST)					\
   ? -1 : ((LIST).aptr[-1] = (__avword)(VAL), 0))
#endif
#if defined(__mips__) || defined(__mipsn32__) || defined(__mips64__) || defined(__sparc64__)
/* Most things are passed as integers:
 */
#define __av_word(LIST,VAL)						\
  (++(LIST).aptr > __av_eptr(LIST)					\
   ? -1 : ((LIST).anum++, (LIST).aptr[-1] = (__avword)(VAL), 0))
#endif
#if defined(__hppa__)
/* Floats and all integer types are passed as words,
 * doubles as two words.
 */
#define __av_word(LIST,VAL)						\
  (--(LIST).aptr < __av_eptr(LIST)					\
   ? -1 : (*(LIST).aptr = (__avword)(VAL), 0))
#endif
#if defined(AMIGA)
/* Some arguments are passed in registers. Query the macro AV_ARG_REGNUM.
 * This should really be an argument to __av_word.
 */
#undef __av_word /**/
#define __av_word(LIST,VAL)						\
  ((AV_ARG_REGNUM) >= 0							\
   ? ((AV_ARG_REGNUM) < 8+7						\
      ? -1 : ((LIST).regargs[(AV_ARG_REGNUM)] = (__avword)(VAL), 0))	\
   : (++(LIST).aptr > __av_eptr(LIST)					\
      ? -1 : ((LIST).aptr[-1] = (__avword)(VAL), 0)))
#endif

/* integer argument types */

#if defined(__x86_64__)
/* The first 6 integer arguments are passed in registers. */
#define av_long(LIST,VAL)						\
  ((LIST).iaptr < &(LIST).iargs[6]					\
   ? (*(LIST).iaptr++ = (long)(VAL), 0)					\
   : __av_word(LIST,(long)(VAL)))
#else
#define av_long(LIST,VAL)	__av_word(LIST,(long)(VAL))
#endif

#if defined(__x86_64__)
/* The first 6 integer arguments are passed in registers. */
#define av_ulong(LIST,VAL)						\
  ((LIST).iaptr < &(LIST).iargs[6]					\
   ? (*(LIST).iaptr++ = (unsigned long)(VAL), 0)			\
   : __av_word(LIST,(unsigned long)(VAL)))
#else
#define av_ulong(LIST,VAL)	__av_word(LIST,(unsigned long)(VAL))
#endif

#if defined(__x86_64__)
/* The first 6 integer arguments are passed in registers. */
#define av_ptr(LIST,TYPE,VAL)						\
  ((LIST).iaptr < &(LIST).iargs[6]					\
   ? (*(LIST).iaptr++ = (__avword)(TYPE)(VAL), 0)			\
   : __av_word(LIST,(TYPE)(VAL)))
#else
#define av_ptr(LIST,TYPE,VAL)	__av_word(LIST,(TYPE)(VAL))
#endif

#define av_char			av_long
#define av_schar		av_long
#define av_short		av_long
#define av_int			av_long
#define av_uchar		av_ulong
#define av_ushort		av_ulong
#define av_uint			av_ulong

#if defined(__mips64__) || defined(__sparc64__) || defined(__alpha__) || defined(__ia64__) || defined(__x86_64__)
/* `long long' and `long' are identical. */
#define av_longlong		av_long
#define av_ulonglong		av_ulong
#elif defined(__mipsn32__)
/* `long long' fits in __avword. */
#define av_longlong		__av_word
#define av_ulonglong(LIST,VAL)	__av_word(LIST,(unsigned long long)(VAL))
#elif defined(__i386__) || defined(__m68k__) || defined(__mips__) || (defined(__sparc__) && !defined(__sparc64__)) || defined(__hppa__) || defined(__arm__) || defined(__rs6000__) || defined(__m88k__) || defined(__convex__) || defined(__s390__)
/* `long long's are passed embedded on the arg stack. */
#define av_longlong(LIST,VAL)	__av_longlong(LIST,long long,VAL)
#define av_ulonglong(LIST,VAL)	__av_longlong(LIST,unsigned long long,VAL)
#if defined(__i386__) || defined(__m68k__) || defined(__arm__) || (defined(__rs6000__) && (defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)))) || defined(__convex__)
/* `long long's are (at most) word-aligned. */
#define __av_longlong(LIST,TYPE,VAL)					\
  (((LIST).aptr += sizeof(TYPE)/sizeof(__avword)) > __av_eptr(LIST)	\
   ? -1 : (((TYPE*)(LIST).aptr)[-1] = (TYPE)(VAL), 0))
#endif
#if defined(__mips__) || (defined(__sparc__) && !defined(__sparc64__)) || defined(__hppa__) || (defined(__rs6000__) && !(defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)))) || defined(__m88k__) || defined(__s390__)
/* `long long's have alignment 8. */
#if defined(__mips__)
#define __av_longlong(LIST,TYPE,VAL)					\
  (((LIST).aptr = (__avword*)(((__avword)(LIST).aptr+sizeof(TYPE)+__AV_alignof(TYPE)-1) & -(long)__AV_alignof(TYPE))) > __av_eptr(LIST) \
   ? -1 : ((LIST).anum++, ((TYPE*)(LIST).aptr)[-1] = (TYPE)(VAL), 0))
#endif
#if defined(__sparc__) && !defined(__sparc64__)
/* Within the arg stack, the alignment is only 4, not 8. */
/* This assumes sizeof(long long) == 2*sizeof(__avword). */
#define __av_longlong(LIST,TYPE,VAL)					\
  (((LIST).aptr += sizeof(TYPE)/sizeof(__avword)) > __av_eptr(LIST)	\
   ? -1 :								\
   ((LIST).tmp._longlong = (TYPE)(VAL),					\
    (LIST).aptr[-2] = (LIST).tmp.words[0],				\
    (LIST).aptr[-1] = (LIST).tmp.words[1],				\
    0))
#endif
#if defined(__hppa__)
#define __av_longlong(LIST,TYPE,VAL)					\
  (((LIST).aptr = (__avword*)(((__avword)(LIST).aptr & -(long)__AV_alignof(TYPE)) - sizeof(TYPE))) < __av_eptr(LIST) \
   ? -1 : (*(TYPE*)(LIST).aptr = (TYPE)(VAL), 0))
#endif
#if (defined(__rs6000__) && !(defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)))) || defined(__m88k__)
#define __av_longlong(LIST,TYPE,VAL)					\
  (((LIST).aptr = (__avword*)(((__avword)(LIST).aptr+sizeof(TYPE)+__AV_alignof(TYPE)-1) & -(long)__AV_alignof(TYPE))) > __av_eptr(LIST) \
   ? -1 : (((TYPE*)(LIST).aptr)[-1] = (TYPE)(VAL), 0))
#endif
#if defined(__s390__)
#define __av_longlong(LIST,TYPE,VAL)					\
  (((LIST).aptr = (__avword*)(((__avword)(LIST).aptr+sizeof(TYPE)+__AV_alignof(TYPE)-1) & -(long)__AV_alignof(TYPE))) > __av_eptr(LIST) \
   ? -1 :						\
   (((LIST).aptr - (LIST).args - (LIST).fargwords == 4 ? ++(LIST).aptr,0 : 0), \
    (((TYPE*)(LIST).aptr)[-1] = (TYPE)(VAL), 0)))
#endif
#endif
#endif

/* floating-point argument types */

#define av_float(LIST,VAL)						\
  ((LIST).flags & __AV_TRADITIONAL_FLOAT_ARGS				\
   ? av_double(LIST,(float)(VAL))					\
   : __av_float(LIST,VAL))

#if defined(__i386__) || defined(__m68k__) || (defined(__sparc__) && !defined(__sparc64__)) || defined(__arm__) || defined(__convex__)

#define __av_float(LIST,VAL)						\
  (++(LIST).aptr > __av_eptr(LIST)					\
   ? -1 : (((float*)(LIST).aptr)[-1] = (float)(VAL), 0))

/* This assumes sizeof(double) == 2*sizeof(__avword). */
#define av_double(LIST,VAL)						\
   (((LIST).aptr += 2) > __av_eptr(LIST)				\
    ? -1 :								\
    ((LIST).tmp._double = (double)(VAL),				\
     (LIST).aptr[-2] = (LIST).tmp.words[0],				\
     (LIST).aptr[-1] = (LIST).tmp.words[1],				\
     0))

#endif

#if defined(__mips__) && !defined(__mipsn32__)

/* Up to 2 leading float or double non-varargs args can be passed in
 * float registers, but we also push them into the corresponding int
 * registers in case of varargs. For doubles we need to align the aptr
 * to an even boundary.
 */
#define __av_float(LIST,VAL)						\
  (++(LIST).aptr > __av_eptr(LIST)					\
   ? -1 : ((++(LIST).anum == 1						\
	    ? ((LIST).flags |= __AV_FLOAT_1,				\
	       ((float*)(LIST).floatarg)[1] = ((float*)(LIST).aptr)[-1] = (float)(VAL))\
	    : (LIST).anum == 2 && ((LIST).flags & __AV_FLOAT_1)		\
	    ? ((LIST).flags |= __AV_FLOAT_2,				\
	       ((float*)(LIST).floatarg)[3] = ((float*)(LIST).aptr)[-1] = (float)(VAL))\
	    : (*(float*)&(LIST).aptr[-1] = (float)(VAL))),		\
	   0))

#define av_double(LIST,VAL)						\
  (((LIST).aptr = (__avword*)(((__avword)(LIST).aptr+15)&-8))		\
   > __av_eptr(LIST)							\
   ? -1 : ((++(LIST).anum == 1						\
	    ? ((LIST).flags |= __AV_FLOAT_1,				\
	       (LIST).floatarg[0] = ((double*)(LIST).aptr)[-1] = (double)(VAL))\
	    : (LIST).anum == 2 && ((LIST).flags & __AV_FLOAT_1)		\
	    ? ((LIST).flags |= __AV_FLOAT_2,				\
	       (LIST).floatarg[1] = ((double*)(LIST).aptr)[-1] = (double)(VAL))\
	    : (((double*)(LIST).aptr)[-1] = (double)(VAL))),		\
	   0))

#endif

#if defined(__mipsn32__) || defined(__mips64__)

/* Up to 8 leading float or double non-varargs args can be passed in
 * float registers, but we also push them into the corresponding int
 * registers in case of varargs.
 */
#define __av_float(LIST,VAL)						\
  ((LIST).aptr >= __av_eptr(LIST)					\
   ? -1 : (((LIST).anum < 8						\
	    ? ((LIST).farg_mask |= (1 << (LIST).anum),			\
	       (LIST).farg[(LIST).anum] = *(float*)(LIST).aptr = (float)(VAL)) \
	    : (*(float*)(LIST).aptr = (float)(VAL))),			\
	   (LIST).anum++,						\
	   (LIST).aptr++,						\
	   0))

#define av_double(LIST,VAL)						\
  ((LIST).aptr >= __av_eptr(LIST)					\
   ? -1 : (((LIST).anum < 8 && ((LIST).darg_mask |= (1 << (LIST).anum))), \
	   *(double*)(LIST).aptr = (double)(VAL),			\
	   (LIST).anum++,						\
	   (LIST).aptr++,						\
	   0))

#endif

#if defined(__sparc64__)

/* Up to 16 leading float or double non-varargs args can be passed in
 * float registers, but we also push them into the corresponding int
 * registers in case of varargs.
 */
#define __av_float(LIST,VAL)						\
  ((LIST).aptr >= __av_eptr(LIST)					\
   ? -1 : (((LIST).anum < 16 && ((LIST).farg_mask |= (1 << (LIST).anum))), \
	   (*(float*)(LIST).aptr = (float)(VAL)),			\
	   (LIST).anum++,						\
	   (LIST).aptr++,						\
	   0))

#define av_double(LIST,VAL)						\
  ((LIST).aptr >= __av_eptr(LIST)					\
   ? -1 : (((LIST).anum < 16 && ((LIST).darg_mask |= (1 << (LIST).anum))), \
	   *(double*)(LIST).aptr = (double)(VAL),			\
	   (LIST).anum++,						\
	   (LIST).aptr++,						\
	   0))

#endif

#if defined(__alpha__)

#define av_double(LIST,VAL)						\
  (++(LIST).aptr > __av_eptr(LIST)					\
   ? -1 : (((double*)(LIST).aptr)[-1] = (double)(VAL), 0))

#define __av_float(LIST,VAL)						\
  (++(LIST).aptr > __av_eptr(LIST)					\
   ? -1									\
   : (((LIST).aptr > &(LIST).args[6]					\
       ? /* These args will be fetched from memory using "lds" instructions */ \
	 /* therefore store them as floats */				\
	 (*(float*)((LIST).aptr-1) = (float)(VAL))			\
       : /* The first 6 args will be put into registers by "ldt" instructions */ \
	 /* (see avcall-alpha.c!). Therefore store them as doubles. */	\
	 /* When viewed as floats, the value will be the correct one. */\
	 (*(double*)((LIST).aptr-1) = (double)(float)(VAL))		\
     ), 0))

#endif

#if defined(__hppa__)

#define __av_float(LIST,VAL)						\
  (--(LIST).aptr < __av_eptr(LIST)					\
   ? -1 : (*(float*)(LIST).aptr = (float)(VAL), 0))

#define av_double(LIST,VAL)						\
  (((LIST).aptr = (__avword*)(((long)(LIST).aptr-sizeof(double)) & -(long)sizeof(double))) \
    < __av_eptr(LIST)							\
    ? -1 : (*(double*)(LIST).aptr = (double)(VAL), 0))

#endif

#if defined(__rs6000__) && (defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)))

/* Up to 13 float or double non-varargs args can be passed in
 * float registers, but we also push them into the corresponding int
 * registers in case of varargs.
 */

#define __av_float(LIST,VAL)						\
  (++(LIST).aptr > __av_eptr(LIST)					\
   ? -1 : (((float*)(LIST).aptr)[-1] = (float)(VAL),			\
	   (LIST).faptr < &(LIST).fargs[13] &&				\
		(*(LIST).faptr++ = (double)(float)(VAL)),		\
	   0))

#define av_double(LIST,VAL)						\
   (((LIST).aptr += 2) > __av_eptr(LIST)				\
    ? -1 :								\
    ((LIST).tmp._double = (double)(VAL),				\
     (LIST).aptr[-2] = (LIST).tmp.words[0],				\
     (LIST).aptr[-1] = (LIST).tmp.words[1],				\
     (LIST).faptr < &(LIST).fargs[13] &&				\
	(*(LIST).faptr++ = (LIST).tmp._double),				\
     0))

#endif

#if defined(__rs6000__) && !(defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)))

/* Up to 8 float or double non-varargs args can be passed in
 * float registers, without occupying space in the general registers.
 */

#define __av_float(LIST,VAL)						\
  ((LIST).faptr < &(LIST).fargs[8]					\
   ? ((*(LIST).faptr++ = (double)(float)(VAL)), 0)			\
   : (++(LIST).aptr > __av_eptr(LIST)					\
      ? -1 : (((float*)(LIST).aptr)[-1] = (float)(VAL), 0)))

#define av_double(LIST,VAL)						\
  ((LIST).faptr < &(LIST).fargs[8]					\
   ? ((*(LIST).faptr++ = (double)(VAL)), 0)				\
   : (((LIST).aptr += 2) > __av_eptr(LIST)				\
      ? -1 :								\
      ((LIST).tmp._double = (double)(VAL),				\
       (LIST).aptr[-2] = (LIST).tmp.words[0],				\
       (LIST).aptr[-1] = (LIST).tmp.words[1],				\
       0)))

#endif

#if defined(__s390__)

/* Up to 2 float or double non-varargs args can be passed in
 * float registers, without occupying space in the general registers.
 */

#define __av_float(LIST,VAL)						\
  ((LIST).faptr < &(LIST).fargs[2]					\
   ? (LIST).daptr++, *(LIST).fargsusedptr++ = 1, *(LIST).dargsusedptr++ = 0, ((*(LIST).faptr++ = (float)(VAL)), 0)		\
   : (++(LIST).aptr > __av_eptr(LIST)					\
      ? -1 : ((LIST).fargwords++, ((float*)(LIST).aptr)[-1] = (float)(VAL), 0)))

#define av_double(LIST,VAL)						\
  ((LIST).daptr < &(LIST).dargs[2]					\
   ? (LIST).faptr++, *(LIST).dargsusedptr++ = 1, *(LIST).fargsusedptr++ = 0, ((*(LIST).daptr++ = (double)(VAL)), 0)		\
   : (((LIST).aptr += 2) > __av_eptr(LIST)				\
      ? -1 :								\
      ((LIST).fargwords+=2, (LIST).tmp._double = (double)(VAL),			\
       (LIST).aptr[-2] = (LIST).tmp.words[0],				\
       (LIST).aptr[-1] = (LIST).tmp.words[1],				\
       0)))

#endif

#if defined(__m88k__)

#define __av_float(LIST,VAL)						\
  (++(LIST).aptr > __av_eptr(LIST)					\
   ? -1 : (((float*)(LIST).aptr)[-1] = (float)(VAL), 0))

#define av_double(LIST,VAL)						\
   (((LIST).aptr = (__avword*)(((long)(LIST).aptr+sizeof(double)+sizeof(double)-1) & -(long)sizeof(double))) \
    > __av_eptr(LIST)							\
    ? -1 : (((double*)(LIST).aptr)[-1] = (double)(VAL), 0))

#endif

#if defined(__ia64__)

/* Up to 8 leading float or double non-varargs args can be passed in
 * float registers, but we also push them into the corresponding int
 * registers in case of varargs.
 */
#define __av_float(LIST,VAL)						\
  ((LIST).aptr >= __av_eptr(LIST)					\
   ? -1 : ((*(float*)(LIST).aptr = (float)(VAL)),			\
	   ((LIST).faptr < &(LIST).fargs[8] && (*(LIST).faptr = *(float*)(LIST).aptr, (LIST).faptr++)), \
	   (LIST).aptr++,						\
	   0))

#define av_double(LIST,VAL)						\
  ((LIST).aptr >= __av_eptr(LIST)					\
   ? -1 : (*(double*)(LIST).aptr = (double)(VAL),			\
	   ((LIST).faptr < &(LIST).fargs[8] && (*(LIST).faptr = *(double*)(LIST).aptr, (LIST).faptr++)), \
	   (LIST).aptr++,						\
	   0))

#endif

#if defined(__x86_64__)

/* Up to 8 leading float or double args can be passed in float registers.
 */
#define __av_float(LIST,VAL)						\
  ((LIST).faptr < &(LIST).fargs[8]					\
   ? (*(LIST).faptr = 0.0, *(float*)(LIST).faptr = (float)(VAL),	\
      (LIST).faptr++,							\
      0)								\
   : ((LIST).aptr >= __av_eptr(LIST)					\
      ? -1 : ((*(float*)(LIST).aptr = (float)(VAL)),			\
	      (LIST).aptr++,						\
	      0)))

#define av_double(LIST,VAL)						\
  ((LIST).faptr < &(LIST).fargs[8]					\
   ? (*(LIST).faptr = (double)(VAL),					\
      (LIST).faptr++,							\
      0)								\
   : ((LIST).aptr >= __av_eptr(LIST)					\
      ? -1 : ((*(double*)(LIST).aptr = (double)(VAL)),			\
	      (LIST).aptr++,						\
	      0)))

#endif

/*
 * structure argument types
 */

#define av_struct(LIST,TYPE,VAL)					\
  __av_struct(LIST,TYPE,sizeof(TYPE),__AV_alignof(TYPE),__av_struct_assign,VAL)
#define __av_struct_assign(TYPE,TYPE_SIZE,TYPE_ALIGN,PLACE,VAL)		\
  *(TYPE*)(PLACE) = (VAL)
/* _av_struct() is like av_struct(), except that you pass the type's size and alignment
 * and the value's address instead of the type and the value themselves.
 */
#define _av_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL_ADDR)			\
  __av_struct(LIST,unknown,TYPE_SIZE,TYPE_ALIGN,__av_struct_copy,VAL_ADDR)
#define __av_struct_copy(TYPE,TYPE_SIZE,TYPE_ALIGN,PLACE,VAL_ADDR)	\
  __structcpy(PLACE,VAL_ADDR,TYPE_SIZE,TYPE_ALIGN)
/* Structure argument alignment. */
#if defined(__i386__) && defined(_MSC_VER)
/* In MSVC, doubles inside structures have alignment 8, i.e.
 * __AV_alignof(double) = 8, but doubles (and also structures containing
 * doubles) are passed on the stack with alignment 4. Looks really weird.
 */
#define __av_struct_alignment(TYPE_ALIGN)  \
  ((TYPE_ALIGN) <= 4 ? (TYPE_ALIGN) : 4)
#else
#define __av_struct_alignment(TYPE_ALIGN)  \
  (TYPE_ALIGN)
#endif
#if defined(__i386__) || defined(__mips__) || defined(__mipsn32__) || defined(__mips64__) || defined(__alpha__) || (defined(__rs6000__) && (defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)))) || defined(__m88k__) || defined(__ia64__) || defined(__s390__)
/* Structures are passed as fully aligned structures on the arg stack.
 * We align the aptr, store the structure, then fill to word alignment.
 * Single-small-integer structures are NOT promoted to integers and have
 * different alignment.
 */
/* little endian -> small structures < 1 word are adjusted to the left */
#if defined(__i386__) || defined(__alpha__) || defined(__x86_64__)
#define __av_struct(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL)		\
  (((LIST).aptr =							\
    (__avword*)(((__avword)(LIST).aptr+(TYPE_SIZE)+__av_struct_alignment(TYPE_ALIGN)-1) & -(long)__av_struct_alignment(TYPE_ALIGN)))\
   > __av_eptr(LIST)							\
   ? -1 : (ASSIGN(TYPE,TYPE_SIZE,TYPE_ALIGN,(void*)((__avword)(LIST).aptr-(TYPE_SIZE)),VAL),\
	   (LIST).aptr = (__avword*)(((__avword)(LIST).aptr+sizeof(__avword)-1) & -(long)sizeof(__avword)),\
	   0))
#endif
#if defined(__ia64__)
/* Types larger than a word have 2-word alignment. */
#define __av_struct(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL)		\
  ((LIST).aptr = (__avword*)(((__avword)(LIST).aptr+(TYPE_SIZE)+__av_struct_alignment(TYPE_ALIGN)-1) & -(long)__av_struct_alignment(TYPE_ALIGN)), \
   ((TYPE_SIZE) > sizeof(__avword) && (((LIST).aptr - &(LIST).args[0]) & 1) ? ++(LIST).aptr : 0), \
   ((LIST).aptr > __av_eptr(LIST)					\
    ? -1 : (ASSIGN(TYPE,TYPE_SIZE,TYPE_ALIGN,(void*)((__avword)(LIST).aptr-(TYPE_SIZE)),VAL),\
	    (LIST).aptr = (__avword*)(((__avword)(LIST).aptr+sizeof(__avword)-1) & -(long)sizeof(__avword)),\
	    0)))
#endif
/* small structures < 1 word are adjusted depending on compiler */
#if defined(__mips__) && !defined(__mipsn32__)
#define __av_struct_leftadjusted(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL) \
  (((LIST).aptr =							\
    (__avword*)(((__avword)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(long)(TYPE_ALIGN)))\
   > __av_eptr(LIST)							\
   ? -1 : (++(LIST).anum,						\
	   ASSIGN(TYPE,TYPE_SIZE,TYPE_ALIGN,(void*)((__avword)(LIST).aptr-(TYPE_SIZE)),VAL),\
	   (LIST).aptr = (__avword*)(((__avword)(LIST).aptr+sizeof(__avword)-1) & -(long)sizeof(__avword)),\
	   0))
#define __av_struct_rightadjusted(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL) \
  (((LIST).aptr =							\
    (__avword*)(((((__avword)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(long)(TYPE_ALIGN))\
		 +sizeof(__avword)-1) & -(long)sizeof(__avword)))	\
   > __av_eptr(LIST)							\
   ? -1 : (++(LIST).anum,						\
	   ASSIGN(TYPE,TYPE_SIZE,TYPE_ALIGN,(void*)((__avword)(LIST).aptr-(TYPE_SIZE)),VAL),\
	   0))
#define __av_struct(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL)		\
  ((LIST).flags & __AV_SGICC_STRUCT_ARGS				\
   ? /* SGI MIPS cc passes small structures left-adjusted, although big-endian! */\
     __av_struct_leftadjusted(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL) \
   : /* SGI MIPS gcc passes small structures within the first four words left-	  \
      * adjusted, for compatibility with cc. But structures in memory are passed  \
      * right-adjusted!! See gcc-2.6.3/config/mips/mips.c:function_arg().	  \
      */									  \
     ((LIST).aptr < &(LIST).args[4]						\
      ? __av_struct_leftadjusted(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL)	\
      : __av_struct_rightadjusted(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL)))
#endif
#if defined(__mipsn32__) || defined(__mips64__)
/* When a structure is passed (partially) in registers, it is passed in the
 * integer registers, except that doubles within the structure are passed in
 * the floating point registers. Instead of distinguishing these cases, we
 * always pass the structure in both the integer and the floating point
 * registers.
 */
#define __av_struct_leftadjusted(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL) \
  (((LIST).aptr =							\
    (__avword*)(((__avword)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(long)(TYPE_ALIGN)))\
   > __av_eptr(LIST)							\
   ? -1 : (ASSIGN(TYPE,TYPE_SIZE,TYPE_ALIGN,(void*)((__avword)(LIST).aptr-(TYPE_SIZE)),VAL),\
	   (LIST).aptr = (__avword*)(((__avword)(LIST).aptr+sizeof(__avword)-1) & -(long)sizeof(__avword)),\
	   ((LIST).anum < 8 && ((LIST).darg_mask |= (-1 << (LIST).anum))), \
	   (LIST).anum += (((((TYPE_SIZE)+(TYPE_ALIGN)-1) & -(long)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(long)sizeof(__avword))/sizeof(__avword),\
	   (LIST).darg_mask &= (1 << ((LIST).anum < 8 ? (LIST).anum : 8)) - 1, \
	   0))
#define __av_struct_rightadjusted(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL) \
  (((LIST).aptr =							\
    (__avword*)(((((__avword)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(long)(TYPE_ALIGN))\
		 +sizeof(__avword)-1) & -(long)sizeof(__avword)))	\
   > __av_eptr(LIST)							\
   ? -1 : (ASSIGN(TYPE,TYPE_SIZE,TYPE_ALIGN,(void*)((__avword)(LIST).aptr-(TYPE_SIZE)),VAL),\
	   ((LIST).anum < 8 && ((LIST).darg_mask |= (-1 << (LIST).anum))), \
	   (LIST).anum += (((((TYPE_SIZE)+(TYPE_ALIGN)-1) & -(long)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(long)sizeof(__avword))/sizeof(__avword),\
	   (LIST).darg_mask &= (1 << ((LIST).anum < 8 ? (LIST).anum : 8)) - 1, \
	   0))
#define __av_struct(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL)		\
  ((LIST).flags & __AV_SGICC_STRUCT_ARGS				\
   ? /* SGI MIPS cc passes small structures left-adjusted, although big-endian! */\
     __av_struct_leftadjusted(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL) \
   : /* SGI MIPS gcc passes small structures right-adjusted. */		\
     __av_struct_rightadjusted(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL))
#endif
#if defined(__rs6000__)
#define __av_struct_leftadjusted(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL)\
  (((LIST).aptr =							\
    (__avword*)(((__avword)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(long)(TYPE_ALIGN)))\
   > __av_eptr(LIST)							\
   ? -1 : (ASSIGN(TYPE,TYPE_SIZE,TYPE_ALIGN,(void*)((__avword)(LIST).aptr-(TYPE_SIZE)),VAL),\
	   (LIST).aptr = (__avword*)(((__avword)(LIST).aptr+sizeof(__avword)-1) & -(long)sizeof(__avword)),\
	   0))
#define __av_struct_rightadjusted(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL)\
  (((LIST).aptr =							\
    (__avword*)(((((__avword)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(long)(TYPE_ALIGN))\
		 +sizeof(__avword)-1) & -(long)sizeof(__avword)))	\
   > __av_eptr(LIST)							\
   ? -1 : (ASSIGN(TYPE,TYPE_SIZE,TYPE_ALIGN,(void*)((__avword)(LIST).aptr-(TYPE_SIZE)),VAL),\
	   0))
#define __av_struct(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL)		\
  ((LIST).flags & __AV_AIXCC_STRUCT_ARGS				\
   ? /* AIX cc and xlc pass small structures left-adjusted, although big-endian! */\
     __av_struct_leftadjusted(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL) \
   : /* gcc passes small structures right-adjusted. */			\
     __av_struct_rightadjusted(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL))
#endif
#if defined(__s390__)
#define __av_struct_rightadjusted(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL)\
  (((LIST).aptr =							\
    (__avword*)(((((__avword)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(long)(TYPE_ALIGN))\
		 +sizeof(__avword)-1) & -(long)sizeof(__avword)))	\
   > __av_eptr(LIST)							\
   ? -1 : (ASSIGN(TYPE,TYPE_SIZE,TYPE_ALIGN,(void*)((__avword)(LIST).aptr-(TYPE_SIZE)),VAL),\
	   0))
#define __av_struct(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL)		\
((TYPE_SIZE) != 1 && (TYPE_SIZE) != 2 && (TYPE_SIZE) != 4 && (TYPE_SIZE) != 8 \
 ? (++(LIST).aptr							\
    > ((LIST).eptr = (__avword*)((long)(LIST).eptr - (((TYPE_SIZE)+7)&-8)))\
    ? -1 :								\
    (ASSIGN(TYPE,TYPE_SIZE,TYPE_ALIGN,(void*)(LIST).eptr,VAL),		\
     (LIST).aptr[-1] = (__avword)(LIST).eptr,				\
     0))								\
 : (((TYPE_SIZE) == 8 && (LIST).aptr - (LIST).args - (LIST).fargwords == 4 ? ++(LIST).aptr,0 : 0), \
    __av_struct_rightadjusted(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL)))
#endif
/* big endian -> small structures < 1 word are adjusted to the right */
#if defined(__m88k__)
#define __av_struct(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL)		\
  (((LIST).aptr =							\
    (__avword*)(((((__avword)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(long)(TYPE_ALIGN))\
		 +sizeof(__avword)-1) & -(long)sizeof(__avword)))	\
   > __av_eptr(LIST)							\
   ? -1 : (ASSIGN(TYPE,TYPE_SIZE,TYPE_ALIGN,(void*)((__avword)(LIST).aptr-(TYPE_SIZE)),VAL),\
	   0))
#endif
#endif
#if defined(__m68k__) || defined(__arm__) || defined(__convex__)
/* Structures are passed as embedded copies on the arg stack.
 */
#define __av_struct(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL)		\
  (((LIST).aptr = (__avword*)(((long)(LIST).aptr+(TYPE_SIZE)+sizeof(__avword)-1) & -(long)sizeof(__avword))) \
    > __av_eptr(LIST)							\
    ? -1 : (ASSIGN(TYPE,TYPE_SIZE,TYPE_ALIGN,(void*)((__avword)(LIST).aptr-(TYPE_SIZE)),VAL),\
	    0))
#endif
#if (defined(__sparc__) && !defined(__sparc64__)) || (defined(__rs6000__) && !(defined(_AIX) || (defined(__MACH__) && defined(__APPLE__))))
/* Structures are passed as pointers to caller-made local copies. We
 * grab space for the copies from the end of the argument list space
 * and always use maximal (double) alignment.
 */
#define __av_struct(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL)		\
   (++(LIST).aptr							\
    > ((LIST).eptr = (__avword*)((long)(LIST).eptr - (((TYPE_SIZE)+7)&-8)))\
    ? -1 :								\
    (ASSIGN(TYPE,TYPE_SIZE,TYPE_ALIGN,(void*)(LIST).eptr,VAL),		\
     (LIST).aptr[-1] = (__avword)(LIST).eptr,				\
     0))
#endif
#if defined(__sparc64__)
/* Structures <= 16 bytes are passed as embedded copies on the arg stack,
 * left-adjusted (although big-endian!).
 * When a structure is passed (partially) in registers, it is passed in the
 * integer registers, except that floats and doubles within the structure
 * are passed in the floating point registers. Instead of distinguishing
 * these cases, we always pass the structure in both the integer and the
 * floating point registers.
 * Big structures are passed as pointers to caller-made local copies.
 * FIXME: Shouldn't (LIST).anum be incremented in sync with (LIST).aptr ?
 */
#define __av_struct(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL)		\
  ((TYPE_SIZE) > 16							\
   ? (++(LIST).aptr							\
      > ((LIST).eptr = (__avword*)((long)(LIST).eptr - (((TYPE_SIZE)+7)&-8)))\
      ? -1 :								\
      (ASSIGN(TYPE,TYPE_SIZE,TYPE_ALIGN,(void*)(LIST).eptr,VAL),	\
       (LIST).aptr[-1] = (__avword)(LIST).eptr,				\
       0))								\
   : (((LIST).aptr =							\
       (__avword*)(((__avword)(LIST).aptr+(TYPE_SIZE)+(TYPE_ALIGN)-1) & -(long)(TYPE_ALIGN)))\
      > __av_eptr(LIST)							\
      ? -1 : (ASSIGN(TYPE,TYPE_SIZE,TYPE_ALIGN,(void*)((__avword)(LIST).aptr-(TYPE_SIZE)),VAL),\
	      (LIST).aptr = (__avword*)(((__avword)(LIST).aptr+sizeof(__avword)-1) & -(long)sizeof(__avword)),\
	      ((LIST).anum < 16						\
		&& ((LIST).farg_mask |= (-1 << (LIST).anum),		\
		    (LIST).darg_mask |= (-1 << (LIST).anum))),		\
	      (LIST).anum += (((((TYPE_SIZE)+(TYPE_ALIGN)-1) & -(long)(TYPE_ALIGN)) + sizeof(__avword)-1) & -(long)sizeof(__avword))/sizeof(__avword),\
	      (LIST).farg_mask &= (1 << ((LIST).anum < 16 ? (LIST).anum : 16)) - 1, \
	      (LIST).darg_mask &= (1 << ((LIST).anum < 16 ? (LIST).anum : 16)) - 1, \
	      0)))
#endif
#if defined(__hppa__)
/* Structures <= 8 bytes are passed as embedded copies on the arg stack.
 * Big structures are passed as pointers to caller-made local copies.
 */
#define __av_struct(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL)			\
  ((TYPE_SIZE) > 8								\
   ? (--(LIST).aptr								\
      < ((LIST).eptr = (__avword*)((long)(LIST).eptr + (((TYPE_SIZE) + 7) & -8))) \
      ? -1									\
      : (ASSIGN(TYPE,TYPE_SIZE,TYPE_ALIGN,(void*)((long)(LIST).eptr - (((TYPE_SIZE) + 7) & -8)), VAL), \
	 *(LIST).aptr = (__avword)((long)(LIST).eptr - (((TYPE_SIZE) + 7) & -8)), \
	 0))									\
   : ((TYPE_SIZE) > 4								\
      ? (((LIST).aptr = (__avword*)((((long)(LIST).aptr & -8) - (long)(TYPE_SIZE)) & -8)) \
	  < &(LIST).args[0]							\
	  ? -1 : (ASSIGN(TYPE,TYPE_SIZE,TYPE_ALIGN,(void*)(LIST).aptr,VAL), 0))	\
      : /* FIXME: gcc-2.6.3 passes structures <= 4 bytes in memory left-adjusted! ?? */\
        (((LIST).aptr = (__avword*)(((long)(LIST).aptr & -4) - (long)(TYPE_SIZE))) \
	  < &(LIST).args[0]							\
	  ? -1 : (ASSIGN(TYPE,TYPE_SIZE,TYPE_ALIGN,(void*)(LIST).aptr,VAL),	\
		  (LIST).aptr = (__avword*)((long)(LIST).aptr & -4),		\
		  0))))
#endif
#if defined(__x86_64__)
/* Structures <= 16 bytes can be passed in integer or floating-point registers
   if there is enough room for the whole number of words needed by the structure
   in the corresponding iargs/fargs block. We can't distinguish the two cases
   and support only passing in integer registers. Other structures are passed
   on the arg stack. */
#define __av_struct(LIST,TYPE,TYPE_SIZE,TYPE_ALIGN,ASSIGN,VAL)			\
  ((LIST).iaptr + ((TYPE_SIZE) + sizeof(__avword)-1) / sizeof(__avword) <= &(LIST).iargs[6] \
   ? (ASSIGN(TYPE,TYPE_SIZE,TYPE_ALIGN,(void*)(LIST).iaptr,VAL),		\
      (LIST).iaptr += ((TYPE_SIZE) + sizeof(__avword)-1) / sizeof(__avword),	\
      0)									\
   : ((LIST).aptr = (__avword*)((__avword)(LIST).aptr + (((TYPE_SIZE)+__av_struct_alignment(TYPE_ALIGN)-1) & -(long)__av_struct_alignment(TYPE_ALIGN))), \
      ((LIST).aptr > __av_eptr(LIST)						\
       ? -1 : (ASSIGN(TYPE,TYPE_SIZE,TYPE_ALIGN,(void*)((__avword)(LIST).aptr - (((TYPE_SIZE)+__av_struct_alignment(TYPE_ALIGN)-1) & -(long)__av_struct_alignment(TYPE_ALIGN))),VAL),\
	       0))))
#endif

/*
 * calling the function
 */

#define av_call(LIST) __builtin_avcall(&(LIST))

/* Determine whether a struct type is word-splittable, i.e. whether each of
 * its components fit into a register.
 * The entire computation is done at compile time.
 */
#define av_word_splittable_1(slot1)  \
  (__av_offset1(slot1)/sizeof(__avword) == (__av_offset1(slot1)+sizeof(slot1)-1)/sizeof(__avword))
#define av_word_splittable_2(slot1,slot2)  \
  ((__av_offset1(slot1)/sizeof(__avword) == (__av_offset1(slot1)+sizeof(slot1)-1)/sizeof(__avword)) \
   && (__av_offset2(slot1,slot2)/sizeof(__avword) == (__av_offset2(slot1,slot2)+sizeof(slot2)-1)/sizeof(__avword)) \
  )
#define av_word_splittable_3(slot1,slot2,slot3)  \
  ((__av_offset1(slot1)/sizeof(__avword) == (__av_offset1(slot1)+sizeof(slot1)-1)/sizeof(__avword)) \
   && (__av_offset2(slot1,slot2)/sizeof(__avword) == (__av_offset2(slot1,slot2)+sizeof(slot2)-1)/sizeof(__avword)) \
   && (__av_offset3(slot1,slot2,slot3)/sizeof(__avword) == (__av_offset3(slot1,slot2,slot3)+sizeof(slot3)-1)/sizeof(__avword)) \
  )
#define av_word_splittable_4(slot1,slot2,slot3,slot4)  \
  ((__av_offset1(slot1)/sizeof(__avword) == (__av_offset1(slot1)+sizeof(slot1)-1)/sizeof(__avword)) \
   && (__av_offset2(slot1,slot2)/sizeof(__avword) == (__av_offset2(slot1,slot2)+sizeof(slot2)-1)/sizeof(__avword)) \
   && (__av_offset3(slot1,slot2,slot3)/sizeof(__avword) == (__av_offset3(slot1,slot2,slot3)+sizeof(slot3)-1)/sizeof(__avword)) \
   && (__av_offset4(slot1,slot2,slot3,slot4)/sizeof(__avword) == (__av_offset4(slot1,slot2,slot3,slot4)+sizeof(slot4)-1)/sizeof(__avword)) \
  )
#define __av_offset1(slot1)  \
  0
#define __av_offset2(slot1,slot2)  \
  ((__av_offset1(slot1)+sizeof(slot1)+__AV_alignof(slot2)-1) & -(long)__AV_alignof(slot2))
#define __av_offset3(slot1,slot2,slot3)  \
  ((__av_offset2(slot1,slot2)+sizeof(slot2)+__AV_alignof(slot3)-1) & -(long)__AV_alignof(slot3))
#define __av_offset4(slot1,slot2,slot3,slot4)  \
  ((__av_offset3(slot1,slot2,slot3)+sizeof(slot3)+__AV_alignof(slot4)-1) & -(long)__AV_alignof(slot4))

/*
 * Miscellaneous declarations.
 */

#if defined(__STDC__) || defined(__GNUC__) || defined(__cplusplus)
extern int __builtin_avcall (av_alist* l);
extern void __structcpy (void* dest, void* src, unsigned long size, unsigned long alignment);
#else
extern int __builtin_avcall ();
extern void __structcpy ();
#endif

#endif /*_avcall_h */
