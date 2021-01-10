#ifndef BIT_H_
#define BIT_H_

#include <string>

class Bit
{
public:
    typedef enum e_BitValue
    {
        ZERO = 0x0,
        ONE  = 0x1
    } BitValue;


    Bit();
    ~Bit();

    Bit(const e_BitValue val);
    Bit(const Bit &b); // copy constructor
    
    Bit& operator=(const Bit &that); // assignment operator
    Bit& operator=(const e_BitValue &val); // assignment operator

    bool operator==(const Bit &that) const; // equals operator
    bool operator==(const e_BitValue &val) const; // equals operator

    e_BitValue get() const;
    void set(const e_BitValue val);

    std::string toString() const;

private:
    e_BitValue value_ = ZERO; 
};


#endif // BIT_H_