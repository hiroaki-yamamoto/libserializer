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

export(TARGETS serializer serializer-st NAMESPACE libraries FILE libserializer-config.cmake)
export(PACKAGE libserializer)

install(TARGETS serializer serializer-st
        EXPORT  libserializer
        RUNTIME DESTINATION "bin"
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib")
install(FILES "serializer.h" "endian_detector.h" "definitions.h" "numeric_detector.h" DESTINATION "include/libserializer")
install(EXPORT libserializer NAMESPACE serializer_lib DESTINATION share/cmake/Modules FILE Findlibserializer.cmake)
