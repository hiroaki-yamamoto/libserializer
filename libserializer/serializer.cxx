#include <iostream>
#include <cassert>
#include "serializer.h"
#include "endian_detector.h"
#include <iterator>
#include <algorithm>
#include <limits>
#ifdef DEBUG_SERIALIZER
    #include<typeinfo>
    #include<fstream>
#endif
using namespace std;
using namespace defs;

/*
  Implementation of serializer_interface
 */
serializer_interface::serializer_interface(istream &in){this->_in=&in;}
serializer_interface::serializer_interface(ostream &out){this->_out=&out;}
serializer_interface::serializer_interface(iostream &io){
    this->_in=dynamic_cast<istream *>(&io);
    this->_out=dynamic_cast<ostream *>(&io);
}
void serializer_interface::stream(istream &in){this->_in=&in;}
void serializer_interface::stream(ostream &out){this->_out=&out;}
void serializer_interface::stream(iostream &io){
    this->_in=dynamic_cast<istream *>(&io);
    this->_out=dynamic_cast<ostream *>(&io);
    assert(this->_in!=nullptr&&this->_out!=nullptr);
}

size_t serializer_interface::size(){
    READABLE_REQUIRED;
    streampos current=this->_in->tellg(),size;
    this->_in->seekg(0,ios::end);
    size=this->_in->tellg();
    this->_in->seekg(current);

    return size;
}
size_t serializer_interface::avail(){
    READABLE_REQUIRED;
    return this->size()-this->_in->tellg();
}

bool serializer_interface::close(){
    this->_in=nullptr;
    this->_out=nullptr;
    return true;
}

serializer::serializer(istream &in):serializer_interface(in){this->endian=getEndian();}
serializer::serializer(ostream &out):serializer_interface(out){this->endian=getEndian();}
serializer::serializer(iostream &io):serializer_interface(io){this->endian=getEndian();}
/*
  Implementation of serializer
 */

template<typename T> serializer& serializer::operator<<(const T &value){
    WRITABLE_REQUIRED;
    unsigned char value_type=NONE;
    numeric_detector<T> detector(value);
    value_type=detector.properly_type();
    this->_out->put((char)value_type);
    if(!isBool(value_type)){
        switch(this->endian){
            case Endian::big:
                copy((char*)detector.start(),(char*)detector.end(),
                     ostream_iterator<char>(*this->_out));
                break;
            case Endian::little:
                reverse_copy((char*)detector.start(),(char*)detector.end(),
                             ostream_iterator<char>(*this->_out));
                break;
            default:
                throw logic_error("Not supported endian.");
        }
    }
    return (*this);
}
template<typename T> serializer& serializer::operator>>(T &ref){
    READABLE_REQUIRED;
    unsigned char type;
    if(this->avail()<sizeof(type)) THROW_WILL_REACHED_END;
    type=this->_in->get();
    if(is_str(type)) THROW_INVALID;
    bool boolbuf;
    if(bool_value(type,&boolbuf)){
        ref=boolbuf;
        return (*this);
    }
    if(((((type&0xf0)|UNSIGNED)^UNSIGNED)==FLOATING&&(!numeric_limits<T>::is_iec559))||((((type&0xf0)|UNSIGNED)^UNSIGNED)!=FLOATING&&(numeric_limits<T>::is_iec559)))THROW_INVALID;
    
    size_t size;
    size=properly_size(type);
    if(sizeof(ref)<size) THROW_OVERFLOW;
    if(this->avail()<size) THROW_WILL_REACHED_END;
    ref=0;
    char buf[size];
    if(!this->_in->read(buf,size)) THROW_INVALID;
    switch(this->endian){
        case Endian::little:
            reverse_copy(buf,buf+size,(char*)&ref);
            break;
        case Endian::big:
            copy_backward(buf,buf+size,(char*)((&ref)+1));
            break;
        default:
            throw logic_error("Not supported endian.");
    }
    return (*this);
}

serializer& serializer::operator<<(const string &s){
    this->_out->put(STRING);
    (*this->_out)<<s<<'\0';
    return (*this);
}

serializer& serializer::operator>>(string &str){
    if(!is_str(this->_in->get()))THROW_INVALID;
    getline(*this->_in,str,'\0');
    return (*this);
}

//The instance. I want to use export keyword, but there is a few compiler that supports export keyword.
template serializer& serializer::operator<<(const float &);
template serializer& serializer::operator<<(const double &);
template serializer& serializer::operator<<(const long double &);

template serializer& serializer::operator<<(const bool &);
template serializer& serializer::operator<<(const char &);
template serializer& serializer::operator<<(const short &);
template serializer& serializer::operator<<(const int &);
template serializer& serializer::operator<<(const long &);
template serializer& serializer::operator<<(const long long &);
template serializer& serializer::operator<<(const unsigned char &);
template serializer& serializer::operator<<(const unsigned short &);
template serializer& serializer::operator<<(const unsigned int &);
template serializer& serializer::operator<<(const unsigned long &);
template serializer& serializer::operator<<(const unsigned long long &);

template serializer& serializer::operator>>(float &);
template serializer& serializer::operator>>(double &);
template serializer& serializer::operator>>(long double &);

template serializer& serializer::operator>>(bool &);
template serializer& serializer::operator>>(char &);
template serializer& serializer::operator>>(short &);
template serializer& serializer::operator>>(int &);
template serializer& serializer::operator>>(long &);
template serializer& serializer::operator>>(long long &);
template serializer& serializer::operator>>(unsigned char &);
template serializer& serializer::operator>>(unsigned short &);
template serializer& serializer::operator>>(unsigned int &);
template serializer& serializer::operator>>(unsigned long &);
template serializer& serializer::operator>>(unsigned long long &);
