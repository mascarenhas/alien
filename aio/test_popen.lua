
require "aio"

local f = aio.popen("tail -f /var/log/apache2/error.log", "r")

for line in f:lines() do
  aio.write(line)
end
