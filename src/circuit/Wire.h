
#ifndef WIRE_H_
#define WIRE_H_

class Wire
{
public:
    void update(const bool value);
    bool output();

private:

    bool output_ = false;
};

#endif // WIRE_H_