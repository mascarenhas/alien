
all: alien.so alien/struct.so

alien.so: alien.o 
	export MACOSX_DEPLOYMENT_TARGET=10.3; ld $(LIB_OPTION) -o alien.so alien.o -lavcall

alien/struct.so: alien/struct.o 
	export MACOSX_DEPLOYMENT_TARGET=10.3; ld $(LIB_OPTION) -o alien/struct.so alien/struct.o

install: alien.so alien/struct.so
	cp alien.so $(LUA_LIBDIR)
	mkdir -p $(LUA_LIBDIR)/alien
	cp alien/struct.so $(LUA_LIBDIR)/alien

clean:
	rm *.so *.o alien/*.so alien/*.o

upload:
	darcs dist -d alien-current
	ncftpput -u mascarenhas ftp.luaforge.net alien/htdocs alien-current.tar.gz
