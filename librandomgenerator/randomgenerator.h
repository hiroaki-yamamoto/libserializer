#pragma once
#include<climits>
#include<ctime>
#include<cstring>
#include<string>
#include<random>

#ifdef DEBUG_RANDOM
#include <fstream>
#include <typeinfo>
#endif

using namespace std;
namespace random_class{
    class randomgenerator{
        public:
            randomgenerator(const string="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()~=-^|~\\@`[{;+:*]}_/?.>,<\n",const size_t=0,const size_t=20);
            ~randomgenerator();
            size_t max() const;
            size_t string_size() const;
            void max(const size_t);
            void string_size(const size_t);
            randomgenerator &operator>>(float &);
            randomgenerator &operator>>(double &);
            randomgenerator &operator>>(long double &);
            randomgenerator &operator>>(bool &);
            randomgenerator &operator>>(string &);
            randomgenerator &operator>>(char &);
            randomgenerator &operator>>(unsigned char &);
            template <typename T> randomgenerator &operator>>(T &to){
                for(unsigned char *pointer=(unsigned char *)&to;pointer<((unsigned char *)&to)+sizeof(to);pointer++) *pointer=(unsigned char)((*this->generator)()&0xff);
                if(this->_max>0) to%=this->_max;
#ifdef DEBUG_RANDOM
                this->writeDump((string("generated_")+typeid(T).name()+string(".log")).c_str(),to);
#endif
                return (*this);
            }
        private:
            size_t _max,_ssize;
            string _map;
            mt19937 *generator;
#ifdef DEBUG_RANDOM
            template <class T> void writeDump(const char *filename,const T &value){
                ofstream log(filename,ios::app);
                for(unsigned char *p=(unsigned char *)&value;p<(unsigned char*)&value+sizeof(value);p++)
                    log<<((*p<0x10)?"0":"")<<hex<<(unsigned short)*p<<" ";
                log<<endl;
                log.close();
            }
#endif
    }typedef randomGenerator,Randomgenerator,RandomGenerator,random_generator;
}
