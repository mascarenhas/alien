// Assembly language support for mips CPU.
// Bruno Haible 29.5.1999

// When assembly language code is compiled into a shared library, ELF linkers
// need to know which symbols are functions.
#if defined(__GNU__) || defined(__NetBSD__)
#define DECLARE_FUNCTION(name) .type name,@function
#else
#define DECLARE_FUNCTION(name)
#endif
