package = "rmrf"
version = "0.1.0-1"
local v = version:gsub("%-%d", "")
source = {
  url = "http://github.com/xpol/rmrf.lua",
  tag="v"..v
}
description={
   summary = "A `mkdir -p` module for Lua.",
   detailed = "A `mkdir -p` module for Lua works on Windows, Linux and Mac OS.",
   homepage = "http://github.com/xpol/rmrf.lua",
   license = "MIT"
}
dependencies = {
  "lua >= 5.1"
}

build = {
	type="builtin",
	modules={
		rmrf={"src/rmrf.c", "src/lua-rmrf.c"}
	}
}
