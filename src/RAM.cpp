#include "RAM.h"

RAMCell::RAMCell(Bus *bus) : IBusNode(bus) 
{
    bus_ = bus;
    R_ = new Register(bus_);
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
