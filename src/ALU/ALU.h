#ifndef ALU_H_
#define ALU_H_

#include "circuit/ByteGates.h"
#include "circuit/Wire.h"
#include "components/Decoder.h"
#include "components/Shifter.h"
#include "components/Enabler.h"
#include "components/Comparator.h"
#include "components/Adder.h"
#include "circuit/Bus.h"
#include "control/ControlUnit.h"

/*! \class ALU
 *  \brief This class implements an arithmetic logic unit (ALU) that performs 
 *         arithmetic and bitwise operations on integer binary numbers.
 *
 *  The inputs to an ALU are the data to be operated on, called operands, and a
 *  code indicating the operation to be performed; the ALU's output is the result
 *  of the performed operation. In many designs, the ALU also has status inputs or 
 *  outputs, or both, which convey information about a previous operation or the 
 *  current operation, respectively, between the ALU and external status registers.
 * 
 *  Operations code:
 *      000: ADD
 *      001: SHR
 *      010: SHL
 *      011: NOT
 *      100: AND
 *      101: OR
 *      110: XOR
 *      111: CMP
 */ 
class ALU : public control::IControllableUnit, public IBusNode
{
public:
    typedef enum OpCode
    {
        OP_CODE_ADD = 0,
        OP_CODE_SHR,
        OP_CODE_SHL,
        OP_CODE_NOT,
        OP_CODE_AND,
        OP_CODE_OR,
        OP_CODE_XOR,
        OP_CODE_CMP,
    } OpCode;


    /** Constructor
     *  @param [in] inputBusA  the input bus A
     *  @param [in] inputBusB  the input bus B
     *  @param [in] outputBus the output bus
     */
    ALU(Bus* inputBusA, Bus* inputBusB, Bus* outputBus);

    /** Destructor
     */
    ~ALU();
    
    /** Update inputs
     *  @param [in] carryIn bit carried in from the previous less-signficant stage
     *  @param [in] op code indicating the operation to be performed
     */
    void update(const bool carryIn, const OpCode op);

    /** Update inputs
     *  @param [in]  carryIn bit carried in from the previous less-signficant stage
     *  @param [in]  op code indicating the operation to be performed
     *  @param [out] carryOut bit of the leftmost column will turn on if the sum of the 
     *                        two numbers is greater than 255
     *  @param [out] equal is set to true if inputs are equal, otherwise is set to false
     *  @param [out] a_larger is set to true if 'a' is larger than 'b' 
     *  @param [out] zero is set to true if the output is zero
     */
    void update(const bool carryIn, const OpCode op,bool &carryOut, bool& equal, bool& a_larger, bool& zero);

    /** Update outputs
     *  @param [out] carryOut bit of the leftmost column will turn on if the sum of the 
     *                        two numbers is greater than 255
     *  @param [out] equal is set to true if inputs are equal, otherwise is set to false
     *  @param [out] a_larger is set to true if 'a' is larger than 'b' 
     *  @param [out] zero is set to true if the output is zero
     */
    void output(bool &carryOut, bool& equal, bool& a_larger, bool& zero);

    /** implements control::IControllableUnit method
     *  Signal received from the Control Unit
     *  @param [in] type signal's type
     *  @param [in] value signal value
     */
    void signal(const control::signalType type, const control::SignalCollection& value) override;

private:
    /// internal devices
    Comparator XOR_;
    ORer OR_; 
    ANDer AND_;
    NOTter NOT_;
    LShifter SHL_;
    RShifter SHR_;
    Adder ADD_;
    Enabler enabler_[7];
    ANDGate and_[3];
    Zero z_;
    Decoder3X8 decoder_;

    /// inputs
    Byte a_;
    Byte b_;
    bool carryIn_;
    OpCode op_;

    Bus* inputBusA_;     ///< input bus A
    Bus* inputBusB_;     ///< input bus B
    Bus* outputBus_;    ///< output bus
};

#endif // ALU_H_