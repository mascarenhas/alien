// Assembly language support for arm CPU.
// Bruno Haible 29.5.1999

#ifdef ASM_UNDERSCORE
#ifdef __STDC__
#define C(entrypoint) _##entrypoint
#else
#define C(entrypoint) _/**/entrypoint
#endif
#else
#define C(entrypoint) entrypoint
#endif

// When assembly language code is compiled into a shared library, ELF linkers
// need to know which symbols are functions.
#if defined(__NetBSD__)
#define DECLARE_FUNCTION(name) .type C(name),%function
#else
#define DECLARE_FUNCTION(name)
#endif
