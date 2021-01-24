#include "Bus1.h"

Bus1::Bus1(Bus *inputBus, Bus *outputBus) 
{
    inputBus_ = inputBus;
    outputBus_ = outputBus;
}

Bus1::~Bus1()
{}

void Bus1::enable(const bool bus1)
{
    bus1_.update(bus1);
    not_.update(bus1_.output());

    Byte input = inputBus_->get();
    Byte output;

    or_.update(input[0], not_.output());
    output.set(0, or_.output());

    for (int i = 0; i < Byte::NUM_BITS - 1; ++i)
    {
        and_[i].update(input[i+1], not_.output());
        output.set(i+1, and_[i].output());
    }
    
    // save output to the bus
    outputBus_->set(output);
}