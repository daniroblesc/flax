#ifndef BUS_H_
#define BUS_H_

#include "Byte.h"

// This is a 8-bit bus: an IBusNode set/get value into the bus 
//  note: set() must be thread-safe 
class Bus
{
public:

    // an IBusNode turn the bit 'e' (enable) to ON so its data
    // is now in the bus
    void set(const Byte& value)
    {
        value_ = value;
    }

    // an IBusNode turn the bit 's' (set) to ON so the byte from
    // the bus has been copied to this IBusNode
    Byte get()
    {
        return value_;
    }

    std::string toString()
    {
        return value_.toString();
    }

private:
    Byte value_;
};

// This is the interface for a Bus node
class IBusNode
{
public:  
    IBusNode(Bus *bus)
    {
        bus_ = bus;   
    };

    ~IBusNode() {};

    virtual void enable(const Bit& e) = 0; // node's content is written to the bus
    virtual void set(const Bit& s) = 0; // node's content is refreshed with the bus content
       
protected:
    Bus* bus_ = nullptr;
};

#endif // BUS_H_