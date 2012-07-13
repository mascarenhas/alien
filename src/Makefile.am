dist_data_DATA += src/alien.lua
bin_SCRIPTS += src/constants

lib_LTLIBRARIES += src/alien_c.la

src_alien_c_la_SOURCES = src/alien.c
src_alien_c_la_LDFLAGS = -module -avoid-version -lffi

# This file is #included, so does not need to be compiled
EXTRA_DIST += src/struct.c
