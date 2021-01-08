#ifndef DECODER_H_
#define DECODER_H_

#include "Gates.h"
#include <vector>

class IDecoder
{
public:

    IDecoder(const int numInputs);
    virtual ~IDecoder();

    virtual std::vector<Bit> execute(const std::vector<Bit>& inputs) = 0;

protected:

    int numInputs_;
    int numOutputs_;

    std::vector<NOTGate> not_;
    std::vector<ANDGate> and_;

    std::string toString(const std::vector<Bit>& inputs);
};

class Decoder2X4 : public IDecoder
{
public:

    Decoder2X4();
    ~Decoder2X4();

    std::vector<Bit> execute(const std::vector<Bit>& inputs);
};

class Decoder3X8 : public IDecoder
{
public:

    Decoder3X8();
    ~Decoder3X8();

    std::vector<Bit> execute(const std::vector<Bit>& inputs);
};


class Decoder4X16 : public IDecoder
{
public:

    Decoder4X16();
    ~Decoder4X16();

    std::vector<Bit> execute(const std::vector<Bit>& inputs);
};


#endif // DECODER_H_  