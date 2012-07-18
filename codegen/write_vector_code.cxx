#include "generator.h"
void generator::generate_write_vector(){
    for(decltype(this->types.size()) index=0;index<this->types.size();index++){
        ofstream vector_out(this->write_vec_sources[index]);
        vector_out<<"#include \""<<this->internal_header_file<<"\""<<endl;
        vector_out<<this->ns<<endl;
        vector_out<<this->write_vec_functions[index]<<"{"<<endl;
        vector_out<<"vector<"<<this->types[index]<<"> vec;"<<endl;
        vector_out<<"for(size_t counter=0;counter<"<<this->array_size<<";counter++){"<<endl;
        vector_out<<this->types[index]<<" value;"<<endl;
        vector_out<<"rgen>>value;"<<endl;
        vector_out<<"vec<<value;"<<endl;
        vector_out<<"}"<<endl;
        vector_out<<"wlog<<vec<<endl;"<<endl;
        vector_out<<"start.stump();"<<endl;
        vector_out<<"s<<vec;"<<endl;
        vector_out<<"end.stump();"<<endl;
        vector_out<<"}"<<endl;
        vector_out.close();
    }
}
void generator::generate_read_vector(){
    for(decltype(this->types.size()) index=0;index<this->types.size();index++){
        ofstream vector_read(this->read_vec_sources[index]);
        vector_read<<"#include \""<<this->internal_header_file<<"\""<<endl;
        vector_read<<this->ns<<endl;
        vector_read<<this->read_vec_functions[index]<<"{"<<endl;
        vector_read<<"vector<"<<this->types[index]<<"> vec;"<<endl;
        vector_read<<"start.stump();"<<endl;
        vector_read<<"s>>vec;"<<endl;
        vector_read<<"end.stump();"<<endl;
        vector_read<<"rlog<<vec<<endl;"<<endl;
        vector_read<<"}"<<endl;
        vector_read.close();
    }
}
