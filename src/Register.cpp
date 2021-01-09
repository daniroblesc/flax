#include "Register.h"

Register::Register(Bus *bus) : IBusNode(bus)
{

}

Register::~Register()
{

}

void Register::enable(const Bit& e)
{
    // the E's inputs go to the outputs
    enabler_.enable(e);
    // get the E's outputs
    Byte output = enabler_.output();
    // save E's outputs to the bus
    bus_->set(output);
}

void Register::set(const Bit& s)
{
    // get bus content
    Byte input = bus_->get();

    // update B's inputs with bus content
    memoryByte_.update(input);
    // save B content
    memoryByte_.set(s);   

    // update E's input with B's output
    enabler_.update(memoryByte_.output());
}
