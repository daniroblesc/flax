#ifndef BIT_GATES_H_
#define BIT_GATES_H_

#include "Wire.h"
#include <vector>

/*  NAND gate (NOT-AND) is a logic gate which produces an output which is false
    only if all its inputs are true:

    a   b  |   c
    ---------------
    0   0  |   1  
    1   0  |   1  
    0   1  |   1   
    1   1  |   0   
 */
class NANDGate
{
public:
    void update(const bool a, const bool b);
    bool output();
    
private:
    Wire a_;    
    Wire b_;    
};

/*  inverter or NOT gate is a logic gate which implements logical negation:

    a   |   not a
    -------------
    0   |    1  
    1   |    0  
 */
class NOTGate
{
public:
    void update(const bool a);
    bool output();

private:
    Wire a_;    
};

/*  The AND gate is a basic digital logic gate that implements logical 
    conjunction - it behaves according to the following truth table:

    a   b  |   c
    ---------------
    0   0  |   0  
    1   0  |   0  
    0   1  |   0   
    1   1  |   1   
 */
class ANDGate
{
public:
    void update(const bool a, const bool b);
    void update(const bool a, const bool b, const bool c);
    void update(const bool a, const bool b, const bool c, const bool d);
    void update(const std::vector<bool>& inputs);

    bool output();

private:
    std::vector<bool> inputs_;
};

/*  The OR gate is a digital logic gate that implements logical 
    disjunction – it behaves according to the following truth table:

    a   b  |   c
    ---------------
    0   0  |   0  
    1   0  |   1  
    0   1  |   1   
    1   1  |   1   
 */
class ORGate
{
public:
    void update(const bool a, const bool b);
    bool output();
    
private:
    Wire a_;    
    Wire b_;   
    Wire c_;
    Wire d_;

    NOTGate not_[2];
    NANDGate nand_; 
};

/*  XOR represents the inequality function, i.e., the output is true if the 
    inputs are not alike otherwise the output is false. A way to remember 
    XOR is "must have one or the other but not both".

    a   b  |   c
    ---------------
    0   0  |   0  
    1   0  |   1  
    0   1  |   1   
    1   1  |   0    
*/
class XORGate
{
public:
    void update(const bool a, const bool b);
    bool output();
    
private:
    Wire a_;    
    Wire b_;   
    Wire c_;
    Wire d_;
    Wire e_;
    Wire f_;

    NOTGate not_[2];
    NANDGate nand_[3]; 
};

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

#endif // BIT_GATES_H_