
pcall(require, "luarocks.require")
require "alien"
require "alien.struct"

local dll = alien.alientest

do
  local f = dll._testfunc_i_bhilfd
  f:types("int", "byte", "short", "int", "int",  "float", "double")
  local result = f(string.byte("x"), 1, 3, 4, 5, 6)
  assert(result == 139)
end

do
  local f = dll._testfunc_p_p
  f:types("pointer", "ref int")
  local result, copy = f(42)
  assert(type(result) == "userdata")
  assert(copy == 42)
end

do
  local f = dll._testfunc_callback_i_if
  f:types("int", "int", "callback")
  local args = {}
  local expected = {262144, 131072, 65536, 32768, 16384, 8192, 4096, 2048,
                    1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1}
  local function callback(v)
    table.insert(args, v)
  end
  local cb = alien.callback(callback, "int", "int")
  f(2 ^ 18, cb)
  assert(#args == #expected)
  for i, v in ipairs(args) do assert(args[i] == expected[i]) end
end

do
  local f = dll._testfunc_callback_i_if
  f:types("int", "int", "callback")
  local function callback(value)
    return value
  end
  local cb = alien.callback(callback, "int", "int")
  local result = f(-10, cb)
  assert(result == -18)
end

do
  local integrate = dll.integrate
  integrate:types("double", "double", "double", "callback", "long")
  local function func(x)
    return x ^ 2
  end
  local result = integrate(0, 1, alien.callback(func, "double", "double"), 10)
  local diff = math.abs(result - 1/3)
  assert(diff < 0.01)
end

do
  dll.tf_b:types("byte", "byte")
  assert(dll.tf_b(-126) == -42)
end

do
  dll.tf_bb:types("byte", "byte", "byte")
  assert(dll.tf_bb(0, -126) == -42)
end

do
  dll.tf_B:types("char", "char")
  assert(dll.tf_B(255) == 85)
end

do
  dll.tf_bB:types("char", "byte", "char")
  assert(dll.tf_bB(0, 255) == 85)
end

do
  dll.tf_h:types("short", "short")
  assert(dll.tf_h(-32766) == -10922)
end

do
  dll.tf_bh:types("short", "byte", "short")
  assert(dll.tf_bh(0, -32766) == -10922)
end

do
  dll.tf_i:types("int", "int")
  assert(dll.tf_i(-2147483646) ==  -715827882)
end

do
  dll.tf_bi:types("int", "byte", "int")
  assert(dll.tf_bi(0, -2147483646) ==  -715827882)
end

do
  dll.tf_l:types("long", "long")
  assert(dll.tf_l(-2147483646) ==  -715827882)
end

do
  dll.tf_bl:types("long", "byte", "long")
  assert(dll.tf_bl(0, -2147483646) ==  -715827882)
end

do
  dll.tf_f:types("float", "float")
  assert(dll.tf_f(-42) == -14)
end

do
  dll.tf_bf:types("float", "byte", "float")
  assert(dll.tf_bf(0, -42) == -14)
end

do
  dll.tf_d:types("double", "double")
  assert(dll.tf_d(-42) == -14)
end

do
  dll.tf_bd:types("double", "byte", "double")
  assert(dll.tf_bd(0, -42) == -14)
end

do
  dll.tv_i:types("void", "int")
  assert(dll.tv_i(42) == nil)
  assert(dll.tv_i(-42) == nil)
end

do
  local strchr = dll.my_strchr
  strchr:types("pointer", "string", "char")
  assert(alien.tostring(strchr("abcdefghi", string.byte("b"))) == "bcdefghi") 
  assert(strchr("abcdefghi", string.byte("x")) == nil)
end

do
  local strtok = dll.my_strtok
  strtok:types("pointer", "string", "ref char")
  local buf = alien.buffer("a\nb\nc")
  local lb = string.byte("\n")
  assert(alien.tostring((strtok(buf, lb))) == "a")
  assert(alien.tostring((strtok(nil, lb))) == "b")
  assert(alien.tostring((strtok(nil, lb))) == "c")
  assert(alien.tostring((strtok(nil, lb))) == nil)
end

do
  local f = dll._testfunc_v
  f:types("void", "int", "int", "ref int")
  local r1, r2 = f(1, 2, 0)
  assert(r1 == nil)
  assert(r2 == 3)
end

do
  local f = dll._testfunc_i_bhilfd
  f:types("int", "byte", "short", "int", "int", "float", "double")
  local result = f(1, 2, 3, 4, 5, 6)
  assert(result == 21)
  local result = f(-1, -2, -3, -4, -5, -6)
  assert(result == -21)
  f:types("short", "byte", "short", "int", "int", "float", "double")
  local result = f(1, 2, 3, 4, 5, 6)
  assert(result == 21)
  local result = f(1, 2, 3, 0x10004, 5.0, 6.0)
  assert(result == 21)
end

do
  local f = dll._testfunc_f_bhilfd
  f:types("float", "byte", "short", "int", "int", "float", "double")
  local result = f(1, 2, 3, 4, 5.0, 6.0)
  assert(result == 21)
  local result = f(-1, -2, -3, -4, -5, -6)
  assert(result == -21)
end

do
  local f = dll._testfunc_d_bhilfd
  f:types("double", "byte", "short", "int", "int", "float", "double")
  local result = f(1, 2, 3, 4, 5.0, 6.0)
  assert(result == 21)
  local result = f(-1, -2, -3, -4, -5, -6)
  assert(result == -21)
end

do
  local f = dll._testfunc_p_p
  f:types("pointer", "string")
  local result = f("123")
  assert(alien.tostring(result) == "123")
  local result = f(nil)
  assert(result == nil)
end

do
  local f = dll.my_sqrt
  f:types("double", "double")
  assert(f(4) == 2)
  assert(f(2) == math.sqrt(2))
end

do
  local function sort(a, b)
    return a - b
  end
  local compare = alien.callback(sort, "int", "ref char", "ref char")
  local qsort = dll.my_qsort
  qsort:types("void", "pointer", "int", "int", "callback")
  local chars = alien.buffer("spam, spam, and spam")
  qsort(chars, chars:len(), alien.sizeof("char"), compare)
  assert(chars:tostring() == "   ,,aaaadmmmnpppsss")
end
