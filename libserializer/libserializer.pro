TEMPLATE = lib
TARGET = libserializer
INCLUDEPATH = .

HEADERS = \
    endian_detector.h \
    numeric_detector.h \
    serializer.h

SOURCES = \
    serializer.cxx \
    endian_detector.cxx \
    numeric_detector.cxx

OTHER_FILES  =  CMakeLists.txt \
                libserializer.vcxproj \
                libserializer.vcxproj.filters
