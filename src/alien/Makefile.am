## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = $(LUA_INCLUDE)
AM_CFLAGS = $(CFLAGS_STACK)

pkglib_LTLIBRARIES = core.la

core_la_SOURCES = core.c
core_la_LDFLAGS = -module -avoid-version -lffi

# This file is #included, so does not need to be compiled
EXTRA_DIST = struct.c
