// Assembly language support for sparc CPU.
// Bruno Haible 29.5.1999

#ifdef ASM_UNDERSCORE
// SunOS4, Linux/a.out
#ifdef __STDC__
#define C(entrypoint) _##entrypoint
#else
#define C(entrypoint) _/**/entrypoint
#endif
#else
// Solaris, Linux/ELF
#define C(entrypoint) entrypoint
#endif

// When assembly language code is compiled into a shared library, ELF linkers
// need to know which symbols are functions.
#if defined(__NetBSD__) || defined(__OpenBSD__)
#define DECLARE_FUNCTION(name) .type C(name),@function
#elif defined(__svr4__) || defined(__ELF__)
// Solaris, Linux/ELF
// Some preprocessors keep the backslash in place, some don't.
// Some complain about the # being not in front of an ANSI C macro.
// Therefore we use a dollar, which will be sed-converted to # later.
#define DECLARE_FUNCTION(name) .type C(name),$function
#else
// SunOS4, Linux/a.out
#define DECLARE_FUNCTION(name)
#endif
