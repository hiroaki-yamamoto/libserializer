project(liboperator CXX)
set(name "operator")
set(src
    "tab_count.cxx"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${name} SHARED ${src})
add_library(${name}-st STATIC ${src})

set_property(TARGET ${name} ${name}-st PROPERTY OUTPUT_NAME ${name})

export(TARGETS ${name} ${name}-st NAMESPACE libs_ FILE lib${name}-config.cmake)
export(PACKAGE lib${name})

install(TARGETS ${name} ${name}-st
        RUNTIME DESTINATION "bin"
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib")
install(FILES "operator.hxx" DESTINATION "include/libserializer")
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Findoperator.cmake 
        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules)
