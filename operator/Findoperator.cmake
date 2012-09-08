set(operator_HEADERS "operator.hxx")
set(operator_LIBRARIES_TO_SEARCH "operator.cxx")
set(operator_VERSION 1.0.0)

find_path(operator_INCLUDE_DIR NAMES ${operator_HEADERS})
find_library(operator_LIBRARIES NAMES ${operator_LIBRARIES_TO_SEARCH})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    operator
    REQUIRED_VARS operator_INCLUDE_DIR operator_LIBRARIES
    VERSION_VAR operator_VERSION
    HANDLE_COMPONENTS
)
