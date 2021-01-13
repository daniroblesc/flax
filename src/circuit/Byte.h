#ifndef BYTE_H_
#define BYTE_H_

#include <string>
#include <vector>

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

    int toInt() const;
    std::string toString() const;

    bool get(const int position) const;
    void set(const int position, const bool value);  

private:
    std::vector<bool> bitCollection_;

    void initBitCollection();
    void setBitCollection(const int val);
};


#endif // BYTE_H_