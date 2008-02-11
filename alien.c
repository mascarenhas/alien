// Lua FFI using avcall

#include <stdlib.h>
#include <string.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "avcall.h"

#define ALIEN_LIBRARY_META "alien_library"
#define ALIEN_FUNCTION_META "alien_function"

typedef enum {
  INT,
  VOID,
  DOUBLE,
  CHAR,
  STRING,
  PTR
} alien_Type;

typedef struct _alien_Library {
  void *lib;
  char *name;
} alien_Library;

typedef struct _alien_Function {
  alien_Library *lib;
  void *fn;
  char *name;
  alien_Type ret_type;
  int nparams;
  alien_Type *params;
} alien_Function;

#if defined(ARCH_OSX)

#define LIB_EXT ".dylib"
#define PLATFORM "osx"
#define USE_DLOPEN

#endif

#if defined(USE_DLOPEN)

#ifndef LIB_EXT
#define LIB_EXT ".so"
#endif
#ifndef PLATFORM
#define PLATFORM "unix"
#endif

#include <dlfcn.h>

static void alien_unload (void *lib) {
  dlclose(lib);
}

static void *alien_load (lua_State *L, const char *libname) {
  char *path;
  const char *path_prefix, *path_suffix;
  void *lib;
  if(libname[0] == '/') {
    path_prefix = "";
    path_suffix = "";
  } else {
    path_prefix = "lib";
    path_suffix = LIB_EXT;
  }
  path = (char*)malloc(strlen(libname) + strlen(path_prefix) + strlen(path_suffix) + 1);
  if(path) {
    strcpy(path, path_prefix);
    strcat(path, libname);
    strcat(path, path_suffix);
    lib = dlopen(path, RTLD_NOW);
    free(path);
    if (lib == NULL) lua_pushstring(L, dlerror());
    return lib;
  } else {
    luaL_error(L, "out of memory!");
  }
}

static void *alien_loadfunc (lua_State *L, void *lib, const char *sym) {
  if(!lib) lib = RTLD_DEFAULT;
  void *f = dlsym(lib, sym);
  if (f == NULL) lua_pushstring(L, dlerror());
  return f;
}

#elif defined(USE_LOADLIBRARY)

#define PLATFORM "windows"

#include <windows.h>

static void pusherror (lua_State *L) {
  int error = GetLastError();
  char buffer[128];
  if (FormatMessage(FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
      NULL, error, 0, buffer, sizeof(buffer), NULL))
    lua_pushstring(L, buffer);
  else
    lua_pushfstring(L, "system error %d\n", error);
}

static void alien_unload (void *lib) {
  FreeLibrary((HINSTANCE)lib);
}

static void *alien_load (lua_State *L, const char *libname) {
  HINSTANCE lib = LoadLibrary(libname);
  if (lib == NULL) pusherror(L);
  return lib;
}

static void *alien_loadfunc (lua_State *L, void *lib, const char *sym) {
  HINSTANCE module;
  void *f;
  module = (HINSTANCE)lib;
  if(!module) module = GetModuleHandle();
  f = (lua_CFunction)GetProcAddress(module, sym);
  if (f == NULL) pusherror(L);
  return f;
}

#else

#define DLMSG   "dynamic libraries not enabled; check your Lua installation"

#define PLATFORM "unknown"

static void alien_unload (void *lib) {
  (void)lib;  /* to avoid warnings */
}

static void *alien_load (lua_State *L, const char *path) {
  (void)path;  /* to avoid warnings */
  lua_pushliteral(L, DLMSG);
  return NULL;
}

static void *alien_loadfunc (lua_State *L, void *lib, const char *sym) {
  (void)lib; (void)sym;  /* to avoid warnings */
  lua_pushliteral(L, DLMSG);
  return NULL;
}

#endif


static alien_Library *alien_checklibrary(lua_State *L, int index) {
  void *ud = luaL_checkudata(L, index, ALIEN_LIBRARY_META);
  luaL_argcheck(L, ud != NULL, index, "alien library expected");
  return (alien_Library *)ud;
}

static alien_Function *alien_checkfunction(lua_State *L, int index) {
  void *ud = luaL_checkudata(L, index, ALIEN_FUNCTION_META);
  luaL_argcheck(L, ud != NULL, index, "alien function expected");
  return (alien_Function *)ud;
}

static int alien_get(lua_State *L) {
  char *name;
  const char *libname;
  size_t len;
  libname = luaL_checklstring(L, lua_gettop(L), &len);
  lua_getfield(L, lua_upvalueindex(1), libname);
  if(!lua_isnil(L, -1)) return 1;
  name = (char*)malloc(len);
  if(name) {
    void *lib;
    alien_Library *al;
    memcpy(name, libname, len);
    al = (alien_Library *)lua_newuserdata(L, sizeof(alien_Library));
    lib = alien_load(L, libname);
    if(lib && al) {
      luaL_getmetatable(L, ALIEN_LIBRARY_META);
      lua_setmetatable(L, -2);
      al->lib = lib;
      al->name = name;
      lua_pushvalue(L, -1);
      lua_setfield(L, lua_upvalueindex(1), libname);
      return 1;
    } else {
      free(name);
      lua_error(L);
    }
  } else {
    luaL_error(L, "out of memory!");
  }
}

static int alien_library_get(lua_State *L) {
  const char *funcname;
  char *name;
  size_t len;
  funcname = luaL_checklstring(L, 2, &len);
  lua_getfield(L, lua_upvalueindex(1), funcname);
  if(!lua_isnil(L, -1)) return 1;
  name = (char*)malloc(len);
  if(name) {
    alien_Library *al;
    alien_Function *af;
    void *fn;
    memcpy(name, funcname, len);
    al = alien_checklibrary(L, 1);
    af = (alien_Function *)lua_newuserdata(L, sizeof(alien_Function));
    fn = alien_loadfunc(L, al->lib, funcname);
    if(fn && af) {
      luaL_getmetatable(L, ALIEN_FUNCTION_META);
      lua_setmetatable(L, -2);
      af->fn = fn;
      af->name = name;
      af->lib = al;
      af->nparams = 0;
      af->ret_type = VOID;
      af->params = NULL;
      lua_pushvalue(L, -1);
      lua_setfield(L, lua_upvalueindex(1), funcname);
      return 1;
    } else {
      free(name);
      lua_error(L);
    }
  } else {
    luaL_error(L, "out of memory!");
  }
}

static int alien_function_types(lua_State *L) {
  static const int type[] = {VOID, INT, DOUBLE, CHAR, STRING, PTR};
  static const char *const typenames[] = {"void", "int", "double", "char", "string", "pointer", NULL};
  alien_Function *af = alien_checkfunction(L, 1);
  int i, j;
  af->ret_type = type[luaL_checkoption(L, 2, "void", typenames)];
  if(af->params) { free(af->params); af->params = NULL; }
  af->nparams = lua_gettop(L) - 2;
  if(af->nparams > 0) {
    af->params = (alien_Type *)malloc(af->nparams * sizeof(alien_Type));
    if(!af->params) luaL_error(L, "alien: out of memory");
  }
  for(i = 0, j = 3; i < af->nparams; i++, j++) {
    af->params[i] = type[luaL_checkoption(L, j, "int", typenames)];
  }
  return 0;
}

static int alien_function_call(lua_State *L) {
  int i, j, nargs;
  int iret; double dret; void *pret;
  av_alist alist;
  alien_Function *af = alien_checkfunction(L, 1);
  nargs = lua_gettop(L) - 1;
  if(nargs != af->nparams) {
    luaL_error(L, "alien: wrong number of arguments (function %s, library %s)", af->name, af->lib->name);
  }
  switch(af->ret_type) {
  case VOID: av_start_void(alist, af->fn); break;
  case INT:
  case CHAR:
    av_start_int(alist, af->fn, &iret); break;
  case DOUBLE: av_start_double(alist, af->fn, &dret); break;
  case STRING:
    av_start_ptr(alist, af->fn, char*, &pret); break;
  case PTR: 
    av_start_ptr(alist, af->fn, void*, &pret); break;
  default: luaL_error(L, "alien: unknown return type (function %s, library %s)", af->name, af->lib->name);
  }
  for(i = 0, j = 2; i < af->nparams; i++, j++) {
    switch(af->params[i]) {
    case INT:
    case CHAR:
      av_int(alist, lua_tointeger(L, j)); break;
    case DOUBLE: av_double(alist, lua_tonumber(L, j)); break;
    case STRING:
      if(lua_isuserdata(L, j))
	av_ptr(alist, char*, lua_touserdata(L, j));
      else
	av_ptr(alist, char*, lua_tostring(L, j)); 
      break;
    case PTR: av_ptr(alist, void*, lua_touserdata(L, j)); break;
    default: luaL_error(L, "alien: parameter %i is of unknown type (function %s, library %s)", j, 
			af->name, af->lib->name);
    }
  }
  av_call(alist);
  switch(af->ret_type) {
  case VOID: return 0;
  case INT:
  case CHAR:
    lua_pushnumber(L, iret); break;
  case DOUBLE: lua_pushnumber(L, dret); break;
  case STRING: lua_pushstring(L, (const char *)pret); break;
  case PTR: lua_pushlightuserdata(L, pret); break;
  default: luaL_error(L, "alien: unknown return type (function %s, library %s)", af->name, af->lib->name);
  }
  return 1;
}

static int alien_library_gc(lua_State *L) {
  alien_Library *al = alien_checklibrary(L, 1);
  alien_unload(al->lib);
  free(al->name);
}

static int alien_function_gc(lua_State *L) {
  alien_Function *af = alien_checkfunction(L, 1);
  free(af->name);
  if(af->params) free(af->params);
}

static int alien_register(lua_State *L) {
  const char *meta = luaL_checkstring(L, 1);
  lua_pushfstring(L, "alien_meta_%s", meta);
  luaL_newmetatable(L, lua_tostring(L, -1));
  return 1;
}

static int alien_pack(lua_State *L) {
  int i;
  void **ud;
  const char *meta = luaL_checkstring(L, 1);
  ud = (void**)lua_newuserdata(L, sizeof(void*) * lua_gettop(L));
  ud[0] = (void *)(lua_gettop(L) - 2);
  for(i = 1; i < lua_gettop(L) - 1 ; i++)
    ud[i] = lua_touserdata(L, i + 1);
  lua_pushfstring(L, "alien_meta_%s", meta);
  luaL_getmetatable(L, lua_tostring(L, -1));
  lua_setmetatable(L, -3);
  lua_pushvalue(L, -2);
  return 1;
}

static int alien_unpack(lua_State *L) {
  int size, i;
  void **ud;
  const char *meta = luaL_checkstring(L, 1);
  lua_pushfstring(L, "alien_meta_%s", meta);
  ud = (void **)luaL_checkudata(L, 2, lua_tostring(L, -1));
  luaL_argcheck(L, ud != NULL, 2, "userdata has wrong metatable");
  size = (int)ud[0];
  for(i = 1; i <= size; i++)
    lua_pushlightuserdata(L, ud[i]);
  return size;
}

static int alien_register_library_meta(lua_State *L) {
  luaL_newmetatable(L, ALIEN_LIBRARY_META);
  lua_pushliteral(L, "__gc");
  lua_pushcfunction(L, alien_library_gc);
  lua_settable(L, -3);
  lua_pushliteral(L, "__index");
  lua_newtable(L);
  lua_pushcclosure(L, alien_library_get, 1);
  lua_settable(L, -3);
  lua_pop(L, 1);
  return 0;
}

static int alien_register_function_meta(lua_State *L) {
  luaL_newmetatable(L, ALIEN_FUNCTION_META);
  lua_pushliteral(L, "__index");
  lua_newtable(L);
  lua_pushliteral(L, "types");
  lua_pushcfunction(L, alien_function_types);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushliteral(L, "__call");
  lua_pushcfunction(L, alien_function_call);
  lua_settable(L, -3);
  lua_pop(L, 1);
  return 0;
}

static const struct luaL_reg alienlib[] = {
  {"register", alien_register},
  {"wrap", alien_pack},
  {"unwrap", alien_unpack},
  {NULL, NULL},
};

static int alien_register_main(lua_State *L) {
  alien_Library *al;
  luaL_register (L, lua_tostring(L, -1), alienlib);
  lua_pushliteral(L, PLATFORM);
  lua_setfield(L, -2, "platform");
  al = (alien_Library *)lua_newuserdata(L, sizeof(alien_Library));
  al->lib = NULL;
  al->name = "default";
  luaL_getmetatable(L, ALIEN_LIBRARY_META);
  lua_setmetatable(L, -2);
  lua_setfield(L, -2, "default");
  lua_newtable(L);
  lua_pushcclosure(L, alien_get, 1);
  lua_setfield(L, -2, "load");
  lua_newtable(L);
  lua_getfield(L, -2, "load");
  lua_setfield(L, -2, "__index");
  lua_setmetatable(L, -2);
}

int luaopen_alien(lua_State *L) {
  alien_register_main(L);
  alien_register_library_meta(L);
  alien_register_function_meta(L);
  return 1;
}
