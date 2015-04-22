--
-- error 404
--
local arg={...}
client=arg[1]
query=arg[2]

if(client~=nil) then
     client:send('HTTP/1.1 404 Not Found\n\n')
     client:send('<!DOCTYPE HTML>\n')
     client:send('<html>\n')
     client:send('<head><meta  content="text/html"; charset=utf-8">\n')
     client:send('<h1> 404 Not Found </h1>');
     client:send('</html>\n')
end

