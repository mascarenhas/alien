/* Lua FFI using avcall/callback */
/* Author: Fabio Mascarenhas */
/* License: MIT/X11 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "avcall.h"
#include "callback.h"

#define ALIEN_LIBRARY_META "alien_library"
#define ALIEN_FUNCTION_META "alien_function"
#define ALIEN_BUFFER_META "alien_buffer"
#define ALIEN_CALLBACK_META "alien_callback"

typedef enum {
  SHORT,
  INT,
  VOID,
  DOUBLE,
  CHAR,
  STRING,
  PTR,
  REFINT,
  REFCHAR,
  REFDOUBLE,
  CALLBACK
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

typedef struct _alien_Callback {
  lua_State *L;
  int fn_ref;
  alien_Type ret_type;
  int nparams;
  alien_Type *params;
} alien_Callback;

typedef struct _alien_Wrap {
  alien_Type tag;
  union {
    void *p;
    int i;
  } val;
} alien_Wrap;

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

#ifndef RTLD_DEFAULT
#define RTLD_DEFAULT 0
#endif

#include <dlfcn.h>

static void alien_unload (void *lib) {
  if(lib && (lib != RTLD_DEFAULT))
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
  if(lib)
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

static __TR_function *alien_checkcallback(lua_State *L, int index) {
  void *ud = luaL_checkudata(L, index, ALIEN_CALLBACK_META);
  luaL_argcheck(L, ud != NULL, index, "alien callback expected");
  return (__TR_function *)ud;
}

static char *alien_checkbuffer(lua_State *L, int index) {
  void *ud = luaL_checkudata(L, index, ALIEN_BUFFER_META);
  luaL_argcheck(L, ud != NULL, index, "alien buffer expected");
  return (char *)ud;
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
  name = (char*)malloc(sizeof(char) * (len + 1));
  if(name) {
    alien_Library *al;
    alien_Function *af;
    void *fn;
    strcpy(name, funcname);
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

static void alien_callback_call(void *data, va_alist alist) {
  alien_Callback *ac;
  int nparams, i;
  void *ptr;
  ac = (alien_Callback *)data;
  switch(ac->ret_type) {
  case VOID: va_start_void(alist); break;
  case INT:
  case CHAR:
    va_start_int(alist); break;
  case DOUBLE: va_start_double(alist); break;
  case STRING:
    va_start_ptr(alist, char*); break;
  case PTR: 
    va_start_ptr(alist, void*); break;
  default: luaL_error(ac->L, "alien: unknown return type in callback");
  }
  lua_getref(ac->L, ac->fn_ref);
  nparams = ac->nparams;
  for(i = 0; i < nparams; i++) {
    switch(ac->params[i]) {
    case CHAR: lua_pushnumber(ac->L, va_arg_char(alist)); break;
    case SHORT: lua_pushnumber(ac->L, (double)va_arg_short(alist)); break;
    case INT: lua_pushnumber(ac->L, va_arg_int(alist)); break;
    case DOUBLE: lua_pushnumber(ac->L, va_arg_double(alist)); break;
    case STRING: lua_pushstring(ac->L, va_arg_ptr(alist, char*)); break;
    case PTR:
      ptr = va_arg_ptr(alist, void*);
      ptr ? lua_pushlightuserdata(ac->L, ptr) : lua_pushnil(ac->L);
      break;
    default: luaL_error(ac->L, "alien: unknown parameter type in callback");
    }
  }
  lua_call(ac->L, nparams, 1);
  switch(ac->ret_type) {
  case VOID: va_return_void(alist); break;
  case INT:
  case CHAR:
    va_return_int(alist, lua_tointeger(ac->L, -1)); break;
  case DOUBLE: va_return_double(alist, lua_tonumber(ac->L, -1)); break;
  case STRING:
    if(lua_isuserdata(ac->L, -1))
      va_return_ptr(alist, char*, lua_touserdata(ac->L, -1));
    else
      va_return_ptr(alist, char*, lua_tostring(ac->L, -1)); 
    break;
  case PTR:
    va_return_ptr(alist, void*, lua_touserdata(ac->L, -1)); break;
  default: luaL_error(ac->L, "alien: unknown return type in callback");
  }
}

static int alien_callback_new(lua_State *L) {
  int fn_ref;
  alien_Callback *ac;
  alien_Type at;
  __TR_function *ud;
  int i;
  static const int types[] = {VOID, INT, DOUBLE, CHAR, STRING, PTR, REFINT, REFDOUBLE, REFCHAR,
			      CALLBACK, SHORT};
  static const char *const typenames[] = {"void", "int", "double", "char", "string", "pointer",
					  "ref int", "ref double", "ref char", "callback", 
                                          "short", NULL};
  luaL_checktype(L, 1, LUA_TFUNCTION);
  ac = (alien_Callback *)malloc(sizeof(alien_Callback));
  ud = (__TR_function *)lua_newuserdata(L, sizeof(__TR_function));
  if(ac != NULL && ud != NULL) {
    int j;
    ac->L = L;
    ac->ret_type = types[luaL_checkoption(L, 2, "void", typenames)];
    ac->nparams = lua_gettop(L) - 3;
    if(ac->nparams > 0) {
      ac->params = (alien_Type *)malloc(ac->nparams * sizeof(alien_Type));
      if(!ac->params) luaL_error(L, "alien: out of memory");
    }
    for(i = 0, j = 3; i < ac->nparams; i++, j++) {
      ac->params[i] = types[luaL_checkoption(L, j, "int", typenames)];
    }
    lua_pushvalue(L, 1);
    ac->fn_ref = lua_ref(L, 1);
    *ud = alloc_callback(&alien_callback_call, ac);
    luaL_getmetatable(L, ALIEN_CALLBACK_META);
    lua_setmetatable(L, -2);
    return 1;
  } else {
    if(ac) free(ac);
    luaL_error(L, "alien: cannot allocate callback");
  }
}

static int alien_sizeof(lua_State *L) {
  static const int sizes[] = {sizeof(int), sizeof(double), sizeof(char), 
			     sizeof(char*), sizeof(void*)};
  static const char *const typenames[] = {"int", "double", "char", "string", 
					  "pointer", NULL};
  lua_pushnumber(L, sizes[luaL_checkoption(L, 1, "char", typenames)]);
  return 1;
}

static int alien_function_types(lua_State *L) {
  static const int types[] = {VOID, INT, DOUBLE, CHAR, STRING, PTR, REFINT, REFDOUBLE, REFCHAR,
			      CALLBACK, SHORT};
  static const char *const typenames[] = {"void", "int", "double", "char", "string", "pointer",
					  "ref int", "ref double", "ref char", "callback", 
                                          "short", NULL};
  alien_Function *af = alien_checkfunction(L, 1);
  int i, j;
  af->ret_type = types[luaL_checkoption(L, 2, "void", typenames)];
  if(af->params) { free(af->params); af->params = NULL; }
  af->nparams = lua_gettop(L) - 2;
  if(af->nparams > 0) {
    af->params = (alien_Type *)malloc(af->nparams * sizeof(alien_Type));
    if(!af->params) luaL_error(L, "alien: out of memory");
  }
  for(i = 0, j = 3; i < af->nparams; i++, j++) {
    af->params[i] = types[luaL_checkoption(L, j, "int", typenames)];
  }
  return 0;
}

static int alien_function_call(lua_State *L) {
  int i, j, nargs, nparams;
  int iret; double dret; void *pret;
  av_alist alist;
  int *refi_args, nrefi, nrefd, nrefc;
  double *refd_args;
  char *refc_args;
  void *ud;
  alien_Function *af = alien_checkfunction(L, 1);
  nparams = af->nparams;
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
  default: luaL_error(L, "alien: unknown return type (function %s, library %s)", 
		      af->name, af->lib->name);
  }
  for(i = 0, nrefi = 0, nrefd = 0, nrefc = 0; i < nparams; i++) {
    switch(af->params[i]) {
    case REFINT: nrefi++; break;
    case REFDOUBLE: nrefd++; break;
    case REFCHAR: nrefc++; break;
    }
  }
  if(nrefi > 0) refi_args = (int*)alloca(sizeof(int) * nrefi);
  if(nrefd > 0) refd_args = (double*)alloca(sizeof(double) * nrefd);
  if(nrefc > 0) refc_args = (char*)alloca(sizeof(char) * nrefc);
  nargs = lua_gettop(L) - 1 + nrefi + nrefd + nrefc;
  if(nargs < nparams)
    luaL_error(L, "alien: too few arguments (function %s)", af->name);
  else if(nargs > nparams)
    luaL_error(L, "alien: too many arguments (function %s)", af->name);
  for(i = 0, j = 2; i < nparams; i++, j++) {
    switch(af->params[i]) {
    case INT:
    case CHAR:
      av_int(alist, lua_tointeger(L, j)); break;
    case SHORT:
      av_short(alist, (short)lua_tointeger(L, j)); break;
    case DOUBLE: av_double(alist, lua_tonumber(L, j)); break;
    case STRING:
      if(lua_isuserdata(L, j))
	av_ptr(alist, char*, lua_isnil(L, j) ? NULL : lua_touserdata(L, j));
      else
	av_ptr(alist, char*, lua_isnil(L, j) ? NULL : lua_tostring(L, j)); 
      break;
    case CALLBACK: av_ptr(alist, void*, 
			  *((__TR_function*)luaL_checkudata(L, j, ALIEN_CALLBACK_META))); break;
    case PTR: av_ptr(alist, void*, lua_isnil(L, j) ? NULL :lua_touserdata(L, j)); break;
    case REFINT: av_ptr(alist, int*, refi_args); refi_args++; j--; break;
    case REFDOUBLE: av_ptr(alist, double*, refd_args); refd_args++; j--; break;
    case REFCHAR: av_ptr(alist, char*, refc_args); refc_args++; j--; break;
    default: luaL_error(L, "alien: parameter %i is of unknown type (function %s)", j, 
			af->name);
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
  case PTR: pret ? lua_pushlightuserdata(L, pret) : lua_pushnil(L); break;
  default: luaL_error(L, "alien: unknown return type (function %s, library %s)", af->name,
		      af->lib->name);
  }
  refi_args -= nrefi; refd_args -= nrefd; refc_args -= nrefc;
  for(i = 0; i < nparams; i++) {
    switch(af->params[i]) {
    case REFINT: lua_pushnumber(L, *refi_args); refi_args++; break;
    case REFDOUBLE: lua_pushnumber(L, *refd_args); refd_args++; break;
    case REFCHAR: lua_pushnumber(L, *refc_args); refc_args++; break;
    }
  }
  return 1 + nrefi + nrefc + nrefd;
}

static int alien_library_gc(lua_State *L) {
  alien_Library *al = alien_checklibrary(L, 1);
  if(al->lib) {
    alien_unload(al->lib);
    free(al->name);
  }
}

static int alien_function_gc(lua_State *L) {
  alien_Function *af = alien_checkfunction(L, 1);
  free(af->name);
  if(af->params) free(af->params);
}

static int alien_callback_gc(lua_State *L) {
  __TR_function *ud = alien_checkcallback(L, 1);
  alien_Callback *ac = (alien_Callback *)callback_data(*ud);
  lua_unref(ac->L, ac->fn_ref);
  if(ac->params) free(ac->params);
  free_callback(*ud);
}

static int alien_register(lua_State *L) {
  const char *meta = luaL_checkstring(L, 1);
  luaL_newmetatable(L, meta);
  return 1;
}

static int alien_pack(lua_State *L) {
  int i, top;
  alien_Wrap *ud;
  const char *meta = luaL_checkstring(L, 1);
  ud = (alien_Wrap*)lua_newuserdata(L, sizeof(alien_Wrap) * lua_gettop(L));
  top = lua_gettop(L);
  for(i = 2; i < top ; i++) {
    if(lua_isnil(L, i)) {
      ud[i - 2].tag = PTR;
      ud[i - 2].val.p = NULL;
    }
    else if(lua_isuserdata(L, i)) {
      ud[i - 2].tag = PTR;
      ud[i - 2].val.p = lua_touserdata(L, i);
    } else {
      ud[i - 2].tag = INT;
      ud[i - 2].val.i = lua_tointeger(L, i);
    }
  }
  ud[lua_gettop(L) - 2].tag = VOID;
  luaL_getmetatable(L, meta);
  lua_setmetatable(L, -2);
  return 1;
}

static int alien_unpack(lua_State *L) {
  int size, i;
  alien_Wrap *ud;
  const char *meta = luaL_checkstring(L, 1);
  ud = (alien_Wrap *)luaL_checkudata(L, 2, meta);
  luaL_argcheck(L, ud != NULL, 2, "userdata has wrong metatable");
  while(ud->tag != VOID) {
    switch(ud->tag) {
    case INT: lua_pushnumber(L, ud->val.i); break;
    case PTR: ud->val.p ? lua_pushlightuserdata(L, ud->val.p) : lua_pushnil(L); break;
    default: luaL_error(L, "wrong type in wrapped value");
    }
    ud++;
  }
  return lua_gettop(L) - 2;
}

static int alien_buffer_new(lua_State *L) {
  char *b;
  int size;
  size = luaL_optint(L, 1, BUFSIZ);
  b = (char *)lua_newuserdata(L, sizeof(char) * size);
  if(b) {
    luaL_getmetatable(L, ALIEN_BUFFER_META);
    lua_setmetatable(L, -2);
    return 1;
  } else {
    luaL_error(L, "cannot allocate buffer");
  }
}

static int alien_buffer_tostring(lua_State *L) {
  char *b = alien_checkbuffer(L, 1);
  int size = luaL_optint(L, 2, BUFSIZ);
  lua_pushlstring(L, b, size);
  return 1;
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

static int alien_register_callback_meta(lua_State *L) {
  luaL_newmetatable(L, ALIEN_CALLBACK_META);
  lua_pushliteral(L, "__gc");
  lua_pushcfunction(L, alien_callback_gc);
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

static int alien_register_buffer_meta(lua_State *L) {
  luaL_newmetatable(L, ALIEN_BUFFER_META);
  lua_pushliteral(L, "__index");
  lua_newtable(L);
  lua_pushliteral(L, "tostring");
  lua_pushcfunction(L, alien_buffer_tostring);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushliteral(L, "__tostring");
  lua_pushcfunction(L, alien_buffer_tostring);
  lua_settable(L, -3);
  lua_pop(L, 1);
  return 0;
}

static int alien_errno(lua_State *L) {
  lua_pushnumber(L, errno);
  return 1;
}

static int alien_udata2str(lua_State *L) {
  char *ud;
  int size;
  luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
  size = luaL_checkinteger(L, 2);
  ud = (char *)lua_touserdata(L, 1);
  lua_pushlstring(L, ud, size);
  return 1;
}

static int alien_udata2double(lua_State *L) {
  double *ud;
  luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
  ud = (double *)lua_touserdata(L, 1);
  lua_pushnumber(L, *ud);
  return 1;
}

static int alien_udata2int(lua_State *L) {
  int *ud;
  luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
  ud = (int *)lua_touserdata(L, 1);
  lua_pushnumber(L, *ud);
  return 1;
}

static int alien_isnull(lua_State *L) {
  void *ud;
  luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
  ud = lua_touserdata(L, 1);
  lua_pushboolean(L, ud == NULL);
  return 1;
}

static const struct luaL_reg alienlib[] = {
  {"new_tag", alien_register},
  {"wrap", alien_pack},
  {"unwrap", alien_unpack},
  {"errno", alien_errno},
  {"tostring", alien_udata2str},
  {"isnull", alien_isnull},
  {"sizeof", alien_sizeof},
  {"todouble", alien_udata2double},
  {"toint", alien_udata2double},
  {"new_buffer", alien_buffer_new},
  {"new_callback", alien_callback_new},
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
  alien_register_library_meta(L);
  alien_register_callback_meta(L);
  alien_register_function_meta(L);
  alien_register_buffer_meta(L);
  alien_register_main(L);
  return 1;
}
