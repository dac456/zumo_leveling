#ifndef __COMMON_H
#define __COMMON_H

#include <Wire.h>
#include <Zumo32U4.h>

#include "MovingAverage.h"
#include "CompFilter.h"
#include "LowpassFilter.h"
#include "Queue.h"

struct ZumoHardware{
    ZumoHardware(){
        lcd = new Zumo32U4LCD;
        motors = new Zumo32U4Motors;
        proxSensors = new Zumo32U4ProximitySensors;
        buzzer = new Zumo32U4Buzzer;
        compass = new LSM303;
        gyro = new L3G;
    }
    ~ZumoHardware(){
        delete lcd;
        delete motors;
        delete proxSensors;
        delete compass;
        delete gyro;
    }
    
    Zumo32U4LCD* lcd;
    Zumo32U4Motors* motors;
    Zumo32U4ProximitySensors* proxSensors;
    Zumo32U4Buzzer* buzzer;
    
    LSM303* compass;
    L3G* gyro;  
};

#endif