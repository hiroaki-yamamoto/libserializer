#include "generator.h"
#include "operator.h"

#include <fstream>
#ifndef _OPENMP
#error "You must use compiler that supports OpenMP to build this generator."
#endif

#include <omp.h>

using namespace std;
generator::generator(const size_t array_size){
    this->array_size=array_size;
    this->test_suffix="_test";
    this->list_suffix="_list";
    this->vector_suffix="_vector";
    this->map_prefix="map_";
    this->internal_header_file="test_internal.h";
    this->write_prefix="w";
    this->read_prefix="r";
    this->include="#include <fstream>\n"
                  "#include <iostream>\n"
                  "#include <string>\n"
                  "#include <vector>\n"
                  "#include <list>\n"
                  "#include <map>\n"
                  "#include <typeinfo>\n"
                  "#include \"../librandomgenerator/randomgenerator.h\"\n"
                  "#include \"../libserializer/serializer.h\"\n"
                  "#include \"time_array.h\"\n"
                  "#include \"operator.hxx\"\n";
    this->ns="using namespace std;\n"
             "using namespace time_class;\n"
             "using namespace random_class;\n";
    this->write_test="void write_test(time_array &start,time_array &end)";
    this->read_test="void read_test(time_array &start,time_array &end)";
    this->write_args="(time_array &start,time_array &end,ostream &wlog,serializer &s,randomgenerator &rgen)";
    this->read_args="(time_array &start,time_array &end,ostream &rlog,serializer &s)";
#pragma omp parallel sections
    {
#pragma omp section
        {
            ifstream types("types.def");
            types>>this->types;
            types.close();
        }
#pragma omp section
        {
            ifstream aliases("aliases.def");
            aliases>>this->aliases;
            aliases.close();
        }
#pragma omp section
        {
            ifstream write_raw_file("write_raw_source.def");
            write_raw_file>>this->write_raw_sources;
            write_raw_file.close();
        }
#pragma omp section
        {
            ifstream read_raw_file("read_raw_source.def");
            read_raw_file>>this->read_raw_sources;
            read_raw_file.close();
        }
#pragma omp section
        {
            ifstream write_vec_file("write_vec_source.def");
            write_vec_file>>this->write_vec_sources;
            write_vec_file.close();
        }
#pragma omp section
        {
            ifstream read_vec_file("read_vec_source.def");
            read_vec_file>>this->read_vec_sources;
            read_vec_file.close();
        }
#pragma omp section
        {
            ifstream write_lst_file("write_lst_source.def");
            write_lst_file>>this->write_lst_sources;
            write_lst_file.close();
        }
#pragma omp section
        {
            ifstream read_lst_file("read_lst_source.def");
            read_lst_file>>this->read_lst_sources;
            read_lst_file.close();
        }
#pragma omp section
        {
            ifstream write_map_file("write_map_source.def");
            write_map_file>>this->write_map_sources;
            write_map_file.close();
        }
#pragma omp section
        {
            ifstream read_map_file("read_map_source.def");
            read_map_file>>this->read_map_sources;
            read_map_file.close();
        }
    }
#pragma omp parallel sections
    {
#pragma omp section
        {
            for(string alias:this->aliases){
                this->write_raw_functions<<("void "+this->write_prefix+alias+this->test_suffix+this->write_args);
                this->read_raw_functions<<("void "+this->read_prefix+alias+this->test_suffix+this->read_args);
                this->write_vec_functions<<("void "+this->write_prefix+alias+this->vector_suffix+this->test_suffix+this->write_args);
                this->read_vec_functions<<("void "+this->read_prefix+alias+this->vector_suffix+this->test_suffix+this->read_args);
                this->write_list_functions<<("void "+this->write_prefix+alias+this->list_suffix+this->test_suffix+this->write_args);
                this->read_list_functions<<("void "+this->read_prefix+alias+this->list_suffix+this->test_suffix+this->read_args);
            }
        }
#pragma omp section
        {
            for(string key:this->aliases)
                for(string value:this->aliases){
                    this->write_map_functions<<("void "+this->write_prefix+this->map_prefix+key+value+this->test_suffix+this->write_args);
                    this->read_map_functions<<("void "+this->read_prefix+this->map_prefix+key+value+this->test_suffix+this->read_args);
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
            string write_test_args="(start,end,wlog,os,rgen)";
            wtest<<"#include \"test.h\""<<endl;
            wtest<<"#include \""<<this->internal_header_file<<"\""<<endl;
            wtest<<this->ns<<endl;
            
            wtest<<this->write_test<<"{"<<endl;
            wtest<<"randomgenerator rgen;"<<endl;
            wtest<<"ofstream write(\"test.dat\"),wlog(\"log_write\");"<<endl;
            wtest<<"serializer os(write);"<<endl;
            for(string::size_type index=0;index<this->types.size();index++){
                string raw_function=this->write_prefix+this->aliases[index]+this->test_suffix+write_test_args,
                       list_function=this->write_prefix+this->aliases[index]+this->list_suffix+this->test_suffix+write_test_args,
                       vector_function=this->write_prefix+this->aliases[index]+this->vector_suffix+this->test_suffix+write_test_args;
                wtest<<"wlog<<\""<<this->types[index]<<" test:\"<<endl;"<<endl;
                wtest<<raw_function<<";"<<endl;
                wtest<<list_function<<";"<<endl;
                wtest<<vector_function<<";"<<endl;
                wtest<<"wlog<<endl;"<<endl;
            }
            
            for(string::size_type key_index=0;key_index<types.size();key_index++)
                for(string::size_type value_index=0;value_index<types.size();value_index++){
                    string function=this->write_prefix+this->map_prefix+this->aliases[key_index]+this->aliases[value_index]+this->test_suffix+write_test_args;
                    wtest<<"wlog<<\"map<"<<this->types[key_index]<<","<<this->types[value_index]<<">"<<" test:\"<<endl;"<<endl;
                    wtest<<function<<";"<<endl;
                    wtest<<"wlog<<endl;"<<endl;
                }
            wtest<<"os.close();"<<"write.close();"<<"wlog.close();"<<endl;
            wtest<<"}"<<endl;
            wtest.close();
        }
#pragma omp section
        {
            string read_test_args="(start,end,rlog,is)";
            ofstream rtest("read_test.cxx");
            rtest<<"#include \"test.h\""<<endl;
            rtest<<"#include \""<<this->internal_header_file<<"\""<<endl;
            rtest<<this->ns<<endl;
            rtest<<this->read_test<<"{"<<endl;
            rtest<<"ifstream read(\"test.dat\");"<<endl;
            rtest<<"ofstream rlog(\"log_read\");"<<endl;
            rtest<<"serializer is(read);"<<endl;
            for(string::size_type index=0;index<this->types.size();index++){
                string raw_function=this->read_prefix+this->aliases[index]+this->test_suffix+read_test_args,
                       list_function=this->read_prefix+this->aliases[index]+this->list_suffix+this->test_suffix+read_test_args,
                       vector_function=this->read_prefix+this->aliases[index]+this->vector_suffix+this->test_suffix+read_test_args;
                rtest<<"rlog<<\""<<types[index]<<" test:\"<<endl;"<<endl;
                rtest<<raw_function<<";"<<endl;
                rtest<<list_function<<";"<<endl;
                rtest<<vector_function<<";"<<endl;
                rtest<<"rlog<<endl;"<<endl;
            }
            
            for(string::size_type key_index=0;key_index<this->types.size();key_index++)
                for(string::size_type value_index=0;value_index<this->types.size();value_index++){
                    string function=this->read_prefix+this->map_prefix+this->aliases[key_index]+this->aliases[value_index]+this->test_suffix+read_test_args;
                    rtest<<"rlog<<\"map<"<<this->types[key_index]<<","<<this->types[value_index]<<">"<<" test:\"<<endl;"<<endl;
                    rtest<<function<<";"<<endl;
                    rtest<<"rlog<<endl;"<<endl;
                }
            rtest<<"is.close();"<<"read.close();"<<"rlog.close();"<<endl;
            rtest<<"}"<<endl;
            rtest.close();
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
            internal_header<<this->write_raw_functions<<endl;
            internal_header<<this->read_raw_functions<<endl;
            internal_header<<this->write_list_functions<<endl;
            internal_header<<this->read_list_functions<<endl;
            internal_header<<this->write_vec_functions<<endl;
            internal_header<<this->read_vec_functions<<endl;
            internal_header<<this->write_map_functions<<endl;
            internal_header<<this->read_map_functions<<endl;
            internal_header.close();
        }
#pragma omp section
        {
            ofstream header("test.h");
            header<<"#pragma once"<<endl;
            header<<"#include \"time_array.h\""<<endl;
            header<<"using namespace time_class;"<<endl;
            header<<this->write_test<<";"<<endl;
            header<<this->read_test<<";"<<endl;
            header.close();
        }
    }
}
