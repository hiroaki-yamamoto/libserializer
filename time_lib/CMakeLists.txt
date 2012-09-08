project(libtime CXX)
set(name "time")
set(src
    "time_array.cxx"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${name} SHARED ${src})
add_library(${name}-st STATIC ${src})

set_property(TARGET time time-st PROPERTY OUTPUT_NAME ${name})

export(TARGETS ${name} ${name}-st NAMESPACE libs_ FILE lib${name}-config.cmake)
export(PACKAGE lib${name})

install(TARGETS ${name} ${name}-st
        RUNTIME DESTINATION "bin"
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib")
install(FILES "time_array.h" DESTINATION "include/libserializer")
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Findtime_lib.cmake DESTINATION ${CMAKE_INSTALL_PREFIX}/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules)
