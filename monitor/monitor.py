#! /usr/bin/env python

import serial
import pygame
import matplotlib.pyplot as plt

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB0', 57600)
    
    accel_xy_mag_val = [] #a
    action = [] #b
    forward_speeds = [] #c
    
    while True:
        c = ser.read()
        
        if c == 'a':
            line = ser.readline()
            accel_xy_mag_val.append(float(line))
        elif c == 'b':
            line = ser.readline()
            action.append(int(line))
        elif c == 'c':
            line = ser.readline()
            forward_speeds.append(int(line))
            
            