#include "generator.h"
void generator::generate_write_map(){
    for(decltype(this->types.size()) key_index=0;key_index<this->types.size();key_index++)
        for(decltype(this->types.size()) value_index=0;value_index<this->types.size();value_index++){
            ofstream map_out(this->write_map_sources[(key_index*this->types.size())+value_index]);
            map_out<<"#include \""<<this->internal_header_file<<"\""<<endl<<this->ns<<endl;
            map_out<<this->write_map_functions[(key_index*this->types.size())+value_index]<<"{"<<endl;
            map_out<<"map <"<<this->types[key_index]<<","<<this->types[value_index]<<"> m;"<<endl;
            map_out<<"for(size_t counter=0;counter<"<<this->array_size<<";counter++){"<<endl;
            map_out<<"pair<"<<this->types[key_index]<<","<<this->types[value_index]<<"> p;"<<endl;
            map_out<<"rgen>>p.first>>p.second;"<<endl;
            map_out<<"m<<p;"<<endl;
            map_out<<"}"<<endl;
            map_out<<"wlog<<m<<endl;"<<endl;
            map_out<<"w_obj+=m.size();"<<endl;
            map_out<<"start.stump();"<<endl;
            map_out<<"s<<m;"<<endl;
            map_out<<"end.stump();"<<endl;
            map_out<<"}"<<endl;
            map_out.close();
        }
}
void generator::generate_read_map(){
    for(decltype(this->types.size()) key_index=0;key_index<this->types.size();key_index++)
        for(decltype(this->types.size()) value_index=0;value_index<this->types.size();value_index++){
            ofstream map_out(this->read_map_sources[(key_index*this->types.size())+value_index]);
            map_out<<"#include \""<<this->internal_header_file<<"\""<<endl<<this->ns<<endl;
            map_out<<this->read_map_functions[(key_index*this->types.size())+value_index]<<"{"<<endl;
            map_out<<"map<"<<this->types[key_index]<<","<<this->types[value_index]<<"> m;"<<endl;
            map_out<<"start.stump();"<<endl;
            map_out<<"s>>m;"<<endl;
            map_out<<"end.stump();"<<endl;
            map_out<<"rlog<<m<<endl;"<<endl;
            map_out<<"r_obj+=m.size();"<<endl;
            map_out<<"}"<<endl;
            map_out.close();
        }
}
