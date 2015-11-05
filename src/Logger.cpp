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

void Logger::printAction(float val){
    char buf[14];
    sprintf(buf, "%8.6f", val);
    
    Serial1.print('b');
    Serial1.println(buf);
}

void Logger::printNewDesiredLinearVel(float val){
    char buf[14];
    sprintf(buf, "%8.6f", val);
    
    Serial1.print('c');
    Serial1.println(buf);
}

void Logger::printPitch(float val){
    char buf[14];
    sprintf(buf, "%8.6f", val);
    
    Serial1.print('d');
    Serial1.println(buf);     
}

void Logger::printHeading(float val){
    char buf[14];
    sprintf(buf, "%8.6f", val);
    
    Serial1.print('e');
    Serial1.println(buf);         
}

void Logger::printMagX(int val){
    char buf[14];
    sprintf(buf, "%i", val);
    
    Serial1.print('f');
    Serial1.println(buf);
}

void Logger::printAccX(int val){
    char buf[14];
    sprintf(buf, "%i", val);
    
    Serial1.print('g');
    Serial1.println(buf);
}