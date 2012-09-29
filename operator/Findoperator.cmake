set(operator_LIBRARIES "operator")
set(operator_HEADERS "operator.h")
set(MODULE_VERSION 1.0)

foreach(header IN LISTS operator_HEADERS)
    find_path(INTERNAL_HEADERS_DIR "${header}")
    
    list(FIND operator_INCLUDE_DIR ${INTERNAL_HEADERS_DIR} result)
    if(result EQUAL -1)
        list(APPEND operator_INCLUDE_DIR ${INTERNAL_HEADERS_DIR})
    endif(result EQUAL -1)
    unset(INTERNAL_HEADERS_DIR CACHE)
endforeach(header)

foreach(library IN LISTS operator_LIBRARIES)
    find_library(INTERNAL_LIBRARIES "${library}")
    list(FIND operator_LIBRARIES_DIR ${INTERNAL_LIBRARIES} result)
    if(result EQUAL -1)
        list(APPEND operator_LIBRARIES_DIR ${INTERNAL_LIBRARIES})
    endif(result EQUAL -1)
    unset(INTERNAL_LIBRARIES_DIR CACHE)
endforeach(library)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(operator
    REQUIRED_VARS 
        operator_INCLUDE_DIR operator_LIBRARIES_DIR
    VERSION_VAR MODULE_VERSION
    HANDLE_COMPONENTS
)
