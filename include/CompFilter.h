#ifndef __COMPFILTER_H
#define __COMPFILTER_H


template<typename T>
class CompFilter{
private:
    T _v1, _v2;
    T _val;
    float _alpha, _beta;
    
public:
    CompFilter(float alpha) : _alpha(alpha)
    {
        _v1 = T(0);
        _v2 = T(0);
        
        _val = T(0);
        
        _beta = 1.0f - _alpha;
    }
    
    ~CompFilter(){}
    
    void integrateValues(T v1, T v2, uint16_t dt){
        _v1 = v1;
        _v2 = v2;
        
        _val = _alpha * (_val + _v1 * (dt/1000.0f)) + _beta * _v2;
    }
    
    T getFilteredValue(){
        return _val;
    }
};

#endif