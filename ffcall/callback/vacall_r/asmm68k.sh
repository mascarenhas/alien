#!/bin/sh
# Translate the assembler syntax of m68k assembler programs
# Usage: asmm68k < sunos-asm-file > portable-asm-file
# The portable-asm-file has to be
#   1. preprocessed,
#   2. grep -v '^ *#line' | grep -v '^#'
#   3. sed -e 's,% ,%,g' -e 's,//.*$,,'

tmpscript1=sed$$tmp1
tmpscript2=sed$$tmp2
tmpremove='rm -f $tmpscript1 $tmpscript2'
trap "$tmpremove" 1 2 15

cat > $tmpscript1 << \EOF
# ----------- Remove #APP/#NO_APP lines
/^#APP$/d
/^#NO_APP$/d
# ----------- Remove gcc self-identification
/gcc2_compiled/d
/gnu_compiled_c/d
EOF

cat > $tmpscript2 << \EOF
# ----------- Prefix register names with $, to be turned into % later
s/,/, /g
s/\([^A-Za-z0-9_]\)\([ad][0-7]\|sp\|fp[0-7]\)\([^A-Za-z0-9_]\)/\1$\2\3/g
s/\([^A-Za-z0-9_]\)\([ad][0-7]\|sp\|fp[0-7]\)$/\1$\2/g
s/, /,/g
# ----------- Declare global symbols as functions (we have no variables)
s/\.globl _\([A-Za-z0-9_]*\)$/.globl _\1\
	DECLARE_FUNCTION(\1)/
# ----------- Global symbols depends on ASM_UNDERSCORE
s/_\([A-Za-z0-9_:]*\)/C(\1)/
EOF

sed -f $tmpscript1 | \
sed -f $tmpscript2

eval "$tmpremove"
