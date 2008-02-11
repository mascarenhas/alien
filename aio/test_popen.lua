
require "aio"
require "thread"

local function tail()
  local f = aio.popen("tail -f /var/log/apache2/error.log", "r")
  local lines = f:lines()
  local line = lines()
  while line do
    aio.write(line)
    line = lines()
  end
end

thread.new(tail)

local i = 0

while true do
  thread.yield("timer", 2000)
  print("yeah!")
end
