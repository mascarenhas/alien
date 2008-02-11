
require "alien"

module(..., package.seeall)

local event = alien.event

event.event_init:types("pointer")
event.event_set:types("void", "pointer", "int", "int", "callback", "pointer")
event.event_add:types("int", "pointer", "pointer")
event.event_dispatch:types("int")
event.event_once:types("int", "int", "int", "callback", "pointer", "pointer")
event.event_loop:types("int", "int")

event.event_init()

local EV_SIZE = 84 -- MAGIC!!!!!
local EV_READ = 0x02
local EV_WRITE = 0x04
local EVLOOP_NONBLOCK = 0x02

local current_thread = nil -- nil is the main thread

local waiting_threads = {
  [EV_READ] = {},
  [EV_WRITE] = {},
  idle = {}
}

local next_thread

local function handle_io(fd, ev_code, arg)
  local queue = waiting_threads[ev_code][fd]
  if queue then
    next_thread = queue[#queue]
    queue[#queue] = nil
  else
    error("no thread waiting for event " .. ev_code .. " on fd " .. fd)
  end
end

local handle_io_cb = alien.new_callback(handle_io, "void", "int", "int",
					  "pointer")

function yield(tag, ev, fd)
  if tag == "io" then
    local ev_code
    if ev == "read" then ev_code = EV_READ else ev_code = EV_WRITE end
    event.event_once(fd, ev_code, handle_io_cb, nil, nil)
    if current_thread then -- in child
      local child = current_thread
      current_thread = nil
      local queue = waiting_threads[ev_code][fd]
      if not queue then 
	queue = {}
	waiting_threads[ev_code][fd] = queue
      end
      table.insert(queue, 1, child)
      return coroutine.yield("yield")
    else
      local queue = waiting_threads[ev_code][fd]
      if not queue then 
	queue = {}
	waiting_threads[ev_code][fd] = queue
      end
      table.insert(queue, 1, "main")
      return event_loop()
    end
  else
    if current_thread then
      local child = current_thread
      table.insert(waiting_threads.idle, 1, child)
      current_thread = nil
      return coroutine.yield("yield")
    else
      table.insert(waiting_threads.idle, 1, "main")
      return event_loop()
    end
  end
end

function new(func)
  if current_thread then
    local child = current_thread
    current_thread = nil
    return coroutine.yield("new", child, func)
  else
    local t = coroutine.wrap(func)
    table.insert(waiting_threads.idle, 1, t)
    return event_loop()
  end
end

function handle(child)
  if child == "main" then return end
  local op, child, arg = child()
  if op == "new" then
    table.insert(waiting_threads.idle, 1, child)
    return new(arg)
  elseif op == "yield" then
    return event_loop()
  end
end

function event_loop()
  event.event_loop(EVLOOP_NONBLOCK)
  local next = next_thread
  next_thread = nil
  if not next then
    next = waiting_threads.idle[#waiting_threads.idle]
    waiting_threads.idle[#waiting_threads.idle] = nil
  end
  if next == "main" then current_thread = nil else current_thread = next end
  return handle(next or "main")
end
