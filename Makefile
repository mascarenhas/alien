
all: alien.so

alien.so: alien.o 
	export MACOSX_DEPLOYMENT_TARGET=10.3; ld $(LIB_OPTION) -o alien.so alien.o -lavcall

install: alien.so
	cp alien.so $(LUA_LIBDIR)

clean:
	rm alien.so alien.o

upload:
	darcs dist -d alien-current
	ncftpput -u mascarenhas ftp.luaforge.net alien/htdocs alien-current.tar.gz
