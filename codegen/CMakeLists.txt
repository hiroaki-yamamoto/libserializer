project(codegen CXX C)

add_definitions(-DCMAKE)

find_package(OpenMP REQUIRED)

include_directories(${CURRENT_SOURCE_DIR})

add_executable(codegen
    "codegen.cxx"
    "generator.cxx"
    "operator.cxx"
    "write_raw_code.cxx"
    "write_vector_code.cxx"
    "write_list_code.cxx"
    "write_map_code.cxx"
)
set_property(TARGET codegen PROPERTY COMPILE_FLAGS "${OpenMP_CXX_FLAGS}")
if(CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(codegen gomp)
endif(CMAKE_COMPILER_IS_GNUCXX)

export(TARGETS codegen NAMESPACE libserializer_ FILE codegen-config.cmake)
export(PACKAGE codegen)

install(TARGETS codegen
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Findcodegen.cmake DESTINATION ${CMAKE_INSTALL_PREFIX}/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules)
