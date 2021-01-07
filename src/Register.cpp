#include "Register.h"

void Register::write(const Byte& input)
{
    B_.save(input);
}

Byte Register::read()
{
    Byte aux = B_.get();
    Byte output = E_.execute(aux);
    return output;
}