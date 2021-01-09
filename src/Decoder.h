#ifndef DECODER_H_
#define DECODER_H_

#include "Gates.h"
#include <vector>

class IDecoder
{
public:

    IDecoder(const int numInputs);
    virtual ~IDecoder();
    
    virtual void update(const std::vector<Bit>& inputs) = 0;

    virtual std::vector<Bit> output() = 0;
    virtual Bit output(const int n) = 0;

protected:

    int numInputs_;
    int numOutputs_;

    std::vector<NOTGate> not_;
    std::vector<ANDGate> and_;
    std::vector<Bit> output_;

    std::string toString(const std::vector<Bit>& inputs);
};

class Decoder2X4 : public IDecoder
{
public:

    Decoder2X4();
    ~Decoder2X4();

    void update(const std::vector<Bit>& inputs);

    std::vector<Bit> output();
    Bit output(const int n);
};

class Decoder3X8 : public IDecoder
{
public:

    Decoder3X8();
    ~Decoder3X8();

    void update(const std::vector<Bit>& inputs);

    std::vector<Bit> output();
    Bit output(const int n);
};


class Decoder4X16 : public IDecoder
{
public:

    Decoder4X16();
    ~Decoder4X16();

    void update(const std::vector<Bit>& inputs);

    std::vector<Bit> output();
    Bit output(const int n);
};


#endif // DECODER_H_  