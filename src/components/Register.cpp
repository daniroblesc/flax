#include "Register.h"
#include <assert.h>     /* assert */
#include <iostream>

Register::Register(const std::string& id, Bus *bus, const Byte& defaultValue) : 
    control::IControllableUnit(id),
    IBusNode(id)
{
    inputBus_ = outputBus_ = bus;
    bus->subscribe(this);
    setDefaultValue(defaultValue);
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

void Register::setDefaultValue(const Byte& defaultValue)
{
    if (defaultValue == 0)
    {
        return;
    }
    memoryByte_.update(defaultValue);
    enabler_.update(memoryByte_.output());
}

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
    if (e == false) 
    {
        return;
    }

    // the E's inputs go to the outputs
    enabler_.enable();
    // get the E's outputs
    Byte output = enabler_.output();
    // save E's outputs to the bus
    outputBus_->write(this, output);
}

void Register::set(const bool s)
{
    if (s == false) 
    {
        return;
    }

    // get bus content
    Byte input = inputBus_->read(this);

    // update B's inputs with bus content & save B content
    memoryByte_.update(input, s);

    // update E's input with B's output
    enabler_.update(memoryByte_.output());
}

Byte Register::output()
{
    return memoryByte_.output();
}