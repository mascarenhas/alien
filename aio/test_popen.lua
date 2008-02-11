
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
  thread.yield()
  if i == 100000 then
    print("yeah!")
    i = 0
  else
    i = i + 1
  end
end
