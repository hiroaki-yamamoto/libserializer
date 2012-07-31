#pragma once
#include <vector>
using namespace std;

union endian_class{
        unsigned int value;
        unsigned short sh[sizeof(decltype(value))/sizeof(unsigned short)];
        unsigned char ch[sizeof(decltype(value))];
};
enum class Endian{big,little,unknown};
Endian getEndian();
