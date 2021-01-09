#ifndef RAM_H_
#define RAM_H_

#include "Gates.h"
#include "Bus.h"
#include "Register.h"

class RAMCell : public IBusNode
{
public:
    RAMCell(Bus *bus);
    ~RAMCell();

    // update Cell's input with address bits
    void update(const Bit& a1, const Bit& a2);

    // write Cell's content to the bus
    void enable(const Bit& e = Bit::ONE);  

    // update Cell's content with data on the bus
    void set(const Bit& s = Bit::ONE);  

private:
    
    ANDGate X0_;
    ANDGate X1_;
    ANDGate X2_;
    Register* R_ = nullptr;
    Bus* bus_ = nullptr;

};

#endif // RAM_H_

/**
 * escritura en memoria (guardar el contenido del regA en memoria):
 *  1.  regA.enable() -> el contenido de regA va al Bus
 *  2.  seleccionamos la celda via "MAR" (Memory Access Register)
 *  3.  celda.set() -> node's content is refreshed with the bus content
 * 
 * lectura en memoria (mover el contenido de la celda al regA)
 *  1.  seleccionamos la celda via "MAR" (Memory Access Register)
 *  2.  celda.enable() -> node's content is written to the bus
 *  3.  regA.set() -> node's content is refreshed with the bus content
 * */