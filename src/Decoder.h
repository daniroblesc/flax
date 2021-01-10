#ifndef DECODER_H_
#define DECODER_H_

#include "Gates.h"
#include "Byte.h"
#include <vector>

class IDecoder
{
public:

    IDecoder(const int numInputs);
    virtual ~IDecoder();
    
    virtual std::vector<Bit> output() = 0;
    virtual Bit output(const int n) = 0;
    int outputToInt();

protected:

    int numInputs_;
    int numOutputs_;

    std::vector<NOTGate> not_;
    std::vector<ANDGate> and_;
    std::vector<Bit> output_;

    std::string toString(const std::vector<Bit>& inputs);
};

/* Decoder2X4:
    input 'A' is bit0
    input 'B' is bit1 

    B   A  |  0/0   0/1   1/0   1/1  |  # (outputToInt)     
    ----------------------------------------
    0   0  |   1     0     0     0   |  0
    0   1  |   0     1     0     0   |  1
    1   0  |   0     0     1     0   |  2
    1   1  |   0     0     0     1   |  3

*/
class Decoder2X4 : public IDecoder
{
public:

    Decoder2X4();
    ~Decoder2X4();

    void update(const Bit& A, const Bit& B);

    std::vector<Bit> output();
    Bit output(const int n);
};


/* Decoder4X16:
    input 'A' is bit0
    input 'B' is bit1 
    input 'C' is bit2
    input 'D' is bit3 

    D C B A | 0000 0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111 | # (outputToInt)     
    -----------------------------------------------------------------------------------------------------------
    0 0 0 0 | 1    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    | 0 
    0 0 0 1 | 0    1    0    0    0    0    0    0    0    0    0    0    0    0    0    0    | 1  
    0 0 1 0 | 0    0    1    0    0    0    0    0    0    0    0    0    0    0    0    0    | 2
    0 0 1 1 | 0    0    0    1    0    0    0    0    0    0    0    0    0    0    0    0    | 3 
    0 1 0 0 | 0    0    0    0    1    0    0    0    0    0    0    0    0    0    0    0    | 4 
    0 1 0 1 | 0    0    0    0    0    1    0    0    0    0    0    0    0    0    0    0    | 5 
    0 1 1 0 | 0    0    0    0    0    0    1    0    0    0    0    0    0    0    0    0    | 6 
    0 1 1 1 | 0    0    0    0    0    0    0    1    0    0    0    0    0    0    0    0    | 7 
    1 0 0 0 | 0    0    0    0    0    0    0    0    1    0    0    0    0    0    0    0    | 8 
    1 0 0 1 | 0    0    0    0    0    0    0    0    0    1    0    0    0    0    0    0    | 9 
    1 0 1 0 | 0    0    0    0    0    0    0    0    0    0    1    0    0    0    0    0    | 10 
    1 0 1 1 | 0    0    0    0    0    0    0    0    0    0    0    1    0    0    0    0    | 11  
    1 1 0 0 | 0    0    0    0    0    0    0    0    0    0    0    0    1    0    0    0    | 12   
    1 1 0 1 | 0    0    0    0    0    0    0    0    0    0    0    0    0    1    0    0    | 13   
    1 1 1 0 | 0    0    0    0    0    0    0    0    0    0    0    0    0    0    1    0    | 14   
    1 1 1 1 | 0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    1    | 15  
*/
class Decoder4X16 : public IDecoder
{
public:

    Decoder4X16();
    ~Decoder4X16();

    void update(const Byte& input);
    void update(const Bit& A, const Bit& B, const Bit& C, const Bit& D);

    std::vector<Bit> output();
    Bit output(const int n);
};


#endif // DECODER_H_  