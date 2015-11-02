#ifndef __ALGORITHMHILLCLIMB_H
#define __ALGORITHMHILLCLIMB_H

#include "AlgorithmBase.h"
#include "PidController.h"

class AlgorithmHillClimb : public AlgorithmBase{
private:
    bool _inclined;
    
    PidController<float>* _headingPid;
    
public:
    AlgorithmHillClimb(ZumoHardware* hwd, uint16_t maxTurnSpeed = 100, uint16_t maxForwardSpeed = 100);
    ~AlgorithmHillClimb();
    
    
    void senseImpl(uint16_t dt);
    void actImpl(uint16_t dt);    
};

#endif