#ifndef GATES_H_
#define GATES_H_

#include "Bit.h"
#include <vector>

class Wire
{
public:
    Wire() {};
    ~Wire() {};

    void update(const bool value)
    {
        output_ = value;
    }

    bool output()
    {
        return output_;
    }

private:

    bool output_;
};

class NANDGate
{
public:
    void update(const bool a, const bool b);
    bool output();
    
private:
    Wire a_;    
    Wire b_;    
};

class NOTGate
{
public:
    void update(const bool a);
    bool output();

private:
    Wire a_;    
};

class ANDGate
{
public:
    void update(const bool a, const bool b);
    void update(const bool a, const bool b, const bool c);
    void update(const bool a, const bool b, const bool c, const bool d);
    void update(const std::vector<bool>& inputs);

    bool output();

private:
    std::vector<bool> inputs_;
};


#endif // GATES_H_