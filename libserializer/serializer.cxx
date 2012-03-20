#include <iostream>
#include <iterator>
#include <algorithm>
#include <limits>
#include "serializer.h"
#include "endian_detector.h"
#ifdef DEBUG_SERIALIZER
    #include<typeinfo>
    #include<fstream>
#endif
using namespace std;

/*
  Implementation of serializer_interface
 */
serializer_interface::serializer_interface(istream &in){this->stream(in);}
serializer_interface::serializer_interface(ostream &out){this->stream(out);}
serializer_interface::serializer_interface(iostream &io){this->stream(io);}
void serializer_interface::stream(istream &in){this->_in=&in; this->setSize();}
void serializer_interface::stream(ostream &out){this->_out=&out;}
void serializer_interface::stream(iostream &io){
    this->_in=dynamic_cast<istream *>(&io);
    this->_out=dynamic_cast<ostream *>(&io);
#ifdef DEBUG_SERIALIZER
    assert(this->_in!=nullptr||this->_out!=nullptr);
#else
    if(this->_in==nullptr&&this->_out==nullptr)
        throw invalid_argument("Casting iostream to istream and ostream is failed.");
#endif
    this->setSize();
}
void serializer_interface::setSize(){
    READABLE_REQUIRED(this->_in);
    streampos current;
    if(this->_in!=nullptr){
        current=this->_in->tellg();
        this->_in->seekg(0,ios::end);
        this->_size=this->_in->tellg();
        this->_in->seekg(current);
    }
}
size_t serializer_interface::size(){return this->_size;}

bool serializer_interface::close(){
    this->_in=nullptr;
    this->_out=nullptr;
    return true;
}

serializer::serializer(istream &in):serializer_interface(in){this->init();}
serializer::serializer(ostream &out):serializer_interface(out){this->init();}
serializer::serializer(iostream &io):serializer_interface(io){this->init();}
void serializer::init(){
    this->endian=getEndian();
    this->buffer_size=sizeof(long double)+1;
    this->buffer=new char[this->buffer_size];
}
serializer::~serializer(){delete []this->buffer;}
/*
  Implementation of serializer
 */

template<typename T> serializer& serializer::operator<<(const T &value){
    WRITABLE_REQUIRED(this->_out);
    unsigned char value_type=NONE;
    numeric_detector<T> detector(value);
    value_type=detector.properly_type();
    this->buffer[0]=(char)value_type;
    if(!isBool(value_type)){
        switch(this->endian){
            case Endian::big:
                copy((char*)detector.start(),(char*)detector.end(),this->buffer+1);
                break;
            case Endian::little:
                reverse_copy((char*)detector.start(),(char*)detector.end(),this->buffer+1);
                break;
            default:
                throw logic_error("Not supported endian.");
        }
    }
    this->_out->write(this->buffer,detector.properly_size()+1);
    return (*this);
}
template<typename T> serializer& serializer::operator>>(T &ref){
    READABLE_REQUIRED(this->_in);
#ifdef DEBUG_SERIALIZER
    assert(this->_in->rdbuf()->in_avail()>0);
#else
    if(this->_in->rdbuf()->in_avail()<=0) throw out_of_range("There are no readable data.");
#endif
    
    this->_in->read(this->buffer,this->buffer_size);
    
#ifdef DEBUG_SERIALIZER
    assert(!is_str(this->buffer[0]));
#else
    if(is_str(this->buffer[0])){
        this->_in->seekg(-this->buffer_size,ios_base::cur);
        throw invalid_argument("The data is string. You have to specify a string variable.");
    }
#endif
    
    bool boolbuf;
    if(bool_value(this->buffer[0],&boolbuf)){
        ref=boolbuf;
        this->_in->seekg(-this->buffer_size+1,ios_base::cur);
        return (*this);
    }
#ifdef DEBUG_SERIALIZER
    assert((is_float(this->buffer[0])&&numeric_limits<T>::is_iec559)||(!is_float(this->buffer[0])&&numeric_limits<T>::is_integer));
#else
    if((!is_float(this->buffer[0])||!numeric_limits<T>::is_iec559)&&(is_float(this->buffer[0])||!numeric_limits<T>::is_integer)){
        this->_in->seekg(-this->buffer_size,ios_base::cur);
        if((!is_float(this->buffer[0])||!numeric_limits<T>::is_iec559)) throw invalid_argument("Tha data is integer. You have to specify a integer variable.");
        else if(is_float(this->buffer[0])||!numeric_limits<T>::is_integer) throw invalid_argument("Tha data is float. You have to specify a float variable.");
    }
#endif
    size_t size=properly_size((unsigned char)this->buffer[0]);
    this->_in->seekg(1+size-this->buffer_size,ios_base::cur);
    ref=0;
    switch(this->endian){
        case Endian::big:
            copy_backward(this->buffer+1,this->buffer+1+size,(char*)((&ref)+1));
            break;
        case Endian::little:
            reverse_copy(this->buffer+1,this->buffer+1+size,(char*)&ref);
            break;
        default:
            throw logic_error("Not supported endian.");
    }
#ifdef DEBUG_SERIALIZER
    cout<<ref<<endl;
#endif
    return (*this);
}

serializer& serializer::operator<<(const string &s){
    READABLE_REQUIRED(this->_in);
    this->_out->put(STRING);
    (*this->_out)<<s<<'\0';
    return (*this);
}

serializer& serializer::operator>>(string &str){
    READABLE_REQUIRED(this->_in);
    //I'm not sure if it is a bug that the pointer of istream is not incremented when using this->_in->get().
    //However this is fact that I should provide the alternative. Instead, I use this->_in->read(char_type*,streamsize).
    this->_in->read(this->buffer,1);
#ifdef DEBUG_SERIALIZER
    assert(this->_in->rdbuf()->in_avail()>0&&is_str((unsigned char)this->buffer[0]));
#else
    if(!is_str((unsigned char)this->buffer[0])||this->_in->rdbuf()->in_avail()<=0){
        this->_in->seekg(-1,ios_base::cur);
        if(!is_str((unsigned char)this->buffer[0])) throw invalid_argument("The data is not string. You have to specify a variable other than string.");
        if(this->_in->rdbuf()->in_avail()<=0) throw out_of_range("There are no readable data.");
    }
#endif
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
