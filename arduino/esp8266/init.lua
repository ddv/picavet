print("init wifi...")
wifi.setmode(wifi.SOFTAP);
wifi.ap.config({ssid="test",pwd="12345678"});
print("IP:"..wifi.ap.getip())
mainfile="main.lua"

print("init...")

tmr.alarm(0, 2000, 0,
     function()
          print("Run main " .. mainfile)
          dofile(mainfile)
          collectgarbage();
     end
)



