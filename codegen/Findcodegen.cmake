set(codegen_EXECUTAVLE_TO_SEARCH "codegen"))
set(codegen_VERSION 1.0.0)

find_program(codegen_EXECUTABLE ${codegen_EXECUTAVLE_TO_SEARCH})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    codegen
    REQUIRED_VARS codegen_EXECUTABLE
    VERSION_VAR codegen_VERSION
    HANDLE_COMPONENTS
)
