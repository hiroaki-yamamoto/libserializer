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

    set(source_write_raw "${codegen_working_dir}/write_raw.cxx")
    set(source_write_vec "${codegen_working_dir}/write_vec.cxx")
    set(source_write_lst "${codegen_working_dir}/write_lst.cxx")
    set(source_write_test "${codegen_working_dir}/write_test.cxx")

    set(source_read_raw "${codegen_working_dir}/read_raw.cxx")
    set(source_read_vec "${codegen_working_dir}/read_vec.cxx")
    set(source_read_lst "${codegen_working_dir}/read_lst.cxx")
    set(source_read_test "${codegen_working_dir}/read_test.cxx")
    
    foreach(key ${alias})
        foreach(value ${alias})
            list(APPEND source_write_map "${codegen_working_dir}/write_map_${key}${value}_test.cxx")
            list(APPEND source_read_map "${codegen_working_dir}/read_map_${key}${value}_test.cxx")
        endforeach(value ${alias})
    endforeach(key)
    set(source_files
        ${source_write_raw}
        ${source_write_vec}
        ${source_write_lst}
        ${source_write_map}
        ${source_write_test}
        ${source_read_raw}
        ${source_read_vec}
        ${source_read_lst}
        ${source_read_map}
        ${source_read_test}
        PARENT_SCOPE
    )

    string(REPLACE ";" "\n" source_wmap "${source_write_map}")
    string(REPLACE ";" "\n" source_rmap "${source_read_map}")

    file(WRITE "${codegen_working_dir}/write_raw_source.def" "${source_write_raw}")
    file(WRITE "${codegen_working_dir}/write_vec_source.def" "${source_write_vec}")
    file(WRITE "${codegen_working_dir}/write_lst_source.def" "${source_write_lst}")
    file(WRITE "${codegen_working_dir}/write_map_source.def" "${source_wmap}")
    file(WRITE "${codegen_working_dir}/write_test_source.def" "${source_write_test}")

    file(WRITE "${codegen_working_dir}/read_raw_source.def" "${source_read_raw}")
    file(WRITE "${codegen_working_dir}/read_vec_source.def" "${source_read_vec}")
    file(WRITE "${codegen_working_dir}/read_lst_source.def" "${source_read_lst}")
    file(WRITE "${codegen_working_dir}/read_map_source.def" "${source_rmap}")
    file(WRITE "${codegen_working_dir}/read_test_source.def" "${source_read_test}")
endfunction(cxx_name)

function(header_name)
    set(header_files "${codegen_working_dir}/test.h" "${codegen_working_dir}/test_internal.h")
    set(header_files ${header_files} PARENT_SCOPE)
    string(REPLACE ";" "\n" headers "${header_files}")
    file(WRITE "${codegen_working_dir}/headers.def" "${headers}")
endfunction(header_name)
