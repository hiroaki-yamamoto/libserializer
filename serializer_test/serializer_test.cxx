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

#include <test.h>
#include <time_array.h>
#include <operator.hxx>

using namespace std;
using namespace time_class;

int main(){
    ios::sync_with_stdio(false);
    cout<<"Serializer test tool:"<<endl<<"====================="<<endl;
    try{
        time_array start,end;
        size_t w_obj=0,r_obj=0;
        cout<<"Writing test"<<endl;
        write_test(start,end,w_obj);
        end-=start;
#ifdef SHOW_TIMEDIFF
        cout<<"Time diff. :"<<endl;
        cout<<end<<endl;
#endif
        cout<<"Writing time:"<<end.sum()<<" sec."<<endl;
        cout<<"Number of written objects:"<<w_obj<<endl;
        
        start.clear();
        end.clear();
        
        cout<<"Reading test"<<endl;
        read_test(start,end,r_obj);
        end-=start;
#ifdef SHOW_TIMEDIFF
        cout<<"Time diff. :"<<endl;
        cout<<end<<endl;
#endif
        cout<<"Reading time:"<<end.sum()<<" sec."<<endl;
        cout<<"Number of read objects:"<<r_obj<<endl;
    }catch(const exception e){
        cout<<e.what()<<endl;
        terminate();
    }catch(const char *e){
        cout<<e<<endl;
        terminate();
    }
    return 0;
}
