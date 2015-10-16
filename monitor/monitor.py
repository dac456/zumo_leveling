#! /usr/bin/env python

import sys

import serial
import matplotlib.pyplot as plt
import numpy as np

if __name__ == '__main__':  
    if len(sys.argv) > 1:
        ser = serial.Serial(sys.argv[1], 57600)
        
        accel_xy_mag_val = [] #a
        action = [] #b
        forward_speeds = [] #c
        pitch = [] #d
        
        print "Press Ctrl+C to break and gerate plots."
        
        while True:              
            
            try:
                line = ser.readline()
                print line
                if len(line) > 0:
                    if(line[0] == 'a'):
                        line = line[1:]
                        try:
                            v = float(line)
                            accel_xy_mag_val.append(v)
                        except ValueError:
                            pass
                    if(line[0] == 'b'):
                        line = line[1:]
                        action.append(int(line))
                    if(line[0] == 'c'):
                        line = line[1:]
                        forward_speeds.append(int(line))
                    if(line[0] == 'd'):
                        line = line[1:]
                        val = float(line)
                        if np.isnan(val):
                            val = 0
                        pitch.append(np.degrees(val))
            except KeyboardInterrupt:
                break
                
        # Generate plot
        fig, ax = plt.subplots(nrows=2, ncols=2)
        
        ax[0,0].set_title("XY Acceleration Magnitude")
        ax[0,0].set_xlabel("Timesteps (100ms)")
        ax[0,0].plot([i for i in range(len(accel_xy_mag_val))], accel_xy_mag_val)
        
        ax[0,1].set_title("Pitch")
        ax[0,1].set_xlabel("Timesteps (100ms)")
        ax[0,1].plot([i for i in range(len(pitch))], pitch)    
        
        ax[1,0].set_title("Forward Speed")
        ax[1,0].set_xlabel("Timesteps (100ms)")
        ax[1,0].plot([i for i in range(len(forward_speeds))], forward_speeds)
        
        plt.show()
        
    else:
        print "Serial port must be specified."
            
    