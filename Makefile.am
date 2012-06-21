## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = $(LUA_INCLUDE)
AM_CFLAGS = $(CFLAGS_STACK)

bin_SCRIPTS =
check_LTLIBRARIES =
dist_data_DATA =
dist_doc_DATA =
pkglib_LTLIBRARIES =
EXTRA_DIST =

include build-aux/Makefile.am
include doc/Makefile.am
include samples/Makefile.am
include src/Makefile.am
include tests/Makefile.am

ROCKSPEC = $(PACKAGE)-$(VERSION)-1.rockspec

rockspec/$(ROCKSPEC): rockspec/$(PACKAGE).rockspec dist
	sed -e 's/@MD5@/'`$(MD5SUM) $(distdir).tar.gz | cut -d " " -f 1`'/g' < rockspec/$(PACKAGE).rockspec > $@

DISTCLEANFILES = rockspec/$(PACKAGE).rockspec

upload-cvs:
	git archive --output alien-current.tar.gz master
	ncftpput -u mascarenhas ftp.luaforge.net alien/htdocs alien-current.tar.gz

upload-dist:
	git archive --format=tar --prefix=alien-$(VERSION)/ $(VERSION) | gzip > alien-$(VERSION).tar.gz
	ncftpput -u mascarenhas ftp.luaforge.net alien/htdocs alien-$(VERSION).tar.gz
	ncftpput -u mascarenhas ftp.luaforge.net alien/htdocs doc/index.html
