################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/opt/arduino/arduino-1.0.6/libraries/SPI/SPI.cpp 

OBJS += \
./SPI/SPI.o 

CPP_DEPS += \
./SPI/SPI.d 


# Each subdirectory must supply rules for building sources it contributes
SPI/SPI.o: /opt/arduino/arduino-1.0.6/libraries/SPI/SPI.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/opt/arduino/arduino-1.0.6/hardware/arduino/cores/arduino" -I"/opt/arduino/arduino-1.0.6/hardware/arduino/variants/standard" -I"/home/ddv/git/picavet/arduino/PicavetFirmWare" -I"/opt/arduino/arduino-1.0.6/libraries/Regexp" -I"/opt/arduino/arduino-1.0.6/libraries/Adafruit_CC3000" -I"/opt/arduino/arduino-1.0.6/libraries/SPI" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=106 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


