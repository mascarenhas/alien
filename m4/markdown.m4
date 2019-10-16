#===
# autoconf macro to check for markdown converters
#

m4_define_default([_AC_MARKDOWN_PROGS],
  [markdown \
   pandoc])
AC_DEFUN([AC_PROG_MARKDOWN], [
  AC_ARG_VAR([MARKDOWN_PROG], [Markdown converter, e.g. /usr/bin/pandoc])
  AS_IF([test "x$MARKDOWN_PROG" != 'x'],
    [
    AC_MSG_RESULT(using $MARKDOWN_PROG to process markdown)
    AC_SUBST(ac_markdown_prog, $MARKDOWN_PROG)],
    [
    AC_CHECK_PROGS(_MARKDOWN_PROG, [_AC_MARKDOWN_PROGS],"")
    AS_IF([test "x$_MARKDOWN_PROG" != 'x'],
      [AC_SUBST(ac_markdown_prog, $_MARKDOWN_PROG)],
      [AC_MSG_ERROR([cannot find a markdown converter (_AC_MARKDOWN_PROGS)])])])])
