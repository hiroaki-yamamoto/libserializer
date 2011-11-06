TEMPLATE = app
TARGET = serializer_test
DEPENDPATH = ../codegen
INCLUDEPATH = .

HEADERS = operator.hxx \
          randomstring.h \
          time_array.h

SOURCES = serializer_test.cxx \
          time_array.cxx \
          tab_count.cxx

OTHER_FILES = CMakeLists.txt \
              generate_cxx.cmake 


