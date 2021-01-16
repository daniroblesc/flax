
#include "Wire.h"

//
// Wire implementation
//

void Wire::update(const bool value)
{
    output_ = value;
}

bool Wire::output()
{
    return output_;
}