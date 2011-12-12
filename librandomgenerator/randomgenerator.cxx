#include "randomgenerator.h"
#include <stdexcept>
#include <cmath>
#include <cassert>

using namespace random_class;
using namespace std;

randomgenerator::randomgenerator(const string map, const size_t max,const size_t string_size){
    this->_max=max;
    this->_ssize=string_size;
    this->_map=map;
    this->generator=new mt19937(time(nullptr));
}

randomgenerator::~randomgenerator(){delete this->generator;}
size_t randomgenerator::max() const{return this->_max;}
size_t randomgenerator::string_size() const{return this->_ssize;}
void randomgenerator::max(const size_t max){this->_max=max;}
void randomgenerator::string_size(const size_t ssize){this->_ssize=ssize;}

randomgenerator &randomgenerator::operator>>(string &ref){
    for(size_t counter=0;counter<this->_ssize;counter++){
        size_t index;
        (*this)>>index;
        ref+=this->_map[index%this->_map.size()];
    }
#ifdef DEBUG_RANDOM
    this->writeDump("generated_str.log",ref);
#endif
    return (*this);
}

randomgenerator &randomgenerator::operator>>(float &ref){
    for(unsigned char *pointer=(unsigned char *)&ref;pointer<((unsigned char *)&ref)+sizeof(ref);pointer++) *pointer=(unsigned char)((*this->generator)()&0xff);
    if(this->_max>0) fmodf(ref,this->max());
#ifdef DEBUG_RANDOM
    this->writeDump("generated_float.log",ref);
#endif
    return (*this);
}
randomgenerator &randomgenerator::operator>>(double &ref){
    for(unsigned char *pointer=(unsigned char *)&ref;pointer<((unsigned char *)&ref)+sizeof(ref);pointer++) *pointer=(unsigned char)((*this->generator)()&0xff);
    if(this->_max>0) fmod(ref,this->max());
#ifdef DEBUG_RANDOM
    this->writeDump("generated_double.log",ref);
#endif
    return (*this);
}
randomgenerator &randomgenerator::operator >>(long double &ref){
    for(unsigned char *pointer=(unsigned char *)&ref;pointer<((unsigned char *)&ref)+sizeof(ref);pointer++) *pointer=(unsigned char)((*this->generator)()&0xff);
    if(this->_max>0) fmodl(ref,this->max());
#ifdef DEBUG_RANDOM
    this->writeDump("generated_long_double.log",ref);
#endif
    return (*this);
}
randomgenerator &randomgenerator::operator>>(bool &ref){
    short s;
    (*this)>>s;
    ref=(bool)(s&0x01);
#ifdef DEBUG_RANDOM
    this->writeDump("generated_bool.log",ref);
#endif
    return (*this);
}
randomgenerator &randomgenerator::operator>>(char &ref){
    size_t index;
    (*this)>>index;
    ref=this->_map[index%this->_map.size()];
#ifdef DEBUG_RANDOM
    this->writeDump("generated_char.log",ref);
#endif
    return (*this);
}
randomgenerator &randomgenerator::operator>>(unsigned char &ref){return (*this)>>(char &)ref;}
