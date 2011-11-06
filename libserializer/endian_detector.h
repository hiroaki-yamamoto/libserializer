#pragma once
#include <vector>
using namespace std;

union endian_class{
        unsigned int value;
        unsigned short sh[sizeof(value)/sizeof(unsigned short)];
        unsigned char ch[sizeof(value)];
};
enum class Endian{big,little,unknown};
Endian getEndian();
