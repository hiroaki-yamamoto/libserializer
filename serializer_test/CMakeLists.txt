project(serializer_test CXX)
find_package(libserializer REQUIRED)
find_package(librandomgenerator REQUIRED)
find_package(codegen REQUIRED)
include(generate_cxx.cmake)
include_directories(AFTER "${serializer_test_BINARY_DIR}/generated" ${serializer_test_SOURCE_DIR})

file(MAKE_DIRECTORY ${codegen_working_dir})

option(STATIC "Build test program statically." OFF)
option(SHOW_TIMEDIFF "Show Time Difference." OFF)

cxx_name()
header_name()

add_custom_command(
    OUTPUT 
        ${write_raw_test_source}
        ${write_lst_test_source}
        ${write_vec_test_source}
        ${write_map_test_source}
        ${write_test_source}
        ${read_raw_test_source}
        ${read_lst_test_source}
        ${read_vec_test_source}
        ${read_map_test_source}
        ${read_test_source}
        ${header_files}
    COMMAND codegen
    DEPENDS codegen
    COMMENT "Generating test source codes."
    WORKING_DIRECTORY ${codegen_working_dir}
)

add_custom_target(
    test 
    DEPENDS  
        ${write_raw_test_source}
        ${write_lst_test_source}
        ${write_vec_test_source}
        ${write_map_test_source}
        ${write_test_source}
        ${read_raw_test_source}
        ${read_lst_test_source}
        ${read_vec_test_source}
        ${read_map_test_source}
        ${read_test_source}
        ${header_files}
    WORKING_DIRECTORY ${codegen_working_dir}
)

add_executable(serializer_test
    time_array.cxx
    tab_count.cxx
    serializer_test.cxx
)

if(STATIC)
    add_library(write_raw_test STATIC ${write_raw_test_source})
    add_library(write_lst_test STATIC ${write_lst_test_source})
    add_library(write_vec_test STATIC ${write_vec_test_source})
    add_library(write_map_test STATIC ${write_map_test_source})
    
    add_library(read_raw_test STATIC ${read_raw_test_source})
    add_library(read_lst_test STATIC ${read_lst_test_source})
    add_library(read_vec_test STATIC ${read_vec_test_source})
    add_library(read_map_test STATIC ${read_map_test_source})
    
    add_library(write_test STATIC ${write_test_source})
    add_library(read_test STATIC ${read_test_source})

    add_dependencies(write_test test)
    add_dependencies(read_test test)
    
    target_link_libraries(write_test write_raw_test write_lst_test write_vec_test write_map_test)
    target_link_libraries(read_test read_raw_test read_lst_test read_vec_test read_map_test)

    target_link_libraries(serializer_test serializer-st randomgenerator-st write_test read_test)
    install(
        TARGETS
            write_raw_test write_lst_test write_vec_test write_map_test write_test
            read_raw_test read_lst_test read_vec_test read_map_test read_test
        EXPORT  libserializer_testing_program
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
    message(STATUS "The test program will linked statically.")
else(STATIC)
    add_library(write_raw_test SHARED ${write_raw_test_source})
    add_library(write_lst_test SHARED ${write_lst_test_source})
    add_library(write_vec_test SHARED ${write_vec_test_source})
    add_library(write_map_test SHARED ${write_map_test_source})
    
    add_library(read_raw_test SHARED ${read_raw_test_source})
    add_library(read_lst_test SHARED ${read_lst_test_source})
    add_library(read_vec_test SHARED ${read_vec_test_source})
    add_library(read_map_test SHARED ${read_map_test_source})
    
    add_library(write_test SHARED ${write_test_source})
    add_library(read_test SHARED ${read_test_source})

    add_dependencies(write_test test)
    add_dependencies(read_test test)
    
    target_link_libraries(write_test write_raw_test write_lst_test write_vec_test write_map_test)
    target_link_libraries(read_test read_raw_test read_lst_test read_vec_test read_map_test)

    target_link_libraries(serializer_test write_test read_test serializer randomgenerator)

    install(
        TARGETS
            serializer_test write_raw_test write_lst_test write_vec_test write_map_test write_test
            read_raw_test read_lst_test read_vec_test read_map_test read_test
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
