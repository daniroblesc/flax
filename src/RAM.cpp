#include "RAM.h"
#include <iostream>
#include <sstream>      // std::stringstream

RAMCell::RAMCell(Bus *bus) 
{
    bus_ = bus;
    R_ = new Register(bus_, bus_);
}   

RAMCell::~RAMCell()
{
    delete R_;
}

void RAMCell::update(const Bit& a1, const Bit& a2)
{
    X0_.update(a1, a2);
}

void RAMCell::enable(const Bit& e)
{
    X2_.update( X0_.output(), e );
    R_->enable( X2_.output() );
}

void RAMCell::set(const Bit& s)
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

IRAM::IRAM(Bus *bus) 
{
    systemBus_ = bus;
}

IRAM::~IRAM() 
{}

std::string IRAM::toString(const std::vector<Bit>& v)
{
    std::stringstream ss_input;
    for (int i = 0; i < v.size(); ++i)
    {
        ss_input << v[i].toString();
    }
    return ss_input.str();
}

// 
// RAM256
// 

RAM256::RAM256(Bus *bus) : IRAM(bus)
{
    MAROutputBus_ = new Bus();
    MAR_ = new Register(systemBus_, MAROutputBus_); 
    cellGrid_ = new RAMCellGrid(systemBus_);
}

RAM256::~RAM256()
{    
    delete MAR_;
    delete MAROutputBus_;
    delete cellGrid_;
}

void RAM256::enable(const Bit& e)
{
    RAMCell* cell = getSelectedCell();

    cell->update(Bit(Bit::ONE), Bit(Bit::ONE));
    cell->enable();
    cell->update(Bit(Bit::ZERO), Bit(Bit::ZERO));
}

void RAM256::set(const Bit& s)
{
    RAMCell* cell = getSelectedCell();

    cell->update(Bit(Bit::ONE), Bit(Bit::ONE));
    cell->set();
    cell->update(Bit(Bit::ZERO), Bit(Bit::ZERO));
}

void RAM256::setAddress(const Bit& sa)
{
    // MAR content is refreshed with the bus content
    MAR_->set(sa);
}

RAMCell* RAM256::getSelectedCell()
{
    // get MAR content (the 'address')
    MAR_->enable();
    Byte address = MAROutputBus_->get();
    //std::cout << "RAM::set( address : " << address.toString() << ")" << std::endl;

    // update Decoder's inputs
    selectCol_.update(address.get(0), address.get(1), address.get(2), address.get(3));
    selectRow_.update(address.get(4), address.get(5), address.get(6), address.get(7));

    // get Decoder's ouputs
    //std::cout << "RAM::set( col : " << selectCol_.outputToInt() << ")" << std::endl; 
    //std::cout << "RAM::set( row : " << selectRow_.outputToInt() << ")" << std::endl; 
    int selectedCol = selectCol_.outputToInt();
    int selectedRow = selectRow_.outputToInt();

    // return the selected cell
    return cellGrid_->getCell(selectedCol, selectedRow);
}

// 
// RAM65K
// 

RAM65K::RAM65K(Bus *bus) : IRAM(bus)
{
    MAROutputBus0_ = new Bus();
    MAROutputBus1_ = new Bus();
    MAR0_ = new Register(systemBus_, MAROutputBus0_); 
    MAR1_ = new Register(systemBus_, MAROutputBus1_); 
    cellGrid_ = new RAMCellGrid(systemBus_, 256);
}

RAM65K::~RAM65K()
{    
    delete MAR0_;
    delete MAR1_;
    delete MAROutputBus0_;
    delete MAROutputBus1_;
    delete cellGrid_;
}

void RAM65K::setS0(const Bit& s0)
{
    // MAR0 content is refreshed with the bus content
    MAR0_->set(s0);
}

void RAM65K::setS1(const Bit& s1)
{
    // MAR1 content is refreshed with the bus content
    MAR1_->set(s1);
}

void RAM65K::enable(const Bit& e)
{
    RAMCell* cell = getSelectedCell();

    cell->update(Bit(Bit::ONE), Bit(Bit::ONE));
    cell->enable();
    cell->update(Bit(Bit::ZERO), Bit(Bit::ZERO));    
}

void RAM65K::set(const Bit& s)
{
    RAMCell* cell = getSelectedCell();

    cell->update(Bit(Bit::ONE), Bit(Bit::ONE));
    cell->set();
    cell->update(Bit(Bit::ZERO), Bit(Bit::ZERO));    
}

RAMCell* RAM65K::getSelectedCell()
{
    // get MAR0 content 
    MAR0_->enable();
    Byte address0 = MAROutputBus0_->get();

    // get MAR1 content
    MAR1_->enable();
    Byte address1 = MAROutputBus1_->get();

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