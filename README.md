This code is intended for the Pololu Zumo 32U4, but may be useful for other platforms.

It is currently intended to experiment with various algorithms for leveling terrain by a swarm of simple agents, 
as described [here](http://dl.acm.org/citation.cfm?id=2744535).

Requires the Arduino SDK, AVR GCC (which should come with the SDK), and CMake.

The monitor script depends on matplotlib, pyserial, and numpy.
The script is meant to be used with an XBee radio module, talking to a paired XBee attached to Serial1 on the Zumo.

upload.sh is for convienience and allows uploading to the device using avrdude, taking the serial port as an argument. Assumes binary is in ./build

upload_mac.sh is the same, except references Arduino.app for avrdude.conf.
