#include "Byte.h"
#include <sstream>      // std::stringstream
#include <string.h>
#include <iostream>      
#include <assert.h>     /* assert */

const int Byte::NUM_BITS = 8;

void Byte::initBitCollection()
{
    if (bitCollection_ == nullptr)
    {
        bitCollection_ = new bool[NUM_BITS];
        for (int i = 0; i < NUM_BITS; ++i )
        {
            bitCollection_[i] = false;
        }
    }
}

void Byte::initBitCollection(const int val)
{
    if (bitCollection_ == nullptr)
    {
        bitCollection_ = new bool[NUM_BITS];
    }

    for (int i = 0; i < NUM_BITS; ++i )
    {
        int b = (val >> i) & 1U;
        bitCollection_[i] = static_cast<bool>(b);
    }
}

void Byte::initBitCollection(bool* val)
{
    if (bitCollection_ == nullptr)
    {
        bitCollection_ = new bool[NUM_BITS];
    }

    for (int i = 0; i < NUM_BITS; ++i )
    {
        bitCollection_[i] = val[i];
    }
}

Byte::Byte()
{
    initBitCollection();
}

Byte::Byte(const int val)
{
    initBitCollection(val);
}

Byte::Byte(const Byte &that)
{
    initBitCollection(that.bitCollection_);
}

Byte::~Byte()
{
    delete [] bitCollection_;
}

Byte& Byte::operator=(const Byte &that)
{
    initBitCollection(that.bitCollection_);
    return *this;
}

Byte& Byte::operator=(const int &val)
{
    initBitCollection(val);
    return *this;
}
        
bool Byte::operator==(const Byte &that) const
{  
   return (toInt() == that.toInt());
}

bool Byte::operator==(const int &val) const
{
    return (val == toInt());
}

int Byte::toInt() const
{
    int retval = 0;
    for (int i = 0; i < NUM_BITS; ++i )
    {
        if (bitCollection_[i] == true)
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

const bool& Byte::operator[](int i) const // read
{
    assert(i < NUM_BITS);
    return bitCollection_[i];
}

void Byte::set(const int position, const bool value)
{
    bitCollection_[position] = value;
}

std::string Byte::toString() const
{
    std::stringstream ss;
    for (int i = NUM_BITS; i > 0; --i)
    {
        ss << bitCollection_[i - 1];
    }
    return ss.str();
}
