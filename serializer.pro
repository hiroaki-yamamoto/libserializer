TEMPLATE = subdirs
DEPENDPATH += . ./codegen ./libserializer ./serializer_test ./librandomgenerator ./doc_scripts
SUBDIRS = ./codegen \
          ./libserializer \
          ./serializer_test \
          ./librandomgenerator \
          ./doc_pics \
          ./doc_scripts

serializer_test.depends += libserializer librandomgenerator codegen

OTHER_FILES += CMakeLists.txt \
               doxygen.cfg \
               doxygen_mainpage \
               specification.odt \
               ReadMe
