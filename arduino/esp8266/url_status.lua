--
-- /status index.html
--
local arg={...}
client=arg[1]
query=arg[2]

if(client~=nil) then

     i2c_responce=i2c_send_command("TTTT")
     
     client:send('HTTP/1.1 200 OK\n\n')
     client:send('<!DOCTYPE HTML>\n')
     client:send('<html>\n')
     client:send('<head>')
     client:send('<meta  content="text/html"; charset=utf-8">')
     client:send('<meta name="viewport" content="width=device-width">')     
     client:send('</head>')
     client:send('<h1> Picavet status: </h1>')
     if(i2c_responce~=nil) then
     client:send('<h2> I2C Responce:'..i2c_responce..' </h2>')
     
     end
     client:send('</html>\n')
end