#ifndef __ALGORITHMBASE_H
#define __ALGORITHMBASE_H

#include "Common.h"
#include "Logger.h"

class AlgorithmBase{
private: 
    uint16_t _maxTurnSpeed;
    uint16_t _maxForwardSpeed;
    
    uint16_t _curTurnSpeed;
    uint16_t _curForwardSpeed;
    
    LowpassFilter<int16_t>* _accelXFilter;
    LowpassFilter<int16_t>* _accelYFilter;
    LowpassFilter<int16_t>* _accelZFilter;
    int16_t _accelX;
    int16_t _accelY;
    int16_t _accelZ;
    
    MovingAverage<int16_t>* _rotXFilter;
    MovingAverage<int16_t>* _rotYFilter;
    MovingAverage<int16_t>* _rotZFilter;
    int16_t _rotX;
    int16_t _rotY;
    int16_t _rotZ;
    
    CompFilter<float>* _pitch;
    
    uint16_t _timeLastTurn;
    uint16_t _timeLastCollision;
    
    uint16_t _lastSpeed;
    uint16_t _timeLastAccel;
    bool _accelerating;
    
protected:
    ZumoHardware* _hwd;
    char* _name;
    
    Logger logger;
    
public:
    AlgorithmBase(ZumoHardware* hwd, uint16_t maxTurnSpeed = 100, uint16_t maxForwardSpeed = 100);
    virtual ~AlgorithmBase();
    
    char* getName();
    
    int16_t getAccelX();
    int16_t getAccelY();
    int16_t getAccelZ();
    
    float getAccelXf();
    float getAccelYf();
    float getAccelZf();
    
    float getRotXf();
    float getRotYf();
    float getRotZf();
    
    float pitch();
    float roll();
    float yaw();
    
    float pitchFiltered();
    
    bool isColliding(int16_t threshold);
    
    void turnLeft();
    void turnRight();
    void moveForward();
    void moveBackward();
    void stop();
    
    void setTurnSpeed(uint16_t speed);
    void setForwardSpeed(uint16_t speed);
    
    void step(uint16_t dt);
    
    void sense(uint16_t dt);
    void act(uint16_t dt);
    
    virtual void senseImpl(uint16_t dt) = 0;
    virtual void actImpl(uint16_t dt) = 0;
    
private:
    void _clampSpeed();
    
};

#endif