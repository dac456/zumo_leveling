#ifndef __COMPFILTER_H
#define __COMPFILTER_H


template<typename T>
class CompFilter{
private:
    T _v1, _v2;
    T _v1Int;
    float _alpha, _beta;
    
public:
    CompFilter(float alpha)
        : _alpha(alpha)
    {
        _v1 = T(0);
        _v2 = T(0);
        
        _v1Int = T(0);
        
        _beta = 1.0f - _alpha;
    }
    
    ~CompFilter(){}
    
    void updateValues(T v1, T v2){
        _v1 = v1;
        _v2 = v2;
    }
    
    void integrateV1(uint16_t dt){
        _v1Int += _v1 * (dt/1000.0f);
    }
    
    T getFilteredValue(bool integrate = true){
        T v1 = T(0);
        integrate ? v1 = _v1Int : v1 = _v1;
        return (_alpha * v1) + (_beta * _v2);
    }
};

#endif