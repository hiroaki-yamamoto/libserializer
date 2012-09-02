project(liboperator CXX)
set(name "operator")
set(src
    "tab_count.cxx"
)

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
