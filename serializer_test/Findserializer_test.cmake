set(serializer_test_VERSION 1.0.0)

find_program(serializer_test_EXECUTABLE "serializer_test")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    serializer_test
    REQUIRED_VARS serializer_test_EXECUTABLE
    VERSION_VAR serializer_test_VERSION
    HANDLE_COMPONENTS
)
