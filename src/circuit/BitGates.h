#ifndef BIT_GATES_H_
#define BIT_GATES_H_

#include "Wire.h"
#include <vector>

class NANDGate
{
public:
    void update(const bool a, const bool b);
    bool output();
    
private:
    Wire a_;    
    Wire b_;    
};

class NOTGate
{
public:
    void update(const bool a);
    bool output();

private:
    Wire a_;    
};

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

/*

Half Adder:

    a   b  |  sum   carry  
    ----------------------
    0   0  |   0      0     
    1   0  |   1      0     
    0   1  |   1      0     
    1   1  |   0      1     

    'sum' is XOR(a,b)
    'carry' is AND(a,b)

A Full Adder adds binary numbers and accounts for values carried in as well as out.
A one-bit Full Adder adds three one-bit numbers, often written as A, B and Cin;
A and B are the operands, and Cin is a bit carried in from the previous less-signficant stage.

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

class CompGate
{
public:
    void update(const bool a, const bool b, const bool equal, const bool a_larger);
    void output(bool& c, bool& equal, bool& a_larger);

private:

    Wire a_;    
    Wire b_; 
    Wire c_;
    Wire allBitsAboveAreEqual_;
    Wire aAboveIsLarger_;


    XORGate xor_;
    NOTGate not_;
    ANDGate and_[2];
    ORGate or_;

};

#endif // BIT_GATES_H_