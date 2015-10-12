#ifndef __MOVINGAVERAGE_H
#define __MOVINGAVERAGE_H

template<typename T>
class MovingAverage{
private:
    T _offset;
    T _values[5];
    
public:
    MovingAverage(T offset = 0) : _offset(offset){
        for(short i=0; i<5; i++){
            _values[i] = T(0);
        }
    }
    ~MovingAverage(){}
    
    T getFilteredValue(T val){
        _shiftValues();
        _values[0] = val + _offset;
        
        
        T s = T(0);
        for(auto v : _values){
            s += v;
        }
        
        return floor(float(s)/5.0f);
    }
    
private:
    void _shiftValues(){
        for(short i=4; i>0; i--){
            _values[i] = _values[i-1];
        }
    }
};

#endif