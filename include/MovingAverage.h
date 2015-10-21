#ifndef __MOVINGAVERAGE_H
#define __MOVINGAVERAGE_H

#define NUM_SAMPLES 7

template<typename T>
class MovingAverage{
private:
    T _offset;
    T _values[NUM_SAMPLES];
    
public:
    MovingAverage(T offset = 0) : _offset(offset){
        for(short i=0; i<NUM_SAMPLES; i++){
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
        
        return floor(float(s)/float(NUM_SAMPLES));
    }
    
private:
    void _shiftValues(){
        for(short i=NUM_SAMPLES-1; i>0; i--){
            _values[i] = _values[i-1];
        }
    }
};

#endif