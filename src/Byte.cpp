
#include "Byte.h"

const int Byte::NUM_BITS = 8;

Byte::Byte()
{
}
    
Byte::Byte(const int val)
{
    val_ = val;
}
    
Byte& Byte::operator=(const Byte &that)
{
    this->val_ = that.val_;
    return *this;
}
    
bool Byte::operator==(const Byte &that) const
{
    return (this->val_ == that.val_); 
}

bool Byte::operator==(const int &val) const
{
    return (this->val_ == val_);
}

int Byte::get() const
{
    return val_;
}

Bit Byte::get(const int position) const
{
    int b = (val_ >> position) & 1U;
    return Bit(b);
}

void Byte::on(const int position)
{
    val_ |= 1UL << position;
}

void Byte::off(const int position)
{
    val_ &= ~(1UL << position);
}

void Byte::set(Bit value, const int position)
{
    if (value == 0)
    {
        off(position);
    }
    else
    {
        on(position);
    }
}