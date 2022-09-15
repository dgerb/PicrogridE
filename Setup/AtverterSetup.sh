#!/bin/bash

# Set Atmega328P Fuses and flash default bootloader

sudo avrdude -c linuxgpio -p atmega328p -v -U lfuse:w:0xFF:m -U hfuse:w:0xDE:m -U efuse:w:0xFD:m
# sometimes you'll need to set the fuses twice; need to experiment with this
sudo avrdude -c linuxgpio -p atmega328p -v -U lfuse:w:0xFF:m -U hfuse:w:0xDE:m -U efuse:w:0xFD:m
sudo avrdude -c linuxgpio -p atmega328p -v -U flash:w:/home/pi/PicrogridEducational/Setup/optiboot_atmega328.hex:i
# note that avrdude cannot process “~”, need absolute directory