project(libserializer CXX)
set(name "serializer")
set(src
    "numeric_detector.cxx"
    "serializer.cxx"
    "endian_detector.cxx"
)

add_library(serializer SHARED ${src})
add_library(serializer-st STATIC ${src})

set_property(TARGET serializer serializer-st PROPERTY OUTPUT_NAME ${name})

export(TARGETS serializer serializer-st NAMESPACE serializer_ FILE libserializer-config.cmake)
export(PACKAGE libserializer)

install(TARGETS serializer serializer-st
        RUNTIME DESTINATION "bin"
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib")
install(FILES "serializer.h" "endian_detector.h" "numeric_detector.h" DESTINATION "include/libserializer")
