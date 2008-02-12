package = "AIO"

version = "cvs-1"

description = {
  summary = "Lua Threads with Asynchronous IO",
  detailed = [[
  ]],
  license = "MIT/X11",
  homepage = "http://alien.luaforge.net/aio"
}

dependencies = { "bitlib", "alien cvs" }

external_dependencies = {
  LIBEVENT = { header = "event.h" },
}

source = {
   url = "http://alien.luaforge.net/aio-current.tar.gz"
}

build = {
   type = "make",
   install_variables = {
      LUA_DIR = "$(LUADIR)",
   },
   build_variables = {
      CFLAGS = "$(CFLAGS)",
      LIBEVENT_INCDIR = "$(LIBEVENT_INCDIR)"
   }
}
