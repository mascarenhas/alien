Alien - Pure Lua extensions
===========================

What is Alien?
--------------

*Alien* is a Foreign Function Interface (FFI) for Lua. An FFI lets you
call functions in dynamic libraries (.so, .dylib, .dll, etc.) from Lua
code without having to write, compile and link a C binding from the
library to Lua. In other words, it lets you write extensions that call
out to native code using just Lua.

Be careful when you use Alien: care has been taken to make it safe,
but it is still very easy to crash Lua if you make a mistake. Alien
itself is not as robust as a standard Lua extension, but you can use
it to write extensions that won't crash if you code them well.

Alien works on Unix-based systems and Windows. It has been tested on
Linux x86, Linux x86_64, Linux ARM, FreeBSD x86, Windows x86, OS X
x86, and OS X PPC. The Windows binary uses MSVCR80.DLL for
compatibility with LuaBinaries.

Installing Alien
----------------

The easiest way to install Alien is through
[LuaRocks](http://luarocks.org). Just do `luarocks install alien`.

Alien is based on libffi. On a GNU/Linux system you should be able
to install it with your package manager; it is probably called
something like `libffi-dev` (Debian, Ubuntu etc.) or `libffi-devel`
(Fedora, CentOS etc.). If your system's package manager does not
have libffi, or you don't have a package manager, you can get the
source code from [the libffi project](http://sources.redhat.com/libffi/).

Go to the Alien rock directory to see local copies of this
documentation, as well as the test suite. If you are in the path of
the test suite (`tests`) you can run the suite with:

    lua -l luarocks.require test_alien.lua

Alien uses the GNU build system. For detailed instructions on
installations that do not use LuaRocks, see INSTALL in the 
distribution. 

For a quick start, if you checked out sources from [Github](http://github.com/mascarenhas/alien) (skip this
step if you downloaded the .zip in the Downloads section):

  ./bootstrap

Then run:

  ./configure && make [&& make install]

You may need to supply non-default paths (e.g. if you are using a
system that supports more than one version of Lua). For example, on Debian or Ubuntu:

  CPPFLAGS='-I/usr/include/lua5.1' ./configure --libdir=/usr/local/lib/lua/5.1 --datadir=/usr/local/share/lua$

To run some tests:

  make check

Alien installs one module, `alien`.

Basic Usage
-----------

The version of the alien library is available in `alien.version`.

Load a library with `alien.load("foo")`. By default, Alien assumes a
naming scheme of lib*name*.dylib for OSX and lib*name*.so for other
Unix systems. You can also specify the full name of the library by calling
`alien.load` with a path or with the appropriate extension, such as
`alien.load("mylibs/libfoo.so")` or `alien.load("libfoo.so")`. 
Either way you get back a reference
to the library that you will use to access its functions.

You can also get a reference to the currently running module using
`alien.default`, this lets you get references to any function exported
by the module and its transitive dependencies on ELF and Mach-O systems.

Once you have a reference to a library you can get a reference to an
exported function with *libref.funcname*. For example:

    > def=alien.default
    > =def.puts
    alien function puts, library defaults
    >

To use a function you first have to tell Alien the function prototype,
using *func:types(ret_type, arg_types...)*, where the types are one of
the following strings: "void", "byte", "char", "short", "ushort",
"int", "uint", "long", "ulong", "ptrdiff\_t", "size\_t", "float",
"double", "string", "pointer", "ref char", "ref int", "ref uint", "ref
double", "longlong", "ulonglong" and "callback". Most correspond
directly to C types; *byte* is a signed char, *string* is *const
char\**, *pointer* is *void\**, *callback* is a generic function
pointer, and *ref char*, *ref int* and *ref double* are by reference
versions of the C types. Continuing the previous example:

    > def.puts:types("int", "string")
    > def.puts("foo")
    foo
    >

As you can see, after defining the prototype you can call the function
just as a Lua function. Alien converts Lua numbers to the C numeric
types, converts *nil* to *NULL* and Lua strings to *const char\** for
*string*, and converts *nil* to *NULL* and userdata to *void\** for
*pointer*. The conversions work in reverse for the return value (with
the *pointer* type converted to a light userdata).

By reference types are special; Alien allocates space on the stack for
the argument, copies the Lua number you passed to it (converting
appropriately), then calling the function with the address of this
space. Then the value is converted back to a Lua number and returned
after the function normal return value. An example, using *scanf*:

    > scanf = alien.default.scanf
    > scanf:types("int", "string", "ref int", "ref double")
    > _, x, y = scanf("%i %lf", 0, 0)
    23 42.5
    > =x
    23
    > =y
    42.5

You have to pass a value even if the function does not use it, as you
can see above.

In most Lua implementations, "longlong" and "ulonglong" won't fit in a
Lua number, so automatic conversion will sometimes fail; on 64-bit
machines the same is true of "ptrdiff\_t" and "size\_t". However, as
long as you perform no computation on such a value, its value will be
preserved, so you can receive it from C and pass it back to C without
worrying.

Another way to specify types is by passing a table to *func:types*. The array
part of this table should have one item for each parameter, and you can also pass
two hash keys, *ret*, the function's return type (defaults to `int` as usual), and
*abi*, the function's calling convention (useful for Windows, where you can specify "stdcall" as the
ABI for `__stdcall` functions. The default ABI is always "default", and all systems
also support "cdecl", the usual C calling convention. On systems that don't have the
stdcall convention "stdcall" is the same as "default".

This is the previous example using this alternate definition:

    > scanf = alien.default.scanf
    > scanf:types{ ret = "int", "string", "ref int", "ref double" }
    > _, x, y = scanf("%i %lf", 0, 0)
    23 42.5
    > =x
    23
    > =y
    42.5

If you get raw function pointer (returned from a function, for example, or 
passed to a callback), you can turn it into an Alien function with `alien.funcptr(fptr)`.
This returns an Alien function object that you can type and call function normally.

Buffers
-------

To work with C APIs that require you to allocate memory that is
mutated by the library, Alien provides a `buffer` abstraction.
The function `alien.buffer` allocates a new buffer. If you call it with no
arguments it will allocate a buffer of size `BUFSIZ` (the default C
buffer size on your platform). If call it with a number it will allocate a
buffer with this number of bytes. If you pass it a string it will allocate a
buffer that is a copy of the string. If you pass a light userdata
it will use this userdata as the buffer (be careful with that).

After making a buffer you can pass it in place of any argument of
*string* or *pointer* type.

`#buf` gives its size in bytes, while `buf:strlen()` returns the
result of calling `strlen` on the buffer.

You can access the i-th character of a buffer with `buf[i]`, and you can
set its value with `buf[i] = v`. Notice that these are C characters (bytes),
not Lua 1-character strings, so you need to use `string.char` and `string.byte`
to convert between Lua characters and C characters. **Access to Alien buffers
from Lua is 1-based, not 0-based**.

You can also get and set other values by using `buf:get(offset, type)`, and
set it by `buf:set(offset, val, type)`. The offset is in bytes, *not* in elements, so
if *buf* has three `int` values: their offsets are 1, 5 and 9, respectively, assuming
each `int` is four bytes long.

The get and set operations do no bounds-checking, so where possible use the
safer `alien.array` abstraction that is built on top of buffers (see below).

To retrieve part of the buffer as a string, use `buf:tostring(len, offset)`.
Both arguments are optional: the first gives the number of characters to return;
if omitted, the buffer is treated as a C string, and the contents up to the first NUL is returned.
The second argument gives the offset to start at within the buffer, and defaults to the start of the buffer (1).
`tostring(buf)` is the same as `buf:tostring()`.

To get a pointer to a buffer, use `buf:topointer(offset)`; the argument is optional, defaulting to 1.

To turn a pointer into a buffer offset, use `buf:tooffset(pointer)`.

You can reallocate a buffer using `buf:realloc(newsize)`. This uses the current Lua state's allocation
function.

An example of how to use a buffer:

    > gets = alien.default.gets
    > gets:types("pointer", "string")
    > buf = alien.buffer()
    > gets(buf)
    Foo bar
    > =tostring(buf)
    Foo bar
    >

Alien also provides `alien.memmove` and `alien.memset`, which work exactly like the C functions
of the same name, and can be used on buffers or other memory. `alien.memmove` can take a string as
its second (source) argument.

Arrays
------

Arrays are buffers with an extra layer of safety and sugar on top. You create an array
with `alien.array(type, length)`, where `type` is the Alien type of the array's elements,
and length is how many elements the array has. After creating an array `arr` you can get the
type of its elements with `arr.type`, how many elements it has with `arr.length`, and the
size (in bytes) of each element with `arr.size`. The underlying buffer is `arr.buffer`.

You can access the i-th element with `arr[i]`, and set it with `arr[i] = val`. Type 
conversions are the same as with buffers, or function calls. Storing a string or userdata
in an array pins it so it won't be collected while it is in the array. You can resize an
array too: `arr:realloc(newlen)` changes the length to `newlen`.

For convenience `alien.array` also accepts two other forms: `alien.array(type, tab)` creates
an array with the same length as *tab* and initializes it with its values; 
`alien.array(type, length, buf)` creates an array with *buf* as the underlying buffer. You can
also iterate over the array's contents with `arr:ipairs()`.

The following example shows an use of arrays:

    local function sort(a, b)
      return a - b
    end
    local compare = alien.callback(sort, "int", "ref int", "ref int")
    
    local qsort = alien.default.qsort
    qsort:types("void", "pointer", "int", "int", "callback")
    
    local nums = alien.array(t, { 4, 5, 3, 2, 6, 1 })
    qsort(nums.buffer, nums.length, nums.size, compare)
    for i, v in nums:ipairs() do print(v) end

This prints numbers one to six on the console.

Structs
-------

Alien also has basic support for declarative structs that is also implemented as a layer of sugar
on the basic buffers. It uses a slightly modified version of Roberto Ierusalimschy's
[struct library](http://www.inf.puc-rio.br/~roberto/struct) that can unpack
binary blobs (userdata) instead of just strings.
The `alien.defstruct(description)` function creates a struct type with the
given description, which is a list of pairs with the name and type of each field, where the type is any
basic alien type (no structs inside structs yet). For example:

    rect = alien.defstruct{
      { "left", "long" },
      { "top", "long" },
      { "right", "long" },
      { "bottom", "long" }
    }

This creates a new struct type with four fields of type "long", and stores it in `rect`. To create an
instance of this structure (backed by a buffer) call `rect:new()`. You can then set the fields of the
struct just like you do on a Lua table, like `r.left = 3`. To get the underlying buffer (to pass it
to a C function, for example) you have to call the instance, `r()`. Continuing the example:

    r = rect:new()
    r.left = 2
    doubleleft = alien.rectdll.double_left
    doubleleft:types("void", "pointer")
    doubleleft(r()))
    assert(r.left == 4)

You can also pass a buffer or other userdata to the `new` method of your struct type, and in this case this will
be the backing store of the struct instance you are creating. This is useful for unpacking a foreign struct that
a C function returned.

Pointer Unpacking
-----------------

Alien also provides three convenience functions that let you
dereference a pointer and convert the value to a Lua type:

* `alien.tostring` takes a userdata (usually returned from a function
  that has a *pointer* return value), casts it to *char\**, and
  returns a Lua string. You can supply an optional size argument (if 
  you don't Alien calls *strlen* on the buffer first).
* `alien.toint` takes a userdata, casts it to *int\**,
  dereferences it and returns it as a number. If you pass it a number
  it assumes the userdata is an array with this number of elements.
* `alien.toshort`, `alien.tolong`, `alien.tofloat`, and
  `alien.todouble` are like `alien.toint`, but works with
  with the respective typecasts. Unsigned versions are also available.

The numeric `alien.to*type*` functions take an optional second argument that
tells how many items to unpack from the userdata. For example, if ptr is
a pointer to an array of four floats, the following code unpacks this array:

    > fs = alien.tofloat(ptr, 4)
    > =#fs
    4
    >

Use these functions with extra care, as they don't make any safety
checks. For more advanced unmarshalling use the `alien.unpack`
function.

Tags
----

A common pattern when wrapping objects from C libraries is to put a
pointer to this object inside a full userdata, then associate this userdata
with a metatable that is associated with a string tag. This tag is
used to check if the userdata is a valid userdata in each function
that uses it. As the userdata is a full userdata it also can have a
`__gc` metamethod for resource reclamation.

Alien has three functions that let you replicate this pattern in your
extensions:

* `alien.tag("tag")` creates a new metatable with tag *tag* if one
  does not exist, or returns the metatable with this tag. The
  namespace for tags is global, so a good pattern is to prefix the tag
  name with the name of your module (such as *mymod_mytag*).
* `alien.wrap("tag", ...)` creates a full userdata, tags it with
  the metatable associated with *tag*, stores the values
  you passed, then returns the full userdata. Valid values are *nil*, 
  integers and other userdata.
* `alien.unwrap("tag", obj)` tests if *obj* is tagged with
  *tag*, throwing an error if it is not, then returns the values
  previously stored in it.
* `alien.rewrap("tag", obj, ...)` replaces the elements on *obj* with
  new values. If you pass more values than *obj* had previously the extra
  values are silently ignored. If you pass less then *obj* is filled with
  *nil*.

For example, suppose *libfoo* has a `create_foo` function that returns
a `Foo*` object. These objects have to be properly disposed by calling
`destroy_foo` when they are not used anymore. This is easy to
implement:

    local tag_foo = alien.tag("libfoo_foo")
    alien.foo.create_foo:types("pointer")
    alien.foo.destroy_foo_types("void", "pointer")

    function new_foo()
      local foo = alien.foo.create_foo()
      return alien.wrap("libfoo_foo", foo)
    end
    
    tag_foo = {
      __gc = function (obj)
               local foo = alien.unwrap("libfoo_foo", obj)
               alien.foo.destroy_foo(foo)
             end
    }

Then on any function that operates on `Foo*` types you first unwrap to
get the pointer, then pass it to the function in *libfoo*.

Error Codes
-----------

Several operating system functions return errors on a special variable
called *errno*. To get the value of *errno* with Alien call
`alien.errno()`.

Callbacks
---------

Some libraries have functions that take *callbacks*, functions that
get called by the library. Most GUI libraries use callbacks, but even
the C library has *qsort*. Alien lets you create a callback from a Lua
function with `alien.callback`. You pass the function and the callback
prototype that the library expects. Alien will return a callback
object that you can pass in any argument of *callback* type. A simple
example, using *qsort*:

    local function cmp(a, b)
      return a - b
    end
    local cmp_cb = alien.callback(sort, "int", "ref char", "ref char")
    
    local qsort = alien.default.qsort
    qsort:types("void", "pointer", "int", "int", "callback")
    
    local chars = alien.buffer("spam, spam, and spam")
    qsort(chars, chars:strlen(), alien.sizeof("char"), cmp_cb)
    assert(chars:tostring() == "   ,,aaaadmmmnpppsss")

The *qsort* function sorts an array in-place, so we have to use a
buffer.

Callbacks are callable from Lua just like any other Alien function, and you can freely
change their types with their "types" method.

Magic Numbers
-------------

C libraries are full of symbolic constants that are in truth magic
numbers, as they are replaced by the preprocessor before even the C
compiler has a chance to see them. This means that all these constants
are on header files. This also includes things such as the layout and
size of structures the library depends on. All this information can
change from version to version of the library, or from platform to
platform.

Alien provides a utility script called *constants* that makes it
easier to work with these numbers. This utility takes three arguments
on the command line: a *definitions file*, the name of the C file you
want it to generate, and the name of a Lua file that the C file will
generate when compiled and run. The definitions file can contain
preprocessor directives, blank lines, and lines with definitions
either of the form *identifier* or *lua_identifier* = *c_identifier*. The first
form is equivalent to *identifier* = *identifier*. It is best to
explain by example (from a libevent binding):

    #include <sys/types.h>
    #include <event.h>
    
    EV_SIZE = sizeof(struct event)
    EV_READ
    EV_WRITE
    EV_TIMEOUT
    EVLOOP_NONBLOCK
    EVLOOP_ONCE

Lines with preprocessor directives are copied verbatim to the C file
*constants generates*. The above definitions file generates this C
file:

    /* Generated by Alien constants */
    
    #include <stdio.h>
    
    #include <sys/types.h>
    #include <event.h>
    #define LUA_FILE "event_constants.lua"
    int main() {
      FILE *f = fopen(LUA_FILE, "w+");
      fprintf(f, "-- Generated by Alien constants\n\n");
      fprintf(f, "%s = %i\n", "EV_SIZE ",  sizeof(struct event));
      fprintf(f, "%s = %i\n", "EV_READ", EV_READ);
      fprintf(f, "%s = %i\n", "EV_WRITE", EV_WRITE);
      fprintf(f, "%s = %i\n", "EV_TIMEOUT", EV_TIMEOUT);
      fprintf(f, "%s = %i\n", "EVLOOP_NONBLOCK", EVLOOP_NONBLOCK);
      fprintf(f, "%s = %i\n", "EVLOOP_ONCE", EVLOOP_ONCE);
      fclose(f);
    }

When compiled and run, this generates this file on a Linux/Intel
system:

    -- Generated by Alien constants
    
    EV_SIZE  = 84
    EV_READ = 2
    EV_WRITE = 4
    EV_TIMEOUT = 1
    EVLOOP_NONBLOCK = 2
    EVLOOP_ONCE = 1

These steps (generating the C file, compiling, generating the Lua
file) are best done in the build step of your extension.

Miscellanea
-----------

You can query what platform your extension is running on with
`alien.platform`. Currently this can be one of "linux", "bsd", "darwin" or "windows". Other
platforms will be added as they are tested. You can use this
information for conditional execution in your extensions.

You can get the sizes of the types Alien supports using
`alien.sizeof("type")`, as the *qsort* example in the Callbacks
section shows. You can also get structure aligment information
with `alien.align("type")`.

Several extensions may need to create Lua tables with preallocated
array and/or hash parts, for performance reasons (implementing a circular queue, for
example). Alien exposes the `lua_createtable` function as `alien.table(narray, nhash)`.

Credits
-------

Alien is designed and implemented by Fabio Mascarenhas. It uses the
great [libffi](http://sources.redhat.com/libffi)
library by Anthony Green (and others) to do the heavy lifting of calling to and from C. The
name is stolen from Common Lisp FFIs.

Changelog
---------

* 0.7.0: feature release
  * replace buffer's size field with a __len metamethod
  * rename buffer:len to buffer:strlen to avoid confusion

* 0.6.1: feature release
  * add support for size\_t and ptrdiff\_t types.
  * add buffer:tooffset method to turn pointers into buffer offsets

* 0.6.0: feature release
  * add alien.memmove; make alien.memset work (previously it called memcpy by mistake)
  * make buffers resizable
  * add long long support
  * improve test output
  * use Lua state's output instead of malloc, and use libffi for closure allocation instead of custom code
  * replace the Unix Makefile with an autotools build system
  * no longer ship libffi sources
  * add alien.version
  * minor updates to documentation

* 0.5.1: bugfix release
  * support for Lua 5.2
  * per-library function cache, instead of global (can load
    two functions with the same name from different libraries)
  * unloading of libraries if they are not being used
  * updated alien.struct to current struct.c from Roberto
  * updated libffi version to 3.0.9
  * updated Windows libffi to reflect ctypes 1.0.2, add Win64 support

* 0.5.0
  * new functions alien.memcpy and alien.memset
  * new type "p" for alien.struct.pack and unpack, to pack pointers
  * new alien.struct.offset function to get the offset of a given record
  * buf:tostring now has optional "offset" argument
  * buf:topointer now has optional "offset" argument
  * added unsigned numbers: uint, ulong, ushort, and "ref uint"
  * basic support for declarative strucutures
  * unified treatment of funcitons and callbacks in the source
  * fixed segfault when collecting 0-arg functions

* 0.4.1
  * fixes bug where Alien was always using cdecl abi for Windows (except in callbacks)
  * fixes build on PPC OSX.

* 0.4.0
  * Windows support - stdcall ABI, including stdcall callbacks
  * alternative syntax for defining types
  * mutable buffers, wrapping lightuserdata in a buffer
  * alien.to*type* functions take optional length argument
  * callbacks are callable from Lua
  * alien.funcptr turns a function pointer into an alien function
  * improved library finding on Linux/FreeBSD, using ldconfig
  * alien.table utility function (wrapper for lua_createtable, useful for extensions)
  * alien.align utility function to get data structure alignment
  * arrays built on mutable buffers, with bounds checking
  * fixed a build bug on Linux ARM

* 0.3.2 - fixes callback bug on NX-bit platforms
* 0.3.1 - initial release with libffi
* 0.3 - retracted due to license conflict

License
-------

Alien's uses the MIT license, reproduced below:

Copyright (c) 2008-2012 Fabio Mascarenhas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
