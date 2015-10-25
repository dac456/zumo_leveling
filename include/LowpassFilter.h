#ifndef __LOWPASSFILTER_H
#define __LOWPASSFILTER_H

template<typename T>
class LowpassFilter{
private:
    float _alpha;
    float _beta;
    T _val;
    T _offset;
    
public:
    LowpassFilter(float alpha, T offset = T(0)) : _alpha(alpha), _offset(offset){
        _val = T(0);
        
        _beta = 1.0f - _alpha;
    }
    ~LowpassFilter(){}
    
    T getFilteredValue(T val){
        _val = _alpha*_val + _beta*(val+_offset);
        
        return _val;
    }
  
};

#endif