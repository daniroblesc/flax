#ifndef BYTE_H_
#define BYTE_H_

#include "Bit.h"

class Byte
{
public:

    static const int NUM_BITS;

    Byte(); // default constructor
    Byte(const int val);
    
    Byte& operator=(const Byte &that); // assignment operator
    Byte& operator=(const int &val); // assignment operator

    bool operator==(const Byte &that) const; // equals operator
    bool operator==(const int &val) const; // equals operator    

    int get() const;
    Bit get(const int position) const;

    void on(const int position);
    void off(const int position);

    void set(Bit value, const int position);

private:
    int val_ = 0; 
};


#endif // BYTE_H_