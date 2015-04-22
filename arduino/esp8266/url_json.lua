--
-- /json
--
local arg={...}
client=arg[1]
query=arg[2]

client:send('HTTP/1.1 200 OK\n\n')
client:send('<!DOCTYPE HTML>\n')
client:send('<html>\n')
client:send('<head><meta  content="plain/text"; charset=utf-8">\n')
client:send("<h1>  JSON </h1>");
--client:send("<h1> method=" .. method .. "</h1>");
--client:send("<h1> method=" .. method .. "</h1>");
--client:send("<h1> path=" .. path .. "</h1>");
          
if(query.pin~=nil)then 
     client:send("<h1> pin=" .. query.pin .. "</h1>");
end
