LUA_PATH ?= ;
LUA_CPATH ?= ;
LUA_ENV = LUA_INIT= LUA_PATH="$(abs_top_srcdir)/src/?.lua;$(LUA_PATH)" LUA_CPATH="$(abs_top_builddir)/src/?$(shrext);$(LUA_CPATH)" LD_LIBRARY_PATH="$(abs_top_builddir)/tests/$(objdir)"

check_LTLIBRARIES += tests/libalientest.la

tests_libalientest_la_SOURCES = tests/alientest.c
# -rpath ensures that the .so is built by "make check"
tests_libalientest_la_LDFLAGS = -module -avoid-version -rpath /dev/null

check-local:
	cp src/$(objdir)/alien_c$(shrext) src/
	cd tests && $(LUA_ENV) $(LUA) test_alien.lua
	rm -f src/alien_c$(shrext)
