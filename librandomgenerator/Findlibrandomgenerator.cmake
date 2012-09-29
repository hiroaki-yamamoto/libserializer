set(librandomgenerator_LIBRARIES "randomgenerator")
set(librandomgenerator_HEADERS "randomgenerator.h")
set(librandomgenerator_VERSION 1.0)

foreach(header IN LISTS librandomgenerator_HEADERS)
    find_path(INTERNAL_HEADERS_DIR "${header}")
    
    list(FIND librandomgenerator_INCLUDE_DIR ${INTERNAL_HEADERS_DIR} result)
    if(result EQUAL -1)
        list(APPEND librandomgenerator_INCLUDE_DIR ${INTERNAL_HEADERS_DIR})
    endif(result EQUAL -1)
    unset(INTERNAL_HEADERS_DIR CACHE)
endforeach(header)

foreach(library IN LISTS librandomgenerator_LIBRARIES)
    find_library(INTERNAL_LIBRARIES "${library}")
    list(FIND librandomgenerator_LIBRARIES_DIR ${INTERNAL_LIBRARIES} result)
    if(result EQUAL -1)
        list(APPEND librandomgenerator_LIBRARIES_DIR ${INTERNAL_LIBRARIES})
    endif(result EQUAL -1)
    unset(INTERNAL_LIBRARIES_DIR CACHE)
endforeach(library)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(librandomgenerator
    REQUIRED_VARS 
        librandomgenerator_INCLUDE_DIR librandomgenerator_LIBRARIES_DIR
    VERSION_VAR MODULE_VERSION
    HANDLE_COMPONENTS
)
