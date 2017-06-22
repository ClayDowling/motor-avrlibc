ARDUINO_BASE=/Applications/Arduino.app/Contents/Java/hardware/arduino/avr
ARDUINO_CORE=$(ARDUINO_BASE)/cores/arduino
ARDUINO_EIGHT_ANALOG_INPUTS=$(ARDUINO_BASE)/variants/eightanaloginputs

CC=/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-gcc
CXX=/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++
LINKER=/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-gcc-ar
OBJCOPY=/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-objcopy
AVRDUDE=/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avrdude

ARDUINO_CFLAGS=-Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 \
	-DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR  \
	-I$(ARDUINO_CORE) -I$(ARDUINO_EIGHT_ANALOG_INPUTS)
CFLAGS=-g -I../machine $(ARDUINO_CFLAGS)

ARDUINO_CXX_FLAGS=-Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p \
	-DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR  \
	 -I$(ARDUINO_CORE) -I$(ARDUINO_EIGHT_ANALOG_INPUTS)
CXXFLAGS=-g $(ARDUINO_CXX_FLAGS)

ASSEMBLY_FLAGS=-w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p -lm

USBPORT=/dev/cu.usbmodem1421
VPATH=../machine:$(ARDUINO_CORE)

CORE_C_SRC=$(wildcard $(ARDUINO_CORE)/*.c)
CORE_C_NOTDIR=$(notdir $(CORE_C_SRC))
CORE_C_BASE=$(basename $(CORE_C_NOTDIR))
CORE_C=$(addsuffix .o, $(CORE_C_BASE))

CORE_CPP_SRC=$(wildcard $(ARDUINO_CORE)/*.cpp)
CORE_CPP_NOTDIR=$(notdir $(CORE_CPP_SRC))
CORE_CPP_BASE=$(basename $(CORE_CPP_NOTDIR))
CORE_CPP=$(addsuffix .o, $(CORE_CPP_BASE))

APPLICATION_OBJECTS=controller.o state_transition.o motor.o switch.o timer.o

motorcontroller: $(APPLICATION_OBJECTS) libwiring.a
	$(CC) $(ASSEMBLY_FLAGS) $(APPLICATION_OBJECTS) -o $@ $(LDFLAGS) -L. -lwiring

libwiring.a: $(CORE_C) $(CORE_CPP)
	$(LINKER) rcs $@ $^

motorcontroller.hex: motorcontroller
	$(OBJCOPY) -O ihex -R .eeprom $^ $@

upload: motorcontroller.hex
	$(AVRDUDE) -C/Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P$(USBPORT) -b57600 -D -Uflash:w:motorcontroller.hex:i

clean:
	rm -f motorcontroller
	rm -f motorcontroller.hex
	rm -f *.o
	rm -f *.a
	rm -f *.d
