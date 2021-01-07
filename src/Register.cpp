#include "Register.h"

void Register::write(const Byte& input)
{
    memoryByte_.write(input);
    enabler_.load(memoryByte_.read());
}

Byte Register::read()
{
    return enabler_.enable();
}