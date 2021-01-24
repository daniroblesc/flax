#ifndef BUS1_H_
#define BUS1_H_

#include "circuit/Bus.h"
#include "circuit/BitGates.h"
#include "circuit/Wire.h"

/*! \class Bus1
 *  \brief This class implements a device that will place the number 1 on a bus 
 *         when we need it
 */ 
class Bus1
{
public:
    /** Constructor
     *  @param [in] inputBus  the input bus
     *  @param [in] outputBus the output bus
     */
    Bus1(Bus* inputBus, Bus* outputBus);

    /** Destructor
     */
    ~Bus1();

    /** The single bit input determines what happens when a byte tries to pass 
     *  through this device.
     *  If 'bus1'=0,then the bits of the input bus pass through to the output bus unchanged
     *  If 'bus1'=1,then the input byte is ignored and the output byte will be 1.
     *  @param [in] bus1 The 'bus1' bit 
     */
    void enable(const bool bus1 = true);  

private:

    ANDGate and_[7]; ///< AND gates
    ORGate or_; ///< OR gate
    NOTGate not_; ///< NOT gate
    Wire bus1_; ///< bus1 bit


    Bus* inputBus_;     ///< input bus
    Bus* outputBus_;    ///< output bus
};

#endif // BUS1_H_