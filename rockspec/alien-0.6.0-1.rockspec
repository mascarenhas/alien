package="alien"
version="0.6.0-1"
source = {
   url = "http://cloud.github.com/downloads/alien/alien-0.6.0.zip"
}
description = {
  summary = "Lua->C FFI",
  detailed = [[
    Alien lets a Lua application call load dynamic libraries and call C functions
    in a portable way, using libffi.
  ]],
  license = "MIT/X11",
  homepage = "http://mascarenhas.github.com/alien"
}
dependencies = {
  "lua >= 5.1"
}
build = {
  type = "command",
  build_command = "LUA=$(LUA) CPPFLAGS=-I$(LUA_INCDIR) ./configure --prefix=$(PREFIX) --libdir=$(LIBDIR) --datadir=$(LUADIR)",
  install_command = "make install"
}
