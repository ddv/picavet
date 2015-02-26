################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/utility/cc3000_common.cpp \
E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/utility/debug.cpp \
E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/utility/evnt_handler.cpp \
E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/utility/hci.cpp \
E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/utility/netapp.cpp \
E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/utility/nvmem.cpp \
E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/utility/security.cpp \
E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/utility/sntp.cpp \
E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/utility/socket.cpp \
E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/utility/wlan.cpp 

OBJS += \
./Adafruit_CC3000/utility/cc3000_common.o \
./Adafruit_CC3000/utility/debug.o \
./Adafruit_CC3000/utility/evnt_handler.o \
./Adafruit_CC3000/utility/hci.o \
./Adafruit_CC3000/utility/netapp.o \
./Adafruit_CC3000/utility/nvmem.o \
./Adafruit_CC3000/utility/security.o \
./Adafruit_CC3000/utility/sntp.o \
./Adafruit_CC3000/utility/socket.o \
./Adafruit_CC3000/utility/wlan.o 

CPP_DEPS += \
./Adafruit_CC3000/utility/cc3000_common.d \
./Adafruit_CC3000/utility/debug.d \
./Adafruit_CC3000/utility/evnt_handler.d \
./Adafruit_CC3000/utility/hci.d \
./Adafruit_CC3000/utility/netapp.d \
./Adafruit_CC3000/utility/nvmem.d \
./Adafruit_CC3000/utility/security.d \
./Adafruit_CC3000/utility/sntp.d \
./Adafruit_CC3000/utility/socket.d \
./Adafruit_CC3000/utility/wlan.d 


# Each subdirectory must supply rules for building sources it contributes
Adafruit_CC3000/utility/cc3000_common.o: E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/utility/cc3000_common.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\cores\arduino" -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\variants\standard" -I"C:\Users\derenok_dv\git\picavet\arduino\PicavetFirmWare" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Regexp" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Adafruit_CC3000" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\SPI" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105-r2 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

Adafruit_CC3000/utility/debug.o: E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/utility/debug.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\cores\arduino" -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\variants\standard" -I"C:\Users\derenok_dv\git\picavet\arduino\PicavetFirmWare" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Regexp" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Adafruit_CC3000" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\SPI" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105-r2 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

Adafruit_CC3000/utility/evnt_handler.o: E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/utility/evnt_handler.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\cores\arduino" -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\variants\standard" -I"C:\Users\derenok_dv\git\picavet\arduino\PicavetFirmWare" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Regexp" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Adafruit_CC3000" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\SPI" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105-r2 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

Adafruit_CC3000/utility/hci.o: E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/utility/hci.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\cores\arduino" -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\variants\standard" -I"C:\Users\derenok_dv\git\picavet\arduino\PicavetFirmWare" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Regexp" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Adafruit_CC3000" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\SPI" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105-r2 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

Adafruit_CC3000/utility/netapp.o: E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/utility/netapp.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\cores\arduino" -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\variants\standard" -I"C:\Users\derenok_dv\git\picavet\arduino\PicavetFirmWare" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Regexp" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Adafruit_CC3000" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\SPI" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105-r2 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

Adafruit_CC3000/utility/nvmem.o: E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/utility/nvmem.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\cores\arduino" -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\variants\standard" -I"C:\Users\derenok_dv\git\picavet\arduino\PicavetFirmWare" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Regexp" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Adafruit_CC3000" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\SPI" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105-r2 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

Adafruit_CC3000/utility/security.o: E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/utility/security.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\cores\arduino" -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\variants\standard" -I"C:\Users\derenok_dv\git\picavet\arduino\PicavetFirmWare" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Regexp" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Adafruit_CC3000" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\SPI" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105-r2 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

Adafruit_CC3000/utility/sntp.o: E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/utility/sntp.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\cores\arduino" -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\variants\standard" -I"C:\Users\derenok_dv\git\picavet\arduino\PicavetFirmWare" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Regexp" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Adafruit_CC3000" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\SPI" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105-r2 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

Adafruit_CC3000/utility/socket.o: E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/utility/socket.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\cores\arduino" -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\variants\standard" -I"C:\Users\derenok_dv\git\picavet\arduino\PicavetFirmWare" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Regexp" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Adafruit_CC3000" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\SPI" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105-r2 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

Adafruit_CC3000/utility/wlan.o: E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/utility/wlan.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\cores\arduino" -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\variants\standard" -I"C:\Users\derenok_dv\git\picavet\arduino\PicavetFirmWare" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Regexp" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Adafruit_CC3000" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\SPI" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105-r2 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


