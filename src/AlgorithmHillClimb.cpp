#include "AlgorithmHillClimb.h"

float lerp(float v0, float v1, float t){
    return v0 + t*(v1-v0);
}

AlgorithmHillClimb::AlgorithmHillClimb(ZumoHardware* hwd, uint16_t maxTurnSpeed, uint16_t maxForwardSpeed)
    : AlgorithmBase(hwd, maxTurnSpeed, maxForwardSpeed),
      _inclined(false)
{
    _name = "HillCli1";
    
    setDesiredLinearVelocity(0.0f);
    setDesiredAngularVelocity(0.0f);
    
    _headingPid = new PidController<float>(0.15f, 0.025f);
    _headingPid->setReference(60.0f);
}

AlgorithmHillClimb::~AlgorithmHillClimb(){
    delete _headingPid;
}

void AlgorithmHillClimb::senseImpl(uint16_t dt){
    (getAccelZ() < 950) ? _inclined = true : _inclined = false;
}

void AlgorithmHillClimb::actImpl(uint16_t dt){
    _headingPid->step(yawFiltered(), dt);
    
    //if(!isColliding(0.3f)){
        setDesiredLinearVelocity(((fabs(pitchFiltered())/90.0f) * 0.3) + 0.1f);
        setDesiredAngularVelocity(0.0f);
        move();
    /*}
    else{
        setDesiredLinearVelocity(-(((fabs(pitchFiltered())/90.0f) * 0.3) + 0.1f));
        setDesiredAngularVelocity(1.5f);
        move();
        delay(1500);
    }*/
    //setDesiredAngularVelocity((-_headingPid->getValue()) * (M_PI/180.0f));
    
    //move();
}