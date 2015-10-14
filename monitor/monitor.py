#! /usr/bin/env python

import serial
import curses
import matplotlib.pyplot as plt

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB1', 57600)
    
    accel_xy_mag_val = [] #a
    action = [] #b
    forward_speeds = [] #c
    
    stdscr = curses.initscr()
    stdscr.nodelay(True)
    
    curses.noecho()
    curses.cbreak()
    
    while True:  
        
        stdscr.clear()
        stdscr.addstr(0,0, "Press space to stop monitoring and generate plot")
        
        # http://ubuntuforums.org/showthread.php?t=1514035&p=9488711#post9488711
        try:
            key = stdscr.getkey()
        except: # in no delay mode getkey raise and exeption if no key is press 
            key = None
        if key == " ": # of we got a space then break
            break       
        
        line = ser.readline()
        if len(line) > 0:
            if(line[0] == 'a'):
                line = line[1:]
                accel_xy_mag_val.append(float(line))
            if(line[0] == 'b'):
                line = line[1:]
                action.append(int(line))

        """elif c == 'b':
            line = ser.readline()
            action.append(int(line))
        elif c == 'c':
            line = ser.readline()
            forward_speeds.append(int(line))"""
            
        stdscr.refresh()
            
    curses.endwin()
            
    # Generate plot
    fig, ax = plt.subplots(nrows=2, ncols=2)
    
    ax[0,0].set_title("XY Acceleration Magnitude")
    ax[0,0].set_xlabel("Timesteps (100ms)")
    ax[0,0].plot([i for i in range(len(accel_xy_mag_val))], accel_xy_mag_val)
    
    ax[0,1].set_title("Action Taken")
    ax[0,1].set_xlabel("Timesteps (100ms)")
    ax[0,1].plot([i for i in range(len(action))], action)    
    
    plt.show()
            
    