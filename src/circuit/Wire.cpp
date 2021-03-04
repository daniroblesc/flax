
#include "Wire.h"
#include <assert.h>
#include <iostream>

//
// Wire implementation
//

Wire::Wire(const bool state)
{
    state_ = state;
}

void Wire::update(const bool state)
{
    state_ = state;
}

void Wire::set(const bool state)
{
    state_ = state;
}

void Wire::low()
{
    state_ = false;
}

void Wire::high()
{
    state_ = true;
}

bool Wire::output()
{
    return state_;
}

bool Wire::get()
{
    return state_;
}


//
// WireCollection implementation
//

WireCollection::WireCollection()
{
    for(size_t bit = 0; bit < Byte::NUM_BITS; ++bit)
    {
        wires_.push_back(Wire());
    }
}

WireCollection::WireCollection(const Byte& byte)
{
    for (size_t bit = 0; bit < Byte::NUM_BITS; ++bit)
    {
        bool value = byte[bit];
        wires_.push_back(Wire(value));
    }
}

bool WireCollection::output(int wire) 
{
    assert(wire < Byte::NUM_BITS);
    bool value = wires_[wire].output();
    return value;
}

Byte WireCollection::output() 
{
    Byte result;
    for (size_t bit = 0; bit < Byte::NUM_BITS; ++bit)
    {
        result.set(bit, wires_[bit].output());
    }

    return result;
}

void WireCollection::on(const int wire)
{
    assert(wire < Byte::NUM_BITS);
    wires_[wire].update(true);
}

void WireCollection::off(const int wire)
{
    assert(wire < Byte::NUM_BITS);
    wires_[wire].update(false);
}

void WireCollection::set(const Byte& byte)
{
    for (size_t bit = 0; bit < Byte::NUM_BITS; ++bit)
    {
        wires_[bit].update(byte[bit]);
    }
}