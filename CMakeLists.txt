cmake_minimum_required(VERSION 2.8)
project(serializer CXX)

find_package(Doxygen COMPONENTS)

include_directories(AFTER ${CMAKE_CURRENT_SOURCE_DIR}/libserializer)

option(WITHOUT_UNIX_MODE "Builds without unix mode." OFF)
option(BUILD_TEST "Builds test program." OFF)
option(GENERATE_DOC "Generates the documents of the libraries." OFF)

if(DOXYGEN_FOUND)
    set(GENERATE_DOC ON)
endif(DOXYGEN_FOUND)

if(GENERATE_DOC)
    message(STATUS "Document generation has been enabled.")
    add_custom_command(
        OUTPUT doc
        DEPENDS doxygen.cfg doc_scripts/example doc_scripts/format doc_scripts/mainpage libserializer/serializer.h
        COMMAND ${DOXYGEN_EXECUTABLE} ARGS doxygen.cfg
        COMMAND rm ARGS -rf ${CMAKE_BINARY_DIR}/doc
        COMMAND mv ARGS doc ${CMAKE_BINARY_DIR}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating the document."
    )
    add_custom_target(
        document ALL
        DEPENDS doc
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
    install(DIRECTORY ${CMAKE_BINARY_DIR}/doc/ DESTINATION /usr/share/doc/libserializer)
endif(GENERATE_DOC)

function(debug WHERE)
    if(WHERE STREQUAL "All")
        add_definitions(-DDEBUG_CONVERTER -DDEBUG_SERIALIZER -DDEBUG_RANDOM)
        message(STATUS "Debug mode:ALL")
    elseif(WHERE STREQUAL "Numeric")
        add_definitions(-DDEBUG_NUMERIC)
        message(STATUS "Debug mode:NUMEIRC")
    elseif(WHERE STREQUAL "Serializer")
        add_definitions(-DDEBUG_SERIALIZER)
        message(STATUS "Debug mode:SERIALIZER")
    elseif(WHERE STREQUAL "None")
        message(STATUS "Debug mode:NONE")
    elseif(WHERE STREQUAL "RandomNumber")
        add_definitions(-DDEBUG_RANDOM)
        message(STATUS "Debug mode:RANDOM_NUMBER")
    else(WHERE STREQUAL "All")
        debug("None")
    endif(WHERE STREQUAL "All")
endfunction(debug)

if(CMAKE_COMPILER_IS_GNUCXX)
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if(GCC_VERSION VERSION_LESS "4.7")
        set(CMAKE_CXX_FLAGS "-std=gnu++0x ${CMAKE_CXX_FLAGS}")
    else(GCC_VERSION VERSION_LESS "4.7")
        set(CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_CXX_FLAGS}")
    endif(GCC_VERSION VERSION_LESS "4.7")
    message(STATUS "Enabled C++0x[${CMAKE_CXX_FLAGS}]")
elseif(MSVC)
    message(STATUS "Compiler:MSVC")
else(CMAKE_COMPILER_IS_GNUCXX)
    message(FATAL_ERROR "This library needs to be built with GCC, because building with the compiler other than GCC is not intended.")
endif(CMAKE_COMPILER_IS_GNUCXX)

if(UNIX AND NOT WITHOUT_UNIX_MODE)
    add_definitions(-DUNIX)
    message(STATUS "Unix mode.")
endif(UNIX AND NOT WITHOUT_UNIX_MODE)

if(DEFINED DEBUG)
    set(CMAKE_BUILD_TYPE "Debug")
endif(DEFINED DEBUG)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    if(NOT DEFINED DEBUG)
        set(DEBUG "None")
    endif(NOT DEFINED DEBUG)
    debug(${DEBUG})
    set(CMAKE_CXX_FLAGS "-Wall -Werror ${CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "-Wall -Werror ${CMAKE_C_FLAGS}")
    message(STATUS "Debugging mode has been enabled. This is not recommended for normal use.")
else(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_BUILD_TYPE Release)
endif(CMAKE_BUILD_TYPE STREQUAL Debug)

add_subdirectory(libserializer)

if(BUILD_TEST)
    include_directories(AFTER 
        ${CMAKE_CURRENT_SOURCE_DIR}/time_lib 
        ${CMAKE_CURRENT_SOURCE_DIR}/serializer_test 
        ${CMAKE_CURRENT_SOURCE_DIR}/librandomgenerator 
        ${CMAKE_CURRENT_SOURCE_DIR}/codegen)
    add_subdirectory(codegen)
    add_subdirectory(librandomgenerator)
    add_subdirectory(time_lib)
    add_subdirectory(serializer_test)
    message(STATUS "Test program will be built")
endif(BUILD_TEST)
message(STATUS "Debug flag [${CMAKE_CXX_FLAGS_DEBUG}]")
message(STATUS "Release flag [${CMAKE_CXX_FLAGS_RELEASE}]")
