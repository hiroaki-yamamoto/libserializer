#include "time_array.h"
#include <cstring>
using namespace time_class;
using namespace std;

time_array &time_array::operator<<(const time_type &val){this->push_back(val);return (*this);}
time_array time_array::operator-(const time_array &ref){
    time_array result;
    for(time_array::size_type index=0;index<this->size()||index<ref.size();index++)
        result.push_back(((index<this->size())?(*this)[index]:zero())-((index<ref.size())?ref[index]:zero()));
    return result;
}
time_array &time_array::operator-=(const time_array &ref){
    for(time_array::size_type index=0;index<this->size()||index<ref.size();index++){
        if(index<this->size()){if(index<ref.size()) (*this)[index]-=ref[index];}
        else this->push_back(zero()-ref[index]);
    }
    return (*this);
}
void time_array::stump(){
    time_type t;
#ifdef UNIX
    gettimeofday(&t,nullptr);
#else
    t=time(nullptr);
#endif
    this->push_back(t);
}
time_type time_array::sum(){
    time_type result=zero();
    for(time_type value:(*this)) result+=value;
    return result;
}
#ifdef UNIX
time_type time_class::operator+(const time_type &a,const time_type &b){
    time_type result;
    result.tv_usec=a.tv_usec+b.tv_usec;
    result.tv_sec=a.tv_sec+b.tv_sec;
    if(result.tv_usec>=1000000){
        result.tv_usec-=1000000;
        result.tv_sec++;
    }
    return result;
}
time_type time_class::operator-(const time_type &a,const time_type &b){
    time_type t;
    t.tv_usec=a.tv_usec-b.tv_usec;
    t.tv_sec=a.tv_sec-b.tv_sec;
    if(t.tv_usec<0){
        t.tv_usec=1000000+t.tv_usec;
        t.tv_sec--;
    }
    return t;
}
time_type &time_class::operator+=(time_type &a,const time_type &b){
    a=a+b;
    return a;
}
time_type &time_class::operator-=(time_type &a,const time_type &b){
    a=a-b;
    return a;
}
ostream &time_class::operator<<(ostream &out,const time_type &a){
    streamsize width=out.width();
    out<<a.tv_sec<<".";
    out.fill('0');
    out.width(6);
    out<<a.tv_usec;
    out.width(width);
    return out;
}
#endif
time_type time_class::zero(){
    time_type result;
    memset(&result,0,sizeof(result));
    return result;
}
ostream &time_class::operator<<(ostream &out,const time_array &array){
    for(auto value:array){out<<value<<" sec."<<endl;}
    return out;
}
