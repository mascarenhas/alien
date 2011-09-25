## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = $(LUA_INCLUDE)
AM_CFLAGS = $(CFLAGS_STACK)

pkglib_LTLIBRARIES = core.la struct.la

core_la_SOURCES = core.c
core_la_LDFLAGS = -module -avoid-version -lffi

struct_la_SOURCES = struct.c
struct_la_LDFLAGS = -module -avoid-version
