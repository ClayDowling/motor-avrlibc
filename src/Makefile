CC=avr-gcc
CFLAGS=-mmcu=atmega328p -DF_CPU=16000000L -I../machine
USBPORT=/dev/ttyUSB0
VPATH=../machine

motorcontroller: application.o controller.o motor.o switch.o
	$(CC) -o $@ $^ $(LDFLAGS)

motorcontroller.hex: motorcontroller
	avr-objcopy -O ihex -R .eeprom $^ $@

upload: motorcontroller.hex
	avrdude -C/home/clay/arduino-1.8.2/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P$(USBPORT) -b57600 -D -Uflash:w:motorcontroller.hex:i

clean:
	rm -f *.o
	rm -f motorcontroller
	rm -f motorcontroller.hex