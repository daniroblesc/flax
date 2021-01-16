#ifndef RAM_H_
#define RAM_H_

#include "circuit/BitGates.h"
#include "circuit/Bus.h"
#include "components/Register.h"
#include "components/Decoder.h"

class RAMCell 
{
public:
    RAMCell(Bus *bus);
    ~RAMCell();

    // update Cell's input with address bits
    void update(const bool a1, const bool a2);

    // write Cell's content to the bus
    void enable(const bool e = true);  

    // update Cell's content with data on the bus
    void set(const bool s = true);  

private:
    
    ANDGate X0_;
    ANDGate X1_;
    ANDGate X2_;
    Register* R_ = nullptr;
    Bus* bus_ = nullptr;
};

class RAMCellGrid
{
public:
    RAMCellGrid(Bus *bus, const int gridSize = 16);
    virtual ~RAMCellGrid();

    RAMCell* getCell(int col, int row);

private:

    int gridSize_ = 16;
    Bus *bus_ = nullptr;
    
    std::vector<std::vector<RAMCell*>> grid_;
};

class IRAM
{
public:
    IRAM(Bus *bus);
    virtual ~IRAM();
    
    virtual void enable(const bool e = true) = 0;
    virtual void set(const bool s = true) = 0; 

protected:

    Bus* systemBus_ = nullptr;

    std::string toString(const std::vector<bool>& v);
};

class RAM256 : public IRAM 
{
public:
    RAM256(Bus *bus);
    virtual ~RAM256();

    void setAddress(const bool sa = true);
    void enable(const bool e = true);
    void set(const bool s = true); 

private:
    
    Bus* MAROutputBus_ = nullptr;
    Register* MAR_ = nullptr;
    Decoder4X16 selectCol_;
    Decoder4X16 selectRow_;
    RAMCellGrid* cellGrid_ = nullptr;

    RAMCell* getSelectedCell();
};

class RAM65K : public IRAM 
{
public:
    RAM65K(Bus *bus);
    virtual ~RAM65K();

    void setS0(const bool s0 = true);
    void setS1(const bool s1 = true);
    void enable(const bool e = true);
    void set(const bool s = true); 

private:

    Bus* MAROutputBus0_ = nullptr;
    Bus* MAROutputBus1_ = nullptr;
    Register* MAR0_ = nullptr;
    Register* MAR1_ = nullptr;
    Decoder8X256 selectCol_;
    Decoder8X256 selectRow_;
    RAMCellGrid* cellGrid_ = nullptr;
    
    RAMCell* getSelectedCell();
};


#endif // RAM_H_
