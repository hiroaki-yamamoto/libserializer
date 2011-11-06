#include "abs.h"
using namespace converter;

Abs::Abs(const unsigned long long value){
    this->_dbl_mode=false;
    this->_int_value=value;
}
Abs::Abs(const long double value){
    this->_dbl_mode=true;
    this->_dbl_value=value;
}
Abs::Abs(){this->_dbl_mode=false;}

bool Abs::is_dblMode() const{return this->_dbl_mode;}
unsigned long long Abs::int_value() const{return this->_int_value;}
double Abs::dbl_value() const{return this->_dbl_value;}
bool Abs::operator==(const Abs &ref){
    return (this->_dbl_mode&&ref.is_dblMode()&&this->_dbl_value==ref.dbl_value())||
           (!this->_dbl_mode&&ref.is_dblMode()&&(long double)this->_int_value==ref.dbl_value())||
           (this->_dbl_mode&&!ref.is_dblMode()&&this->_dbl_value==(long double)ref.int_value())||
            this->_int_value==ref.int_value();
}
bool Abs::operator>(const Abs &ref){
    return (this->_dbl_mode&&ref.is_dblMode()&&this->_dbl_value>ref.dbl_value())||
           (!this->_dbl_mode&&ref.is_dblMode()&&(long double)this->_int_value>ref.dbl_value())||
           (this->_dbl_mode&&!ref.is_dblMode()&&this->_dbl_value>(long double)ref.int_value())||
                                                this->_int_value>ref.int_value();
}
bool Abs::operator!=(const Abs &ref){return !((*this)==ref);}
bool Abs::operator>=(const Abs &ref){return !((*this)<ref);}
bool Abs::operator<=(const Abs &ref){return !((*this)>ref);}
bool Abs::operator<(const Abs &ref){return ((*this)<=ref)&&((*this)!=ref);}
std::ostream& converter::operator<<(std::ostream &o,const converter::Abs &r){
    if(r._dbl_mode) o<<r._dbl_value;
    else o<<r._int_value;
    return o;
}
