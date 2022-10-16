MMCU=atmega328p
MODEL=ATMEGA328P
DEVICE=/dev/ttyACM0
DF_CPU=16000000UL
FILE=main

all: compile flash clean

compile:
	avr-gcc -Os -DF_CPU=$(DF_CPU) -mmcu=$(MMCU) -c -o $(FILE).o $(FILE).c
	avr-gcc -mmcu=$(MMCU) $(FILE).o -o $(FILE)
	avr-objcopy -O ihex -R .eeprom $(FILE) $(FILE).hex

flash:
	avrdude -F -V -c arduino -p $(MODEL) -P $(DEVICE) -b 115200 -U flash:w:$(FILE).hex

clean:
	rm ./*.o
	rm ./*.hex
	rm ./$(FILE)