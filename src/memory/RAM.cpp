#include "RAM.h"
#include <iostream>
#include <sstream>      // std::stringstream
#include <assert.h>     /* assert */

RAMCell::RAMCell(Bus *bus) 
{
    bus_ = bus;
    R_ = new Register("RamCell", bus_, bus_);
}   

RAMCell::~RAMCell()
{
    delete R_;
}

void RAMCell::update(const bool a1, const bool a2)
{
    X0_.update(a1, a2);
}

void RAMCell::enable(const bool e)
{
    X2_.update( X0_.output(), e );
    R_->enable( X2_.output() );
}

void RAMCell::set(const bool s)
{
    X1_.update( X0_.output(), s );
    R_->set( X1_.output() );
}

//
// RAMCellGrid
//

RAMCellGrid::RAMCellGrid(Bus *bus, const int gridSize)
{
    bus_ = bus;
    gridSize_ = gridSize;
    grid_.resize(gridSize, std::vector<RAMCell*>(gridSize, nullptr));

    for (int col = 0; col < gridSize; ++col)
    {       
        for (int row = 0; row < gridSize; ++row)
        {
            grid_[col][row] = new RAMCell(bus);
        }
    }
}

RAMCellGrid::~RAMCellGrid()
{
    for (int col = 0; col < gridSize_; ++col)
    {
        for (int row = 0; row < gridSize_; ++row)
        {
            delete grid_[col][row];
        }
    }
}

RAMCell* RAMCellGrid::getCell(int col, int row)
{
   return grid_[col][row];
}

// 
// IRAM
// 

IRAM::IRAM(Bus *systemBus) 
{
    systemBus_ = systemBus;
}

IRAM::~IRAM() 
{}

std::string IRAM::toString(const std::vector<bool>& v)
{
    std::stringstream ss_input;
    for (int i = 0; i < v.size(); ++i)
    {
        ss_input << v[i];
    }
    return ss_input.str();
}

// 
// RAM256
// 

RAM256::RAM256(Bus *systemBus, Register* MAR) : 
    IRAM(systemBus), IBusNode("RAM256"), control::IControllableUnit("RAM256")
{
    MAROutputBus_ = MAR->getOutputBus();
    MAR_ = MAR;
    cellGrid_ = new RAMCellGrid(systemBus_);
}

RAM256::~RAM256()
{    
    delete cellGrid_;
}

void RAM256::enable(const bool e)
{
    RAMCell* cell = getSelectedCell();

    cell->update(true, true);
    cell->enable();
    cell->update(false, false);
}

void RAM256::set(const bool s)
{
    RAMCell* cell = getSelectedCell();

    cell->update(true, true);
    cell->set();
    cell->update(false, false);
}

RAMCell* RAM256::getSelectedCell()
{
    // get MAR content (the 'address')
    MAR_->enable();
    Byte address = MAROutputBus_->read(this);
    //std::cout << "RAM::set( address : " << address.toString() << ")" << std::endl;

    // update Decoder's inputs
    selectCol_.update(address[0], address[1], address[2], address[3]);
    selectRow_.update(address[4], address[5], address[6], address[7]);

    // get Decoder's ouputs
    //std::cout << "RAM::set( col : " << selectCol_.outputToInt() << ")" << std::endl; 
    //std::cout << "RAM::set( row : " << selectRow_.outputToInt() << ")" << std::endl; 
    int selectedCol = selectCol_.outputToInt();
    int selectedRow = selectRow_.outputToInt();

    // return the selected cell
    return cellGrid_->getCell(selectedCol, selectedRow);
}

void RAM256::signal(const control::signalType type, const control::SignalCollection& value)
{
    assert(value.size()==1);

    switch (type)
    {
    case control::SIG_ENABLE:
        enable(value[0]);
        break;
    
    case control::SIG_SET:
        set(value[0]);
        break;

    default:
        assert(0);
        break;
    }    
}

// 
// RAM65K
// 

RAM65K::RAM65K(Bus *bus) : IRAM(bus), IBusNode("RAM65K")
{
    MAROutputBus0_ = std::make_unique<Bus>("MAR0_out"); 
    MAROutputBus0_->subscribe(this);

    MAROutputBus1_ = std::make_unique<Bus>("MAR1_out"); 
    MAROutputBus1_->subscribe(this);

    MAR0_ = new Register("MAR0", systemBus_, MAROutputBus0_.get()); 
    MAR1_ = new Register("MAR1", systemBus_, MAROutputBus1_.get()); 
    cellGrid_ = new RAMCellGrid(systemBus_, 256);
}

RAM65K::~RAM65K()
{    
    delete MAR0_;
    delete MAR1_;
    delete cellGrid_;
}

void RAM65K::setS0(const bool s0)
{
    // MAR0 content is refreshed with the bus content
    MAR0_->set(s0);
}

void RAM65K::setS1(const bool s1)
{
    // MAR1 content is refreshed with the bus content
    MAR1_->set(s1);
}

void RAM65K::enable(const bool e)
{
    RAMCell* cell = getSelectedCell();

    cell->update(true, true);
    cell->enable();
    cell->update(false, false);    
}

void RAM65K::set(const bool s)
{
    RAMCell* cell = getSelectedCell();

    cell->update(true, true);
    cell->set();
    cell->update(false, false);    
}

RAMCell* RAM65K::getSelectedCell()
{
    // get MAR0 content 
    MAR0_->enable();
    Byte address0 = MAROutputBus0_->read(this);

    // get MAR1 content
    MAR1_->enable();
    Byte address1 = MAROutputBus1_->read(this);

    //std::cout << "RAM65K::getSelectedCell( address= " << address1.toString() << ":" << address0.toString() << ")" << std::endl;

    // update Decoder's inputs
    selectCol_.update(address0);
    selectRow_.update(address1);

    // get Decoder's ouputs
    int selectedCol = selectCol_.outputToInt();
    int selectedRow = selectRow_.outputToInt();
    //std::cout << "RAM65K::getSelectedCell( col : " << selectedCol << ")" << std::endl; 
    //std::cout << "RAM65K::getSelectedCell( row : " << selectedRow << ")" << std::endl; 

    // return the selected cell
    return cellGrid_->getCell(selectedCol, selectedRow);
}