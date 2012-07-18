project(serializer_test CXX)
find_package(libserializer REQUIRED)
find_package(librandomgenerator REQUIRED)
find_package(codegen REQUIRED)
include(generate_cxx.cmake)
include(ExternalProject)
include_directories(AFTER "${serializer_test_BINARY_DIR}/generated" ${serializer_test_SOURCE_DIR})

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
    COMMAND codegen
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
    time_array.cxx
    tab_count.cxx
    serializer_test.cxx
)

if(STATIC)
    add_library(raw_test STATIC ${raw_sources})
    add_library(lst_test STATIC ${vec_sources})
    add_library(vec_test STATIC ${lst_sources})
    add_library(map_test STATIC ${map_sources})
    
    add_library(test STATIC "${codegen_working_dir}/write_test.cxx" "${codegen_working_dir}/read_test.cxx")
    
    target_link_libraries(test raw_test lst_test vec_test map_test)
    target_link_libraries(serializer_test serializer-st randomgenerator-st test)

    install(
        TARGETS raw_test vec_test lst_test map_test test
        EXPORT  libserializer_testing_program
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

    target_link_libraries(test raw_test lst_test vec_test map_test)
    target_link_libraries(serializer_test serializer randomgenerator test)

    install(
        TARGETS raw_test vec_test lst_test map_test test
        EXPORT  libserializer_testing_program
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
    message(STATUS "The test program will linked dinamically.")
endif(STATIC)

if(SHOW_TIMEDIFF)
    add_definitions(-DSHOW_TIMEDIFF)
    message(STATUS "Showing time difference is enabled.")
else(SHOW_TIMEDIFF)
    message(STATUS "Showing time difference is not enabled.")
endif(SHOW_TIMEDIFF)

export(TARGETS serializer_test NAMESPACE serializer_ FILE serializer_test-config.cmake)
export(PACKAGE serializer_test)

install(
    EXPORT libserializer_testing_program 
    NAMESPACE serializer_
    DESTINATION share/cmake/Modules 
    FILE Findserializer_test.cmake
)
