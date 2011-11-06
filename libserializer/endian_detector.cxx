#include "endian_detector.h"
Endian getEndian(){
    endian_class test_value={0x0a0b0c0d};
    return (test_value.sh[0]==0x0c0d&&test_value.sh[1]==0x0a0b)?Endian::little:
           (test_value.sh[0]==0x0a0b&&test_value.sh[1]==0x0c0d)?Endian::big:Endian::unknown;
}
