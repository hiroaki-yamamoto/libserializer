#pragma once

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class generator{
    public:
        generator(const char *,const size_t=20);
        void generate_write_raw();
        void generate_write_vector();
        void generate_write_list();
        void generate_write_map();
        
        void generate_read_raw();
        void generate_read_vector();
        void generate_read_list();
        void generate_read_map();
        
        void generate_front_source();
        void generate_headers();
    private:
        size_t array_size;
        vector<string> types,write_raw_sources,read_raw_sources,
        write_vec_sources,read_vec_sources,write_lst_sources,read_lst_sources,
        write_map_sources,read_map_sources,write_raw_functions,write_vec_functions,
        write_list_functions,write_map_functions,read_raw_functions,read_vec_functions,
        read_list_functions,read_map_functions;
        string   test_suffix,list_suffix,vector_suffix,map_prefix,internal_header_file,
                 write_prefix,read_prefix,include,ns,write_args,read_args,read_test,write_test;
};
