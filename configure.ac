dnl Process this file with autoconf to produce a configure script

AC_INIT(alien, 0.7.1, http://mascarenhas.github.com/alien)
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([1.11.1 -Wall -Werror foreign subdir-objects])

AM_SILENT_RULES([yes])

dnl Check for programs
ifdef([AM_PROG_AR], [AM_PROG_AR])
AC_PROG_CC
AS_IF([test "x$GCC" = "xyes"],[CFLAGS_STACK="-fno-stack-protector -Wall"])
AC_SUBST(CFLAGS_STACK)

dnl Set up libtool
LT_PREREQ([2.2.6])
LT_INIT([disable-static])
module=yes eval shrext=$shrext_cmds
AC_SUBST([objdir])
AC_SUBST([shrext])
AC_SUBST(LIBTOOL_DEPS)

dnl Check for header files
AC_HEADER_STDC

dnl Check for functions
AC_FUNC_ALLOCA

dnl libffi
AC_CHECK_HEADERS([ffi.h ffi/ffi.h], [break])
case $ac_cv_header_ffi_h$ac_cv_header_ffi_ffi_h in
  *yes*) ;;
  *)     AC_MSG_FAILURE([cannot find ffi.h]) ;;
esac
AC_CHECK_LIB([ffi], [ffi_closure_alloc], , AC_MSG_FAILURE([cannot find new enough libffi]))
AC_CHECK_HEADERS([stdint.h])

dnl Lua >= 5.1
AX_PROG_LUA(5.1, 5.4)
AX_LUA_HEADERS

dnl Generate output files
AC_CONFIG_MACRO_DIR(m4)
AC_CONFIG_HEADER(config.h)
AC_CONFIG_FILES(Makefile $PACKAGE-$VERSION-1.rockspec:$PACKAGE.rockspec.in)
AC_OUTPUT
