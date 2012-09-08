project(librandomgenerator CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

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
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Findlibrandomgenerator.cmake 
        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules)
