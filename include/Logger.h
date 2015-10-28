#ifndef __LOGGER_H
#define __LOGGER_H

#include "Common.h"

typedef enum{
    TURN_LEFT,
    TURN_RIGHT,
    COLLISION
} ACTION;

class Logger{
private:
    

public:
    Logger();
    ~Logger();
    
    void printXYAccelMag(float val);
    void printAction(float val);
    void printNewDesiredLinearVel(float val);
    void printPitch(float val);

};

#endif