#include <iostream>
#include "generator.h"
#ifndef _OPENMP
#error "You must build with OpenMP."
#endif

using namespace std;

int main(){
    generator gen(10000);
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
