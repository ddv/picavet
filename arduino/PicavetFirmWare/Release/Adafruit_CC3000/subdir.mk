################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/Adafruit_CC3000.cpp \
E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/Adafruit_CC3000_Server.cpp \
E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/ccspi.cpp 

OBJS += \
./Adafruit_CC3000/Adafruit_CC3000.o \
./Adafruit_CC3000/Adafruit_CC3000_Server.o \
./Adafruit_CC3000/ccspi.o 

CPP_DEPS += \
./Adafruit_CC3000/Adafruit_CC3000.d \
./Adafruit_CC3000/Adafruit_CC3000_Server.d \
./Adafruit_CC3000/ccspi.d 


# Each subdirectory must supply rules for building sources it contributes
Adafruit_CC3000/Adafruit_CC3000.o: E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/Adafruit_CC3000.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\cores\arduino" -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\variants\standard" -I"C:\Users\derenok_dv\git\picavet\arduino\PicavetFirmWare" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Regexp" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Adafruit_CC3000" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\SPI" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105-r2 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

Adafruit_CC3000/Adafruit_CC3000_Server.o: E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/Adafruit_CC3000_Server.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\cores\arduino" -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\variants\standard" -I"C:\Users\derenok_dv\git\picavet\arduino\PicavetFirmWare" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Regexp" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Adafruit_CC3000" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\SPI" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105-r2 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

Adafruit_CC3000/ccspi.o: E:/arduino/arduino-1.0.5-r2-windows/libraries/Adafruit_CC3000/ccspi.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\cores\arduino" -I"E:\arduino\arduino-1.0.5-r2-windows\hardware\arduino\variants\standard" -I"C:\Users\derenok_dv\git\picavet\arduino\PicavetFirmWare" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Regexp" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\Adafruit_CC3000" -I"E:\arduino\arduino-1.0.5-r2-windows\libraries\SPI" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105-r2 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


