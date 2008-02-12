
all: alien.so alien/struct.so

osx:
	cd ffcall && cat executables | xargs chmod +x && ./configure CC=gcc && make CC=gcc
	make all	

alien.o: alien.c
	$(CC) -c $(CFLAGS) $(FFCALL_INCDIR) -o alien.o alien.c

alien.so: alien.o 
	export MACOSX_DEPLOYMENT_TARGET=10.3; $(LD) $(LIB_OPTION) -o alien.so alien.o $(FFCALL_LIBDIR)  -lavcall -lcallback

alien/struct.so: alien/struct.o 
	export MACOSX_DEPLOYMENT_TARGET=10.3; $(LD) $(LIB_OPTION) -o alien/struct.so alien/struct.o

install: alien.so alien/struct.so
	cp alien.so $(LUA_LIBDIR)
	mkdir -p $(LUA_LIBDIR)/alien
	cp alien/struct.so $(LUA_LIBDIR)/alien
	chmod +x constants
	cp constants $(BIN_DIR)/

clean:
	rm *.so *.o alien/*.so alien/*.o

upload:
	darcs dist -d alien-current
	ncftpput -u mascarenhas ftp.luaforge.net alien/htdocs alien-current.tar.gz
