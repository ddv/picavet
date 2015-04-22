--
-- / index.html
--
local arg={...}
client=arg[1]
query=arg[2]

if(client~=nil) then
     client:send('HTTP/1.1 200 OK\n\n')
     client:send('<!DOCTYPE HTML>\n')
     client:send('<html>\n')
     client:send('<head>')
     client:send('<meta  content="text/html"; charset=utf-8">')
     client:send('<meta name="viewport" content="width=device-width">')     
     client:send('</head>')
     client:send('<h1> Picavet </h1>')
     client:send('<a href="/status"> status: </a><br>')
     client:send('</html>\n')
end
