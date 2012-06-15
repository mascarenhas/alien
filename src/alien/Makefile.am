pkglib_LTLIBRARIES += 		\
	src/alien/core.la	\
	src/alien/struct.la

src_alien_core_la_SOURCES = src/alien/core.c
src_alien_core_la_LDFLAGS = -module -avoid-version -lffi

src_alien_struct_la_SOURCES = src/alien/struct.c
src_alien_struct_la_LDFLAGS = -module -avoid-version

pkglib_LTLIBRARIES = core.la

core_la_SOURCES = core.c
core_la_LDFLAGS = -module -avoid-version -lffi

# This file is #included, so does not need to be compiled
EXTRA_DIST = struct.c
