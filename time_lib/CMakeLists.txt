project(libtime CXX)
set(name "time")
set(src
    "time_array.cxx"
)

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
