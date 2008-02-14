

local core = require "alien.core"
local io = require "io"

local pairs = pairs
local setmetatable = setmetatable
local error = error
local pcall = pcall

module "alien"

loaded = {}

local load_library, find_library = {}, {}

local function find_library_helper(libname, opt)
  local expr = '/[^() ]*lib' .. libname .. '\.so[^() ]*'
  local cmd = '/sbin/ldconfig ' .. opt .. 
    ' 2>/dev/null | egrep -o "' .. expr .. '"'
  local pipe = io.popen(cmd)
  if pipe then
    local res = pipe:read()
    pipe:close()
    return res and res:match("([^%s]*)")
  end
  return nil
end

function find_library.linux(libname)
  return find_library_helper(libname, "-p")
end

function find_library.bsd(libname)
  return find_library_helper(libname, "-r")
end

function find_library.darwin(libname)
  local ok, lib = pcall(core.load, libname .. ".dylib")
  if ok then return lib end
  ok, lib = pcall(core.load, libname .. ".framework/" .. libname)
  if ok then return lib end
  return nil
end

function load_library_helper(libname, libext)
  if libname:match("/") or libname:match("%" .. libext) then
    return core.load(libname)
  else
    local ok, lib = pcall(core.load, "lib" .. libname .. libext)
    if not ok then
      local name = find_library[core.platform](libname)
      if name then
	lib = core.load(name)
      else
	error("library " .. libname .. " not found")
      end
    end
    return lib
  end
end

function load_library.linux(libname)
  return load_library_helper(libname, ".so")
end

load_library.bsd = load_library.linux

function load_library.darwin(libname)
  return load_library_helper(libname, ".dylib")
end

setmetatable(load_library, { __index = function (t, plat)
					 return core.load
				       end } )

function load_library.windows(libname)
  return core.load(libname)
end

setmetatable(loaded, { __index = function (t, libname)
				   local lib = 
				     load_library[core.platform](libname)
				   t[libname] = lib
				   return lib
				 end })

setmetatable(_M, { __index = loaded })

for name, f in pairs(core) do
  _M[name] = f
end

function load(libname)
  return loaded[libname]
end

