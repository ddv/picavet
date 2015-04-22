local arg={...}
print("starting http request handler")

client=arg[1]
request=arg[2]

local buf = "";
local _, _, method, path, vars = string.find(request, "([A-Z]+) (.+)%?(.+) HTTP");
if(method == nil)then _, _, method, path = string.find(request, "([A-Z]+) (.+) HTTP"); end
local _GET = {}
if (vars ~= nil)then for k, v in string.gmatch(vars, "(%w+)=(%w+)&*") do _GET[k] = v end end 

if(_GET.pin~=nil)then 
     print("\npin=" .._GET.pin)
end

print("\nMethod: "..method);
print("Path: "..path);
          
-- send data
--client:send("Content-type: text/html\n\n");
--client:send("Content-type: plain/text\n\n");


-- repalce "/"
file="url_"..string.gsub(path, "/", "")..".lua"
print("File:"..file);

local result
local func, errorMsg = loadfile(file)

if func then
--    result = func()
    assert(loadfile(file))(client,_GET)
else
    print(errorMsg)
    assert(loadfile("url_error_404.lua"))(client,_GET)
end
--assert(loadfile(file))(client,_GET)

          