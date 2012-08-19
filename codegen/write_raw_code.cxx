#include "generator.h"
#include <fstream>

using namespace std;
void generator::generate_write_raw(){
    for(decltype(this->types.size()) index=0;index<this->types.size();index++){
        ofstream raw_out(this->write_raw_sources[index]);
        raw_out<<"#include \""<<this->internal_header_file<<"\""<<endl;
        raw_out<<this->ns<<endl;
        raw_out<<this->write_raw_functions[index]<<"{"<<endl;
        raw_out<<this->types[index]<<" "<<"var;"<<endl;
        raw_out<<"rgen>>var;"<<endl;
        raw_out<<"wlog<<var<<endl;"<<endl;
        raw_out<<"w_obj++;"<<endl;
        raw_out<<"start.stump();"<<endl;
        raw_out<<"s<<var;"<<endl;
        raw_out<<"end.stump();"<<endl;
        raw_out<<"}"<<endl;
        raw_out.close();
    }
}
void generator::generate_read_raw(){
    for(decltype(this->types.size()) index=0;index<this->types.size();index++){
        ofstream raw_read(this->read_raw_sources[index]);
        raw_read<<"#include \""<<this->internal_header_file<<"\""<<endl;
        raw_read<<this->ns<<endl;
        raw_read<<this->read_raw_functions[index]<<"{"<<endl;
        raw_read<<this->types[index]<<" var;"<<endl;
        raw_read<<"start.stump();"<<endl;
        raw_read<<"s>>var;"<<endl;
        raw_read<<"end.stump();"<<endl;
        raw_read<<"rlog<<var<<endl;"<<endl;
        raw_read<<"r_obj++;"<<endl;
        raw_read<<"}"<<endl;
        raw_read.close();
    }
}
