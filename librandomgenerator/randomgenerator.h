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
/*! Random number generator namespace. */
namespace random_class{
    /*!
        Random number generator.
        This class generates random number with mt19937 algorithm having time as a seed.
     */
    class randomgenerator{
        public:
            /*!
              A constructor.
              If a string is specified to const string, this class generates random string mapped by the specified string when operator>>(string &), operator>>(char &), or operator>>(unsigned char &) is called. \n
              By default, const string is capitalized alphabets, uncapitalized alphabets, 0-9, "!"#$%&'()~=-^|~\\@`[{;+:*]}_/?.>,<" and new line code.
              
              If const size_t is set to n, this generator generates string consisting of n character/a number that is smaller than n. \n
              If this parameter is set to 0, the max value is enough-large and the max character size is set to 20.
              By default, it is set to 0.
              
              @param "const string" Character map to generate random string.
              @param "const size_t" Max character size or max value.
             */
            randomgenerator(const string="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()~=-^|~\\@`[{;+:*]}_/?.>,<\n",const size_t=0);
            /*!
              A destructor.
             */
            ~randomgenerator();
            /*!
              Returns max character size or max value.
              @return max character size or max value.
              @see max(const size_t)
             */
            size_t max() const;
            /*!
              Sets max character size/max value to const size_t.
              @param "const size_t" max character size/max value.
              @see max()
             */
            void max(const size_t);
            /*!
              Generates a random number.
              Generates a random number that is smaller than max value.
              @param float The variable to store the generated ramdom number.
              @return (*this) after generating number.
              @see max()
              @see max(const size_t)
              @see operator>>(double &)
              @see operator>>(long double &)
              @see operator>>(bool &)
              @see operator>>(string &)
              @see operator>>(char &)
              @see operator>>(T &)
              @see operator>>(unsigned char &)
             */
            randomgenerator &operator>>(float &);
            /*!
              Generates a random number.
              Generates a random number that is smaller than max value.
              @param double The variable to store the generated ramdom number.
              @return (*this) after generating number.
              @see max()
              @see max(const size_t)
              @see operator>>(float &)
              @see operator>>(long double &)
              @see operator>>(bool &)
              @see operator>>(string &)
              @see operator>>(char &)
              @see operator>>(T &)
              @see operator>>(unsigned char &)
             */
            randomgenerator &operator>>(double &);
            /*!
              Generates a random number.
              Generates a random number that is smaller than max value.
              @param "long double" The variable to store the generated ramdom number.
              @return (*this) after generating number.
              @see max()
              @see max(const size_t)
              @see operator>>(double &)
              @see operator>>(float &)
              @see operator>>(bool &)
              @see operator>>(string &)
              @see operator>>(char &)
              @see operator>>(T &)
              @see operator>>(unsigned char &)
             */
            randomgenerator &operator>>(long double &);
            /*!
              Generates a random number.
              Generates a random number that is smaller than max value.
              @param bool The variable to store the generated ramdom number.
              @return (*this) after generating number.
              @see max()
              @see max(const size_t)
              @see operator>>(double &)
              @see operator>>(long double &)
              @see operator>>(float &)
              @see operator>>(string &)
              @see operator>>(char &)
              @see operator>>(T &)
              @see operator>>(unsigned char &)
             */
            randomgenerator &operator>>(bool &);
            /*!
              Generates a random string.
              Generates a random string of which size is smaller than max value.
              @param string The variable to store the generated ramdom number.
              @return (*this) after generating number.
              @see max()
              @see max(const size_t)
              @see operator>>(double &)
              @see operator>>(long double &)
              @see operator>>(bool &)
              @see operator>>(float &)
              @see operator>>(char &)
              @see operator>>(T &)
              @see operator>>(unsigned char &)
             */
            randomgenerator &operator>>(string &);
            /*!
              Generates a random character.
              Generates a random character.
              @param char The variable to store the generated ramdom number..
              @return (*this) after generating number.
              @see max()
              @see max(const size_t)
              @see operator>>(double &)
              @see operator>>(long double &)
              @see operator>>(bool &)
              @see operator>>(string &)
              @see operator>>(float &)
              @see operator>>(T &)
              @see operator>>(unsigned char &)
             */
            randomgenerator &operator>>(char &);
            /*!
              Generates a random character.
              Generates a random character.
              @param char The variable to store the generated ramdom number..
              @return (*this) after generating number.
              @see max()
              @see max(const size_t)
              @see operator>>(double &)
              @see operator>>(long double &)
              @see operator>>(bool &)
              @see operator>>(string &)
              @see operator>>(float &)
              @see operator>>(T &)
              @see operator>>(char &)
             */
            randomgenerator &operator>>(unsigned char &);
            /*!
              Generates a random number.
              Generates a random number that is smaller than max value.
              @warning T must be a primitive type. If not, the behavior is undefined.
              
              @param "typename T" The type of the variable to store the generated rundom number.
              @param to The variable to store the generated ramdom number.
              @return (*this) after generating number.
              @see max()
              @see max(const size_t)
              @see operator>>(double &)
              @see operator>>(long double &)
              @see operator>>(bool &)
              @see operator>>(string &)
              @see operator>>(char &)
              @see operator>>(float &)
              @see operator>>(unsigned char &)
             */
            template <typename T> randomgenerator &operator>>(T &to){
                for(unsigned char *pointer=(unsigned char *)&to;pointer<((unsigned char *)&to)+sizeof(to);pointer++) *pointer=(unsigned char)((*this->generator)()&0xff);
                if(this->_max>0) to%=this->_max;
#ifdef DEBUG_RANDOM
                this->writeDump((string("generated_")+typeid(T).name()+string(".log")).c_str(),to);
#endif
                return (*this);
            }
        private:
            size_t _max;
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
