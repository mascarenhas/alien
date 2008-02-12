
require "alien"
require "alien.struct"

module(..., package.seeall)

local event = alien.event

event.event_init:types("pointer")
event.event_set:types("void", "pointer", "int", "int", "callback", "pointer")
event.event_add:types("int", "pointer", "pointer")
event.event_dispatch:types("int")
event.event_once:types("int", "int", "int", "callback", "pointer", "string")
event.event_loop:types("int", "int")

event.event_init()

require("event_constants")

local events = {
  read = EV_READ,
  write = EV_WRITE,
  timer = EV_TIMEOUT
}

local current_thread = nil -- nil is the main thread

local waiting_threads = {
  [EV_READ] = {},
  [EV_WRITE] = {},
  [EV_TIMEOUT] = {},
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
  return 0
end

local handle_io_cb = alien.new_callback(handle_io, "void", "int", "int",
					  "pointer")

local function queue_event(thr, ev_code, fd)
  local queue
  if fd then
    queue = waiting_threads[ev_code][fd]
  else
    queue = waiting_threads[ev_code]
  end
  if not queue then 
    queue = {}
    waiting_threads[ev_code][fd] = queue
  end
  table.insert(queue, 1, thr)
end

function yield(tag, ev, fd, timeout)
  local ev_code = events[ev]
  if tag == "io" then
    local time
    if timeout then
      time = alien.struct.pack("ll", math.floor(timeout / 1000),
			       (timeout % 1000) * 1000)
    end
    event.event_once(fd, ev_code, handle_io_cb, nil, time)
  elseif tag == "timer" then
    fd = -1
    ev_code = events["timer"]
    local time = alien.struct.pack("ll", math.floor(ev / 1000),
				   (ev % 1000) * 1000)
    event.event_once(fd, ev_code, handle_io_cb, nil, time)
  end
  queue_event(current_thread or "main", ev_code or "idle", fd)
  if current_thread then 
    current_thread = nil
    return coroutine.yield(tag)
  else
    return event_loop()
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
  end
end

function handle(child)
  if child == "main" then return end
  local op, child, arg = child()
  if op == "new" then
    table.insert(waiting_threads.idle, 1, child)
    return new(arg)
  else
    return event_loop()
  end
end

function event_loop(block)
  if block then
    event.event_loop(EVLOOP_ONCE)
  else
    event.event_loop(EVLOOP_NONBLOCK)
  end
  local next = next_thread
  next_thread = nil
  if not next then
    next = waiting_threads.idle[#waiting_threads.idle]
    waiting_threads.idle[#waiting_threads.idle] = nil
  end
  if next == "main" then current_thread = nil else current_thread = next end
  if next then
    return handle(next)
  else
    return event_loop(true)
  end
end
