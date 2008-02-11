
require "aio"
require "thread"

local function tail(file)
  local f = aio.popen("tail -f " .. file, "r")
  local lines = f:lines()
  local line = lines()
  while line do
    aio.write(line)
    line = lines()
  end
end

thread.new(function () return tail("/var/log/apache2/error.log") end)
thread.new(function () return tail("/var/log/apache2/access.log") end)

local i = 0

while true do
  thread.yield("timer", 2000)
  print("yeah!")
end
