#include "ByteEnabler.h"

ByteEnabler::ByteEnabler()
{
    gatesCollection_.resize(Byte::NUM_BITS);
}

ByteEnabler::~ByteEnabler()
{}

void ByteEnabler::update(const Byte& input)
{
    input_ = input;
}

void ByteEnabler::enable(const bool e)
{
    e_.update(e);
}

Byte ByteEnabler::output()
{
    Byte retval;
    for ( int n = 0; n < Byte::NUM_BITS; ++n )
    {
        bool InputBit = input_[n];
        gatesCollection_[n].update(InputBit, e_.output());
        bool OutputBit = gatesCollection_[n].output();
        retval.set(n, OutputBit);
    }
    return retval;
}
