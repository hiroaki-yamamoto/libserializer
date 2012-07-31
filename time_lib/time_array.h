#pragma once
#include <vector>
#include <iostream>
#ifdef UNIX
    extern "C"{
        #include <sys/time.h>
    }
    typedef struct timeval time_type;
#else
    #include <ctime>
    typedef time_t time_type;
#endif

using namespace std;

namespace time_class{
#if defined(_WIN32)||defined(_WIN64)
    __declspec(dllexport) class time_array:public vector<time_type>
#else
    class time_array:public vector<time_type>
#endif
    {
        public:
            time_array &operator<<(const time_type &);
            time_array operator-(const time_array &);
            time_array &operator-=(const time_array &);
            time_type sum();
            void stump();
    };
#ifdef UNIX
    time_type operator+(const time_type &,const time_type &);
    time_type operator-(const time_type &,const time_type &);
    time_type &operator+=(time_type &,const time_type &);
    time_type &operator-=(time_type &,const time_type &);
    ostream &operator<<(ostream &,const time_type &);
#endif
    ostream &operator<<(ostream &,const time_array &);
    time_type zero();
}
