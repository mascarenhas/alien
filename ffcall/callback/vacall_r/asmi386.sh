#!/bin/sh
# Translate the assembler syntax of i386 assembler programs
# Usage: asmsyntax [-no-C] < gas-asm-file > all-asm-file
# Warning! All comments are stripped.

tmpscript01=sed$$tmp01
tmpscript02=sed$$tmp02
tmpscript03=sed$$tmp03
tmpscript04=sed$$tmp04
tmpscript05=sed$$tmp05
tmpscript06=sed$$tmp06
tmpscript07=sed$$tmp07
tmpscript08=sed$$tmp08
tmpscript09=sed$$tmp09
tmpscript10=sed$$tmp10
tmpscript11=sed$$tmp11
tmpremove='rm -f $tmpscript01 $tmpscript02 $tmpscript03 $tmpscript04 $tmpscript05 $tmpscript06 $tmpscript07 $tmpscript08 $tmpscript09 $tmpscript10 $tmpscript11'
trap "$tmpremove" 1 2 15

cat > $tmpscript01 << \EOF
# ----------- Strip comments
s,# .*,,
s,[ 	][ 	]*$,,
EOF

cat > $tmpscript02 << \EOF
# ----------- Remove #APP/#NO_APP lines, add a blank line at the end
/^#APP$/d
/^#NO_APP$/d
/gcc2_compiled/d
/gnu_compiled_c/d
EOF

cat > $tmpscript03 << \EOF
# ----------- Global symbols depends on ASM_UNDERSCORE
s/_\([A-Za-z0-9_:]*\)/C(\1)/
EOF

cat > $tmpscript04 << \EOF
# ----------- Introduce macro syntax for operands
s/\([-+0-9A-Z_]\+\)[(]%\(e..\)[)]/MEM_DISP(\2,\1)/g
s/[(]%\(e..\)[)]/MEM(\1)/g
s/\([-+0-9A-Z_]\+\)[(],%\(e..\),\([0-9]*\)[)]/MEM_DISP_SHINDEX0(\1,\2,\3)/g
s/\([-+0-9A-Z_]\+\)[(]%\(e..\),%\(e..\),\([0-9]*\)[)]/MEM_DISP_SHINDEX(\2,\1,\3,\4)/g
s/[(]%\(e..\),%\(e..\),\([0-9]*\)[)]/MEM_SHINDEX(\1,\2,\3)/g
s/[(]%\(e..\),%\(e..\)[)]/MEM_INDEX(\1,\2)/g
EOF

cat > $tmpscript05 << \EOF
# ----------- Introduce macro syntax for instructions
s/\(push\|pop\|mul\|div\|not\|neg\|inc\|dec\|fld\|fstp\)\(.\)\( \+\)\(.*\)$/INSN1(\1,\2	,\4)/
s/\(call\|jmp\|jc\|jnc\|je\|jne\|jz\|jnz\|ja\|jae\|jb\|jbe\|jl\|jge\|js\|jns\)\( \+\)\(.*\)$/INSN1(\1,_	,\3)/
s/\(movs\|movz\)\(.\)l\( \+\)\(.*\)$/INSN2MOVX(\1,\2	,\4)/
s/\(mov\|add\|sub\|adc\|sbb\|xor\|test\|cmp\|rcl\|rcr\|and\|or\|sar\|shr\|shl\|lea\)\(.\)\( \+\)\(.*\)$/INSN2(\1,\2	,\4)/
s/\(shld\|shrd\)\(.\)\( \+\)shcl\( \+\)\(.*\)$/INSN2SHCL(\1,\2	,\5)/
s/rep ;/REP/
s/repz ;/REPZ/
EOF

cat > $tmpscript06 << \EOF
# ----------- Add size prefixes to memory references' \
s/\([(]f[^(,]*,s.*\),MEM/\1,X4 MEM/g
s/\([(]f[^(,]*,l.*\),MEM/\1,X8 MEM/g
s/\([(][^(,]*,b.*\),MEM/\1,X1 MEM/g
s/\([(][^(,]*,w.*\),MEM/\1,X2 MEM/g
s/\([(][^(,]*,l.*\),MEM/\1,X4 MEM/g
EOF

cat > $tmpscript07 << \EOF
# ----------- Introduce macro syntax for register names
s/%\(e..\)/R(\1)/g
s/%\(..\)/R(\1)/g
s/\$\([-0-9]*\)/NUM(\1)/g
EOF

cat > $tmpscript08 << \EOF
# ----------- Treat table jumps (hairy)
# (Needed because the MSVC inline assembler does not have pseudo-ops.
# Note that we transform a table of absolute addresses with 4 bytes
# per entry into a table of absolute addresses with 8 bytes per entry.)
s/^	\.long \(.*\)$/#ifdef _MSC_VER\
	nop\
	nop\
	push \1\
#else\
	.long \1\
#endif/
s/^	\(INSN1[(]jmp,_[^,]*,\)\*MEM_DISP_SHINDEX0[(]\([^,)]*\),\([^,)]*\),4[)][)]$/#ifdef _MSC_VER\
	INSN2(lea,l	,MEM_DISP_SHINDEX0(\2+8,\3,8),R(\3))\
	INSN2(mov,l	,X4 MEM_DISP(\3,-4),R(\3))\
	INSN1(jmp,_	,INDIR(R(\3)))\
#else\
	\1INDIR(MEM_DISP_SHINDEX0(\2,\3,4)))\
#endif/
EOF

cat > $tmpscript09 << \EOF
# ----------- Treat indirect calls
s/\(INSN1[(]\(call\|jmp\),_[^,]*,\)\*\(R[(][^)]*[)]\)[)]$/\1INDIR(\3))/
EOF

cat > $tmpscript10 << \EOF
# ----------- Introduce macro syntax for assembler pseudo-ops
/\.file\([ 	]\+\)/d
s/\.text/TEXT()/
s/^\([^#]*\)\.align \(.*\)/\1ALIGN(\2)/
s/\.globl\( \+\)\(.*\)$/GLOBL(\2)/
s/^C(\([A-Za-z0-9_]*\):)/FUNBEGIN(\1)/
# The next 5 lines add FUNEND() after each ret followed by an empty line
/[ 	]ret *$/{
n
/^$/s/^$/FUNEND()\
/
}
EOF

cat > $tmpscript11 << \EOF
# ----------- Declare global symbols as functions (we have no variables)
s/GLOBL(C(\([A-Za-z0-9_]*\)))$/GLOBL(C(\1))\
	DECLARE_FUNCTION(\1)/
EOF

sed -f $tmpscript01 | \
sed -f $tmpscript02 | \
(cat - ; echo) | \
(if [ $# = 1 -a "x$1" = "x-no-C" ] ; then cat - ; else sed -f $tmpscript03 ; fi) | \
sed -f $tmpscript04 | \
sed -f $tmpscript05 | \
sed -f $tmpscript06 | \
sed -f $tmpscript07 | \
sed -f $tmpscript08 | \
sed -f $tmpscript09 | \
sed -f $tmpscript10 | \
(if [ $# = 1 -a "x$1" = "x-no-C" ] ; then cat - ; else sed -f $tmpscript11 ; fi)

eval "$tmpremove"

