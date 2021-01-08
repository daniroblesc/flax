#include "Decoder.h"
#include <sstream>      // std::stringstream
#include <iostream>      

IDecoder::IDecoder(const int numInputs)
{
    numInputs_ = numInputs;

    not_.reserve(numInputs_);
    for (int i = 0; i < numInputs_; ++i)
    {
        not_.push_back(NOTGate());
    }

    numOutputs_ = 2^numInputs_;

    and_.reserve(numOutputs_);
    for (int i = 0; i < numOutputs_; ++i)
    {
        and_.push_back(ANDGate());
    }
}

IDecoder::~IDecoder()
{}

std::string IDecoder::toString(const std::vector<Bit>& inputs)
{
    std::stringstream ss_input;
    for (int i = 0; i < inputs.size(); ++i)
    {
        ss_input << inputs[i].toString();
    }
    return ss_input.str();
}

//
// Decoder2X4
//

Decoder2X4::Decoder2X4() : IDecoder(2)
{
}

Decoder2X4::~Decoder2X4()
{}

std::vector<Bit> Decoder2X4::execute(const std::vector<Bit>& inputs)
{
    //std::cout << "Decoder2X4::execute( input : " << toString(inputs) << ")" << std::endl;

    Bit a = inputs[0];
    Bit b = inputs[1];

    std::vector<Bit> negatedInputs;
    negatedInputs.push_back(not_[0].execute(a));
    negatedInputs.push_back(not_[1].execute(b));

    std::vector<Bit> output;
    output.reserve(numOutputs_);
    output.push_back( and_[0].execute(negatedInputs[0], negatedInputs[1]) );
    output.push_back( and_[1].execute(negatedInputs[0], b) );
    output.push_back( and_[2].execute(a, negatedInputs[1]) );
    output.push_back( and_[3].execute(a, b) );

    //std::cout << "Decoder2X4::execute( output : " << toString(output) << ")" << std::endl;

    return output;
}

//
// Decoder3X8
//

Decoder3X8::Decoder3X8() : IDecoder(3)
{
}

Decoder3X8::~Decoder3X8()
{}

std::vector<Bit> Decoder3X8::execute(const std::vector<Bit>& inputs)
{
    //std::cout << "Decoder3X8::execute( input : " << toString(inputs) << ")" << std::endl;

    Bit A = inputs[0];
    Bit B = inputs[1];
    Bit C = inputs[2];

    Bit notA = not_[0].execute(A);
    Bit notB = not_[1].execute(B);
    Bit notC = not_[2].execute(C);
    
    std::vector<Bit> output;
    output.reserve(numOutputs_);
    output.push_back(and_[0].execute(notA, notB, notC));// 000
    output.push_back(and_[1].execute(notA, notB, C));   // 001       
    output.push_back(and_[2].execute(notA, B, notC));   // 010
    output.push_back(and_[3].execute(notA, B, C));      // 011
    output.push_back(and_[4].execute(A, notB, notC));   // 100
    output.push_back(and_[5].execute(A, notB, C));      // 101
    output.push_back(and_[6].execute(A, B, notC));      // 110
    output.push_back(and_[7].execute(A, B, C));         // 111

    //std::cout << "Decoder3X8::execute( output : " << toString(output) << ")" << std::endl;

    return output;
}


//
// Decoder4X16
//

Decoder4X16::Decoder4X16() : IDecoder(4)
{
}

Decoder4X16::~Decoder4X16()
{}

std::vector<Bit> Decoder4X16::execute(const std::vector<Bit>& inputs)
{
    //std::cout << "Decoder4X16::execute( inputs : " << toString(inputs) << ")" << std::endl;

    Bit A = inputs[0];
    Bit B = inputs[1];
    Bit C = inputs[2];
    Bit D = inputs[3];

    Bit notA = not_[0].execute(A);
    Bit notB = not_[1].execute(B);
    Bit notC = not_[2].execute(C);
    Bit notD = not_[3].execute(D);
    
    std::vector<Bit> output;
    output.reserve(numOutputs_);
    /* 0000 */output.push_back(and_[0].execute(notA, notB, notC, notD));
    /* 0001 */output.push_back(and_[1].execute(notA, notB, notC, D));
    /* 0010 */output.push_back(and_[2].execute(notA, notB, C, notD));
    /* 0011 */output.push_back(and_[3].execute(notA, notB, C, D));
    /* 0100 */output.push_back(and_[4].execute(notA, B, notC, notD));
    /* 0101 */output.push_back(and_[5].execute(notA, B, notC, D));
    /* 0110 */output.push_back(and_[6].execute(notA, B, C, notD));
    /* 0111 */output.push_back(and_[7].execute(notA, B, C, D));
    /* 1000 */output.push_back(and_[8].execute(A, notB, notC, notD));
    /* 1001 */output.push_back(and_[9].execute(A, notB, notC, D));
    /* 1010 */output.push_back(and_[10].execute(A, notB, C, notD));
    /* 1011 */output.push_back(and_[11].execute(A, notB, C, D));
    /* 1100 */output.push_back(and_[12].execute(A, B, notC, notD));
    /* 1101 */output.push_back(and_[13].execute(A, B, notC, D));
    /* 1110 */output.push_back(and_[14].execute(A, B, C, notD));
    /* 1111 */output.push_back(and_[15].execute(A, B, C, D));

    //std::cout << "Decoder4X16::execute( output : " << toString(output) << ")" << std::endl;

    return output;
}