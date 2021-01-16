#include "ByteGates.h"
#include <iostream>

//
// Notter
//

Notter::Notter()
{
    not_.resize(Byte::NUM_BITS);
}

Notter::~Notter()
{}


void Notter::update(const Byte& a)
{
    a_ = a;
}

Byte Notter::output()
{
    Byte output;
    for ( int i = 0; i < Byte::NUM_BITS; ++i )
    {
        not_[i].update(a_[i]);
        output.set(i, not_[i].output());
    }

    return output;
}

//
// Ander
//

Ander::Ander()
{
    and_.resize(Byte::NUM_BITS);
}

Ander::~Ander()
{}


void Ander::update(const Byte& a, const Byte& b)
{
    a_ = a;
    b_ = b;
}

Byte Ander::output()
{
    Byte output;
    for ( int i = 0; i < Byte::NUM_BITS; ++i )
    {
        and_[i].update(a_[i], b_[i]);
        output.set(i, and_[i].output());
    }

    return output;
}


//
// Orer
//

Orer::Orer()
{
    or_.resize(Byte::NUM_BITS);
}

Orer::~Orer()
{}


void Orer::update(const Byte& a, const Byte& b)
{
    a_ = a;
    b_ = b;
}

Byte Orer::output()
{
    Byte output;
    for ( int i = 0; i < Byte::NUM_BITS; ++i )
    {
        or_[i].update(a_[i], b_[i]);
        output.set(i, or_[i].output());
    }

    return output;
}


//
// XOrer
//

XOrer::XOrer()
{
    xor_.resize(Byte::NUM_BITS);
}

XOrer::~XOrer()
{}


void XOrer::update(const Byte& a, const Byte& b)
{
    a_ = a;
    b_ = b;
}

Byte XOrer::output()
{
    Byte output;
    for ( int i = 0; i < Byte::NUM_BITS; ++i )
    {
        xor_[i].update(a_[i], b_[i]);
        output.set(i, xor_[i].output());
    }

    return output;
}

//
// Adder
//

Adder::Adder()
{
    add_.resize(Byte::NUM_BITS);
}

Adder::~Adder()
{}

void Adder::update(const Byte& a, const Byte& b, const bool carryIn)
{
    a_ = a;
    b_ = b;
    carryIn_ = carryIn;
}

void Adder::output(Byte &sum, bool &carryOut)
{
   // bit 0
   add_[0].update(a_[0],b_[0],carryIn_);
   bool sumAux;
   add_[0].output(sumAux, carryOut);
   sum.set(0, sumAux);

   // bits 1 to 7
   for ( int i = 1; i < Byte::NUM_BITS; ++i )
   {
      add_[i].update(a_[i],b_[i],carryOut);
      add_[i].output(sumAux, carryOut);
      sum.set(i, sumAux);
   }
}

//
// Comparator
//

Comparator::Comparator()
{
    cmp_.resize(Byte::NUM_BITS);
}

Comparator::~Comparator()
{}

void Comparator::update(const Byte& a, const Byte& b)
{
    a_ = a;
    b_ = b;
}

void Comparator::output(Byte& c, bool& equal, bool& a_larger)
{
    equal = equal_;
    a_larger = a_larger_;

    for ( int i = Byte::NUM_BITS-1; i >= 0; --i )
    {
        cmp_[i].update(a_[i], b_[i], equal, a_larger);
        
        bool BitC;
        cmp_[i].output(BitC, equal, a_larger);

        c.set(i, BitC);
    }
}

//
// Z
//

void Z::update(const Byte& a)
{
    a_ = a;
}

bool Z::output()
{
    for ( int i = 0; i < Byte::NUM_BITS; ++i )
    {
        if (a_[i])
        {
            return false;
        }
    }

    return true;
}