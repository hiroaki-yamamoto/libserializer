#pragma once
#include<cfloat>
#include<stdexcept>

using namespace std;

#define THROW_NO_WRITABLE_ATTRIBUTE throw logic_error("There is no writable attribute at the specified stream.")
#define THROW_NO_READABLE_ATTRIBUTE throw logic_error("There is no readable attribute at the specified stream.")
#define THROW_WILL_REACHED_END      throw range_error("The stream will be reached at the end.")
#define THROW_INVALID               throw logic_error("The data is invalid.")
#define THROW_OVERFLOW              throw out_of_range("Overflow")
#define THROW_UNDERFLOW             throw out_of_range("Underflow")
#define THROW_UNKNOWN               throw logic_error("Unknown type.")

namespace defs{
    const float FLT_NEGATIVE_MAX=-FLT_MAX;
    const float FLT_NEGATIVE_MIN=-FLT_MIN;
    const double DBL_NEGATIVE_MAX=-DBL_MAX;
    const double DBL_NEGATIVE_MIN=-DBL_MIN;
}
