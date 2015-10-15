#!/bin/sh

avrdude -C/Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -v -patmega32u4 -cavr109 -P/dev/$1 -D -Uflash:w:./build/zumo_leveling.hex

