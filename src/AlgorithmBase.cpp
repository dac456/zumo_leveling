#include "AlgorithmBase.h"

AlgorithmBase::AlgorithmBase(ZumoHardware* hwd, uint16_t maxTurnSpeed, uint16_t maxForwardSpeed)
    : //_hwd(hwd),
      _maxTurnSpeed(maxTurnSpeed),
      _maxForwardSpeed(maxForwardSpeed),
      _curTurnSpeed(0),
      _curForwardSpeed(0),
      _accelY(0),
      _accelZ(0),
      _timeLastTurn(0),
      _timeLastCollision(0),
      _lastSpeed(0),
      _timeLastAccel(0),
      _accelerating(false)
{
    _hwd = hwd;
    
    _accelXFilter = new MovingAverage<int16_t>();
    _accelYFilter = new MovingAverage<int16_t>();
    _accelZFilter = new MovingAverage<int16_t>(-111);
}

AlgorithmBase::~AlgorithmBase(){
    delete _accelXFilter;
    delete _accelYFilter;
    delete _accelZFilter;
}

char* AlgorithmBase::getName(){
    return _name;
}

int16_t AlgorithmBase::getAccelX(){
    return _accelX;
}

int16_t AlgorithmBase::getAccelY(){
    return _accelY;
}

int16_t AlgorithmBase::getAccelZ(){
    return _accelZ;
}

/* http://cegt201.bradley.edu/projects/proj2015/autonomous_underwater_robots/Deliverables/Doxygen_Report_2_13_2015/_l_s_m303_d_8c_source.xhtml */
float AlgorithmBase::getAccelXf(){
    return static_cast<float>(_accelX) / 104.41575f;
}

float AlgorithmBase::getAccelYf(){
    return static_cast<float>(_accelY) / 104.41575f;
}

float AlgorithmBase::getAccelZf(){
    return static_cast<float>(_accelZ) / 104.41575f;
}

float AlgorithmBase::pitch(){
    return atan2(_accelX, sqrt(_accelY*_accelY + _accelZ*_accelZ));
}

float AlgorithmBase::roll(){
    return atan2(_accelY, sqrt(_accelY*_accelY + _accelX*_accelX));
}

float AlgorithmBase::yaw(){
    return atan2(sqrt(_accelX*_accelX + _accelY*_accelY), _accelZ);
}

bool AlgorithmBase::isColliding(int16_t threshold){
    //int16_t thresh2 = threshold*threshold;
    //int16_t xyDot = _accelX*_accelX + _accelY*_accelY;
    float Xf = getAccelXf();
    float Yf = getAccelYf();
    float mag = sqrt(Xf*Xf + Yf*Yf);
    
    if((mag > 0.4f) && (millis() - _timeLastTurn > 750) && (millis() - _timeLastCollision > 1000) && !_accelerating && (millis() - _timeLastAccel > 1000)){
        logger.printAction(COLLIDING);
        
        _timeLastCollision = millis();
        return true;
    }
    else{
        return false;
    }
}

void AlgorithmBase::turnLeft(){
    if(millis() - _timeLastTurn > 1000){
        _hwd->motors->setSpeeds(_curTurnSpeed, -_curTurnSpeed);
        delay(750);
        stop();
        
        _timeLastTurn = millis();
        
        logger.printAction(TURN_LEFT);
    }
}

void AlgorithmBase::turnRight(){
    if(millis() - _timeLastTurn > 1000){
        _hwd->motors->setSpeeds(-_curTurnSpeed, _curTurnSpeed);
        delay(750);
        stop();
        
        _timeLastTurn = millis();
        
        logger.printAction(TURN_RIGHT);
    }
}

void AlgorithmBase::moveForward(){
    _hwd->motors->setSpeeds(_curForwardSpeed, _curForwardSpeed);
}

void AlgorithmBase::moveBackward(){
    _hwd->motors->setSpeeds(-_curForwardSpeed, -_curForwardSpeed);
}

void AlgorithmBase::stop(){
    _hwd->motors->setSpeeds(0,0);
}

void AlgorithmBase::setTurnSpeed(uint16_t speed){
    _curTurnSpeed = speed;
    _clampSpeed();
}

void AlgorithmBase::setForwardSpeed(uint16_t speed){
    (speed > _lastSpeed) ? _accelerating = true : _accelerating = false;
    _lastSpeed = speed;
    if(_accelerating) _timeLastAccel = millis();
    
    _curForwardSpeed = speed;
    _clampSpeed();
    
    logger.printNewForwardSpeed(speed);
}

void AlgorithmBase::step(uint16_t dt){
    sense(dt);
    act(dt);
}

void AlgorithmBase::sense(uint16_t dt){
    _hwd->compass->read();
    _hwd->proxSensors->read(); 
    
    _accelX = _accelXFilter->getFilteredValue(_hwd->compass->a.x/16);
    _accelY = _accelYFilter->getFilteredValue(_hwd->compass->a.y/16);
    _accelZ = _accelZFilter->getFilteredValue(_hwd->compass->a.z/16);
    
    senseImpl(dt);   
}

void AlgorithmBase::act(uint16_t dt){
    actImpl(dt);
}

void AlgorithmBase::_clampSpeed(){
    if(_curForwardSpeed > _maxForwardSpeed){
        _curForwardSpeed = _maxForwardSpeed;
    }
    
    if(_curTurnSpeed > _maxTurnSpeed){
        _curTurnSpeed = _maxTurnSpeed;
    }
}