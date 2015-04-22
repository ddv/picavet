print("Running http server...")

-- 30s time out for a inactive client
srv=net.createServer(net.TCP,30)
--srv=net.createConnection(net.TCP,30)

print("http server started")

srv:listen(80,function(conn)
     conn:on("receive", function(client,request)
          --вызываем обработчик
          assert(loadfile("http_r_handler.lua"))(client,request)
          client:close();

          collectgarbage();
          
     end)
end)


