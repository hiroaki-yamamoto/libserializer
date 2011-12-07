#include <iostream>
#include <exception>
#include <sstream>
#ifdef UNIX
    extern "C"{
        #include <sys/time.h>
    }
#else
    #include <ctime>
#endif

#include "test.h"
#include "time_array.h"
#include "operator.hxx"

using namespace std;
using namespace time_class;

int main(){
    ios::sync_with_stdio(false);
    cout<<"Serializer test tool:"<<endl<<"====================="<<endl;
    try{
        time_array start,end;
        cout<<"Writing test"<<endl;
        write_test(start,end);
        end-=start;
#ifdef SHOW_TIMEDIFF
        cout<<"Time diff. :"<<endl;
        cout<<end<<endl;
#endif
        cout<<"Writing time:"<<end.sum()<<" sec."<<endl;
        
        start.clear();
        end.clear();
        
        cout<<"Reading test"<<endl;
        read_test(start,end);
        end-=start;
#ifdef SHOW_TIMEDIFF
        cout<<"Time diff. :"<<endl;
        cout<<end<<endl;
#endif
        cout<<"Reading time:"<<end.sum()<<" sec."<<endl;
    }catch(const exception e){
        cout<<e.what()<<endl;
        terminate();
    }catch(const char *e){
        cout<<e<<endl;
        terminate();
    }
    return 0;
}
