TEMPLATE = app
TARGET = codegen
INCLUDEPATH = .

HEADERS = generator.h operator.h

SOURCES = codegen.cxx \
          generator.cxx \
          operator.cxx \
          write_raw_code.cxx \
          write_vector_code.cxx \
          write_list_code.cxx \
          write_map_code.cxx 

OTHER_FILES = CMakeLists.txt
