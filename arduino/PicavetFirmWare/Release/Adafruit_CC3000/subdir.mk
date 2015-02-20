################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/opt/arduino/arduino-1.0.6/libraries/Adafruit_CC3000/Adafruit_CC3000.cpp \
/opt/arduino/arduino-1.0.6/libraries/Adafruit_CC3000/Adafruit_CC3000_Server.cpp \
/opt/arduino/arduino-1.0.6/libraries/Adafruit_CC3000/ccspi.cpp 

OBJS += \
./Adafruit_CC3000/Adafruit_CC3000.o \
./Adafruit_CC3000/Adafruit_CC3000_Server.o \
./Adafruit_CC3000/ccspi.o 

CPP_DEPS += \
./Adafruit_CC3000/Adafruit_CC3000.d \
./Adafruit_CC3000/Adafruit_CC3000_Server.d \
./Adafruit_CC3000/ccspi.d 


# Each subdirectory must supply rules for building sources it contributes
Adafruit_CC3000/Adafruit_CC3000.o: /opt/arduino/arduino-1.0.6/libraries/Adafruit_CC3000/Adafruit_CC3000.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/opt/arduino/arduino-1.0.6/hardware/arduino/cores/arduino" -I"/opt/arduino/arduino-1.0.6/hardware/arduino/variants/standard" -I"/home/ddv/git/picavet/arduino/PicavetFirmWare" -I"/opt/arduino/arduino-1.0.6/libraries/Regexp" -I"/opt/arduino/arduino-1.0.6/libraries/Adafruit_CC3000" -I"/opt/arduino/arduino-1.0.6/libraries/SPI" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=106 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

Adafruit_CC3000/Adafruit_CC3000_Server.o: /opt/arduino/arduino-1.0.6/libraries/Adafruit_CC3000/Adafruit_CC3000_Server.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/opt/arduino/arduino-1.0.6/hardware/arduino/cores/arduino" -I"/opt/arduino/arduino-1.0.6/hardware/arduino/variants/standard" -I"/home/ddv/git/picavet/arduino/PicavetFirmWare" -I"/opt/arduino/arduino-1.0.6/libraries/Regexp" -I"/opt/arduino/arduino-1.0.6/libraries/Adafruit_CC3000" -I"/opt/arduino/arduino-1.0.6/libraries/SPI" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=106 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

Adafruit_CC3000/ccspi.o: /opt/arduino/arduino-1.0.6/libraries/Adafruit_CC3000/ccspi.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/opt/arduino/arduino-1.0.6/hardware/arduino/cores/arduino" -I"/opt/arduino/arduino-1.0.6/hardware/arduino/variants/standard" -I"/home/ddv/git/picavet/arduino/PicavetFirmWare" -I"/opt/arduino/arduino-1.0.6/libraries/Regexp" -I"/opt/arduino/arduino-1.0.6/libraries/Adafruit_CC3000" -I"/opt/arduino/arduino-1.0.6/libraries/SPI" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=106 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


