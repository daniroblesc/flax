#ifndef SHIFTER_H_
#define SHIFTER_H_

#include "misc/Byte.h"
 
/*! \class RShifter
 *  \brief RShifter class implement a Right Shifter.
 * 
 *  It doesn't use any gates at all, it just wires up the bus a bit oddly.
 *  A right shifter will change 0100 0010, to 0010 0001
 * 
 *  If 'shift out' is connected to 'shift in', a right shift will change
 *  0001 1001 to 1000 1100
 */
class RShifter
{
public:
    /** Update register inputs
     *  @param [in] a byte to shift
     *  @param [in] shiftIn 'shift in' bit
     */
    void update(const Byte& a, const bool shiftIn);

    /** Update register inputs
     *  @param [out] retval input byte shifted
     *  @param [out] shiftOut 'shift out' bit
     */
    void output(Byte &retval, bool &shiftOut);

private:
    Byte a_;    ///< byte to shift
    bool shiftIn_;  ///< 'shift in' bit
};

 
/*! \class LShifter
 *  \brief LShifter class implement a Left Shifter.
 * 
 *  It doesn't use any gates at all, it just wires up the bus a bit oddly.
 *  A left shifter will change 0100 0010 to 1000 0100
 */
class LShifter
{
public:
    /** Update register inputs
     *  @param [in] a byte to shift
     *  @param [in] shiftIn 'shift in' bit
     */
    void update(const Byte& a, const bool shiftIn);

    /** Update register inputs
     *  @param [out] retval input byte shifted
     *  @param [out] shiftOut 'shift out' bit
     */
    void output(Byte &retval, bool &shiftOut);

private:
    Byte a_;    ///< byte to shift
    bool shiftIn_;  ///< 'shift in' bit
};

#endif // SHIFTER_H_