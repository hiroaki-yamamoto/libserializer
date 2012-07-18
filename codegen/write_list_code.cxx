#include "generator.h"
void generator::generate_write_list(){
    for(decltype(this->types.size()) index=0;index<this->types.size();index++){
        ofstream list_out(this->write_lst_sources[index]);
        list_out<<"#include \""<<this->internal_header_file<<"\""<<endl;
        list_out<<this->ns<<endl;
        list_out<<this->write_list_functions[index]<<"{"<<endl;
        list_out<<"list<"<<this->types[index]<<"> lst;"<<endl;
        list_out<<"for(size_t counter=0;counter<"<<array_size<<";counter++){"<<endl;
        list_out<<this->types[index]<<" value;"<<endl;
        list_out<<"rgen>>value;"<<endl;
        list_out<<"lst<<value;"<<endl;
        list_out<<"}"<<endl;
        list_out<<"wlog<<lst<<endl;"<<endl;
        list_out<<"start.stump();"<<endl;
        list_out<<"s<<lst;"<<endl;
        list_out<<"end.stump();"<<endl;
        list_out<<"}"<<endl;
        list_out.close();
    }
}
void generator::generate_read_list(){
    for(decltype(this->types.size()) index=0;index<this->types.size();index++){
        ofstream list_read(this->read_lst_sources[index]);
        list_read<<"#include \""<<this->internal_header_file<<"\""<<endl;
        list_read<<this->ns<<endl;
        list_read<<this->read_list_functions[index]<<"{"<<endl;
        list_read<<"list<"<<this->types[index]<<"> lst;"<<endl;
        list_read<<"start.stump();"<<endl;
        list_read<<"s>>lst;"<<endl;
        list_read<<"end.stump();"<<endl;
        list_read<<"rlog<<lst<<endl;"<<endl;
        list_read<<"}"<<endl;
        list_read.close();
    }
}
