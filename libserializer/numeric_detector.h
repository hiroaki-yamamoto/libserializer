#pragma once
#include <iostream>
#include <cstddef>
#include <cassert>
#include <stdexcept>
#include <typeinfo>

using namespace std;
/*
  Typebit specification:
  +-------------------+--------------------------------------------------------------+
  |is unsigned?(1 bit)|                     Type ID(7 bits)                          |
  +-------------------+--------------------------------------------------------------+
  
  The type IDs are defined as follows:
 */
enum type_id:unsigned char{
    NONE=0x00,
    UNSIGNED=0x80,
    BOOL=0x40,
    FLOATING=0x20,
    STRING=0x10
};

/*
 If you want to serialize your own class "directly", you have to define type ID other than these.
 However, you don't need to define them if you wrap the class.
 */

template <typename T> class numeric_detector{
    public:
        numeric_detector(const T &);
        unsigned char properly_type();
        ptrdiff_t properly_size()const;
        void *start() const;
        void *end() const;
    private:
        const T *value;
        ptrdiff_t distance;
        unsigned char type;
        char *_start,*_end;
};
inline bool is_str(const unsigned char type){return (type&0xf0)==STRING;}
inline bool is_float(const unsigned char type){return (type&0xf0)==FLOATING;}
inline bool isBool(const unsigned char type){return ((type&0xf0)==(UNSIGNED|BOOL));}

inline size_t properly_size(const unsigned char type){
    if(is_str(type)) throw logic_error("Unknown type.");
    if((type&0xf0)==FLOATING) return (size_t)(type^FLOATING)+1;
    return (size_t)(type&0x0f)+1;
}
template<typename T> inline bool bool_value(const unsigned char type,T &to){
    if(!isBool(type)||(&to)==nullptr) return false;
    to=(bool)(type&0x01);
    return true;
}
