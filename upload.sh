#!/bin/sh

avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -v -patmega32u4 -cavr109 -P/dev/$1 -D -Uflash:w:./build/zumo_leveling.hex

