#include "Gates.h"

//
// NANDGate implementation
//

void NANDGate::update(const bool a, const bool b)
{
    a_.update(a);
    b_.update(b);
}

bool NANDGate::output()
{
    if ((a_.output()) && (b_.output()))
    {
        return false;          
    }

    return true;
}

//
// NOTGate implementation
//

void NOTGate::update(const bool a)
{
    a_.update(a);
}

bool NOTGate::output()
{
    if (a_.output())
    {
        return false;  
    }

    return true;
}

//
// ANDGate implementation
//

void ANDGate::update(const bool a, const bool b)
{
    inputs_.clear();
    inputs_.push_back(a);
    inputs_.push_back(b);
}

void ANDGate::update(const bool a, const bool b, const bool c)
{
    inputs_.clear();
    inputs_.push_back(a);
    inputs_.push_back(b);
    inputs_.push_back(c);
}

void ANDGate::update(const bool a, const bool b, const bool c, const bool d)
{
    inputs_.clear();
    inputs_.push_back(a);
    inputs_.push_back(b);
    inputs_.push_back(c);
    inputs_.push_back(d);
}

void ANDGate::update(const std::vector<bool>& inputs)
{
    inputs_.clear();
    inputs_ = inputs;
}

bool ANDGate::output()
{
    size_t n = inputs_.size();
    for (int i = 0; i < n; ++i)
    {
        if (inputs_[i] == false)
        {
            return false;
        }
    }

    return true;
}