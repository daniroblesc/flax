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

std::string IDecoder::toString(const std::vector<Bit>& v)
{
    std::stringstream ss;
    for (int i = 0; i < v.size(); ++i)
    {
        ss << v[i].toString();
    }
    return ss.str();
}

int IDecoder::outputToInt()
{
    int retval = 0;
    for (int i = 0; i < output_.size(); ++i )
    {
        if (output_[i] == Bit::ONE)
        {
            return i;
        }
    }

    return 0;
}

//
// Decoder2X4
//

Decoder2X4::Decoder2X4() : IDecoder(2)
{}

Decoder2X4::~Decoder2X4()
{}

void Decoder2X4::update(const Bit& A, const Bit& B)
{
    //std::cout << "Decoder2X4::update( A: " << A.get() << " B: " << B.get() << ")" << std::endl;

    // Update NOT gates inputs
    not_[0].update(A);
    not_[1].update(B);

    // Get NOT gates outputs
    Bit notA = not_[0].output();
    Bit notB = not_[1].output();

    //Update AND gates inputs
    and_[0].update(notB, notA);
    and_[1].update(notB, A);
    and_[2].update(B,    notA);
    and_[3].update(B,    A);

    output_.clear();    
    output_.push_back( and_[0].output() );
    output_.push_back( and_[1].output() );
    output_.push_back( and_[2].output() );
    output_.push_back( and_[3].output() );

    //std::cout << "Decoder2X4::update( output : " << toString(output_) << ")" << std::endl;
    //std::cout << "Decoder2X4::update( outputToInt : " << outputToInt() << ")" << std::endl;
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
// Decoder4X16
//

Decoder4X16::Decoder4X16() : IDecoder(4)
{
}

Decoder4X16::~Decoder4X16()
{}

void Decoder4X16::update(const Byte& input)
{
    update(input.get(0), input.get(1), input.get(2), input.get(3));
}

void Decoder4X16::update(const Bit& A, const Bit& B, const Bit& C, const Bit& D)
{
    //std::cout << "Decoder4X16::update( A: " << A.get() << " B: " << B.get() << " C: " << C.get() << " D: " << D.get() << ")" << std::endl;

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
    /* 0000 */and_[0].update(notD, notC, notB, notA);
    /* 0001 */and_[1].update(notD, notC, notB, A);
    /* 0010 */and_[2].update(notD, notC, B,    notA);
    /* 0011 */and_[3].update(notD, notC, B,    A);

    /* 0100 */and_[4].update(notD, C, notB, notA);
    /* 0101 */and_[5].update(notD, C, notB, A);
    /* 0110 */and_[6].update(notD, C, B,    notA);
    /* 0111 */and_[7].update(notD, C, B,    A);

    /* 1000 */and_[8].update( D, notC, notB, notA);
    /* 1001 */and_[9].update( D, notC, notB, A);
    /* 1010 */and_[10].update(D, notC, B,    notA);
    /* 1011 */and_[11].update(D, notC, B,    A);

    /* 1100 */and_[12].update(D, C, notB, notA);
    /* 1101 */and_[13].update(D, C, notB, A);
    /* 1110 */and_[14].update(D, C, B,    notA);
    /* 1111 */and_[15].update(D, C, B,    A);

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

    //std::cout << "Decoder4X16::update( output : " << toString(output_) << ")" << std::endl;
    //std::cout << "Decoder4X16::update( outputToInt : " << outputToInt() << ")" << std::endl;
}

std::vector<Bit> Decoder4X16::output()
{
    return output_;
}

Bit Decoder4X16::output(const int n)
{
    return output_[n];
}

