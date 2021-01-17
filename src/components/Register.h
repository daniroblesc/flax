#ifndef REGISTER_H_
#define REGISTER_H_

#include "Enabler.h"
#include "memory/MemoryByte.h"
#include "circuit/Bus.h"

class Register 
{
public:

    Register(Bus* bus);
    Register(Bus* inputBus, Bus* outputBus);
    ~Register();

    void enable(const bool e = true);  // register's content is written to the bus
    void set(const bool s = true);  // register content is refreshed with the bus content

private:

    Enabler enabler_;
    MemoryByte memoryByte_;

    Bus* inputBus_;
    Bus* outputBus_;
};

#endif // REGISTER_H_  