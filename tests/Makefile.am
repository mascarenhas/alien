LUA_PATH ?= ;
LUA_CPATH ?= ;
LUA_ENV = LUA_INIT= LUA_PATH="$(abs_top_srcdir)/src/?.lua;$(LUA_PATH)" LUA_CPATH="$(abs_top_builddir)/src/?$(shrext);$(LUA_CPATH)" LD_LIBRARY_PATH="$(abs_top_builddir)/tests/$(objdir)"

pkglib_LTLIBRARIES += tests/libalientest.la

tests_libalientest_la_SOURCES = tests/alientest.c
tests_libalientest_la_LDFLAGS = -module -avoid-version

check-local:
	cp "$(abs_top_builddir)/src/alien/$(objdir)/"core$(shrext) "$(abs_top_builddir)/src/alien/"
	$(LUA_ENV) $(LUA) test_alien.lua
	rm -f "$(abs_top_builddir)/src/alien/core$(shrext)"
