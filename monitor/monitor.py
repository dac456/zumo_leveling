#! /usr/bin/env python

import serial
import matplotlib as plt

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB0', 57600)
    
    accel_xy_mag_val = []
    action = []
    
    while True:
        c = ser.read()
        
        if c == 'a':
            line = ser.readline()
            accel_xy_mag_val.append(float(line))
        elif c == 'b':
            line = ser.readline()
            action.append(int(line))