TEMPLATE = lib
TARGET = libserializer
INCLUDEPATH = .

HEADERS = serializer.h \
          definitions.h \
          endian_detector.h \
          numeric_detector.h 

SOURCES = serializer.cxx \
          endian_detector.cxx \
          numeric_detector.cxx 

OTHER_FILES = CMakeLists.txt


