Alien - Pure Lua extensions
===========================

Status
------

This is Alien version 0.3.1.

What is Alien
-------------

*Alien* is a Foreign Function Interface (FFI) for Lua. An FFI lets you
call functions in dynamic libraries (.so, .dylib, .dll, etc.) from Lua
code without having to write, compile and link a C binding from the
library to Lua. In other words, it lets you write extensions that call
out to native code using just Lua.

Be careful when you use Alien, I tried to make it as safe as possible,
but it is still very easy to crash Lua if you make a mistake. Alien
itself is not as robust as a standard Lua extension, but you can use
it to write extensions that won't crash if you code them well.

Alien should work in any Unix-based system, and it will work on
Windows shortly.

Installing Alien
----------------

The best way to install Alien is through
[LuaRocks](http://luarocks.org). Just add [this
repository](http://www.lua.inf.puc-rio.br/~mascarenhas/rocks) to your
LuaRocks configuration, then do `luarocks install alien`. You may need
root permissions to do this, depending on your LuaRocks configuration.

Go to the Alien rock directory to see local copies of this
documentation, as well as the test suite. If you are in the path of
the test suite (`tests`) you can run the suite with:

    lua -l luarocks.require test_alien.lua

If everything is ok you should see no output.

Alien installs to modules, `alien` and `alien.struct`. The latter is a
slightly modified version of Roberto Ierusalimschy's [struct
library](http://www.inf.puc-rio.br/~roberto/struct) that can unpack
binary blobs (userdata) instead of just strings.

Basic Usage
-----------

Loading a dynamic library is very simple; Alien by default assumes a
naming scheme of lib*name*.dylib for OSX and lib*name*.so for other
Unix systems. If *name* is not one of the
functions the `alien` module exports then you can get a reference to
the library with `alien.`*`name`*. Otherwise (for example, to load a
library called *libwrap.so*) you have to use `alien.load("wrap")`.

You can also specify the full name of the library by calling
`alien.load` with a path, such as
`alien.load("mylibs/libfoo.so")`. Either way you get back a reference
to the library that you will use to access its functions.

You can also get a reference to the currently running module using
`alien.default`, this lets you get references to any function exported
by the module and its transitive dependencies.

Once you have a reference to a library you can get a reference to an
exported function with *libref.funcname*. For example:

    > def=alien.default
    > =def.puts
    alien function puts, library defaults
    >

To use a function you first have to tell Alien the function prototype,
using *func:types(ret_type, arg_types...)*, where the types are one of
the following strings: "void", "int", "double", "char", "string",
"pointer", "ref int", "ref double", "ref char", "callback", "short",
"byte", "long", and "float". Most correspond directly to C types;
*byte* is a signed char, *string* is *const char\**, *pointer* is *void\**,
*callback* is a generic function pointer, and *ref char*, *ref int*
and *ref double* are by reference versions of the C types. Continuing
the previous example:

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

Buffers
-------

The basic usage is enough to do a lot of interfacing with C code,
specially with well-behaved libraries that handle their own memory
allocation (the Lua C API is a good example of such an API). But there
are libraries that do not export such a well-behaved API, and require
you to allocate memory that is mutated by the library. This prevents
you from passing Lua strings to them, as Lua strings have to be
immutable, so Alien provides a *buffer* interface. The function
`alien.buffer` allocates a new buffer. If you call it with no
arguments it will allocate a buffer with the standard buffer size for
your platform. If call it with a number it will allocate a buffer with
this number of bytes. If you pass it a string it will allocate a
buffer that is a copy of the string.

After making a buffer you can pass it in place of any argument of
*string* or *pointer* type. To get back the contents of the buffer you
use `buf:tostring`, and again you can either pass the number of
characters to read from the buffer or don't pass anything, which treat
the buffer as a C string (read until finding a *\0*). You can also
call `buf:len`, which calls *strlen* on the buffer. Finally,
`tostring(buf)` is the same as `buf:tostring()`.

An example of how to use a buffer:

    > gets = alien.default.gets
    > gets:types("pointer", "string")
    > buf = alien.buffer()
    > gets(buf)
    Foo bar
    > =tostring(buf)
    Foo bar
    >

Pointer Unpacking
-----------------

Alien also provides three convenience functions that let you
dereference a pointer and convert the value to a Lua type:

* `alien.tostring` takes a userdata (usually returned from a function
  that has a *pointer* return value), casts it to *char\**, and
  returns a Lua string. You can supply an optional size argument (if 
  you don't Alien calls *strlen* on the buffer first).

* `alien.tointeger` takes a userdata, casts it to *int\**,
  dereferences it and returns it as a number. If you pass it a number
  it assumes the userdata is an array with this number of elements.

* `alien.toshort`, `alien.tolong`, `alien.tofloat`, and
  `alien.todouble` are like `alien.tointeger`, but works with
  with the respective typecasts.

Use these functions with extra care, they don't make any safety
checks. For more advanced unmarshaling use the `alien.struct.unpack`
function.

Tags
----

A common pattern when wrapping objects from C libraries is to put a
pointer to this object inside a full userdata, then associate this userdata
with a metatable that is associated with a string tag. This tag is
used to check if the userdata is a valid userdata in each function
that uses it. As the userdata is a full userdata it also can have a
`__gc` metamethod for resource reclamation.

Alien has three functions that let you replicate this pattern on your
extensions:

* `alien.tag(*tagname*)` creates a new metatable with tag *tagname* if one
  does not exist, or returns the metatable with this tag. The
  namespace for tags is global, so a good pattern is to prefix the tag
  name with the name of your module (such as *mymod_mytag*).
* `alien.wrap(*tagname*, ...)` creates a full userdata, tags it with
  the metatable associated with *tagname*, stores the values
  you passed, then returns the full userdata. Valid values are *nil*, 
  integers and other userdata.
* `alien.unwrap(*tagname*, obj)` tests if *obj* is tagged with
  *tagname*, throwing an error if it is not, then returns the values
  previously stored in it.

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
    qsort(chars, chars:len(), alien.sizeof("char"), cmp_cb)
    assert(chars:tostring() == "   ,,aaaadmmmnpppsss")

The *qsort* function sorts an array in-place, so we have to use a
buffer.

Magic Numbers
-------------

C libraries are full of symbolic constants that are in truth magic
numbers, as they are replaced by the preprocessor before even the C
compiler has a chance to see them. This means that all these constants
are on header files. This also includes things such as the layout and
size of strucutres the library depends on. All this information can
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

Which, when compile and run, generates this file on a Linux/Intel
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
`alien.platform`. Right now this can be either "unix" or "osx". Other
platforms will be added as they are tested. You can use this
information for conditional execution in your extensions.

You can get the sizes of the types Alien supports using
`alien.sizeof(*typename*)`, as the *qsort* example in the Callbacks
section shows.

Credits
-------

Alien is designed and implemented by Fabio Mascarenhas. It uses the
great [libffi](http://sources.redhat.com/libffi)
library by Anthony Green (and others) to do the heavy lifting of calling to and from C. The
name is stolen from Common Lisp FFIs.

License
-------

Alien's uses the MIT license, reproduced below:

Copyright (c) 2008 Fabio Mascarenhas

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
