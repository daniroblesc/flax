
#include "Byte.h"
#include <sstream>      // std::stringstream
#include <string.h>

const int Byte::NUM_BITS = 8;

Byte::Byte()
{
}
    
Byte::Byte(const int val)
{
    setBitCollection(val, bitCollection_);     
}

Byte::Byte(const Byte &that)
{
    memcpy(this->bitCollection_, that.bitCollection_, sizeof(this->bitCollection_));
}
    
Byte& Byte::operator=(const Byte &that)
{
    memcpy(this->bitCollection_, that.bitCollection_, sizeof(this->bitCollection_));
    return *this;
}

Byte& Byte::operator=(const int &val)
{
    setBitCollection(val, bitCollection_);
    return *this;
}
        
bool Byte::operator==(const Byte &that) const
{
   int n = memcmp(this->bitCollection_, that.bitCollection_, sizeof(this->bitCollection_));
   if (n == 0)
   {
       return true;
   }

   return false;
}

bool Byte::operator==(const int &val) const
{
    return (val == get());
}

int Byte::get() const
{
    int retval = 0;
    for (int i = 0; i < NUM_BITS; ++i )
    {
        if (bitCollection_[i] == Bit::ONE)
        {
            retval |= 1UL << i;
        }
        else
        {
            retval &= ~(1UL << i);
        }    
    }
    
    return retval;
}

Bit Byte::get(const int position) const
{
    if (position >= NUM_BITS)
    {
        return Bit::ZERO;
    }

    return bitCollection_[position];
}

void Byte::set(const int position, Bit value)
{
    bitCollection_[position] = value.get();
}

void Byte::setBitCollection(const int val, Bit::e_BitValue* bitCollection)
{
    for (int i = 0; i < NUM_BITS; ++i )
    {
        int b = (val >> i) & 1U;
        bitCollection[i] = static_cast<Bit::e_BitValue>(b);
    }
}

std::string Byte::toString()
{
    std::stringstream ss;
    for (int i = NUM_BITS; i > 0; --i)
    {
        ss << bitCollection_[i - 1];
    }
    return ss.str();
}
