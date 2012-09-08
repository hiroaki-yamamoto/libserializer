project(serializer_test CXX)
find_package(libserializer REQUIRED)
find_package(librandomgenerator REQUIRED)
find_package(codegen REQUIRED)
find_package(libtime REQUIRED)
find_package(liboperator REQUIRED)

include(generate_cxx.cmake)
include_directories(AFTER "${serializer_test_BINARY_DIR}/generated" ${CMAKE_CURRENT_SOURCE_DIR})

file(MAKE_DIRECTORY ${codegen_working_dir})

option(STATIC "Build test program statically." OFF)
option(SHOW_TIMEDIFF "Show Time Difference." OFF)

make_typedef()
make_sources("${types}")

foreach(source ${raw_write} ${raw_read})
    list(APPEND raw_sources "${codegen_working_dir}/${source}")
endforeach(source)

foreach(source ${vec_write} ${vec_read})
    list(APPEND vec_sources "${codegen_working_dir}/${source}")
endforeach(source)

foreach(source ${lst_write} ${lst_read})
    list(APPEND lst_sources "${codegen_working_dir}/${source}")
endforeach(source)

foreach(source ${map_write} ${map_read})
    list(APPEND map_sources "${codegen_working_dir}/${source}")
endforeach(source)

list(APPEND sources ${raw_sources} ${vec_sources} ${lst_sources} ${map_sources})

add_custom_command(
    OUTPUT  ${sources} "${codegen_working_dir}/write_test.cxx" "${codegen_working_dir}/read_test.cxx"
    COMMAND codegen ARGS ${type_file} ${codegen_working_dir}
    DEPENDS codegen
    COMMENT "Generating test source codes."
    WORKING_DIRECTORY ${codegen_working_dir}
)
add_custom_target(
    test_library
    DEPENDS ${sources} "${codegen_working_dir}/write_test.cxx" "${codegen_working_dir}/read_test.cxx"
    WORKING_DIRECTORY ${codegen_working_dir}
)

add_executable(
    serializer_test
    serializer_test.cxx
)

if(STATIC)
    add_dependencies(serializer_test serializer_serializer-st)
    add_library(raw_test STATIC ${raw_sources})
    add_library(lst_test STATIC ${vec_sources})
    add_library(vec_test STATIC ${lst_sources})
    add_library(map_test STATIC ${map_sources})
    
    add_library(test STATIC "${codegen_working_dir}/write_test.cxx" "${codegen_working_dir}/read_test.cxx")
    
    target_link_libraries(raw_test serializer_serializer-st libs_randomgenerator-st libs_time-st libs_operator-st)
    target_link_libraries(lst_test serializer_serializer-st libs_randomgenerator-st libs_time-st libs_operator-st)
    target_link_libraries(vec_test serializer_serializer-st libs_randomgenerator-st libs_time-st libs_operator-st)
    target_link_libraries(map_test serializer_serializer-st libs_randomgenerator-st libs_time-st libs_operator-st)
    target_link_libraries(test  raw_test lst_test vec_test map_test serializer_serializer-st 
                                libs_randomgenerator-st libs_time-st  libs_operator-st)
    target_link_libraries(serializer_test   test serializer_serializer-st libs_randomgenerator-st 
                                            libs_time-st  libs_operator-st)

    install(
        TARGETS raw_test
                vec_test
                lst_test
                map_test
                serializer_test
                test
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
    message(STATUS "The test program will linked statically.")
else(STATIC)
    add_library(raw_test SHARED ${raw_sources})
    add_library(lst_test SHARED ${vec_sources})
    add_library(vec_test SHARED ${lst_sources})
    add_library(map_test SHARED ${map_sources})
    
    add_library(test SHARED "${codegen_working_dir}/write_test.cxx" "${codegen_working_dir}/read_test.cxx")


    target_link_libraries(raw_test serializer_serializer libs_randomgenerator libs_time libs_operator)
    target_link_libraries(lst_test serializer_serializer libs_randomgenerator libs_time libs_operator)
    target_link_libraries(vec_test serializer_serializer libs_randomgenerator libs_time libs_operator)
    target_link_libraries(map_test serializer_serializer libs_randomgenerator libs_time libs_operator)

    target_link_libraries(test serializer_serializer raw_test lst_test vec_test map_test libs_time 
                                libs_randomgenerator libs_operator)
    target_link_libraries(serializer_test serializer_serializer libs_time libs_randomgenerator test libs_operator)

    install(
        TARGETS raw_test vec_test lst_test map_test test
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
    message(STATUS "The test program will linked dinamically.")
endif(STATIC)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Findserializer_test.cmake 
        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules)

if(SHOW_TIMEDIFF)
    add_definitions(-DSHOW_TIMEDIFF)
    message(STATUS "Showing time difference is enabled.")
else(SHOW_TIMEDIFF)
    message(STATUS "Showing time difference is not enabled.")
endif(SHOW_TIMEDIFF)

export(TARGETS serializer_test NAMESPACE serializer_ FILE serializer_test-config.cmake)
export(PACKAGE serializer_test)
