#include "MemoryByte.h"

MemoryByte::MemoryByte()
{
    memoryBitCollection_.reserve(Byte::NUM_BITS);
    for ( int position = 0; position < Byte::NUM_BITS; ++position )
    {
        memoryBitCollection_.push_back(MemoryBit());
    }
}

MemoryByte::~MemoryByte()
{}

void MemoryByte::save(const Byte& I)
{
    for ( int position = 0; position < Byte::NUM_BITS; ++position )
    {
        Bit bit = I.get(position);
        memoryBitCollection_[position].save(bit);
    }
}
    
Byte MemoryByte::get() const
{
    Byte retval;

    for ( int position = 0; position < Byte::NUM_BITS; ++position )
    {
        Bit bit = memoryBitCollection_[position].get();
        retval.set(bit, position);
    }

    return retval;
}