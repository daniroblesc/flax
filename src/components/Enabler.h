#ifndef ENABLER_H_
#define ENABLER_H_

#include "circuit/BitGates.h"
#include "circuit/Byte.h"
#include <vector>

class Enabler
{
public:
    
    Enabler();
    ~Enabler();


    // update the input
    void update(const Byte& input);
    
    // enable/disable 'e' bit
    void enable(const bool e = true);

    // get the output
    Byte output();
    
private:
    std::vector< ANDGate > gatesCollection_;
    Byte input_;
    Wire e_;
};

#endif // ENABLER_H_  