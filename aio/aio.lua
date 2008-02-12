
require "alien"
require "bit"
require "thread"

module(..., package.seeall)

local file_meta = alien.new_tag("aio_file")

local libc = alien.default

libc.strerror:types("string", "int")
libc.open:types("int", "string", "int", "int")
libc.close:types("int", "int")
libc.read:types("int", "int", "string", "int")
libc.write:types("int", "int","string", "int")
libc.fdopen:types("pointer", "int", "string")
libc.fgets:types("int", "string", "int", "pointer")
libc.ferror:types("int", "pointer")
libc.strlen:types("int", "string")
libc.fscanf:types("int", "pointer", "string", "ref double")
libc.fcntl:types("int", "int", "int", "int")
libc.popen:types("pointer", "string", "string")
libc.fileno:types("int", "pointer")

local O_ACCMODE = tonumber("0003", 8)
local O_RDONLY = tonumber("00", 8)
local O_WRONLY = tonumber("01", 8)
local O_RDWR = tonumber("02", 8)
local O_CREAT = tonumber("0100", 8)
local O_EXCL = tonumber("0200", 8)
local O_NOCTTY = tonumber("0400", 8)
local O_TRUNC = tonumber("01000", 8)
local O_APPEND = tonumber("02000", 8)
--local O_NONBLOCK = tonumber("04000", 8)
local O_NONBLOCK = 0x0004
local O_SYNC = tonumber("010000", 8)
local O_ASYNC = tonumber("020000", 8)

local F_GETFL = 3
local F_SETFL = 4

local DEFFILEMODE = tonumber("666", 8)

--local EAGAIN = 11
local EAGAIN = 35

local MAXINT = 2^32 - 1

local STDIN, STDOUT, STDERR = 0, 1, 2

local mode2flags = {
  ["r"] = O_RDONLY,
  ["rb"] = O_RDONLY,
  ["r+"] = bit.bor(O_RDWR, O_CREAT),
  ["rb+"] = bit.bor(O_RDWR, O_CREAT),
  ["r+b"] = bit.bor(O_RDWR, O_CREAT),
  ["w"] = bit.bor(O_WRONLY, O_CREAT, O_TRUNC),
  ["wb"] = bit.bor(O_WRONLY, O_CREAT, O_TRUNC),
  ["a"] = bit.bor(O_WRONLY, O_CREAT, O_APPEND),
  ["ab"] = bit.bor(O_WRONLY, O_CREAT, O_APPEND),
  ["w+"] = bit.bor(O_RDWR, O_CREAT, O_TRUNC),
  ["wb"] = bit.bor(O_RDWR, O_CREAT, O_TRUNC),
  ["w+b"] = bit.bor(O_RDWR, O_CREAT, O_TRUNC),
  ["a+"] = bit.bor(O_RDWR, O_CREAT, O_APPEND),
  ["ab+"] = bit.bor(O_RDWR, O_CREAT, O_APPEND),
  ["a+b"] = bit.bor(O_RDWR, O_CREAT, O_APPEND)
}

local function aio_error(path)
  local en = alien.errno()
  local err = libc.strerror(en)
  if path then
    return nil, string.format("%s: %s", path, err)
  else
    return nil, err
  end
end

function open(path, mode)
  mode = mode or "r"
  local flags = mode2flags[mode]
  flags = bit.bor(flags, O_NONBLOCK)
  fd = libc.open(path, flags, DEFFILEMODE)
  if fd ~= -1 then
    local stream = libc.fdopen(fd, mode)
    local file = alien.wrap("aio_file", fd, stream)
    return file
  else
    return aio_error(path)
  end
end

function close(file)
  local fd = alien.unwrap("aio_file", file)
  local status = libc.close(fd)
  if status ~= -1 then
    return true
  else
    return aio_error()
  end
end

local BUFSIZ = 8192

local function aio_read_bytes(fd, n)
  local buf = alien.new_buffer(math.min(n, BUFSIZ))
  local out = {}
  local r = n
  while n > 0 and r > 0 do
    local size = math.min(n, BUFSIZ)
    r = libc.read(fd, buf, size)
    if r == -1 then
      local en = alien.errno()
      if en == EAGAIN then
	r = 1
	thread.yield("io", "read", fd)
      else
	return nil, libc.strerror(en)
      end
    else
      out[#out + 1] = buf:tostring(r)
      n = n - r
    end
  end
  return table.concat(out)
end

local function aio_read_all(fd)
  return aio_read_bytes(fd, MAXINT)
end

local function aio_read_number(fd, stream)
  local n, out = libc.fscanf(stream, "%lf")
  if n == -1 then
    if libc.ferror(stream) ~= 0 then
      local en = alien.errno()
      if en == EAGAIN then
	thread.yield("io", "read", fd)
	return aio_read_number(stream)
      else
	return nil, libc.strerror(en)
      end
    else
      return nil
    end
  elseif n == 0 then
    return nil
  else
    return out
  end
end

local function aio_read_line(fd, stream)
  local buf = alien.new_buffer(BUFSIZ)
  local again = false
  repeat
    local n = libc.fgets(buf, BUFSIZ, stream)
    if n == 0 then
      if libc.ferror(stream) ~= 0 then
	local en = alien.errno()
	if en == EAGAIN then
	  thread.yield("io", "read", fd)
	  again = true
	else
	  return nil, libc.strerror(en)
	end
      else
	return nil
      end
    else
      local len = libc.strlen(buf)
      local res = buf:tostring(len)
      if not res:sub(#res) == "\n" then
	local next, err = aio_read_line(stream)
	if err then return nil, err end
	return res .. (next or "")
      else
	return res
      end
    end
  until not again
end

local function aio_read_item(fd, stream, what)
  if type(what) == "number" then
    return aio_read_bytes(fd, what)
  elseif what == "*n" then
    return aio_read_number(fd, stream)
  elseif what == "*l" then
    return aio_read_line(fd, stream)
  elseif what == "*a" then
    return aio_read_all(fd)
  else
    error("invalid option")
  end
end

local function aio_read(file, ...)
  local fd, stream = alien.unwrap("aio_file", file)
  local nargs = select("#", ...)
  if nargs == 0 then
    return aio_read_line(fd, stream)
  elseif nargs == 1 then
    return aio_read_item(fd, stream, ...)
  else
    local items = {}
    for i = 1, nargs do
      local what = select(i, ...)
      items[#items + 1] = aio_read_item(fd, stream, what)
    end
    return unpack(items)
  end
end

function read(...)
  return aio_read(stdin, ...)
end

local function aio_write_item(fd, item)
  local s = tostring(item)
  local size = string.len(s)
  local w = libc.write(fd, s, size)
  if w == -1 then
    local en = alien.errno()
    if en == EAGAIN then
      thread.yield("io", "write", fd)
      return aio_write_item(fd, s)
    else
      return false
    end
  else
    return w == size
  end
end

local function aio_write(file, ...)
  local fd = alien.unwrap("aio_file", file)
  local nargs = select("#", ...)
  local status = true
  for i = 1, nargs do
    status = status and aio_write_item(fd, select(i, ...))
  end
  if not status then
    return nil, libc.strerror(alien.errno())
  else
    return true
  end
end

function write(...)
  return aio_write(stdout, ...)
end

function lines(file)
  file = file or stdin
  if type(file) == "string" then
    file = open(file, "r")
  end
  return function ()
	   return file:read("*l")
	 end
end

function popen(cmd, mode)
  mode = mode or "r"
  local stream = libc.popen(cmd, mode)
  if stream then
    local fd = libc.fileno(stream)
    local status = libc.fcntl(fd, F_GETFL, 0)
    status = libc.fcntl(fd, F_SETFL, bit.bor(status, O_NONBLOCK))
    if status ~= -1 then
      return alien.wrap("aio_file", fd, stream)
    end
  end
  return aio_error(cmd)
end

file_meta.__gc = close

file_meta.__index = {
  read = aio_read,
  write = aio_write,
  close = close,
  lines = lines
}

stdin = alien.wrap("aio_file", STDIN, libc.fdopen(STDIN, "r"))
stdout = alien.wrap("aio_file", STDOUT, libc.fdopen(STDOUT, "w"))
stderr = alien.wrap("aio_file", STDERR, libc.fdopen(STDERR, "w"))
