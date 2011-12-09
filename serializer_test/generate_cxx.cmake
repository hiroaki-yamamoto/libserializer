set(codegen_working_dir "${serializer_test_BINARY_DIR}/generated")

function(cxx_name)
    set(alias
        "str"
        "bln"
        "ch"
        "sh"
        "i"
        "l"
        "ll"
        "uch"
        "ush"
        "ui"
        "ul"
        "ull"
        "flt"
        "dbl"
        "ldbl"
    )
    set(types
        "string" "bool" "char" "short" "int" "long" "long long" 
        "unsigned char" "unsigned short" "unsigned int" "unsigned long" "unsigned long long"
        "float" "double" "long double"
    )
    string(REPLACE ";" "\n" alias_file "${alias}")
    string(REPLACE ";" "\n" types_file "${types}")
    file(WRITE "${codegen_working_dir}/aliases.def" "${alias_file}")
    file(WRITE "${codegen_working_dir}/types.def" "${types_file}")

    set(write_raw_test_source "${codegen_working_dir}/write_raw.cxx")
    set(write_vec_test_source "${codegen_working_dir}/write_vec.cxx")
    set(write_lst_test_source "${codegen_working_dir}/write_lst.cxx")
    set(write_test_source "${codegen_working_dir}/write_test.cxx")

    set(read_raw_test_source "${codegen_working_dir}/read_raw.cxx")
    set(read_vec_test_source "${codegen_working_dir}/read_vec.cxx")
    set(read_lst_test_source "${codegen_working_dir}/read_lst.cxx")
    set(read_test_source "${codegen_working_dir}/read_test.cxx")

    set(write_raw_test_source "${write_raw_test_source}" PARENT_SCOPE)
    set(write_vec_test_source "${write_vec_test_source}" PARENT_SCOPE)
    set(write_lst_test_source "${write_lst_test_source}" PARENT_SCOPE)
    set(write_test_source "${write_test_source}" PARENT_SCOPE)

    set(read_raw_test_source "${read_raw_test_source}" PARENT_SCOPE)
    set(read_vec_test_source "${read_vec_test_source}" PARENT_SCOPE)
    set(read_lst_test_source "${read_lst_test_source}" PARENT_SCOPE)
    set(read_test_source "${read_test_source}" PARENT_SCOPE)
    
    foreach(key ${alias})
        foreach(value ${alias})
            list(APPEND write_map_test_source "${codegen_working_dir}/write_map_${key}${value}_test.cxx")
            list(APPEND read_map_test_source "${codegen_working_dir}/read_map_${key}${value}_test.cxx")
        endforeach(value ${alias})
    endforeach(key)
    set(write_map_test_source ${write_map_test_source} PARENT_SCOPE)
    set(read_map_test_source ${read_map_test_source} PARENT_SCOPE)

    string(REPLACE ";" "\n" source_wmap "${write_map_test_source}")
    string(REPLACE ";" "\n" source_rmap "${read_map_test_source}")

    file(WRITE "${codegen_working_dir}/write_raw_source.def" "${write_raw_test_source}")
    file(WRITE "${codegen_working_dir}/write_vec_source.def" "${write_vec_test_source}")
    file(WRITE "${codegen_working_dir}/write_lst_source.def" "${write_lst_test_source}")
    file(WRITE "${codegen_working_dir}/write_map_source.def" "${source_wmap}")
    file(WRITE "${codegen_working_dir}/write_test_source.def" "${source_write_test}")

    file(WRITE "${codegen_working_dir}/read_raw_source.def" "${read_raw_test_source}")
    file(WRITE "${codegen_working_dir}/read_vec_source.def" "${read_vec_test_source}")
    file(WRITE "${codegen_working_dir}/read_lst_source.def" "${read_lst_test_source}")
    file(WRITE "${codegen_working_dir}/read_map_source.def" "${source_rmap}")
    file(WRITE "${codegen_working_dir}/read_test_source.def" "${source_read_test}")
endfunction(cxx_name)

function(header_name)
    set(header_files "${codegen_working_dir}/test.h" "${codegen_working_dir}/test_internal.h")
    set(header_files ${header_files} PARENT_SCOPE)
    string(REPLACE ";" "\n" headers "${header_files}")
    file(WRITE "${codegen_working_dir}/headers.def" "${headers}")
endfunction(header_name)
