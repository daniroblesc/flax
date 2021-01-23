#ifndef ENABLER_H_
#define ENABLER_H_

#include "circuit/BitGates.h"
#include "misc/Byte.h"
#include <vector>

/*! \class Enabler
 *  \brief The Enabler passes an 8-bit value from in to out if enable is set to 1.  
*/ 
class Enabler
{
public:
    
    Enabler();
    ~Enabler();

    /** Update enabler's input
     *  @param [in] input The input byte
     */
    void update(const Byte& input);
    
    /** This is the "enable" signal 
     *  If e=1 passes the input byte to the output
     *  @param [in] e 'e' bit 
     */ 
    void enable(const bool e = true);

    /** Returns the Enabler's output
     *  @return The output byte
     */
    Byte output();
    
private:
    std::vector< ANDGate > gatesCollection_;    ///< AND gates
    Byte input_;    ///< input byte
    Wire e_; ///< Wire 'e'
};

#endif // ENABLER_H_  