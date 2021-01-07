#include "Bit.h"

Bit::Bit()
{

}

Bit::Bit(const int val)
{
    val_ = val;
}

Bit::Bit(const bool val)
{
    val_ = static_cast<int>(val);
}

Bit::Bit(const Bit &b)
{
    val_ = b.val_;
}

int Bit::get() const
{
    return val_;
}
    
void Bit::on()
{
    val_ = 1;
}

void Bit::off()
{
    val_ = 0;
}

Bit& Bit::operator=(const Bit &a) 
{
    this->val_ = a.val_;
    return *this;  // Return a reference to myself.
}

Bit& Bit::operator=(const int &val)
{
    this->val_ = val;
    return *this;  // Return a reference to myself.
}

Bit& Bit::operator=(const bool &val)
{
    this->val_ = static_cast<int>(val);
    return *this;  // Return a reference to myself.
}

bool Bit::operator==(const Bit &that) const
{
    return (this->val_ == that.val_);
}

bool Bit::operator==(const int &val) const
{
    return (this->val_ == val);
}

bool Bit::operator==(const bool &val) const
{
    return (this->val_ == val);
}