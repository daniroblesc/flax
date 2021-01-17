#include "Decoder.h"
#include <sstream>      // std::stringstream
#include <iostream>      
#include <math.h>


IDecoder::IDecoder(const int numInputs)
{
    numOutputs_ = pow(2, numInputs);
    output_.reserve(numOutputs_);    
}

IDecoder::~IDecoder()
{}

std::vector<bool> IDecoder::output()
{
    return output_;
}

bool IDecoder::output(const int n)
{
    return output_[n];
}

std::string IDecoder::toString(const std::vector<bool>& bitStream)
{
    std::stringstream ss;
    for (int i = 0; i < bitStream.size(); ++i)
    {
        ss << bitStream[i];
    }
    return ss.str();
}

int IDecoder::outputToInt()
{
    int retval = 0;
    for (int i = 0; i < output_.size(); ++i )
    {
        if (output_[i] == true)
        {
            return i;
        }
    }

    return 0;
}

//
// IBasicDecoder
//

BasicDecoder::BasicDecoder(const int numInputs) : IDecoder(numInputs)
{
    not_.reserve(numInputs);
    for (int i = 0; i < numInputs; ++i)
    {
        not_.push_back(NOTGate());
    }
    
    int numOutputs = pow(2, numInputs);

    and_.reserve(numOutputs);
    for (int i = 0; i < numOutputs; ++i)
    {
        and_.push_back(ANDGate());
    }
}

BasicDecoder::~BasicDecoder()
{}

//
// Decoder2X4
//

Decoder2X4::Decoder2X4() : BasicDecoder(2)
{}

Decoder2X4::~Decoder2X4()
{}

void Decoder2X4::update(const Byte& input)
{
    update(input[0], input[1]);
}

void Decoder2X4::update(const bool A, const bool B)
{
    //std::cout << "Decoder2X4::update( A: " << A.get() << " B: " << B.get() << ")" << std::endl;

    // Update NOT gates inputs
    not_[0].update(A);
    not_[1].update(B);

    // Get NOT gates outputs
    bool notA = not_[0].output();
    bool notB = not_[1].output();

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


//
// Decoder3X8
//

Decoder3X8::Decoder3X8() : BasicDecoder(3)
{}

Decoder3X8::~Decoder3X8()
{}

void Decoder3X8::update(const Byte& input)
{
    update(input[0], input[1], input[2]);
}

void Decoder3X8::update(const bool A, const bool B, const bool C)
{
    // Update NOT gates inputs
    not_[0].update(A);
    not_[1].update(B);
    not_[2].update(C);

    // Get NOT gates outputs
    bool notA = not_[0].output();
    bool notB = not_[1].output();
    bool notC = not_[2].output();

    //Update AND gates inputs
    and_[0].update(notC, notB, notA);
    and_[1].update(notC, notB, A);
    and_[2].update(notC, B,    notA);
    and_[3].update(notC, B,    A);

    and_[4].update(C, notB, notA);
    and_[5].update(C, notB, A);
    and_[6].update(C, B,    notA);
    and_[7].update(C, B,    A);

    output_.clear();    
    output_.push_back( and_[0].output() );
    output_.push_back( and_[1].output() );
    output_.push_back( and_[2].output() );
    output_.push_back( and_[3].output() );
    output_.push_back( and_[4].output() );
    output_.push_back( and_[5].output() );
    output_.push_back( and_[6].output() );
    output_.push_back( and_[7].output() );
}

//
// Decoder4X16
//

Decoder4X16::Decoder4X16() : BasicDecoder(4)
{
}

Decoder4X16::~Decoder4X16()
{}

void Decoder4X16::update(const Byte& input)
{
    update(input[0], input[1], input[2], input[3]);
}

void Decoder4X16::update(const bool A, const bool B, const bool C, const bool D)
{
    //std::cout << "Decoder4X16::update( A: " << A.get() << " B: " << B.get() << " C: " << C.get() << " D: " << D.get() << ")" << std::endl;

    // Update NOT gates inputs
    not_[0].update(A);
    not_[1].update(B);
    not_[2].update(C);
    not_[3].update(D);

    // Get NOT gates outputs
    bool notA = not_[0].output();
    bool notB = not_[1].output();
    bool notC = not_[2].output();
    bool notD = not_[3].output();

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


//
// Decoder8X256
//

Decoder8X256::Decoder8X256() : IDecoder(8)
{
    decoders4x16_.reserve(NUM_4X16DECODERS);
    for (int i=0; i < NUM_4X16DECODERS; i++)
    {
        decoders4x16_.push_back(Decoder4X16());
    }
}

Decoder8X256::~Decoder8X256()
{}

void Decoder8X256::update(const Byte& input)
{   
    //std::cout << "Decoder8X256::update( input : " << input.toString() << ")" << std::endl;

    bool a = input[0];
    bool b = input[1];
    bool c = input[2];
    bool d = input[3];
    bool e = input[4];
    bool f = input[5];
    bool g = input[6];
    bool h = input[7];

	decoderSelector_.update(e, f, g, h);   

    index_ = 0;
    for (int i=0; i < NUM_4X16DECODERS; i++)
	{
		updateDecoder(a, b, c, d, i, 16*i);
	}  

    output_.clear();
    for (int i=0; i < numOutputs_; i++)
    {
        if (index_ == i)
        {
            output_.push_back(true);
        }
        else
        {
            output_.push_back(false);            
        }
    }  
    //std::cout << "Decoder8X256::update( index_:" << index_ << ")" << std::endl;
    //std::cout << "Decoder8X256::update( output : " << toString(output_) << ")" << std::endl;
    //std::cout << "Decoder8X256::update( outputToInt : " << outputToInt() << ")" << std::endl;
}

void Decoder8X256::updateDecoder(bool& a, bool& b, bool& c, bool& d, int decoderIndex, int outputWireStart) 
{
	if (decoderSelector_.output(decoderIndex) == true)
    {
		decoders4x16_[decoderIndex].update(a, b, c, d);
        //std::cout << "Decoder8X256::updateDecoder( decoders4x16_[" << decoderIndex << "]: " << decoders4x16_[decoderIndex].outputToInt() << ")" << std::endl;

		for (int i=0; i < NUM_4X16DECODERS; i++)
        {
			if (decoders4x16_[decoderIndex].output(i) == true) 
            {
				index_ = outputWireStart + i;
			}
		}
	}
}

