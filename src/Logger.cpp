#include "Logger.h"

Logger::Logger(){
    
}

Logger::~Logger(){
    
}

void Logger::printXYAccelMag(float val){
    char buf[14];
    sprintf(buf, "%8.6f", val);
    
    Serial1.print('a');
    Serial1.println(buf);    
}

void Logger::printAction(int val){
    char buf[14];
    sprintf(buf, "%i", val);
    
    Serial1.print('b');
    Serial1.println(buf);
}