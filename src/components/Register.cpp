#include "Register.h"

Register::Register(Bus *bus) 
{
    inputBus_ = outputBus_ = bus;
}

Register::Register(Bus *inputBus, Bus *outputBus) 
{
    inputBus_ = inputBus;
    outputBus_ = outputBus;
}

Register::~Register()
{}

void Register::enable(const bool e)
{
    // the E's inputs go to the outputs
    enabler_.enable(e);
    // get the E's outputs
    Byte output = enabler_.output();
    // save E's outputs to the bus
    outputBus_->set(output);
}

void Register::set(const bool s)
{
    // get bus content
    Byte input = inputBus_->get();

    // update B's inputs with bus content
    memoryByte_.update(input);
    // save B content
    memoryByte_.set(s);   

    // update E's input with B's output
    enabler_.update(memoryByte_.output());
}
