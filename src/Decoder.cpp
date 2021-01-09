#include "Decoder.h"
#include <sstream>      // std::stringstream
#include <iostream>      
#include <math.h>

IDecoder::IDecoder(const int numInputs)
{
    numInputs_ = numInputs;

    not_.reserve(numInputs_);
    for (int i = 0; i < numInputs_; ++i)
    {
        not_.push_back(NOTGate());
    }
    
    numOutputs_ = pow(2, numInputs_);

    and_.reserve(numOutputs_);
    for (int i = 0; i < numOutputs_; ++i)
    {
        and_.push_back(ANDGate());
    }

    output_.reserve(numOutputs_);    
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
{}

Decoder2X4::~Decoder2X4()
{}

void Decoder2X4::update(const std::vector<Bit>& inputs)
{
   // std::cout << "Decoder2X4::execute( input : " << toString(inputs) << ")" << std::endl;

    Bit A = inputs[0];
    Bit B = inputs[1];

    // Update NOT gates inputs
    not_[0].update(A);
    not_[1].update(B);

    // Get NOT gates outputs
    Bit notA = not_[0].output();
    Bit notB = not_[1].output();

    // Update AND gates inputs
    and_[0].update(notA, notB);
    and_[1].update(notA, B);
    and_[2].update(A, notB);
    and_[3].update(A, B);

    output_.clear();    
    output_.push_back( and_[0].output() );
    output_.push_back( and_[1].output() );
    output_.push_back( and_[2].output() );
    output_.push_back( and_[3].output() );

   // std::cout << "Decoder2X4::execute( output : " << toString(output_) << ")" << std::endl;
}

std::vector<Bit> Decoder2X4::output()
{
    return output_;
}

Bit Decoder2X4::output(const int n)
{
    return output_[n];
}


//
// Decoder3X8
//

Decoder3X8::Decoder3X8() : IDecoder(3)
{}

Decoder3X8::~Decoder3X8()
{}

void Decoder3X8::update(const std::vector<Bit>& inputs)
{
    //std::cout << "Decoder3X8::execute( input : " << toString(inputs) << ")" << std::endl;

    Bit A = inputs[0];
    Bit B = inputs[1];
    Bit C = inputs[2];

    // Update NOT gates inputs
    not_[0].update(A);
    not_[1].update(B);
    not_[2].update(C);

    // Get NOT gates outputs
    Bit notA = not_[0].output();
    Bit notB = not_[1].output();
    Bit notC = not_[2].output();

    // Update AND gates inputs
    and_[0].update(notA, notB, notC);// 000
    and_[1].update(notA, notB, C);   // 001       
    and_[2].update(notA, B, notC);   // 010
    and_[3].update(notA, B, C);      // 011
    and_[4].update(A, notB, notC);   // 100
    and_[5].update(A, notB, C);      // 101
    and_[6].update(A, B, notC);      // 110
    and_[7].update(A, B, C);         // 111

    output_.clear();
    output_.push_back(and_[0].output());
    output_.push_back(and_[1].output());
    output_.push_back(and_[2].output());
    output_.push_back(and_[3].output());
    output_.push_back(and_[4].output());
    output_.push_back(and_[5].output());
    output_.push_back(and_[6].output());
    output_.push_back(and_[7].output());

    //std::cout << "Decoder3X8::execute( output : " << toString(output) << ")" << std::endl;
}

std::vector<Bit> Decoder3X8::output()
{
    return output_;
}

Bit Decoder3X8::output(const int n)
{
    return output_[n];
}

//
// Decoder4X16
//

Decoder4X16::Decoder4X16() : IDecoder(4)
{
}

Decoder4X16::~Decoder4X16()
{}

void Decoder4X16::update(const std::vector<Bit>& inputs)
{
//std::cout << "Decoder4X16::execute( inputs : " << toString(inputs) << ")" << std::endl;

    Bit A = inputs[0];
    Bit B = inputs[1];
    Bit C = inputs[2];
    Bit D = inputs[3];

    // Update NOT gates inputs
    not_[0].update(A);
    not_[1].update(B);
    not_[2].update(C);
    not_[3].update(D);

    // Get NOT gates outputs
    Bit notA = not_[0].output();
    Bit notB = not_[1].output();
    Bit notC = not_[2].output();
    Bit notD = not_[3].output();

    // Update AND gates inputs
    /* 0000 */and_[0].update(notA, notB, notC, notD);
    /* 0001 */and_[1].update(notA, notB, notC, D);
    /* 0010 */and_[2].update(notA, notB, C, notD);
    /* 0011 */and_[3].update(notA, notB, C, D);
    /* 0100 */and_[4].update(notA, B, notC, notD);
    /* 0101 */and_[5].update(notA, B, notC, D);
    /* 0110 */and_[6].update(notA, B, C, notD);
    /* 0111 */and_[7].update(notA, B, C, D);
    /* 1000 */and_[8].update(A, notB, notC, notD);
    /* 1001 */and_[9].update(A, notB, notC, D);
    /* 1010 */and_[10].update(A, notB, C, notD);
    /* 1011 */and_[11].update(A, notB, C, D);
    /* 1100 */and_[12].update(A, B, notC, notD);
    /* 1101 */and_[13].update(A, B, notC, D);
    /* 1110 */and_[14].update(A, B, C, notD);
    /* 1111 */and_[15].update(A, B, C, D);

    output_.clear();
    /* 0000 */output_.push_back(and_[0].output());
    /* 0001 */output_.push_back(and_[1].output());
    /* 0010 */output_.push_back(and_[2].output());
    /* 0011 */output_.push_back(and_[3].output());
    /* 0100 */output_.push_back(and_[4].output());
    /* 0101 */output_.push_back(and_[5].output());
    /* 0110 */output_.push_back(and_[6].output());
    /* 0111 */output_.push_back(and_[7].output());
    /* 1000 */output_.push_back(and_[8].output());
    /* 1001 */output_.push_back(and_[9].output());
    /* 1010 */output_.push_back(and_[10].output());
    /* 1011 */output_.push_back(and_[11].output());
    /* 1100 */output_.push_back(and_[12].output());
    /* 1101 */output_.push_back(and_[13].output());
    /* 1110 */output_.push_back(and_[14].output());
    /* 1111 */output_.push_back(and_[15].output());

    //std::cout << "Decoder4X16::execute( output : " << toString(output) << ")" << std::endl;
}

std::vector<Bit> Decoder4X16::output()
{
    return output_;
}

Bit Decoder4X16::output(const int n)
{
    return output_[n];
}
