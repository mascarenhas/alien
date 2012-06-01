## Process this file with automake to produce Makefile.in

SUBDIRS = src tests doc samples

ACLOCAL_AMFLAGS = -I m4

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
