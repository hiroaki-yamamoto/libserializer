project(serializer_test CXX)
find_package(libserializer REQUIRED)
find_package(librandomgenerator REQUIRED)
find_package(codegen REQUIRED)
include(generate_cxx.cmake)
include_directories(AFTER "${serializer_test_BINARY_DIR}/generated" ${serializer_test_SOURCE_DIR})

file(MAKE_DIRECTORY ${codegen_working_dir})

option(STATIC "Build test program statically." OFF)

cxx_name()
header_name()

add_custom_command(
    OUTPUT ${source_files} ${header_files}
    COMMAND codegen
    DEPENDS codegen
    COMMENT "Generating test source codes."
    WORKING_DIRECTORY ${codegen_working_dir}
)

add_custom_target(
    test 
    DEPENDS  ${source_files} ${header_files}
    WORKING_DIRECTORY ${codegen_working_dir}
)


add_executable(serializer_test
    ${source_files}
    time_array.cxx
    tab_count.cxx
    serializer_test.cxx
)

if(STATIC)
    add_dependencies(serializer_test serializer-st randomgenerator-st test)
    target_link_libraries(serializer_test serializer-st randomgenerator-st)
    message(STATUS "The test program will linked statically.")
else(STATIC)
    add_dependencies(serializer_test serializer randomgenerator test)
    target_link_libraries(serializer_test serializer randomgenerator)
    message(STATUS "The test program will linked dinamically.")
endif(STATIC)

export(TARGETS serializer_test NAMESPACE test FILE serializer_test-config.cmake)
export(PACKAGE serializer_test)

install(TARGETS serializer_test
        EXPORT  libserializer_testing_program
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(EXPORT libserializer_testing_program NAMESPACE serializer_bin DESTINATION share/cmake/Modules FILE Findserializer_test.cmake)
