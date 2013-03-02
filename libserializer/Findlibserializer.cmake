set(libserializer_LIBRARIES "serializer")
set(libserializer_HEADERS "serializer.h" "endian_detector.h" "numeric_detector.h")
set(libserializer_VERSION 1.0)
find_package(PackageHandleStandardArgs REQUIRED)

foreach(header IN LISTS libserializer_HEADERS)
    find_path(INTERNAL_HEADERS_DIR ${header}
                HINTS /usr/include/libserializer /usr/local/include/libserializer
    )
    list(FIND libserializer_INCLUDE_DIR ${INTERNAL_HEADERS_DIR} result)
    if(result EQUAL -1)
        list(APPEND libserializer_INCLUDE_DIR ${INTERNAL_HEADERS_DIR})
    endif(result EQUAL -1)
    unset(INTERNAL_HEADERS_DIR CACHE)
endforeach(header)

foreach(library IN LISTS libserializer_LIBRARIES)
    find_library(INTERNAL_LIBRARIES "${library}")
    list(FIND libserializer_LIBRARIES_DIR ${INTERNAL_LIBRARIES} result)
    if(result EQUAL -1)
        list(APPEND libserializer_LIBRARIES_DIR ${INTERNAL_LIBRARIES})
    endif(result EQUAL -1)
    unset(INTERNAL_LIBRARIES_DIR CACHE)
endforeach(library)

find_package_handle_standard_args(libserializer
    REQUIRED_VARS 
        libserializer_INCLUDE_DIR libserializer_LIBRARIES_DIR
    VERSION_VAR MODULE_VERSION
    HANDLE_COMPONENTS
)
