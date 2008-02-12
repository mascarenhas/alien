package = "Alien"

version = "cvs-1"

description = {
  summary = "Lua->C FFI",
  detailed = [[
    Alien lets a Lua application call load dynamic libraries and call C functions
    in a portable way, using ffcall.
  ]],
  license = "MIT/X11",
  homepage = "http://alien.luaforge.net"
}

dependencies = { "bitlib" }

source = {
   url = "http://alien.luaforge.net/alien-current.tar.gz"
}

build = {
   type = "make",
   install_variables = {
      LUA_LIBDIR = "$(LIBDIR)"
   },
   platforms = {
     linux = {
       	build_variables = {
         LIB_OPTION = "-shared",
         CFLAGS = "$(CFLAGS) -I$(LUA_INCDIR) -DUSE_DLOPEN",
       	},
     },
     bsd = {
       	build_variables = {
         LIB_OPTION = "-shared",
         CFLAGS = "$(CFLAGS) -I$(LUA_INCDIR) -DUSE_DLOPEN",
       	},
     },
     macosx = {
       	build_variables = {
         LIB_OPTION = "-bundle -undefined dynamic_lookup",
         CFLAGS = "$(CFLAGS) -I$(LUA_INCDIR) -DARCH_OSX",
       	},
     },
     win32 = {
       	build_variables = {
         LIB_OPTION = "$(LUA_LIBDIR)\\lua5.1.lib",
         CFLAGS = "$(CFLAGS) /I$(LUA_INCDIR) /DUSE_LOADLIBRARY",
       	}
     }
  }
}
