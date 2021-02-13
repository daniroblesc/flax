#include "MemoryByte.h"

MemoryByte::MemoryByte()
{
    bits_.resize(Byte::NUM_BITS);
    output_.resize(Byte::NUM_BITS);
}

MemoryByte::~MemoryByte()
{
}

void MemoryByte::update(const Byte& input, const bool s)
{  
    // set new content
    for ( int n = 0; n < Byte::NUM_BITS; ++n )
    {
        bool inputBit = input[n];
        bits_[n].update(inputBit, s);
        output_[n].update(bits_[n].output());
    }
}

Byte MemoryByte::output()
{
    Byte output;

    for ( int n = 0; n < Byte::NUM_BITS; ++n )
    {
        output.set(n, output_[n].output());
    }

    return output;    
}
