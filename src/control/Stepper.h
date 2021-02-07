#ifndef STEPPER_H_
#define STEPPER_H_

#include "memory/MemoryBit.h"
#include "circuit/BitGates.h"
#include <vector>
#include <string>

namespace control
{

/*! \class Stepper
 *  \brief This class implements a seven stage stepper.
 * 
 *  It has two inputs: a clock and a reset.
 *  For outputs, it has a number of bits, each of which will come on for one 
 *  clock cycle.
 *  We have relocated the Reset bit to the right side of the diagram,
 *  and connected it to the last step (7), so that the stepper will automatically
 *  reset itself. Step 7 will not be on very long, however, because it 
 *  shuts itself off as soon as the zero can get through the string of bits. 
 *  This mean that step 7 will not last long enough to be used for one of our data
 *  transfers over the bus. All of the things we want to accomplish will take
 *  place in steps 1 through 6.
 */ 
class Stepper
{
public:

    Stepper();
    ~Stepper();

    /** Get device output
     *  @param [in] clk The system clock
     */
    void update(bool clk);

    /** Get stepper output
     *  @param [in] index the selected output wire
     *  @return the output wire value
     */
    bool output(int index);

    /** Get stepper output in string format
     *  @return the stepper output converted to string
     */
    std::string toString();

private:

    const size_t NUM_STEPS = 7;

    void step();

    MemoryBit bits_[12];
	Wire reset_;          
	NOTGate resetNotGate_;
    Wire clockIn_;
	NOTGate clockInNotGate_;
	ORGate inputOrGates_[2];
	std::vector<Wire> outputs_;
	ANDGate outputAndGates_[5];
	ORGate outputOrGate_;
	NOTGate outputNotGates_[6];
};

}


#endif // STEPPER_H_ 