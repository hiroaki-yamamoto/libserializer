set(librandomgenerator_HEADERS "randomgenerator.h")
set(librandomgenerator_LIBRARIES_TO_SEARCH "randomgenerator")
set(librandomgenerator_VERSION 1.0.0)

find_path(librandomgenerator_INCLUDE_DIR NAMES ${librandomgenerator_HEADERS})
find_library(librandomgenerator_LIBRARIES NAMES ${librandomgenerator_LIBRARIES_TO_SEARCH})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    librandomgenerator
    REQUIRED_VARS librandomgenerator_INCLUDE_DIR librandomgenerator_LIBRARIES
    VERSION_VAR librandomgenerator_VERSION
    HANDLE_COMPONENTS
)
