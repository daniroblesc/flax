#ifndef BIT_H_
#define BIT_H_

class Bit
{
public:

    Bit(); // default constructor
    Bit(const int val);
    Bit(const bool val);
    Bit(const Bit &b); // copy constructor
    
    Bit& operator=(const Bit &a); // assignment operator
    bool operator==(const Bit &that) const; // equals operator
    bool operator==(const int &val) const; // equals operator
    bool operator==(const bool &val) const; // equals operator

    int get() const;

    void on();
    void off();

private:
    int val_ = 0; 
};


#endif // BIT_H_