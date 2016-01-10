#ifndef __QUEUE_H
#define __QUEUE_H

template<typename T>
struct QueueItem{
    T val;
    
    QueueItem* next;
    QueueItem* prev;
};

template<typename T>
class Queue{
private:
    QueueItem<T>* _head;
    QueueItem<T>* _tail;
    
    size_t _size;
    
public:
    Queue()
        : _head(nullptr),
          _tail(nullptr),
          _size(0)
    {
    }
    
    ~Queue(){
       while(!isEmpty()){
           pop();
       }
    }
    
    void push(T val){
        QueueItem<T>* item = new QueueItem<T>();
        item->val = val;
        
        if(isEmpty()){
            item->next = nullptr;
            item->prev = nullptr;
            
            _head = item;
            _tail = item;
        }
        else{
            _tail->next = item;
            item->prev = _tail;
            item->next = nullptr;
            
            _tail = item;
        }
        
        _size++;
    }
    
    T pop(){
        if(!isEmpty()){
            T retVal = _head->val;
            QueueItem<T>* tmp = _head;
            
            _head->next->prev = nullptr;
            _head = _head->next;
            
            delete tmp;
            
            _size--;
            return retVal;
        }
    }
    
    size_t size(){
        return _size;
    }
    
    bool isEmpty(){
        return ((_head == nullptr) && (_tail == nullptr));
    }
    
    T operator [](int index){
        if((index > 0) && (index < _size) && !isEmpty()){
            QueueItem<T>* i = _tail;
            size_t c = 0;
            while(i != nullptr){
                if(c == index){
                    return i->val;
                }
                
                i = i->next;
                c++;
            }
        }
    }
    
};

#endif