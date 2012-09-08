set(time_lib_HEADERS "time_array.h")
set(time_lib_LIBRARIES_TO_SEARCH "time")
set(time_lib_VERSION 1.0.0)

find_path(time_lib_INCLUDE_DIR NAMES ${time_lib_HEADERS})
find_library(time_lib_LIBRARIES NAMES ${time_lib_LIBRARIES_TO_SEARCH})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    time_lib
    REQUIRED_VARS time_lib_INCLUDE_DIR time_lib_LIBRARIES
    VERSION_VAR time_lib_VERSION
    HANDLE_COMPONENTS
)
