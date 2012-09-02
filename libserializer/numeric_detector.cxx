#include "numeric_detector.h"
#include "endian_detector.h"
#include <limits>
using namespace std;


template<typename T> numeric_detector<T>::numeric_detector(const T &value){
    this->value=&value;
    this->type=NONE;
    this->distance=0;
}

template<typename T> unsigned char numeric_detector<T>::properly_type(){
    if(numeric_limits<T>::is_iec559){
        this->type=FLOATING;
        this->_start=(char *)(this->value);
        this->_end=(char *)(this->value+1);
    }else{
        if(*this->value>=0) this->type=UNSIGNED;
        if(*this->value==0||*this->value==1){
            this->type|=BOOL|(unsigned char)*this->value;
            return this->type;
        }
        //integer
        this->_start=(char *)this->value;
        this->_end=(char *)(this->value+1);
        Endian endian=getEndian();
        switch(endian){
            case Endian::little:
                while(*(--this->_end)==0x00);
                this->_end++;
                break;
            case Endian::big:
                while(*(this->_start++)==0x00);
                break;
            case Endian::unknown:
            default: throw logic_error("Not supported endian.");
        }
    }
    
    this->distance=this->_end-this->_start;
    this->type|=(char)(this->distance-1);
    
    return this->type;
}
template <typename T> ptrdiff_t numeric_detector<T>::properly_size()const{ return this->distance;}
template<typename T> void *numeric_detector<T>::start() const{return this->_start;}
template<typename T> void *numeric_detector<T>::end() const{return this->_end;}

//The instance

template class numeric_detector<bool>;
template class numeric_detector<float>;
template class numeric_detector<double>;
template class numeric_detector<long double>;

template class numeric_detector<char>;
template class numeric_detector<short>;
template class numeric_detector<int>;
template class numeric_detector<long>;
template class numeric_detector<long long>;

template class numeric_detector<unsigned char>;
template class numeric_detector<unsigned short>;
template class numeric_detector<unsigned int>;
template class numeric_detector<unsigned long>;
template class numeric_detector<unsigned long long>;
