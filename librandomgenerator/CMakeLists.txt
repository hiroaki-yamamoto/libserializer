project(librandomgenerator CXX)
set(src "randomgenerator.cxx")
add_library(randomgenerator SHARED ${src})
add_library(randomgenerator-st STATIC ${src})
set(name "randomgenerator")

set_property(TARGET randomgenerator randomgenerator-st PROPERTY OUTPUT_NAME ${name})

export(TARGETS randomgenerator randomgenerator-st NAMESPACE libs_ FILE librandomgenerator-config.cmake)
export(PACKAGE librandomgenerator)

install(TARGETS randomgenerator randomgenerator-st
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(FILES "randomgenerator.h" DESTINATION "include")
