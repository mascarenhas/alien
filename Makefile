
all: src/alien.so src/alien/struct.so tests/libalientest.so

osx:
	cd ffcall && cat executables | xargs chmod +x && ./configure CC=gcc && make CC=gcc
	make all	

src/alien.o: src/alien.c
	$(CC) -c $(CFLAGS) $(FFCALL_INCDIR) -o src/alien.o src/alien.c

src/alien.so: src/alien.o 
	export MACOSX_DEPLOYMENT_TARGET=10.3; $(LD) $(LIB_OPTION) -o src/alien.so src/alien.o $(FFCALL_LIBDIR)  -lavcall -lcallback

src/alien/struct.so: src/alien/struct.o 
	export MACOSX_DEPLOYMENT_TARGET=10.3; $(LD) $(LIB_OPTION) -o src/alien/struct.so src/alien/struct.o

install: src/alien.so src/alien/struct.so
	cp src/alien.so $(LUA_LIBDIR)
	mkdir -p $(LUA_LIBDIR)/alien
	cp src/alien/struct.so $(LUA_LIBDIR)/alien
	chmod +x src/constants
	cp src/constants $(BIN_DIR)/
	cp -r tests $(PREFIX)/
	cp -r samples $(PREFIX)/
	cp -r doc $(PREFIX)/

clean:
	find . -name "*.so" -o -name "*.o" | xargs rm -f

upload:
	darcs dist -d alien-current
	ncftpput -u mascarenhas ftp.luaforge.net alien/htdocs alien-current.tar.gz

tests/libalientest.so: tests/alientest.c
	$(CC) $(LIB_OPTION) $(CFLAGS) -o tests/libalientest.so tests/alientest.c

test:
	cd tests && lua -l luarocks.require test_alien.lua
