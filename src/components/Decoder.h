#ifndef DECODER_H_
#define DECODER_H_

#include "circuit/BitGates.h"
#include "circuit/Byte.h"
#include <vector>

class IDecoder
{
public:
    IDecoder(const int numInputs);
    virtual ~IDecoder();

    virtual void update(const Byte& input) = 0;

    std::vector<bool> output();
    bool output(const int n);
    int outputToInt();

protected:
    int numOutputs_;
    std::vector<bool> output_;

    std::string toString(const std::vector<bool>& bitStream);
};

class BasicDecoder : public IDecoder
{
public:

    BasicDecoder(const int numInputs);
    virtual ~BasicDecoder();
    

protected:

    std::vector<NOTGate> not_;
    std::vector<ANDGate> and_;
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
class Decoder2X4 : public BasicDecoder
{
public:

    Decoder2X4();
    ~Decoder2X4();

    void update(const Byte& input);
    void update(const bool A, const bool B);
};


/* Decoder3X8:
    input 'A' is bit0
    input 'B' is bit1 
    input 'C' is bit2 

    C   B   A  |  0/0/0   0/0/1   0/1/0   0/1/1   1/0/0   1/0/1   1/1/0   1/1/1   |  # (outputToInt)     
    -------------------------------------------------------------------------------------------------
    0   0   0  |    1       0       0       0       0       0       0       0     |  0
    0   0   1  |    0       1       0       0       0       0       0       0     |  1
    0   1   0  |    0       0       1       0       0       0       0       0     |  2
    0   1   1  |    0       0       0       1       0       0       0       0     |  3
    1   0   0  |    0       0       0       0       1       0       0       0     |  4
    1   0   1  |    0       0       0       0       0       1       0       0     |  5
    1   1   0  |    0       0       0       0       0       0       1       0     |  6
    1   1   1  |    0       0       0       0       0       0       0       1     |  7
*/
class Decoder3X8 : public BasicDecoder
{
public:

    Decoder3X8();
    ~Decoder3X8();

    void update(const Byte& input);
    void update(const bool A, const bool B, const bool C);
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
class Decoder4X16 : public BasicDecoder
{
public:

    Decoder4X16();
    ~Decoder4X16();

    void update(const Byte& input);
    void update(const bool A, const bool B, const bool C, const bool D);
};

/* Decoder8X256:
*/

class Decoder8X256 : public IDecoder
{
public:

    Decoder8X256();
    ~Decoder8X256();

    void update(const Byte& input);

private:

    const int NUM_4X16DECODERS = 16;

    Decoder4X16 decoderSelector_;
	std::vector<Decoder4X16> decoders4x16_;
    int index_;
    
    void updateDecoder(bool& a, bool& b, bool& c, bool& d, int decoderIndex, int outputWireStart);
};

#endif // DECODER_H_  