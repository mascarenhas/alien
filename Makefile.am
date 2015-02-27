## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = $(LUA_INCLUDE)
AM_CFLAGS = $(CFLAGS_STACK)

dist_bin_SCRIPTS =
check_LTLIBRARIES =
dist_data_DATA =
dist_doc_DATA =
lib_LTLIBRARIES =
EXTRA_DIST = $(PACKAGE).rockspec.in $(PACKAGE)-$(VERSION)-1.rockspec

include build-aux/Makefile.am
include doc/Makefile.am
include samples/Makefile.am
include src/Makefile.am
include tests/Makefile.am

release: all
	git diff --exit-code && \
	git tag -a -m "Release tag" "v$(VERSION)" && \
	git push && git push --tags && \
	$(LUAROCKS) build $(ROCKSPEC) && \
	$(LUAROCKS) upload $(ROCKSPEC)
