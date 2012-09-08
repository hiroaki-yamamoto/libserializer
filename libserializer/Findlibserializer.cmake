set(libserializer_HEADERS "endian_detector.h" "numeric_detector.h" "serializer.h")
set(libserializer_LIBRARIES_TO_SEARCH "serializer")
set(libserializer_VERSION 1.0.0)

find_path(libserializer_INCLUDE_DIR NAMES ${libserializer_HEADERS})
find_library(libserializer_LIBRARIES NAMES ${libserializer_LIBRARIES_TO_SEARCH})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    libserializer
    REQUIRED_VARS libserializer_INCLUDE_DIR libserializer_LIBRARIES
    VERSION_VAR libserializer_VERSION
    HANDLE_COMPONENTS
)
