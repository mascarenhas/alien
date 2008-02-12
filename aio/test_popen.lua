
require "aio"
require "thread"

local function tail(file)
  local f = aio.popen("tail -f " .. file)
  local lines = f:lines()
  local line = lines()
  while line do
    aio.write(line)
    line = lines()
  end
end

thread.new(function () return tail("foo.txt") end)
thread.new(function () return tail("bar.txt") end)

local i = 0

while true do
  thread.yield("timer", 2000)
--  thread.yield()
--  if i == 100000 then
  print("yeah!")
--  i = 0
--  else
--  i = i + 1
--  end
end
