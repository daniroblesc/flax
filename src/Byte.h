#ifndef BYTE_H_
#define BYTE_H_

#include "Bit.h"
#include <string>

class Byte
{
public:

    static const int NUM_BITS;

    Byte(); // default constructor
    Byte(const Byte &that);
    Byte(const int val);
    
    Byte& operator=(const Byte &that); // assignment operator
    Byte& operator=(const int &val); // assignment operator

    bool operator==(const Byte &that) const; // equals operator
    bool operator==(const int &val) const; // equals operator    

    int get() const;
    Bit get(const int position) const;

    void set(Bit value, const int position);

    std::string toString();

private:
    Bit::e_BitValue bitCollection_[8];

    void setBitCollection(const int val, Bit::e_BitValue* bitCollection);
};


#endif // BYTE_H_