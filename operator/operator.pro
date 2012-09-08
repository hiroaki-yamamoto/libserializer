TEMPLATE = lib
TARGET = liboperator
INCLUDEPATH = .

HEADERS += operator.hxx
SOURCES += tab_count.cxx

OTHER_FILES  =  CMakeLists.txt \
                Findoperator.cmake \
                operator.vcxproj \
                operator.vcxproj.filters
