ARDUINO_BASE=/home/clay/arduino-1.8.2/hardware/arduino/avr
ARDUINO_CORE=$(ARDUINO_BASE)/cores/arduino
ARDUINO_EIGHT_ANALOG_INPUTS=$(ARDUINO_BASE)/variants/eightanaloginputs

CC=avr-gcc
CXX=avr-g++

ARDUINO_CFLAGS=-Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 \
	-DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR  \
	-I$(ARDUINO_CORE) -I$(ARDUINO_EIGHT_ANALOG_INPUTS)
CFLAGS=-I../machine $(ARDUINO_CFLAGS)

ARDUINO_CXX_FLAGS=-Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p \
	-DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR  \
	 -I$(ARDUINO_CORE) -I$(ARDUINO_EIGHT_ANALOG_INPUTS)
CXXFLAGS=$(ARDUINO_CXX_FLAGS)

USBPORT=/dev/ttyUSB0
VPATH=../machine:$(ARDUINO_CORE)

CORE_C_SRC=$(wildcard $(ARDUINO_CORE)/*.c)
CORE_C_NOTDIR=$(notdir $(CORE_C_SRC))
CORE_C_BASE=$(basename $(CORE_C_NOTDIR))
CORE_C=$(addsuffix .o, $(CORE_C_BASE))

CORE_CPP_SRC=$(wildcard $(ARDUINO_CORE)/*.cpp)
CORE_CPP_NOTDIR=$(notdir $(CORE_CPP_SRC))
CORE_CPP_BASE=$(basename $(CORE_CPP_NOTDIR))
CORE_CPP=$(addsuffix .o, $(CORE_CPP_BASE))

motorcontroller: controller.o motor.o switch.o libwiring.a
	$(CC) -o $@ $^ $(LDFLAGS) -L. -lwiring

libwiring.a: $(CORE_C) $(CORE_CPP)
	avr-gcc-ar rcs $@ $^
	
motorcontroller.hex: motorcontroller
	avr-objcopy -O ihex -R .eeprom $^ $@

upload: motorcontroller.hex
	avrdude -C/home/clay/arduino-1.8.2/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P$(USBPORT) -b57600 -D -Uflash:w:motorcontroller.hex:i

clean:
	rm -f motorcontroller
	rm -f motorcontroller.hex
	rm -f *.o
	rm -f *.a
	rm -f *.d