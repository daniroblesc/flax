#ifndef GATES_H_
#define GATES_H_

class NANDGate
{
public:
    bool execute(const bool a, const bool b);
};

class NOTGate
{
public:
    bool execute(const bool a);
};

class ANDGate
{
public:
    bool execute(const bool a, const bool b);
};


#endif // GATES_H_