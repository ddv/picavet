--
-- I2C module
--
local id=0
local slave_id=0x77
local sda = 3
local scl = 4

-- init
print("Init I2C...")
i2c.setup(id, sda, scl, i2c.SLOW)
print("OK")

     
-- I2C chat
function i2c_send_command(data_transmit)
     dev_addr=slave_id
     i2c.start(id)
     i2c.address(id, dev_addr ,i2c.TRANSMITTER)
     i2c.write(id,data_transmit)
     i2c.stop(id)
     i2c.start(id)
     i2c.address(id, dev_addr,i2c.RECEIVER)
     c=i2c.read(id,30)
     i2c.stop(id)
     return c
end

print("I2C responce["..i2c_send_command("123").."]")
