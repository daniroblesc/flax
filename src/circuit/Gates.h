#ifndef GATES_H_
#define GATES_H_

#include "Wire.h"
#include <vector>

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

class ORGate
{
public:
    void update(const bool a, const bool b);
    bool output();
    
private:
    Wire a_;    
    Wire b_;   
    Wire c_;
    Wire d_;

    NOTGate not_[2];
    NANDGate nand_; 
};

class XORGate
{
public:
    void update(const bool a, const bool b);
    bool output();
    
private:
    Wire a_;    
    Wire b_;   
    Wire c_;
    Wire d_;
    Wire e_;
    Wire f_;

    NOTGate not_[2];
    NANDGate nand_[3]; 
};

#endif // GATES_H_