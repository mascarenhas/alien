
all: alien.so alien/struct.so

alien.o: alien.c
	cd ffcall && cat executables | xargs chmod +x && ./configure CC=gcc && make CC=gcc
	$(CC) -c $(CFLAGS) -Iffcall/callback -Iffcall/avcall -o alien.o alien.c

alien.so: alien.o 
	export MACOSX_DEPLOYMENT_TARGET=10.3; $(LD) $(LIB_OPTION) -o alien.so alien.o -Lffcall/avcall/.libs -Lffcall/callback/.libs -lavcall -lcallback

alien/struct.so: alien/struct.o 
	export MACOSX_DEPLOYMENT_TARGET=10.3; $(LD) $(LIB_OPTION) -o alien/struct.so alien/struct.o

install: alien.so alien/struct.so
	cp alien.so $(LUA_LIBDIR)
	mkdir -p $(LUA_LIBDIR)/alien
	cp alien/struct.so $(LUA_LIBDIR)/alien
	chmod +x constants
	cp constants $(BIN_DIR)/
	cd aio && make all LIBEVENT_INCDIR=$(LIBEVENT_INCDIR)

clean:
	rm *.so *.o alien/*.so alien/*.o
	cd ffcall && make clean
	cd aio && make clean

upload:
	darcs dist -d alien-current
	ncftpput -u mascarenhas ftp.luaforge.net alien/htdocs alien-current.tar.gz
