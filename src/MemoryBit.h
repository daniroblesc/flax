#ifndef MEMORY_BIT_H_
#define MEMORY_BIT_H_

class MemoryBit
{
public:

    void save(const bool I);
    bool get();

private:

    bool O_ = false; // output of the remembered bit
};


#endif // MEMORY_BIT_H_