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

dependencies = { }

external_dependencies = { 
  platforms = {
    linux = {
	FFCALL = { header = "avcall.h" }
    },
    bsd = {
	FFCALL = { header = "avcall.h" }
    },
    win32 = {
	FFCALL = { header = "avcall.h" }
    }
  }
}

source = {
   url = "http://alien.luaforge.net/alien-current.tar.gz"
}

build = {
   type = "make",
   install_variables = {
      LUA_LIBDIR = "$(LIBDIR)",
      BIN_DIR = "$(BINDIR)",
   },
   platforms = {
     linux = {
       	build_variables = {
         LIB_OPTION = "-shared",
         CFLAGS = "$(CFLAGS) -I$(LUA_INCDIR) -DUSE_DLOPEN",
	 FFCALL_INCDIR = "-I$(FFCALL_INCDIR)",
	 FFCALL_LIBDIR = "-L$(FFCALL_LIBDIR)"
       	},
     },
     bsd = {
       	build_variables = {
         LIB_OPTION = "-shared",
         CFLAGS = "$(CFLAGS) -I$(LUA_INCDIR) -DUSE_DLOPEN",
	 FFCALL_INCDIR = "-I$(FFCALL_INCDIR)",
	 FFCALL_LIBDIR = "-L$(FFCALL_LIBDIR)"
       	},
     },
     macosx = {
        build_target = "osx",
       	build_variables = {
         LIB_OPTION = "-bundle -undefined dynamic_lookup",
         CFLAGS = "$(CFLAGS) -I$(LUA_INCDIR) -DARCH_OSX",
	 FFCALL_INCDIR = "-Iffcall/avcall -Iffcall/callback",
         FFCALL_LIBDIR = "-Lffcall/alcall/.libs -Lffcall/callback/.libs"
       	},
     },
     win32 = {
       	build_variables = {
         LIB_OPTION = "$(LUA_LIBDIR)\\lua5.1.lib $(FFCALL_LIBDIR)\\libavcall.lib $(FFCALL_LIBDIR)\\libcallback.lib",
         CFLAGS = "$(CFLAGS) /I$(LUA_INCDIR) /I$(FFCALL_INCDIR) /DUSE_LOADLIBRARY",
       	}
     }
  }
}
