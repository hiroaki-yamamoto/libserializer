set(codegen_working_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

function(make_typedef)
    set(types
        "string" "bool" "char" "short" "int" "long" "long long" 
        "unsigned char" "unsigned short" "unsigned int" "unsigned long" "unsigned long long"
        "float" "double" "long double"
    )
    set(types ${types} PARENT_SCOPE)
    string(REPLACE ";" "\n" types_file "${types}")
    set(file "${codegen_working_dir}/types.def")
    set(type_file "${file}" PARENT_SCOPE)
    file(WRITE "${file}" "${types_file}")
endfunction(make_typedef)

function(make_sources type_array)
    foreach(type ${type_array})
        string(REPLACE " " "_" type_replaced "${type}")
        list(APPEND raw_write "write_${type_replaced}.cxx")
        list(APPEND raw_read "read_${type_replaced}.cxx")
        list(APPEND vec_write "write_vec_${type_replaced}.cxx")
        list(APPEND vec_read "read_vec_${type_replaced}.cxx")
        list(APPEND lst_write "write_lst_${type_replaced}.cxx")
        list(APPEND lst_read "read_lst_${type_replaced}.cxx")
        foreach(value ${type_array})
            string(REPLACE " " "_" value_replaced "${value}")
            list(APPEND map_write "write_map_${type_replaced}_${value_replaced}.cxx")
            list(APPEND map_read "read_map_${type_replaced}_${value_replaced}.cxx")
        endforeach(value)
    endforeach(type)

    string(REPLACE ";" "\n" raw_write_sources "${raw_write}")
    string(REPLACE ";" "\n" vec_write_sources "${vec_write}")
    string(REPLACE ";" "\n" lst_write_sources "${lst_write}")
    string(REPLACE ";" "\n" map_write_sources "${map_write}")

    string(REPLACE ";" "\n" raw_read_sources "${raw_read}")
    string(REPLACE ";" "\n" vec_read_sources "${vec_read}")
    string(REPLACE ";" "\n" lst_read_sources "${lst_read}")
    string(REPLACE ";" "\n" map_read_sources "${map_read}")

    file(WRITE "${codegen_working_dir}/write_raw.def" ${raw_write_sources})
    file(WRITE "${codegen_working_dir}/write_vec.def" ${vec_write_sources})
    file(WRITE "${codegen_working_dir}/write_lst.def" ${lst_write_sources})
    file(WRITE "${codegen_working_dir}/write_map.def" ${map_write_sources})
    
    file(WRITE "${codegen_working_dir}/read_raw.def" ${raw_read_sources})
    file(WRITE "${codegen_working_dir}/read_vec.def" ${vec_read_sources})
    file(WRITE "${codegen_working_dir}/read_lst.def" ${lst_read_sources})
    file(WRITE "${codegen_working_dir}/read_map.def" ${map_read_sources})

    set(raw_write ${raw_write} PARENT_SCOPE)
    set(vec_write ${vec_write} PARENT_SCOPE)
    set(lst_write ${lst_write} PARENT_SCOPE)
    set(map_write ${map_write} PARENT_SCOPE)

    set(raw_read ${raw_read} PARENT_SCOPE)
    set(vec_read ${vec_read} PARENT_SCOPE)
    set(lst_read ${lst_read} PARENT_SCOPE)
    set(map_read ${map_read} PARENT_SCOPE)
endfunction(make_sources)
