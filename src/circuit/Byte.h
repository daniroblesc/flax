#ifndef BYTE_H_
#define BYTE_H_

#include <string>

class Byte
{
public:

    static const int NUM_BITS;

    Byte(); // default constructor
    Byte(const Byte &that);
    Byte(const int val);
    ~Byte();
    
    Byte& operator=(const Byte &that); // assignment operator
    Byte& operator=(const int &val); // assignment operator

    bool operator==(const Byte &that) const; // equals operator
    bool operator==(const int &val) const; // equals operator    

    int toInt() const;
    std::string toString() const;
    
    const bool& operator[](int) const; // read
    void set(const int position, const bool value);  

private:
    bool* bitCollection_ = nullptr;

    void initBitCollection();
    void initBitCollection(const int val);
    void initBitCollection(bool* val);
};


#endif // BYTE_H_