set(time_lib_LIBRARIES "time_lib")
set(time_lib_HEADERS "time_lib.h")
set(time_lib_VERSION 1.0)

foreach(header IN LISTS time_lib_HEADERS)
    find_path(INTERNAL_HEADERS_DIR "${header}")
    
    list(FIND time_lib_INCLUDE_DIR ${INTERNAL_HEADERS_DIR} result)
    if(result EQUAL -1)
        list(APPEND time_lib_INCLUDE_DIR ${INTERNAL_HEADERS_DIR})
    endif(result EQUAL -1)
    unset(INTERNAL_HEADERS_DIR CACHE)
endforeach(header)

foreach(library IN LISTS time_lib_LIBRARIES)
    find_library(INTERNAL_LIBRARIES "${library}")
    list(FIND time_lib_LIBRARIES_DIR ${INTERNAL_LIBRARIES} result)
    if(result EQUAL -1)
        list(APPEND time_lib_LIBRARIES_DIR ${INTERNAL_LIBRARIES})
    endif(result EQUAL -1)
    unset(INTERNAL_LIBRARIES_DIR CACHE)
endforeach(library)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(time_lib
    REQUIRED_VARS 
        time_lib_INCLUDE_DIR time_lib_LIBRARIES_DIR
    VERSION_VAR MODULE_VERSION
    HANDLE_COMPONENTS
)
