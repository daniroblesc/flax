#include "Bus1.h"
#include <iostream>
#include <assert.h>     /* assert */

Bus1::Bus1(const std::string& id, const std::shared_ptr<Bus>& inputBus, const std::shared_ptr<Bus>& outputBus)  : 
    control::IControllableUnit(id),
    IBusNode(id)
{
    inputBus_ = inputBus;
    outputBus_ = outputBus;
    inputBus_->subscribe(this);
    outputBus_->subscribe(this);    
}

void Bus1::enable(const bool bus1)
{
    // get bus content
    Byte input = inputBus_->read(this);
    
    bus1_.update(bus1);
    not_.update(bus1_.output());  

    Byte output;
    or_.update(input[0], bus1_.output());
    output.set(0, or_.output());

    for (int i = 0; i < Byte::NUM_BITS - 1; ++i)
    {
        and_[i].update(input[i+1], not_.output());
        output.set(i+1, and_[i].output());
    }
    
    // save output to the bus
    outputBus_->write(this, output);
}

void Bus1::signal(const control::signalType type, const control::SignalCollection& value)
{
    assert(value.size()==1);

    switch (type)
    {
    case control::SIG_ENABLE:
        enable(value[0]);
        break;
    
    default:
        assert(0);
        break;
    }

}