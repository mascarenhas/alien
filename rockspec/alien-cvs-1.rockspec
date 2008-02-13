package = "Alien"

version = "cvs-1"

description = {
  summary = "Lua->C FFI",
  detailed = [[
    Alien lets a Lua application call load dynamic libraries and call C functions
    in a portable way, using libffi.
  ]],
  license = "MIT/X11",
  homepage = "http://alien.luaforge.net"
}

dependencies = { }

external_dependencies = { 
  LIBFFI = { header = "ffi.h" }
}

source = {
   url = "http://alien.luaforge.net/alien-current.tar.gz"
}

build = {
   type = "make",
   install_variables = {
      LUA_LIBDIR = "$(LIBDIR)",
      BIN_DIR = "$(BINDIR)",
      PREFIX = "$(PREFIX)"
   },
   platforms = {
     linux = {
       	build_variables = {
         LIB_OPTION = "-shared",
         CFLAGS = "$(CFLAGS) -I$(LUA_INCDIR) -DUSE_DLOPEN",
	 LIBFFI_INCDIR = "-I$(LIBFFI_INCDIR)",
	 LIBFFI_LIBDIR = "-L$(LIBFFI_DIR)/.libs"
       	},
     },
     bsd = {
       	build_variables = {
         LIB_OPTION = "-shared",
         CFLAGS = "$(CFLAGS) -I$(LUA_INCDIR) -DUSE_DLOPEN",
	 LIBFFI_INCDIR = "-I$(LIBFFI_INCDIR)",
	 LIBFFI_LIBDIR = "-L$(LIBFFI_DIR)/.libs"
       	},
     },
     macosx = {
       	build_variables = {
         LIB_OPTION = "-bundle -undefined dynamic_lookup",
         CFLAGS = "$(CFLAGS) -I$(LUA_INCDIR) -DARCH_OSX",
	 LIBFFI_INCDIR = "-I$(LIBFFI_INCDIR)",
	 LIBFFI_LIBDIR = "-L$(LIBFFI_DIR)/.libs"
       	},
     },
     win32 = {
       	build_variables = {
         LIB_OPTION = "$(LUA_LIBDIR)\\lua5.1.lib $(LIBFFI_DIR)\\libffi.lib",
         CFLAGS = "$(CFLAGS) /I$(LUA_INCDIR) /I$(LIBFFI_INCDIR) /DUSE_LOADLIBRARY",
       	}
     }
  }
}
