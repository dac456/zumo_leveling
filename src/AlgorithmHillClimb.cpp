#include "AlgorithmHillClimb.h"

float lerp(float v0, float v1, float t){
    return v0 + t*(v1-v0);
}

AlgorithmHillClimb::AlgorithmHillClimb(ZumoHardware* hwd, uint16_t maxTurnSpeed, uint16_t maxForwardSpeed)
    : AlgorithmBase(hwd, maxTurnSpeed, maxForwardSpeed),
      _inclined(false)
{
    _name = "HillCli1";
    
    setTurnSpeed(100);
}

AlgorithmHillClimb::~AlgorithmHillClimb(){
}

void AlgorithmHillClimb::senseImpl(uint16_t dt){
    (getAccelZ() < 950) ? _inclined = true : _inclined = false;
}

void AlgorithmHillClimb::actImpl(uint16_t dt){
    float r = static_cast<float>(random(65535)) / 65535.0f;
    if(r < 0.03f){
        if(!_inclined){
            (random(65535) % 2) ? turnLeft() : turnRight();
        }
    }
    
    //(_inclined == true) ? setForwardSpeed(100) : setForwardSpeed(40);
    uint16_t Z = getAccelZ();
    if(Z > 950){
        Z = 950;
    }
    if(Z < 700){
        Z = 700;
    }
    
    float sm = Z - 700.0f;
    sm = sm/250.0f;
    setForwardSpeed(floor((1.0f-sm)*400.0f) + 80);        

    
    moveForward();
    
    if(isColliding(150)){
        _hwd->buzzer->playNote(NOTE_G(3), 50, 12);
        
        moveBackward();
        delay(750);
        turnRight();
    }
    /*if(_inclined){
        setForwardSpeed(40);
        moveForward();
    }
    else{
        stop();
    }*/
}