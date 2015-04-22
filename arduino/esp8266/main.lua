print ("Running main")
-- init I2C
dofile("i2c.lua")
collectgarbage();
-- init WEB Server
dofile("httpserver.lua")
collectgarbage();
