#include "Adder.h"



//
// AddGate implementation
//

void AddGate::update(const bool a, const bool b, const bool carryIn)
{
    a_.update(a);
    b_.update(b);
    carryIn_.update(carryIn);
}

void AddGate::output(bool &sum, bool &carryOut)
{
    xor_[0].update(a_.output(), b_.output());

    and_[0].update(carryIn_.output(), xor_[0].output());
    and_[1].update(a_.output(), b_.output());

    xor_[1].update(xor_[0].output(), carryIn_.output());
    sum_.update(xor_[1].output());
    sum = sum_.output();

    or_.update(and_[0].output(), and_[1].output());
    carryOut_.update(or_.output());
    carryOut = carryOut_.output();
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
