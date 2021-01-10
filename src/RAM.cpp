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
// RAM
// 

RAM::RAM(Bus *bus)
{
    systemBus_ = bus;
    MAROutputBus_ = new Bus();
    MAR_ = new Register(systemBus_, MAROutputBus_);
  
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 16; ++j)
        {
            cells_[i][j] = new RAMCell(systemBus_);
        }
    }
}

RAM::~RAM()
{    
    delete MAR_;
    delete MAROutputBus_;
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 16; ++j)
        {
            delete cells_[i][j];
        }
    }
}

void RAM::enable(const Bit& e)
{
    RAMCell* cell = getSelectedCell();

    cell->update(Bit(Bit::ONE), Bit(Bit::ONE));
    cell->enable();
}

void RAM::set(const Bit& s)
{
    RAMCell* cell = getSelectedCell();

    cell->update(Bit(Bit::ONE), Bit(Bit::ONE));
    cell->set();
}

void RAM::setAddress(const Bit& sa)
{
    // MAR content is refreshed with the bus content
    MAR_->set(sa);
}

RAMCell* RAM::getSelectedCell()
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

    // disable all cells
    for (int col = 0; col < 16; ++col)
    {
        for (int row = 0; row < 16; ++row)
        {
            cells_[col][row]->update(Bit(Bit::ZERO), Bit(Bit::ZERO));
        }
    }

    // return the selected cell
    return cells_[selectedCol][selectedRow];
}

std::string RAM::toString(const std::vector<Bit>& v)
{
    std::stringstream ss_input;
    for (int i = 0; i < v.size(); ++i)
    {
        ss_input << v[i].toString();
    }
    return ss_input.str();
}
