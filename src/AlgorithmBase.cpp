#include "AlgorithmBase.h"

AlgorithmBase::AlgorithmBase(ZumoHardware* hwd, float maxAngular, float maxLinear, int16_t maxRpm)
    : //_hwd(hwd),
      _maxAngular(maxAngular),
      _maxLinear(maxLinear),
      _maxRpm(maxRpm),
      _accelY(0),
      _accelZ(0),
      _timeLastTurn(0),
      _timeLastCollision(0),
      _lastSpeed(0),
      _timeLastAccel(0),
      _accelerating(false)
{
    _hwd = hwd;
    
    _accelXFilter = new LowpassFilter<int16_t>(0.98f);
    _accelYFilter = new LowpassFilter<int16_t>(0.98f);
    _accelZFilter = new LowpassFilter<int16_t>(0.98f, -111);
    
    _rotXFilter = new MovingAverage<int16_t>();
    _rotYFilter = new MovingAverage<int16_t>();
    _rotZFilter = new MovingAverage<int16_t>();
    
    _pitch = new CompFilter<float>(0.98f);
    _heading = new CompFilter<float>(0.5f);
    //_heading = new LowpassFilter<float>(0.96f);
}

AlgorithmBase::~AlgorithmBase(){
    delete _accelXFilter;
    delete _accelYFilter;
    delete _accelZFilter;
    
    delete _rotXFilter;
    delete _rotYFilter;
    delete _rotZFilter;
    
    delete _pitch;
    delete _heading;
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

float AlgorithmBase::getRotXf(){
    return (static_cast<float>(_rotX) * 8.75f) / 1000.0f;
}

float AlgorithmBase::getRotYf(){
    return (static_cast<float>(_rotY) * 8.75f) / 1000.0f;
}

float AlgorithmBase::getRotZf(){
    return (static_cast<float>(_rotZ) * 8.75f) / 1000.0f;
}

float AlgorithmBase::pitch(){
    //return atan2(_accelX, sqrt(_accelY*_accelY + _accelZ*_accelZ));
    uint16_t y2 = uint16_t(_accelY*_accelY);
    uint16_t z2 = uint16_t(_accelZ*_accelZ);
    return atan(float(_accelX) / sqrt(y2+z2));
}

float AlgorithmBase::roll(){
    return atan(float(-_accelY) / float(_accelZ));
    //return atan2(_accelY, sqrt(_accelY*_accelY + _accelX*_accelX));
}

float AlgorithmBase::yaw(){
    return _hwd->compass->heading(LSM303::vector<int>{1,0,0});
}

float AlgorithmBase::pitchFiltered(){
    return _pitch->getFilteredValue();
}

float AlgorithmBase::yawFiltered(){
    return _heading->getFilteredValue();
}

bool AlgorithmBase::isColliding(int16_t threshold){
    //int16_t thresh2 = threshold*threshold;
    //int16_t xyDot = _accelX*_accelX + _accelY*_accelY;
    float Xf = getAccelXf();
    float Yf = getAccelYf();
    float mag = sqrt(Xf*Xf + Yf*Yf);
    
    if((mag < 0.05f) && (millis() - _timeLastTurn > 750) && (millis() - _timeLastCollision > 1000) && !_accelerating && (millis() - _timeLastAccel > 1000)){
        logger.printAction(COLLISION);
        
        _timeLastCollision = millis();
        return true;
    }
    else{
        return false;
    }
}

void AlgorithmBase::move(){
    const float r = 0.01f; //wheel radius (m)
    const float L = 0.6f; //wheel base (m)
    
    float vLeft = ((2.0f*_desiredLinearVelocity) - (L*_desiredAngularVelocity)) / (2.0f*r); //rad/s
    float vRight = ((2.0f*_desiredLinearVelocity) + (L*_desiredAngularVelocity)) / (2.0f*r); //rad/s
    
    //rad/s -> rpm
    int16_t rpmLeft = static_cast<int16_t>(floor(vLeft * 9.551f));
    int16_t rpmRight = static_cast<int16_t>(floor(vRight * 9.551f));
    
    //TODO: assumes full 6V. need to account for battery degredation
    float dutyCycleLeft = static_cast<float>(rpmLeft) / static_cast<float>(_maxRpm);
    int16_t pwmLeft = static_cast<int16_t>(floor(dutyCycleLeft * 400.0f));
    
    float dutyCycleRight = static_cast<float>(rpmRight) / static_cast<float>(_maxRpm);
    int16_t pwmRight = static_cast<int16_t>(floor(dutyCycleRight * 400.0f));    
    
    logger.printAction(pwmLeft);
    _hwd->motors->setSpeeds(pwmLeft, pwmRight);
}

void AlgorithmBase::stop(){
    _hwd->motors->setSpeeds(0,0);
}

void AlgorithmBase::setDesiredAngularVelocity(float vel){
    _desiredAngularVelocity = vel;
    _clampSpeed();
}

void AlgorithmBase::setDesiredLinearVelocity(float vel){
    //(speed > _lastSpeed) ? _accelerating = true : _accelerating = false;
    //_lastSpeed = speed;
    //if(_accelerating) _timeLastAccel = millis();
    
    _desiredLinearVelocity = vel;
    _clampSpeed();
    
    logger.printNewDesiredLinearVel(vel);
}

void AlgorithmBase::step(uint16_t dt){
    sense(dt);
    act(dt);
}

void AlgorithmBase::sense(uint16_t dt){
    _hwd->compass->read();
    _hwd->gyro->read();
    //_hwd->proxSensors->read(); 
    
    logger.printMagX(_hwd->compass->m.y);
    logger.printAccX(_hwd->compass->m.z);
    
    _accelX = _accelXFilter->getFilteredValue(_hwd->compass->a.x/16);
    _accelY = _accelYFilter->getFilteredValue(_hwd->compass->a.y/16);
    _accelZ = _accelZFilter->getFilteredValue(_hwd->compass->a.z/16);
    
    _rotX = _rotXFilter->getFilteredValue(_hwd->gyro->g.x);
    _rotY = _rotYFilter->getFilteredValue(_hwd->gyro->g.y);
    _rotZ = _rotZFilter->getFilteredValue(_hwd->gyro->g.z);
    
    if(!isnan(this->pitch())){
        _pitch->integrateValues(-this->getRotYf(), this->pitch() * (180.0f/M_PI), dt);
    }
    _heading->integrateValues(this->getRotZf(), this->yaw(), dt);
    
    senseImpl(dt);   
}

void AlgorithmBase::act(uint16_t dt){
    actImpl(dt);
}

void AlgorithmBase::_clampSpeed(){
    if(_desiredLinearVelocity > _maxLinear){
        _desiredLinearVelocity = _maxLinear;
    }
    
    if(_desiredAngularVelocity > _maxAngular){
        _desiredAngularVelocity = _maxAngular;
    }
}