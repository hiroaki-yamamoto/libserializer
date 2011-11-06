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

#include "../libserializer/serializer.h"
#include "../librandomgenerator/randomgenerator.h"
#include "operator.hxx"
#include <fstream>
#include <map>

using namespace std;
using namespace time_class;

using namespace random_class;

int main(){
    ios::sync_with_stdio(false);
    cout<<"Serializer test tool:"<<endl<<"====================="<<endl;
    try{
        time_array start,end;
        cout<<"Writing test"<<endl;
        write_test(start,end);
        end-=start;
        cout<<"Time diff. :"<<endl;
        cout<<end<<endl;
        cout<<"Writing time:"<<end.sum()<<" sec."<<endl;
        
        start.clear();
        end.clear();
        
        cout<<"Reading test"<<endl;
        read_test(start,end);
        end-=start;
        cout<<"Time diff. :"<<endl;
        cout<<end<<endl;
        cout<<"Reading time:"<<end.sum()<<" sec."<<endl;
    }catch(const exception e){
        cout<<e.what()<<endl;
        terminate();
    }catch(const char *e){
        cout<<e<<endl;
        terminate();
    }
    
    /*ofstream obuf("test.dat",ios::binary);
    serializer os(obuf);
    randomgenerator rgen;
    vector<int> a;
    time_array tarray;
    for(unsigned int counter=0;counter<200000;counter++){
        int b;
        rgen>>b;
        a<<b;
    }
    tarray.stump();
    os<<a;
    tarray.stump();
    os.close();
    obuf.close();
    
    cout<<"Writing time:"<<tarray[1]-tarray[0]<<" sec."<<endl;
    tarray.clear();
    
    ifstream ibuf("test.dat",ios::binary);
    serializer is(ibuf);
    vector<int> c;
    
    tarray.stump();
    is>>c;
    tarray.stump();
    is.close();
    ibuf.close();
    
    cout<<"Writing time:"<<tarray[1]-tarray[0]<<" sec."<<endl;
    tarray.clear();*/
    
    /*ofstream obuf("test.dat",ios::binary),wlog("log_write"),rlog("log_read");
    serializer os(obuf);
    map<long double,long double> a;
    time_array tarray;
    for(unsigned int counter=0;counter<200000;counter++)
        a.insert(make_pair<long double,long double>(counter,counter));
    tarray.stump();
    os<<a;
    tarray.stump();
    wlog<<a<<endl;
    os.close();
    obuf.close();
    wlog.close();
    
    cout<<"Writing time:"<<tarray[1]-tarray[0]<<" sec."<<endl;
    tarray.clear();
    
    ifstream ibuf("test.dat",ios::binary);
    serializer is(ibuf);
    map<long double,long double> c;
    
    tarray.stump();
    is>>c;
    tarray.stump();
    rlog<<c;
    is.close();
    ibuf.close();
    rlog.close();
    
    cout<<"Writing time:"<<tarray[1]-tarray[0]<<" sec."<<endl;
    tarray.clear();*/
    return 0;
}
