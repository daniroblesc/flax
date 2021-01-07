#include "ByteEnabler.h"


void ByteEnabler::load(const Byte& input)
{
    input_ = input;
}

Byte ByteEnabler::enable()
{
    Byte retval;
    for ( int position = 0; position < Byte::NUM_BITS; ++position )
    {
        Bit InputBit = input_.get(position);
        Bit OutputBit = gatesCollection_[position].execute(InputBit, Bit::ONE);
        retval.set(OutputBit, position);
    }
    return retval;
}
