
CFLAGS= -O2 -DARCH_OSX -I/usr/local/include/lua51 -I/opt/local/include
MY_LDFLAGS= -L/opt/local/lib -lavcall

alien.so: alien.o 
	export MACOSX_DEPLOYMENT_TARGET=10.3; ld -bundle -undefined dynamic_lookup -o alien.so alien.o $(MY_LDFLAGS)

all: alien.so

clean:
	rm alien.so alien.o
