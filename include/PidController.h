#ifndef __PIDCONTROLLER_H
#define __PIDCONTROLLER_H

template<typename T>
class PidController{
private:
    float _p, _i, _d;
    T _setPoint, _u;
    
    T _integral;
    T _derivative;
    
    T _error, _lastError;
    
public:	    
    PidController(float p, float i, float d)
        : _p(p), _i(i), _d(d)
    {
        _integral = T(0);
        _derivative = T(0);
        _u = T(0);
        _setPoint = T(0);
        
        _error = T(0);
        _lastError = T(0);
    }
    ~PidController(){}
    
    void step(T val, uint16_t dt){
        _error = _setPoint - val;
        float dtf = dt / 1000.0f;
        
        _derivative = (_error - _lastError) / dtf;
        _integral += _error * dt;
        
        _u = (_p*_error) + (_i*_integral) + (_d*_derivative);
        
        _lastError = _error;
    }
    
    void setReference(T val){
        _setPoint = val;
    }
    
    T getValue(){
        return _u;
    }
};

#endif