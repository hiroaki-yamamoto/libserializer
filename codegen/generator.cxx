#include "generator.h"
#include "operator.h"

#include <fstream>
#ifndef _OPENMP
#error "You must use compiler that supports OpenMP to build this generator."
#endif

#include <omp.h>

using namespace std;

generator::generator(const char *type_path,const size_t array_size){
    this->array_size=array_size;
    this->test_suffix="_test";
    this->list_suffix="_list";
    this->vector_suffix="_vector";
    this->map_prefix="map_";
    this->internal_header_file="test_internal.h";
    this->write_prefix="w_";
    this->read_prefix="r_";
    this->include="#include <fstream>\n"
                  "#include <iostream>\n"
                  "#include <string>\n"
                  "#include <vector>\n"
                  "#include <list>\n"
                  "#include <map>\n"
                  "#include <randomgenerator.h>\n"
                  "#include <serializer.h>\n"
                  "#include <time_array.h>\n"
                  "#include <operator.hxx>\n";
    this->ns="using namespace std;\n"
             "using namespace time_class;\n"
             "using namespace random_class;\n";
    this->write_test="void write_test(time_array &start,time_array &end,size_t &w_obj)";
    this->read_test="void read_test(time_array &start,time_array &end,size_t &r_obj)";
    this->write_args="(time_array &start,time_array &end,ostream &wlog,serializer &s,randomgenerator &rgen,size_t &w_obj)";
    this->read_args="(time_array &start,time_array &end,ostream &rlog,serializer &s,size_t &r_obj)";

#pragma omp parallel sections
    {
#pragma omp section
        {
            ifstream types(type_path);
            types>>this->types;
            types.close();
        }
    }
    
#pragma omp parallel sections
    {
#pragma omp section
        {
            for(string type:this->types){
                for(char &t_c:type) if(t_c==' ') t_c='_';
                this->write_raw_sources<<"write_"+type+".cxx";
                this->read_raw_sources<<"read_"+type+".cxx";
            }
        }
#pragma omp section
        {
            for(string type:this->types){
                for(char &t_c:type) if(t_c==' ') t_c='_';
                this->write_vec_sources<<"write_vec_"+type+".cxx";
                this->read_vec_sources<<"read_vec_"+type+".cxx";
            }
        }
#pragma omp section
        {
            for(string type:this->types){
                for(char &t_c:type) if(t_c==' ') t_c='_';
                this->write_lst_sources<<"write_lst_"+type+".cxx";
                this->read_lst_sources<<"read_lst_"+type+".cxx";
            }
        }
#pragma omp section
        {
            for(string key:this->types){
                for(char &t_c:key) if(t_c==' ') t_c='_';
                for(string value:this->types){
                    for(char &t_c:value) if(t_c==' ') t_c='_';
                    this->write_map_sources<<"write_map_"+key+"_"+value+".cxx";
                    this->read_map_sources<<"read_map_"+key+"_"+value+".cxx";
                }
            }
        }
    }
    
#pragma omp parallel sections
    {
#pragma omp section
        {
            for(string type:this->types){
                for(char &t_c:type) if(t_c==' ') t_c='_';
                this->write_raw_functions<<"void "+this->write_prefix+type+this->test_suffix+this->write_args;
                this->read_raw_functions<<"void "+this->read_prefix+type+this->test_suffix+this->read_args;
                
                this->write_vec_functions<<"void "+this->write_prefix+type+this->vector_suffix+this->test_suffix+this->write_args;
                this->read_vec_functions<<"void "+this->read_prefix+type+this->vector_suffix+this->test_suffix+this->read_args;
                
                this->write_list_functions<<"void "+this->write_prefix+type+this->list_suffix+this->test_suffix+this->write_args;
                this->read_list_functions<<"void "+this->read_prefix+type+this->list_suffix+this->test_suffix+this->read_args;
            }
        }
#pragma omp section
        {
            for(string key:this->types){
                for(char &t_c:key) if(t_c==' ') t_c='_';
                for(string value:this->types){
                    for(char &t_c:value) if(t_c==' ') t_c='_';
                    this->write_map_functions<<"void "+this->write_prefix+this->map_prefix+key+"_"+value+this->test_suffix+this->write_args;
                    this->read_map_functions<<"void "+this->read_prefix+this->map_prefix+key+"_"+value+this->test_suffix+this->read_args;
                }
            }
        }
    }
}
void generator::generate_front_source(){
#pragma omp parallel sections
    {
#pragma omp section
        {
            ofstream wtest("write_test.cxx");
            string write_test_args="(start,end,wlog,os,rgen,w_obj)";
            wtest<<"#include \"test.h\""<<endl;
            wtest<<"#include \""<<this->internal_header_file<<"\""<<endl;
            wtest<<this->ns<<endl;
            
            wtest<<this->write_test<<"{"<<endl;
            wtest<<"randomgenerator rgen;"<<endl;
            wtest<<"ofstream write(\"test.dat\"),wlog(\"log_write\");"<<endl;
            wtest<<"serializer os(write);"<<endl;
            
            for(string type:this->types){
                wtest<<"wlog<<\""<<type<<" test:\"<<endl;"<<endl;
                for(char &t_c:type) if(t_c==' ') t_c='_';
                string raw_function=this->write_prefix+type+this->test_suffix+write_test_args,
                       list_function=this->write_prefix+type+this->list_suffix+this->test_suffix+write_test_args,
                       vector_function=this->write_prefix+type+this->vector_suffix+this->test_suffix+write_test_args;
                wtest<<raw_function<<";"<<endl;
                wtest<<list_function<<";"<<endl;
                wtest<<vector_function<<";"<<endl;
                wtest<<"wlog<<endl;"<<endl;
            }
            
            for(string key:this->types){
                string key_b=key;
                for(char &t_c:key) if(t_c==' ') t_c='_';
                for(string value:this->types){
                    wtest<<"wlog<<\"map<"<<key_b<<","<<value<<">"<<" test:\"<<endl;"<<endl;
                    for(char &t_c:value) if(t_c==' ') t_c='_';
                    string function=this->write_prefix+this->map_prefix+key+"_"+value+this->test_suffix+write_test_args;
                    wtest<<function<<";"<<endl;
                    wtest<<"wlog<<endl;"<<endl;
                }
            }
            wtest<<"os.close();"<<"write.close();"<<"wlog.close();"<<endl;
            wtest<<"}"<<endl;
            wtest.close();
        }
#pragma omp section
        {
            string read_test_args="(start,end,rlog,is,r_obj)";
            ofstream rtest("read_test.cxx");
            rtest<<"#include \"test.h\""<<endl;
            rtest<<"#include \""<<this->internal_header_file<<"\""<<endl;
            rtest<<this->ns<<endl;
            rtest<<this->read_test<<"{"<<endl;
            rtest<<"ifstream read(\"test.dat\");"<<endl;
            rtest<<"ofstream rlog(\"log_read\");"<<endl;
            rtest<<"serializer is(read);"<<endl;
            for(string type:this->types){
                rtest<<"rlog<<\""<<type<<" test:\"<<endl;"<<endl;
                for(char &t_c:type) if(t_c==' ') t_c='_';
                
                string raw_function=this->read_prefix+type+this->test_suffix+read_test_args,
                       list_function=this->read_prefix+type+this->list_suffix+this->test_suffix+read_test_args,
                       vector_function=this->read_prefix+type+this->vector_suffix+this->test_suffix+read_test_args;
                
                rtest<<raw_function<<";"<<endl;
                rtest<<list_function<<";"<<endl;
                rtest<<vector_function<<";"<<endl;
                rtest<<"rlog<<endl;"<<endl;
            }
            
            for(string key:this->types){
                string key_b=key;
                for(char &t_c:key) if(t_c==' ') t_c='_';
                for(string value:this->types){
                    rtest<<"rlog<<\"map<"<<key_b<<","<<value<<">"<<" test:\"<<endl;"<<endl;
                    for(char &t_c:value) if(t_c==' ') t_c='_';
                    string function=this->read_prefix+this->map_prefix+key+"_"+value+this->test_suffix+read_test_args;
                    rtest<<function<<";"<<endl;
                    rtest<<"rlog<<endl;"<<endl;
                }
            }
            
            rtest<<"is.close();"<<"read.close();"<<"rlog.close();"<<endl;
            rtest<<"}"<<endl;
            rtest.close();
            
        }
#pragma omp section
        {
            ofstream sources_raw("sources_raw.def"),sources_lst("sources_lst.def"),
                    sources_vec("sources_vec.def"),sources_map("sources_map.def");
            
            sources_raw<<this->write_raw_sources<<this->read_raw_sources;
            sources_lst<<this->write_lst_sources<<this->read_lst_sources;
            sources_vec<<this->write_vec_sources<<this->read_vec_sources;
            sources_map<<this->write_map_sources<<this->read_map_sources;
            
            sources_raw.close();
            sources_lst.close();
            sources_vec.close();
            sources_map.close();
        }
    }
}
void generator::generate_headers(){
#pragma omp parallel sections
    {
#pragma omp section
        {
            ofstream internal_header(this->internal_header_file);
            internal_header<<"#pragma once"<<endl;
            internal_header<<this->include<<this->ns<<endl;
            
            //First make a list that contains addresses of all written function.
            list<vector<string> *> functions_list;
            functions_list.push_back(&(this->write_raw_functions));
            functions_list.push_back(&(this->read_raw_functions));
            functions_list.push_back(&(this->write_list_functions));
            functions_list.push_back(&(this->read_list_functions));
            functions_list.push_back(&(this->write_vec_functions));
            functions_list.push_back(&(this->read_vec_functions));
            functions_list.push_back(&(this->write_map_functions));
            functions_list.push_back(&(this->read_map_functions));
            
            //Then, write all functions into internal_header with functions_list.
            for(vector<string> *functions:functions_list){
                for(string function:*functions) internal_header<<
                                                  #if defined(_WIN32)||defined(_WIN64)
                                                                  "__declspec(dllexport) "<<
                                                  #endif
                                                                  function<<";"<<endl;
                internal_header<<endl;
            }
            internal_header.close();
        }
#pragma omp section
        {
            ofstream header("test.h");
            header<<"#pragma once"<<endl;
            header<<"#include \"time_array.h\""<<endl;
            header<<"using namespace time_class;"<<endl;
            header<<
            #if defined(_WIN32)||defined(_WIN64)
                            "__declspec(dllexport) "<<
            #endif
                        this->write_test<<";"<<endl;
            header<<
             #if defined(_WIN32)||defined(_WIN64)
                             "__declspec(dllexport) "<<
             #endif
                     this->read_test<<";"<<endl;
            header.close();
        }
    }
}
