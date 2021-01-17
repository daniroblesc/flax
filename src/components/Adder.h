
#ifndef ADDER_H_
#define ADDER_H_

#include "misc/Byte.h"
#include "circuit/Wire.h"
#include "circuit/BitGates.h"
#include <vector>

/* Half Adder:

    a   b  |  sum   carry  
    ----------------------
    0   0  |   0      0     
    1   0  |   1      0     
    0   1  |   1      0     
    1   1  |   0      1     

    'sum' is XOR(a,b)
    'carry' is AND(a,b)

    A Full Adder adds binary numbers and accounts for values carried in as well
    as out.
    
    A one-bit Full Adder adds three one-bit numbers, often written as A, B and Cin.

    A and B are the operands, and Cin is a bit carried in from the previous 
    less-signficant stage.
*/
class AddGate
{
public:
    void update(const bool a, const bool b, const bool carryIn);
    void output(bool &sum, bool &carryOut);

private:
    Wire a_;    
    Wire b_; 
    Wire carryIn_; 
    Wire sum_; 
    Wire carryOut_; 

    XORGate xor_[2];
    ANDGate and_[2];
    ORGate or_;
};


//
// Adder
//
class Adder
{
public:

    Adder();
    ~Adder();

    void update(const Byte& a, const Byte& b, const bool carryIn);
    void output(Byte &sum, bool &carryOut);

private:

    Byte a_;
    Byte b_;
    bool carryIn_; 
    bool carryOut_; 
    std::vector<AddGate> add_;
};

#endif // ADDER_H_