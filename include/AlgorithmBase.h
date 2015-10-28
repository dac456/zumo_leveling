#ifndef __ALGORITHMBASE_H
#define __ALGORITHMBASE_H

#include "Common.h"
#include "Logger.h"

class AlgorithmBase{
private: 
    float _desiredLinearVelocity;
    float _desiredAngularVelocity;
    float _maxLinear;
    float _maxAngular;
    uint16_t _maxRpm;
    
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
    AlgorithmBase(ZumoHardware* hwd, float maxAngular = 10.0f, float maxLinear = 0.34f, int16_t maxRpm = 320);
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
    
    void move();
    void stop();
    
    void setDesiredLinearVelocity(float vel);
    void setDesiredAngularVelocity(float vel);
    
    void step(uint16_t dt);
    
    void sense(uint16_t dt);
    void act(uint16_t dt);
    
    virtual void senseImpl(uint16_t dt) = 0;
    virtual void actImpl(uint16_t dt) = 0;
    
private:
    void _clampSpeed();
    
};

#endif