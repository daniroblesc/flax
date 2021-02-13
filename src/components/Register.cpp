#include "Register.h"
#include <assert.h>     /* assert */

Register::Register(const std::string& id, Bus *bus) : 
    control::IControllableUnit(id),
    IBusNode(id)
{
    inputBus_ = outputBus_ = bus;
    bus->subscribe(this);
}

Register::Register(const std::string& id, Bus *inputBus, Bus *outputBus) : 
    control::IControllableUnit(id),
    IBusNode(id)
{
    inputBus_ = inputBus;
    outputBus_ = outputBus;
    inputBus_->subscribe(this);
    outputBus_->subscribe(this);
}

Register::~Register()
{}

void Register::signal(const control::signalType type, const control::SignalCollection& value)
{
    assert(value.size()==1);

    switch (type)
    {
    case control::SIG_ENABLE:
        enable(value[0]);
        break;
    
    case control::SIG_SET:
        set(value[0]);
        break;

    default:
        assert(0);
        break;
    }
}

void Register::enable(const bool e)
{
    // the E's inputs go to the outputs
    enabler_.enable(e);
    // get the E's outputs
    Byte output = enabler_.output();
    // save E's outputs to the bus
    outputBus_->write(this, output);
}

void Register::set(const bool s)
{
    // get bus content
    Byte input = inputBus_->read(this);

    // update B's inputs with bus content & save B content
    memoryByte_.update(input, s);

    // update E's input with B's output
    enabler_.update(memoryByte_.output());
}
