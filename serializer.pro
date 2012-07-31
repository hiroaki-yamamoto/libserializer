TEMPLATE = subdirs

DEPENDPATH  +=  . \
                ./codegen \
                ./libserializer \
                ./serializer_test \
                ./librandomgenerator \
                ./doc_scripts \
                ./time_lib

SUBDIRS =   ./codegen \
            ./libserializer \
            ./serializer_test \
            ./librandomgenerator \
            ./doc_pics \
            ./doc_scripts \
            ./time_lib

serializer_test.depends +=  libserializer \
                            librandomgenerator \
                            codegen \
                            time_lib

OTHER_FILES += CMakeLists.txt \
               doxygen.cfg \
               doxygen_mainpage \
               specification.odt \
               ReadMe
