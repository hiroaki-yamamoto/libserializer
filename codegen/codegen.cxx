#include <iostream>
#include "generator.h"

extern "C"{
#if defined(_WIN32)||defined(_WIN64)
    #include <direct.h>
#elif defined(UNIX)
    #include <unistd.h>
#else
    #error The system is neither Windows nor UNIX. cd function uses direct.h on Windows system, and unistd.h on UNIX system
#endif
}

#ifndef _OPENMP
#error You must build with OpenMP.
#endif
using namespace std;

inline void cd(const char *dir){
#if defined(_WIN32)||defined(_WIN64)
    _chdir(dir);
#elif defined(UNIX)
    chdir(dir);
#endif
}

int main(int argc,const char *argv[]){
    if(argc<3){
        cout<<"Usage:"<<argv[0]<<" <File which is written about types.> <OutDir>"<<endl;
        return 1;
    }
    cd(argv[2]);
    generator gen(argv[1],10000);
#pragma omp parallel sections
    {
#pragma omp section
        gen.generate_write_raw();
#pragma omp section
        gen.generate_write_vector();
#pragma omp section
        gen.generate_write_list();
#pragma omp section
        gen.generate_write_map();
#pragma omp section
        gen.generate_read_raw();
#pragma omp section
        gen.generate_read_vector();
#pragma omp section
        gen.generate_read_list();
#pragma omp section
        gen.generate_read_map();
#pragma omp section
        gen.generate_front_source();
#pragma omp section
        gen.generate_headers();
    }
    cout<<"Writing test files have been generated."<<endl;
    cout<<"Reading test files have been generated."<<endl;
    cout<<"Front source code and headers have been generated."<<endl;
    return 0;
}
