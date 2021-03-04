#include "BitGates.h"
#include <iostream>
#include <assert.h>     /* assert */

//
// NANDGate implementation
//

void NANDGate::update(const bool a, const bool b)
{
    a_.update(a);
    b_.update(b);
}

bool NANDGate::output()
{
    if ((a_.output()) && (b_.output()))
    {
        return false;          
    }

    return true;
}

//
// NOTGate implementation
//

NOTGate::NOTGate()
{

}

NOTGate::NOTGate(const pWire& a)
{
    input_ = a;
    new_=true;
}

void NOTGate::update(const bool a)
{
    a_.update(a);
}

bool NOTGate::output()
{
    if (!new_)
    {
        if (a_.output())
        {
            return false;  
        }

        return true;
    }

    if(input_->get())
        return false;
    
    return true;

}

//
// ANDGate implementation
//

void ANDGate::update(const bool a, const bool b)
{
    a_.update(a);
    b_.update(b);
    numOfInputs_ = 2;
}

void ANDGate::update(const bool a, const bool b, const bool c)
{
    a_.update(a);
    b_.update(b);
    c_.update(c);
    numOfInputs_ = 3;
}

void ANDGate::update(const bool a, const bool b, const bool c, const bool d)
{
    a_.update(a);
    b_.update(b);
    c_.update(c);
    d_.update(d);
    numOfInputs_ = 4;
}

bool ANDGate::output()
{
    switch ( numOfInputs_)
    {
        case 2:        
        if (!a_.output() || !b_.output())
        {
            return false;
        }
        break;
        case 3:        
        if (!a_.output() || !b_.output() || !c_.output())
        {
            return false;
        }
        break;
        case 4:        
        if (!a_.output() || !b_.output() || !c_.output() || !d_.output())
        {
            return false;
        }
        break;
        default:
        assert(0);
        break;
    }

    return true;
}

//
// ORGate implementation
//

void ORGate::update(const bool a, const bool b)
{
    a_.update(a);
    b_.update(b);
}

bool ORGate::output()
{
   not_[0].update(a_.output());
   c_.update(not_[0].output());

   not_[1].update(b_.output());
   d_.update(not_[1].output());

   nand_.update(c_.output(), d_.output());
   return nand_.output();
}


//
// XORGate implementation
//

void XORGate::update(const bool a, const bool b)
{
    a_.update(a);
    b_.update(b);
}

bool XORGate::output()
{
    not_[0].update(a_.output());
    c_.update(not_[0].output());

    not_[1].update(b_.output());
    d_.update(not_[1].output());

    nand_[0].update(c_.output(), b_.output());
    e_.update(nand_[0].output());

    nand_[1].update(a_.output(), d_.output());
    f_.update(nand_[1].output());

    nand_[2].update(e_.output(), f_.output());
    return nand_[2].output();
}
