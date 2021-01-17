#include "Comparator.h"


//
// CompGate implementation
//

void CompGate::update(const bool a, const bool b, const bool equal, const bool a_larger)
{
    //std::cout << "a: " << a << " b: " << b << std::endl;
    a_.update(a);
    b_.update(b);    
    allBitsAboveAreEqual_.update(equal);
    aAboveIsLarger_.update(a_larger);
}

void CompGate::output(bool& c, bool& equal, bool& a_larger)
{
    // 1
    //
    xor_.update(a_.output(), b_.output());
    c_.update(xor_.output()); 

    // 2
    //
    not_.update(c_.output());
    Wire wireEqual;
    wireEqual.update(not_.output());

    // 3
    // 
    and_[0].update(wireEqual.output(), allBitsAboveAreEqual_.output());

    // 4
    // 
    and_[1].update(allBitsAboveAreEqual_.output(), a_.output(), c_.output());    

    // 5
    //
    or_.update(and_[1].output(), aAboveIsLarger_.output());
    
    // Prepare output args
    //
    c = c_.output();  
    equal = and_[0].output();
    a_larger = or_.output();
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