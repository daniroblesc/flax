#include "MemoryByte.h"

void MemoryByte::write(const Byte& I)
{
    for ( int position = 0; position < Byte::NUM_BITS; ++position )
    {
        Bit bit = I.get(position);
        memoryBitCollection_[position].write(bit);
    }
}
    
Byte MemoryByte::read() const
{
    Byte retval;

    for ( int position = 0; position < Byte::NUM_BITS; ++position )
    {
        Bit bit = memoryBitCollection_[position].read();
        retval.set(bit, position);
    }

    return retval;
}