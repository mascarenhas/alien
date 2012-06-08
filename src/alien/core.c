/* Lua FFI using libffi */
/* Author: Fabio Mascarenhas */
/* License: MIT/X11 */

#include "config.h"

#ifdef WINDOWS
#define _CRT_SECURE_NO_DEPRECATE 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#define LUA_COMPAT_ALL

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "ffi.h"

#if LUA_VERSION_NUM == 502
#define lua_setfenv lua_setuservalue
#define lua_getfenv lua_getuservalue

static int luaL_typerror (lua_State *L, int narg, const char *tname) {
  const char *msg = lua_pushfstring(L, "%s expected, got %s",
                                    tname, luaL_typename(L, narg));
  return luaL_argerror(L, narg, msg);
}
#else
static void *luaL_testudata(lua_State *L, int ud, const char *tname) {
  void *p = lua_touserdata(L, ud);
  if(p == NULL) return NULL;
  if(!lua_getmetatable(L, ud)) return NULL;
  lua_getfield(L, LUA_REGISTRYINDEX, tname);
  if(!lua_rawequal(L, -1, -2))
    p = NULL;
  lua_pop(L, 2);
  return p;
}
#endif

#ifdef HAVE_ALLOCA_H
# include <alloca.h>
#elif defined __GNUC__
# define alloca __builtin_alloca
#elif defined _AIX
# define alloca __alloca
#elif defined _MSC_VER
# include <malloc.h>
# define alloca _alloca
#else
# error "cannot find alloca"
#endif

#define ALIEN_LIBRARY_META "alien library"
#define ALIEN_FUNCTION_META "alien function"
#define ALIEN_BUFFER_META "alien buffer"
#define ALIEN_LBUFFER_META "alien light buffer"

/* The following enum and arrays MUST all be in the same order. */
/* N.B. void is first so it can be ignored for sizeof/alignment. */

typedef enum {
  AT_VOID, AT_BYTE, AT_CHAR,
  AT_SHORT, AT_USHORT, AT_INT, AT_UINT,
  AT_LONG, AT_ULONG, AT_FLOAT, AT_DOUBLE,
  AT_STRING, AT_PTR,
  AT_REFCHAR, AT_REFINT, AT_REFUINT, AT_REFDOUBLE,
  AT_CALLBACK,
} alien_Type;

static const char *const alien_typenames[] =  {
  "void", "byte", "char",
  "short", "ushort", "int", "uint",
  "long", "ulong", "float", "double",
  "string", "pointer",
  "ref char", "ref int", "ref uint", "ref double",
  "callback",
  NULL
};

static ffi_type* ffitypes[] = {
  &ffi_type_void, &ffi_type_sint8, &ffi_type_uchar,
  &ffi_type_sshort, &ffi_type_ushort, &ffi_type_sint, &ffi_type_uint,
  &ffi_type_slong, &ffi_type_ulong, &ffi_type_float, &ffi_type_double,
  &ffi_type_pointer, &ffi_type_pointer,
  &ffi_type_pointer, &ffi_type_pointer, &ffi_type_pointer, &ffi_type_pointer,
  &ffi_type_pointer,
};

typedef struct {
  void *lib;
  char *name;
} alien_Library;

typedef struct {
  alien_Library *lib;
  void *fn;
  char *name;
  alien_Type ret_type;
  ffi_cif cif;
  ffi_type *ffi_ret_type;
  int nparams;
  alien_Type *params;
  ffi_type **ffi_params;
  /* callback part */
  lua_State *L;
  void *ffi_codeloc;
  int fn_ref;
} alien_Function;

typedef struct {
  alien_Type tag;
  union {
    void *p;
    int i;
  } val;
} alien_Wrap;

/* Information to compute structure access */

typedef struct { char c; char x; } s_char;
typedef struct { char c; short x; } s_short;
typedef struct { char c; int x; } s_int;
typedef struct { char c; long x; } s_long;
typedef struct { char c; float x; } s_float;
typedef struct { char c; double x; } s_double;
typedef struct { char c; char *x; } s_char_p;
typedef struct { char c; void *x; } s_void_p;

#define AT_CHAR_ALIGN (offsetof(s_char, x))
#define AT_SHORT_ALIGN (offsetof(s_short, x))
#define AT_INT_ALIGN (offsetof(s_int, x))
#define AT_LONG_ALIGN (offsetof(s_long, x))
#define AT_FLOAT_ALIGN (offsetof(s_float, x))
#define AT_DOUBLE_ALIGN (offsetof(s_double, x))
#define AT_CHAR_P_ALIGN (offsetof(s_char_p, x))
#define AT_VOID_P_ALIGN (offsetof(s_void_p, x))

/******************************************************************/

#if defined(linux)
#define PLATFORM "linux"
#define USE_DLOPEN
#elif defined(BSD)
#define PLATFORM "bsd"
#define USE_DLOPEN
#elif defined(DARWIN)
#define PLATFORM "darwin"
#define USE_DLOPEN
#endif

#if defined(USE_DLOPEN)

#ifndef RTLD_DEFAULT
#define RTLD_DEFAULT 0
#endif

#include <dlfcn.h>

static void alien_unload (void *lib) {
  if(lib && (lib != RTLD_DEFAULT))
    dlclose(lib);
}

static void *alien_openlib (lua_State *L, const char *libname) {
  void *lib;
  lib = dlopen(libname, RTLD_NOW);
  if(lib == NULL) lua_pushstring(L, dlerror());
  return lib;
}

static void *alien_loadfunc (lua_State *L, void *lib, const char *sym) {
  if(!lib) lib = RTLD_DEFAULT;
  void *f = dlsym(lib, sym);
  if (f == NULL) lua_pushstring(L, dlerror());
  return f;
}

#elif defined(WINDOWS)

#define PLATFORM "windows"

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

static void *alien_openlib (lua_State *L, const char *libname) {
  HINSTANCE lib = LoadLibrary(libname);
  if (lib == NULL) pusherror(L);
  return lib;
}

static void *alien_loadfunc (lua_State *L, void *lib, const char *sym) {
  HINSTANCE module;
  void *f;
  module = (HINSTANCE)lib;
  if(!module) module = GetModuleHandle(NULL);
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

static void *alien_openlib (lua_State *L, const char *path) {
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

#if !defined(WINDOWS) || defined(_WIN64)
#define FFI_STDCALL FFI_DEFAULT_ABI
#endif

#ifdef DARWIN
#define FFI_SYSV FFI_DEFAULT_ABI
#endif

static const ffi_abi ffi_abis[] = { FFI_DEFAULT_ABI, FFI_SYSV, FFI_STDCALL };
static const char *const ffi_abi_names[] = { "default", "cdecl", "stdcall", NULL };

static alien_Library *alien_checklibrary(lua_State *L, int index) {
  return (alien_Library *)luaL_checkudata(L, index, ALIEN_LIBRARY_META);
}

static alien_Function *alien_checkfunction(lua_State *L, int index) {
  return (alien_Function *)luaL_checkudata(L, index, ALIEN_FUNCTION_META);
}

static char *alien_checkbuffer(lua_State *L, int index) {
  void *ud = luaL_testudata(L, index, ALIEN_BUFFER_META);
  if(ud == NULL) {
    void **ud2 = luaL_testudata(L, index, ALIEN_LBUFFER_META);
    if (ud2) ud = *ud2;
  }
  luaL_argcheck(L, ud != NULL, index, "alien buffer expected");
  return (char *)ud;
}

static int alien_load(lua_State *L) {
  size_t len;
  void *aud, *lib;
  alien_Library *al;
  const char *libname = luaL_checklstring(L, lua_gettop(L), &len);
  lua_Alloc lalloc = lua_getallocf(L, &aud);
  char *name = (char*)lalloc(aud, NULL, 0, sizeof(char) * (len + 1));
  if(!name)
    return luaL_error(L, "alien: out of memory");
  strcpy(name, libname);
  al = (alien_Library *)lua_newuserdata(L, sizeof(alien_Library));
  if(!al) return luaL_error(L, "alien: out of memory");
  lib = alien_openlib(L, libname);
  if(!lib)
    return lua_error(L);
  lua_newtable(L);
  lua_setfenv(L, -2);
  luaL_getmetatable(L, ALIEN_LIBRARY_META);
  lua_setmetatable(L, -2);
  al->lib = lib;
  al->name = name;
  return 1;
}

static int alien_makefunction(lua_State *L, void *lib, void *fn, char *name) {
  alien_Function *af = (alien_Function *)lua_newuserdata(L, sizeof(alien_Function));
  if(!af)
    return luaL_error(L, "alien: out of memory");
  luaL_getmetatable(L, ALIEN_FUNCTION_META);
  lua_setmetatable(L, -2);
  af->fn = fn;
  af->fn_ref = 0;
  af->name = name;
  af->lib = lib;
  af->nparams = 0;
  af->ret_type = AT_VOID;
  af->params = NULL;
  af->ffi_params = NULL;
  return 1;
}

static int alien_library_get(lua_State *L) {
  char *name;
  int cache;
  void *aud, *fn;
  lua_Alloc lalloc = lua_getallocf(L, &aud);
  alien_Library *al = alien_checklibrary(L, 1);
  size_t len;
  const char *funcname = luaL_checklstring(L, 2, &len);
  lua_getfenv(L, 1);
  cache = lua_gettop(L);
  lua_getfield(L, cache, funcname);
  if(!lua_isnil(L, -1)) return 1;
  name = (char*)lalloc(aud, NULL, 0, sizeof(char) * (len + 1));
  if(!name)
    return luaL_error(L, "alien: out of memory");
  strcpy(name, funcname);
  fn = alien_loadfunc(L, al->lib, funcname);
  if(!fn) {
    lalloc(aud, name, 0, 0);
    return lua_error(L);
  }
  alien_makefunction(L, al, fn, name);
  lua_newtable(L);
  lua_pushvalue(L, 1);
  lua_rawseti(L, -2, 1);
  lua_setfenv(L, -2);
  lua_pushvalue(L, -1);
  lua_setfield(L, cache, funcname);
  return 1;
}

static int alien_function_new(lua_State *L) {
  if(lua_isuserdata(L, 1)) {
    void *fn = lua_touserdata(L, 1);
    return alien_makefunction(L, NULL, fn, NULL);
  } else return luaL_error(L, "alien: not a userdata");
}

static int alien_library_tostring(lua_State *L) {
  alien_Library *al = alien_checklibrary(L, 1);
  lua_pushfstring(L, "alien library %s", (al->name ? al->name : "default"));
  return 1;
}

static void alien_callback_call(ffi_cif *cif, void *resp, void **args, void *data) {
  alien_Function *ac = (alien_Function *)data;
  lua_State *L = ac->L;
  int i;
  lua_rawgeti(L, LUA_REGISTRYINDEX, ac->fn_ref);
  for(i = 0; i < ac->nparams; i++) {
    switch(ac->params[i]) {
    case AT_BYTE: lua_pushnumber(L, (signed char)*((int*)args[i])); break;
    case AT_CHAR: lua_pushnumber(L, (unsigned char)*((int*)args[i])); break;
    case AT_SHORT: lua_pushnumber(L, (short)*((int*)args[i])); break;
    case AT_LONG: lua_pushnumber(L, (long)*((long*)args[i])); break;
    case AT_INT: lua_pushnumber(L, *((int*)args[i])); break;
    case AT_USHORT: lua_pushnumber(L, (unsigned short)*((unsigned int*)args[i])); break;
    case AT_ULONG: lua_pushnumber(L, (unsigned long)*((unsigned long*)args[i])); break;
    case AT_UINT: lua_pushnumber(L, *((unsigned int*)args[i])); break;
    case AT_FLOAT: lua_pushnumber(L, (float)*((float*)args[i])); break;
    case AT_DOUBLE: lua_pushnumber(L, *((double*)args[i])); break;
    case AT_STRING: lua_pushstring(L, *((char**)args[i])); break;
    case AT_REFINT: lua_pushnumber(L, **((int**)args[i])); break;
    case AT_REFUINT: lua_pushnumber(L, **((unsigned int**)args[i])); break;
    case AT_REFCHAR: lua_pushnumber(L, **((unsigned char**)args[i])); break;
    case AT_REFDOUBLE: lua_pushnumber(L, **((double**)args[i])); break;
    case AT_PTR:
      {
        void *ptr = *((void**)args[i]);
        ptr ? lua_pushlightuserdata(L, ptr) : lua_pushnil(L);
      }
      break;
    default: luaL_error(L, "alien: unknown parameter type in callback");
    }
  }
  lua_call(L, ac->nparams, 1);
  switch(ac->ret_type) {
  case AT_VOID: break;
  case AT_SHORT: *((int*)resp) = (short)lua_tonumber(L, -1); break;
  case AT_LONG: *((long*)resp) = (long)lua_tonumber(L, -1); break;
  case AT_INT: *((int*)resp) = (int)lua_tonumber(L, -1); break;
  case AT_USHORT: *((unsigned int*)resp) = (unsigned short)lua_tonumber(L, -1); break;
  case AT_ULONG: *((unsigned long*)resp) = (unsigned long)lua_tonumber(L, -1); break;
  case AT_UINT: *((unsigned int*)resp) = (unsigned int)lua_tonumber(L, -1); break;
  case AT_CHAR: *((int*)resp) = (unsigned char)lua_tointeger(L, -1); break;
  case AT_BYTE: *((int*)resp) = (signed char)lua_tointeger(L, -1); break;
  case AT_FLOAT: *((float*)resp) = (float)lua_tonumber(L, -1); break;
  case AT_DOUBLE: *((double*)resp) = (double)lua_tonumber(L, -1); break;
  case AT_STRING:
    if(lua_isuserdata(L, -1))
      *((char**)resp) = lua_touserdata(L, -1);
    else
      *((const char**)resp) = lua_tostring(L, -1);
    break;
  case AT_PTR:
    if(lua_isstring(L, -1))
      *((void**)resp) = (void*)lua_tostring(L, -1);
    else
      *((void**)resp) = lua_touserdata(L, -1);
    break;
  default: luaL_error(L, "alien: unknown return type in callback");
  }
}

static int alien_callback_new(lua_State *L) {
  alien_Function *ac;
  ffi_status status;
  luaL_checktype(L, 1, LUA_TFUNCTION);
  ac = (alien_Function *)lua_newuserdata(L, sizeof(alien_Function));
  if(!ac) return luaL_error(L, "alien: out of memory");
  ac->fn = ffi_closure_alloc(sizeof(ffi_closure), &ac->ffi_codeloc);
  if(ac->fn == NULL) return luaL_error(L, "alien: cannot allocate callback");
  ac->L = L;
  ac->ret_type = AT_VOID;
  ac->ffi_ret_type = &ffi_type_void;
  ac->nparams = 0;
  ac->params = NULL;
  ac->ffi_params = NULL;
  lua_pushvalue(L, 1);
  ac->fn_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  luaL_getmetatable(L, ALIEN_FUNCTION_META);
  lua_setmetatable(L, -2);
  status = ffi_prep_cif(&(ac->cif), FFI_DEFAULT_ABI, ac->nparams,
                        ac->ffi_ret_type, ac->ffi_params);
  if(status == FFI_OK)
    status = ffi_prep_closure_loc(ac->fn, &(ac->cif), &alien_callback_call, ac, ac->ffi_codeloc);
  if(status != FFI_OK) {
    ffi_closure_free(ac->fn);
    return luaL_error(L, "alien: cannot create callback");
  }
  ac->lib = NULL;
  ac->name = NULL;
  return 1;
}

static int alien_sizeof(lua_State *L) {
  static const size_t sizes[] = {
    /* No void */ sizeof(unsigned char), sizeof(char),
    sizeof(short), sizeof(unsigned short), sizeof(int), sizeof(unsigned int),
    sizeof(long), sizeof(unsigned long), sizeof(float), sizeof(double),
    sizeof(char*), sizeof(void*),
    sizeof(char*), sizeof(int*), sizeof(unsigned int*), sizeof(double*),
    sizeof(void*),
  };
  lua_pushinteger(L, sizes[luaL_checkoption(L, 1, "int", alien_typenames + 1)]); /* N.B. Add 1 to miss out "void" */
  return 1;
}

static int alien_align(lua_State *L) {
  static const size_t aligns[] = {
    /* No void */ AT_CHAR_ALIGN, AT_CHAR_ALIGN,
    AT_SHORT_ALIGN, AT_SHORT_ALIGN, AT_INT_ALIGN, AT_INT_ALIGN,
    AT_LONG_ALIGN, AT_LONG_ALIGN, AT_FLOAT_ALIGN, AT_DOUBLE_ALIGN,
    AT_CHAR_P_ALIGN, AT_VOID_P_ALIGN,
    AT_CHAR_P_ALIGN, AT_VOID_P_ALIGN, AT_VOID_P_ALIGN, AT_VOID_P_ALIGN,
    AT_VOID_P_ALIGN,
  };
  lua_pushinteger(L, aligns[luaL_checkoption(L, 1, "char", alien_typenames + 1)]);
  return 1;
}

static int alien_function_types(lua_State *L) {
  ffi_status status;
  ffi_abi abi;
  alien_Function *af = alien_checkfunction(L, 1);
  int i, ret_type;
  void *aud;
  lua_Alloc lalloc = lua_getallocf(L, &aud);
  if(lua_istable(L, 2)) {
    lua_getfield(L, 2, "ret");
    ret_type = luaL_checkoption(L, -1, "int", alien_typenames);
    af->ret_type = ret_type;
    af->ffi_ret_type = ffitypes[ret_type];
    lua_getfield(L, 2, "abi");
    abi = ffi_abis[luaL_checkoption(L, -1, "default", ffi_abi_names)];
    lua_pop(L, 2);
  } else {
    ret_type = luaL_checkoption(L, 2, "int", alien_typenames);
    af->ret_type = ret_type;
    af->ffi_ret_type = ffitypes[ret_type];
    abi = FFI_DEFAULT_ABI;
  }
  if(af->params) {
    lalloc(aud, af->params, 0, 0); lalloc(aud, af->ffi_params, 0, 0);
    af->params = NULL; af->ffi_params = NULL;
  }
  af->nparams = lua_istable(L, 2) ? lua_objlen(L, 2) : lua_gettop(L) - 2;
  if(af->nparams > 0) {
    af->ffi_params = (ffi_type **)lalloc(aud, NULL, 0, sizeof(ffi_type *) * af->nparams);
    if(!af->ffi_params) return luaL_error(L, "alien: out of memory");
    af->params = (alien_Type *)lalloc(aud, NULL, 0, af->nparams * sizeof(alien_Type));
    if(!af->params) return luaL_error(L, "alien: out of memory");
  } else {
    af->ffi_params = NULL;
    af->params = NULL;
  }
  if(lua_istable(L, 2)) {
    for(i = 0; i < af->nparams; i++) {
      int type;
      lua_rawgeti(L, 2, i + 1);
      type = luaL_checkoption(L, -1, "int", alien_typenames);
      af->params[i] = type;
      af->ffi_params[i] = ffitypes[type];
      lua_pop(L, 1);
    }
  } else {
    for(i = 0; i < af->nparams; i++) {
      int type = luaL_checkoption(L, i + 3, "int", alien_typenames);
      af->ffi_params[i] = ffitypes[type];
      af->params[i] = type;
    }
  }
  status = ffi_prep_cif(&(af->cif), abi, af->nparams,
                        af->ffi_ret_type,
                        af->ffi_params);
  if(status != FFI_OK)
    return luaL_error(L, "alien: error in libffi preparation");
  if(af->fn_ref) {
    status = ffi_prep_closure(af->fn, &(af->cif), &alien_callback_call, af);
    if(status != FFI_OK) return luaL_error(L, "alien: cannot create callback");
  }
  return 0;
}

static int alien_function_tostring(lua_State *L) {
  alien_Function *af = alien_checkfunction(L, 1);
  lua_pushfstring(L, "alien function %s, library %s", af->name ? af->name : "anonymous",
                   ((af->lib && af->lib->name) ? af->lib->name : "default"));
  return 1;
}

static int alien_function_call(lua_State *L) {
  int iret; double dret; void *pret; long lret; unsigned long ulret; float fret;
  int i, nrefi = 0, nrefui = 0, nrefd = 0, nrefc = 0;
  void **args = NULL;
  alien_Function *af = alien_checkfunction(L, 1);
  ffi_cif *cif = &(af->cif);
  int nargs = lua_gettop(L) - 1;
  if(nargs != af->nparams)
    return luaL_error(L, "alien: too %s arguments (function %s)", nargs < af->nparams ? "few" : "many",
                      af->name ? af->name : "anonymous");
  if(nargs > 0) args = alloca(sizeof(void*) * nargs);
  for(i = 0; i < nargs; i++) {
    void *arg;
    int j = i + 2;
    switch(af->params[i]) {
    case AT_SHORT:
      arg = alloca(sizeof(short)); *((short*)arg) = (short)lua_tonumber(L, j);
      break;
    case AT_LONG:
      arg = alloca(sizeof(long)); *((long*)arg) = (long)lua_tonumber(L, j);
      break;
    case AT_INT:
      arg = alloca(sizeof(int)); *((int*)arg) = (int)lua_tonumber(L, j);
      break;
    case AT_USHORT:
      arg = alloca(sizeof(unsigned short)); *((unsigned short*)arg) = (unsigned short)lua_tonumber(L, j);
      break;
    case AT_ULONG:
      arg = alloca(sizeof(unsigned long)); *((unsigned long*)arg) = (unsigned long)lua_tonumber(L, j);
      break;
    case AT_UINT:
      arg = alloca(sizeof(unsigned int)); *((unsigned int*)arg) = (unsigned int)lua_tonumber(L, j);
      break;
    case AT_CHAR:
      arg = alloca(sizeof(unsigned char)); *((unsigned char*)arg) = (unsigned char)lua_tointeger(L, j);
      break;
    case AT_BYTE:
      arg = alloca(sizeof(char)); *((char*)arg) = (signed char)lua_tointeger(L, j);
      break;
    case AT_FLOAT:
      arg = alloca(sizeof(float)); *((float*)arg) = (float)lua_tonumber(L, j);
      break;
    case AT_DOUBLE:
      arg = alloca(sizeof(double)); *((double*)arg) = (double)lua_tonumber(L, j);
      break;
    case AT_STRING:
      arg = alloca(sizeof(char*));
      if(lua_isuserdata(L, j))
        *((char**)arg) = lua_isnil(L, j) ? NULL : lua_touserdata(L, j);
      else
        *((const char**)arg) = lua_isnil(L, j) ? NULL : lua_tostring(L, j);
      break;
    case AT_CALLBACK:
      arg = alloca(sizeof(void*)); *((void**)arg) = (alien_Function *)alien_checkfunction(L, j)->fn;
      break;
    case AT_PTR:
      arg = alloca(sizeof(char*));
      *((void**)arg) = lua_isnil(L, j) ? NULL :
             (lua_isstring(L, j) ? (void*)lua_tostring(L, j) :
              lua_touserdata(L, j));
      break;
    case AT_REFINT:
      arg = alloca(sizeof(int *));
      *((int **)arg) = alloca(sizeof(int));
      **((int **)arg) = (int)lua_tonumber(L, j);
      nrefi++;
      break;
    case AT_REFUINT:
      arg = alloca(sizeof(unsigned int *));
      *((unsigned int **)arg) = alloca(sizeof(unsigned int));
      **((unsigned int **)arg) = (unsigned int)lua_tonumber(L, j);
      nrefui++;
      break;
    case AT_REFCHAR:
      arg = alloca(sizeof(char *));
      *((char **)arg) = alloca(sizeof(char));
      **((char **)arg) = (char)lua_tonumber(L, j);
      nrefc++;
      break;
    case AT_REFDOUBLE:
      arg = alloca(sizeof(double *));
      *((double **)arg) = alloca(sizeof(double));
      **((double **)arg) = (double)lua_tonumber(L, j);
      nrefd++;
      break;
    default:
      return luaL_error(L, "alien: parameter %i is of unknown type (function %s)", j,
                        af->name ? af->name : "anonymous");
    }
    args[i] = arg;
  }
  pret = NULL;
  switch(af->ret_type) {
  case AT_VOID: ffi_call(cif, af->fn, NULL, args); lua_pushnil(L); break;
  case AT_SHORT: ffi_call(cif, af->fn, &iret, args); lua_pushnumber(L, (short)iret); break;
  case AT_LONG: ffi_call(cif, af->fn, &lret, args); lua_pushnumber(L, lret); break;
  case AT_INT: ffi_call(cif, af->fn, &iret, args); lua_pushnumber(L, iret); break;
  case AT_USHORT: ffi_call(cif, af->fn, &iret, args); lua_pushnumber(L, (unsigned short)iret); break;
  case AT_ULONG: ffi_call(cif, af->fn, &ulret, args); lua_pushnumber(L, (unsigned long)ulret); break;
  case AT_UINT: ffi_call(cif, af->fn, &iret, args); lua_pushnumber(L, (unsigned int)iret); break;
  case AT_CHAR: ffi_call(cif, af->fn, &iret, args); lua_pushnumber(L, (unsigned char)iret); break;
  case AT_BYTE: ffi_call(cif, af->fn, &iret, args); lua_pushnumber(L, (signed char)iret); break;
  case AT_FLOAT: ffi_call(cif, af->fn, &fret, args); lua_pushnumber(L, fret); break;
  case AT_DOUBLE: ffi_call(cif, af->fn, &dret, args); lua_pushnumber(L, dret); break;
  case AT_STRING: ffi_call(cif, af->fn, &pret, args);
    (pret ? lua_pushstring(L, (const char *)pret) : lua_pushnil(L)); break;
  case AT_PTR: ffi_call(cif, af->fn, &pret, args);
    (pret ? lua_pushlightuserdata(L, pret) : lua_pushnil(L)); break;
  default:
    return luaL_error(L, "alien: unknown return type (function %s)", af->name ?
                      af->name : "anonymous");
  }
  for(i = 0; i < nargs; i++) {
    switch(af->params[i]) {
    case AT_REFINT: lua_pushnumber(L, **(int **)args[i]); break;
    case AT_REFUINT: lua_pushnumber(L, **(unsigned int **)args[i]); break;
    case AT_REFDOUBLE: lua_pushnumber(L, **(double **)args[i]); break;
    case AT_REFCHAR: lua_pushnumber(L, **(char **)args[i]); break;
    default: break;
    }
  }
  return 1 + nrefi + nrefui + nrefc + nrefd;
}

static int alien_library_gc(lua_State *L) {
  alien_Library *al = alien_checklibrary(L, 1);
  void *aud;
  lua_Alloc lalloc = lua_getallocf(L, &aud);
  if(al->lib) {
    alien_unload(al->lib);
    al->lib = NULL;
    if(al->name) { lalloc(aud, al->name, 0, 0); al->name = NULL; }
  }
  return 0;
}

static int alien_function_gc(lua_State *L) {
  alien_Function *af = alien_checkfunction(L, 1);
  void *aud;
  lua_Alloc lalloc = lua_getallocf(L, &aud);
  if(af->name) lalloc(aud, af->name, 0, 0);
  if(af->params) lalloc(aud, af->params, 0, 0);
  if(af->ffi_params) lalloc(aud, af->ffi_params, 0, 0);
  if(af->fn_ref) {
    luaL_unref(af->L, LUA_REGISTRYINDEX, af->fn_ref);
    ffi_closure_free(af->fn);
  }
  return 0;
}

static int alien_register(lua_State *L) {
  const char *meta = luaL_checkstring(L, 1);
  luaL_getmetatable(L, meta);
  if(lua_isnil(L, -1))
    luaL_newmetatable(L, meta);
  return 1;
}

static void alien_wrap_one(lua_State *L, int i, alien_Wrap *ud) {
  if(lua_isnoneornil(L, i)) {
    ud->tag = AT_PTR;
    ud->val.p = NULL;
  } else if(lua_isuserdata(L, i)) {
    ud->tag = AT_PTR;
    ud->val.p = lua_touserdata(L, i);
  } else {
    ud->tag = AT_INT;
    ud->val.i = lua_tointeger(L, i);
  }
}

static int alien_wrap(lua_State *L) {
  const char *meta = luaL_checkstring(L, 1);
  alien_Wrap *ud = (alien_Wrap*)lua_newuserdata(L, sizeof(alien_Wrap) * lua_gettop(L));
  int top = lua_gettop(L);
  int i;
  for(i = 2; i < top; i++)
    alien_wrap_one(L, i, ud++);
  ud->tag = AT_VOID;
  luaL_getmetatable(L, meta);
  lua_setmetatable(L, -2);
  return 1;
}

static int alien_rewrap(lua_State *L) {
  const char *meta = luaL_checkstring(L, 1);
  alien_Wrap *ud = (alien_Wrap *)luaL_checkudata(L, 2, meta);
  int i;
  for (i = 3; ud->tag != AT_VOID; i++)
    alien_wrap_one(L, i, ud++);
  return 0;
}

static int alien_unwrap(lua_State *L) {
  const char *meta = luaL_checkstring(L, 1);
  alien_Wrap *ud = (alien_Wrap *)luaL_checkudata(L, 2, meta);
  while(ud->tag != AT_VOID) {
    switch(ud->tag) {
    case AT_INT: lua_pushnumber(L, ud->val.i); break;
    case AT_PTR: ud->val.p ? lua_pushlightuserdata(L, ud->val.p) :
      lua_pushnil(L); break;
    default: return luaL_error(L, "wrong type in wrapped value");
    }
    ud++;
  }
  return lua_gettop(L) - 2;
}

static int alien_buffer_new(lua_State *L) {
  const char *s; char *b;
  size_t size;
  if(lua_type(L, 1) == LUA_TSTRING) {
    s = lua_tolstring(L, 1, &size);
    size++;
  } else if(lua_type(L, 1) == LUA_TLIGHTUSERDATA) {
  	void *p = lua_touserdata(L, 1);
	void **ud = lua_newuserdata(L, sizeof(void*));
	*ud = p;
    luaL_getmetatable(L, ALIEN_LBUFFER_META);
    lua_setmetatable(L, -2);
    return 1;
  } else {
    s = NULL;
    size = luaL_optinteger(L, 1, BUFSIZ);
  }
  b = (char *)lua_newuserdata(L, size);
  if(!b)
    return luaL_error(L, "cannot allocate buffer");
  if(s) {
    memcpy(b, s, size - 1);
    b[size - 1] = '\0';
  }
  lua_newtable(L);
  lua_pushnumber(L, size);
  lua_setfield(L, -2, "size");
  lua_setfenv(L, -2);
  luaL_getmetatable(L, ALIEN_BUFFER_META);
  lua_setmetatable(L, -2);
  return 1;
}

static int alien_buffer_tostring(lua_State *L) {
  size_t size;
  ptrdiff_t offset;
  char *b = alien_checkbuffer(L, 1);
  if(lua_gettop(L) < 2 || lua_isnil(L, 2)) {
    size = strlen(b);
    offset = 0;
  } else {
    size = luaL_checkinteger(L, 2);
    offset = luaL_optinteger(L, 3, 1) - 1;
  }
  lua_pushlstring(L, b + offset, size);
  return 1;
}

static int alien_buffer_len(lua_State *L) {
  char *b = alien_checkbuffer(L, 1);
  lua_pushinteger(L, strlen(b));
  return 1;
}

static int alien_buffer_topointer(lua_State *L) {
  char *b = alien_checkbuffer(L, 1);
  ptrdiff_t offset = luaL_optinteger(L, 2, 1) - 1;
  lua_pushlightuserdata(L, b + offset);
  return 1;
}

static int alien_buffer_set(lua_State *L) {
  char *b = alien_checkbuffer(L, 1);
  ptrdiff_t offset = luaL_checkinteger(L, 2) - 1;
  int type = luaL_checkoption(L, 4, "char", alien_typenames);
  switch(type) {
  case AT_SHORT: *((short*)(&b[offset])) = (short)lua_tonumber(L, 3); break;
  case AT_INT: *((int*)(&b[offset])) = (int)lua_tonumber(L, 3); break;
  case AT_LONG: *((long*)(&b[offset])) = (long)lua_tonumber(L, 3); break;
  case AT_USHORT: *((unsigned short*)(&b[offset])) = (unsigned short)lua_tonumber(L, 3); break;
  case AT_UINT: *((unsigned int*)(&b[offset])) = (unsigned int)lua_tonumber(L, 3); break;
  case AT_ULONG: *((unsigned long*)(&b[offset])) = (unsigned long)lua_tonumber(L, 3); break;
  case AT_BYTE: b[offset] = (signed char)lua_tointeger(L, 3); break;
  case AT_CHAR: b[offset] = (char)lua_tointeger(L, 3); break;
  case AT_FLOAT: *((float*)(&b[offset])) = (float)lua_tonumber(L, 3); break;
  case AT_DOUBLE: *((double*)(&b[offset])) = (double)lua_tonumber(L, 3); break;
  case AT_PTR: {
        if(lua_isnil(L, 3) || lua_isuserdata(L, 3)) {
          *((void**)(&b[offset])) =
              (lua_isnil(L, 3) ? NULL : lua_touserdata(L, 3));
          break;
        }
      }
  case AT_STRING: {
       const char *s;
       size_t size;
       s = lua_tolstring(L, 3, &size);
       memcpy(*((char**)(&b[offset])), s, size + 1);
       break;
      }
  case AT_CALLBACK: *((void**)(&b[offset])) = (alien_Function *)alien_checkfunction(L, 3)->fn; break;
  default:
    return luaL_error(L, "alien: unknown type in buffer:put");
  }
  return 0;
}

static int alien_buffer_get(lua_State *L) {
  static const void* funcs[] = {&alien_buffer_tostring,
                                &alien_buffer_topointer,
                                &alien_buffer_len,
                                &alien_buffer_get,
                                &alien_buffer_set};
  static const char *const funcnames[] = { "tostring", "topointer", "len", "get", "set", NULL };
  char *b = alien_checkbuffer(L, 1);
  if(lua_type(L, 2) == LUA_TSTRING) {
    lua_getfenv(L, 1);
    if(!lua_isnil(L, -1))
      lua_getfield(L, -1, lua_tostring(L, 2));
    if(lua_isnil(L, -1))
      lua_pushcfunction(L,
                        (lua_CFunction)funcs[luaL_checkoption(L, 2, "tostring", funcnames)]);
  } else {
    void *p;
    ptrdiff_t offset = luaL_checkinteger(L, 2) - 1;
    int type = luaL_checkoption(L, 3, "char", alien_typenames);
    switch(type) {
    case AT_SHORT: lua_pushnumber(L, *((short*)(&b[offset]))); break;
    case AT_INT: lua_pushnumber(L, *((int*)(&b[offset]))); break;
    case AT_LONG: lua_pushnumber(L, *((long*)(&b[offset]))); break;
    case AT_USHORT: lua_pushnumber(L, *((unsigned short*)(&b[offset]))); break;
    case AT_UINT: lua_pushnumber(L, *((unsigned int*)(&b[offset]))); break;
    case AT_ULONG: lua_pushnumber(L, *((unsigned long*)(&b[offset]))); break;
    case AT_BYTE: lua_pushnumber(L, (signed char)b[offset]); break;
    case AT_CHAR: lua_pushnumber(L, b[offset]); break;
    case AT_FLOAT: lua_pushnumber(L, *((float*)(&b[offset]))); break;
    case AT_DOUBLE: lua_pushnumber(L, *((double*)(&b[offset]))); break;
    case AT_STRING:
      p = *((void**)&b[offset]);
      if(p) lua_pushstring(L, (const char *)p); else lua_pushnil(L);
      break;
    case AT_CALLBACK:
      p = *((void**)&b[offset]);
      p ? alien_makefunction(L, NULL, p, NULL) : lua_pushnil(L);
      break;
    case AT_PTR:
      p = *((void**)&b[offset]);
      p ? lua_pushlightuserdata(L, p) : lua_pushnil(L);
      break;
    default:
      return luaL_error(L, "alien: unknown type in buffer:get");
    }
  }
  return 1;
}

#define alien_udata2x_head(name, type, ptrtype) \
  static int alien_udata2 ## name(lua_State *L) { \
    type *ud; \
    size_t size; \
    if(lua_isnil(L, 1)) { \
      lua_pushnil(L); \
      return 1; \
    } \
    luaL_checktype(L, 1, LUA_TLIGHTUSERDATA); \
    ud = (ptrtype)lua_touserdata(L, 1); \
    if(lua_gettop(L) >= 2 && !lua_isnil(L, 2)) \
      size = luaL_checkinteger(L, 2); \
    else

#define alien_udata2x(name, type) \
  alien_udata2x_head(name, type, type *) \
      size = 1; \
    { \
      size_t i; \
      for (i = 0; i < size; i++) \
        lua_pushnumber(L, ud[i]); \
    } \
    return size; \
  }

/* Define alien_udata2str as a special case */
alien_udata2x_head(str, char, char *)
    size = strlen(ud);
  lua_pushlstring(L, ud, size);
  return 1;
}

alien_udata2x(char, char)
alien_udata2x(short, short)
alien_udata2x(ushort, unsigned short)
alien_udata2x(int, int)
alien_udata2x(uint, unsigned int)
alien_udata2x(long, long)
alien_udata2x(ulong, unsigned long)
alien_udata2x(float, float)
alien_udata2x(double, double)

static int alien_isnull(lua_State *L) {
  luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
  lua_pushboolean(L, lua_touserdata(L, 1) == NULL);
  return 1;
}


/* Expose existing APIs for convenience */

static int alien_table_new(lua_State *L) {
  int narray = luaL_optint(L, 1, 0);
  int nhash = luaL_optint(L, 2, 0);
  lua_createtable(L, narray, nhash);
  return 1;
}

static int alien_errno(lua_State *L) {
  lua_pushnumber(L, errno);
  return 1;
}

static int alien_memmove(lua_State *L) {
  void* src;
  size_t size;
  void *dst = lua_touserdata(L, 1);
  if(!dst)
    return luaL_typerror(L, 1, "userdata");
  if (!(lua_isuserdata(L, 2) || lua_isstring(L, 2)))
    return luaL_typerror(L, 2, "string or userdata");
  if (lua_isuserdata(L, 2)) {
    src = lua_touserdata(L, 2);
    size = luaL_checkinteger(L, 3);
  } else {
    src = (void*)lua_tolstring(L, 2, &size);
    size = luaL_optinteger(L, 3, size);
  }
  if (size > 0)
    memmove(dst, src, size);
  return 0;
}

static int alien_memset(lua_State *L) {
  int c;
  size_t n;
  void *dst = lua_touserdata(L, 1);
  if(!dst)
    return luaL_typerror(L, 1, "userdata");
  c = luaL_checkinteger(L, 2);
  n = luaL_checkinteger(L, 3);
  memset(dst, c, n);
  return 0;
}


static const luaL_Reg alienlib[] = {
  {"load", alien_load},
  {"align", alien_align},
  {"tag", alien_register},
  {"wrap", alien_wrap},
  {"rewrap", alien_rewrap},
  {"unwrap", alien_unwrap},
  {"tostring", alien_udata2str},
  {"isnull", alien_isnull},
  {"sizeof", alien_sizeof},
  {"todouble", alien_udata2double},
  {"toint", alien_udata2int},
  {"tolong", alien_udata2long},
  {"touint", alien_udata2uint},
  {"toulong", alien_udata2ulong},
  {"tofloat", alien_udata2float},
  {"toshort", alien_udata2short},
  {"toushort", alien_udata2ushort},
  {"tochar", alien_udata2char},
  {"buffer", alien_buffer_new},
  {"callback", alien_callback_new},
  {"funcptr", alien_function_new},
  {"table", alien_table_new},
  {"errno", alien_errno},
  {"memmove", alien_memmove },
  {"memcpy", alien_memmove }, /* For backwards compatibility only; deprecated */
  {"memset", alien_memset },
  {NULL, NULL},
};

int luaopen_alien_core(lua_State *L) {
  alien_Library *al;

  /* Library metatable */
  luaL_newmetatable(L, ALIEN_LIBRARY_META);
  lua_pushliteral(L, "__gc");
  lua_pushcfunction(L, alien_library_gc);
  lua_settable(L, -3);
  lua_pushliteral(L, "__tostring");
  lua_pushcfunction(L, alien_library_tostring);
  lua_settable(L, -3);
  lua_pushliteral(L, "__index");
  lua_pushcfunction(L, alien_library_get);
  lua_settable(L, -3);
  lua_pop(L, 1);

  /* Function metatable */
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
  lua_pushliteral(L, "__gc");
  lua_pushcfunction(L, alien_function_gc);
  lua_settable(L, -3);
  lua_pushliteral(L, "__tostring");
  lua_pushcfunction(L, alien_function_tostring);
  lua_settable(L, -3);
  lua_pop(L, 1);

  /* Buffer metatable */
  luaL_newmetatable(L, ALIEN_BUFFER_META);
  lua_pushliteral(L, "__index");
  lua_pushcfunction(L, alien_buffer_get);
  lua_settable(L, -3);
  lua_pushliteral(L, "__newindex");
  lua_pushcfunction(L, alien_buffer_set);
  lua_settable(L, -3);
  lua_pushliteral(L, "__tostring");
  lua_pushcfunction(L, alien_buffer_tostring);
  lua_settable(L, -3);
  lua_pop(L, 1);
  luaL_newmetatable(L, ALIEN_LBUFFER_META);
  lua_pushliteral(L, "__index");
  lua_pushcfunction(L, alien_buffer_get);
  lua_settable(L, -3);
  lua_pushliteral(L, "__newindex");
  lua_pushcfunction(L, alien_buffer_set);
  lua_settable(L, -3);
  lua_pushliteral(L, "__tostring");
  lua_pushcfunction(L, alien_buffer_tostring);
  lua_settable(L, -3);
  lua_pop(L, 1);

  /* Register top-level table */
  lua_getglobal(L, "alien");
  if(lua_isnil(L, -1)) {
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setglobal(L, "alien");
  }
  lua_newtable(L);
  lua_pushvalue(L, -1);
  lua_setfield(L, -3, "core");

  /* Register main library */
  luaL_register (L, NULL, alienlib);
  lua_pushliteral(L, PLATFORM);
  lua_setfield(L, -2, "platform");
  al = (alien_Library *)lua_newuserdata(L, sizeof(alien_Library));
  al->lib = NULL;
  al->name = "default";
  luaL_getmetatable(L, ALIEN_LIBRARY_META);
  lua_setmetatable(L, -2);
  lua_setfield(L, -2, "default");
  return 1;
}
