#ifndef __LOGGER_H
#define __LOGGER_H

#include "Common.h"

class Logger{
private:
    

public:
    Logger();
    ~Logger();
    
    void printXYAccelMag(float val);
    void printAction(int val);

};

#endif