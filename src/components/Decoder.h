#ifndef DECODER_H_
#define DECODER_H_

#include "circuit/BitGates.h"
#include "misc/Byte.h"
#include <vector>

/*! \class IDecoder
 *  \brief IDecoder interface.
 * 
 *  The name “Decoder” means to translate or decode coded information from one 
 *  format into another, so a binary decoder transforms “n” binary input signals 
 *  into an equivalent code using 2n outputs.
 * 
 *  A decoder generally decodes a binary value into a non-binary one by setting 
 *  exactly one of its n outputs to logic “1”.
 * 
 *  If a binary decoder receives n inputs it activates one and only one of its 2n 
 *  outputs based on that input with all other outputs deactivated.
 * 
 */
class IDecoder
{
public:
    /** Constructor
     *  @param [in] numInputs decoder's number of inputs
     */
    IDecoder(const int numInputs);

    /** Destructor
     */  
    virtual ~IDecoder();

    /** Update decoder input
     *  @param [in] a The input byte
     */
    virtual void update(const Byte& input) = 0;

    /** Generate decoder output
     *  @return decoder output as an array of bits
     */  
    std::vector<bool> output();

    /** Generate decoder output for a given bit
     *  @param [in] n the bit number which output want to be generated
     *  @return bit output
     */  
    bool output(const int n);

    /** Generate decoder output
     *  @return decoder output as an int value
     */  
    int outputToInt();

protected:
    int numOutputs_; ///< decoder's number of outputs 
    std::vector<bool> output_; ///< decoder output as an array of bits 

    /// Convert input bit stream to a string of chars
    std::string toString(const std::vector<bool>& bitStream);
};

/*! \class BasicDecoder
 *  \brief This class implements common functional for basic binary decoders (2x4,3x8,4x16).
 * 
 */ 
class BasicDecoder : public IDecoder
{
public:
    /** Constructor
     *  @param [in] numInputs decoder's number of inputs
     */  
    BasicDecoder(const int numInputs);

    /** Destructor
     */
    virtual ~BasicDecoder();
    
protected:

    std::vector<NOTGate> not_;  ///< NOT gates
    std::vector<ANDGate> and_;  ///< AND gates
};

/*! \class Decoder2X4
 *  \brief Decoder2X4 class.
 *
 *  The 2 binary inputs labelled A and B are decoded into one of 4 outputs, 
 *  hence the description of 2-to-4 binary decoder. Each output represents 
 *  one of the miniterms of the 2 input variables, (each output = a miniterm).
 * 
 *   input 'A' is bit0
 *   input 'B' is bit1 
 *
 *   B   A  |  0/0   0/1   1/0   1/1  |  # (outputToInt)     
 *   ----------------------------------------
 *   0   0  |   1     0     0     0   |  0
 *   0   1  |   0     1     0     0   |  1
 *   1   0  |   0     0     1     0   |  2
 *   1   1  |   0     0     0     1   |  3
*/
class Decoder2X4 : public BasicDecoder
{
public:

    Decoder2X4();
    ~Decoder2X4();

    /** Update decoder input
     *  @param [in] input The input byte
     */
    void update(const Byte& input);

    /** Update decoder input
     *  @param [in] A The input bit A
     *  @param [in] B The input bit B
     */
    void update(const bool A, const bool B);
};

/*! \class Decoder3X8
 *  \brief Decoder3X8 class.
 *
 *  input 'A' is bit0
 *  input 'B' is bit1 
 *  input 'C' is bit2 
 *
 *   C   B   A  |  0/0/0   0/0/1   0/1/0   0/1/1   1/0/0   1/0/1   1/1/0   1/1/1   |  # (outputToInt)     
 *   -------------------------------------------------------------------------------------------------
 *   0   0   0  |    1       0       0       0       0       0       0       0     |  0
 *   0   0   1  |    0       1       0       0       0       0       0       0     |  1
 *   0   1   0  |    0       0       1       0       0       0       0       0     |  2
 *   0   1   1  |    0       0       0       1       0       0       0       0     |  3
 *   1   0   0  |    0       0       0       0       1       0       0       0     |  4
 *   1   0   1  |    0       0       0       0       0       1       0       0     |  5
 *   1   1   0  |    0       0       0       0       0       0       1       0     |  6
 *   1   1   1  |    0       0       0       0       0       0       0       1     |  7
 */ 
class Decoder3X8 : public BasicDecoder
{
public:

    Decoder3X8();
    ~Decoder3X8();

    /** Update decoder input
     *  @param [in] input The input byte
     */
    void update(const Byte& input);

    /** Update decoder input
     *  @param [in] A The input bit A
     *  @param [in] B The input bit B
     *  @param [in] C The input bit C
     */    
    void update(const bool A, const bool B, const bool C);
};

/*! \class Decoder4X16
 *  \brief Decoder4X16 class.
 *
 *   input 'A' is bit0
 *   input 'B' is bit1 
 *   input 'C' is bit2
 *   input 'D' is bit3 
 *
 *   D C B A | 0000 0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111 | # (outputToInt)     
 *   -----------------------------------------------------------------------------------------------------------
 *   0 0 0 0 | 1    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    | 0 
 *   0 0 0 1 | 0    1    0    0    0    0    0    0    0    0    0    0    0    0    0    0    | 1  
 *   0 0 1 0 | 0    0    1    0    0    0    0    0    0    0    0    0    0    0    0    0    | 2
 *   0 0 1 1 | 0    0    0    1    0    0    0    0    0    0    0    0    0    0    0    0    | 3 
 *   0 1 0 0 | 0    0    0    0    1    0    0    0    0    0    0    0    0    0    0    0    | 4 
 *   0 1 0 1 | 0    0    0    0    0    1    0    0    0    0    0    0    0    0    0    0    | 5 
 *   0 1 1 0 | 0    0    0    0    0    0    1    0    0    0    0    0    0    0    0    0    | 6 
 *   0 1 1 1 | 0    0    0    0    0    0    0    1    0    0    0    0    0    0    0    0    | 7 
 *   1 0 0 0 | 0    0    0    0    0    0    0    0    1    0    0    0    0    0    0    0    | 8 
 *   1 0 0 1 | 0    0    0    0    0    0    0    0    0    1    0    0    0    0    0    0    | 9 
 *   1 0 1 0 | 0    0    0    0    0    0    0    0    0    0    1    0    0    0    0    0    | 10 
 *   1 0 1 1 | 0    0    0    0    0    0    0    0    0    0    0    1    0    0    0    0    | 11  
 *   1 1 0 0 | 0    0    0    0    0    0    0    0    0    0    0    0    1    0    0    0    | 12   
 *   1 1 0 1 | 0    0    0    0    0    0    0    0    0    0    0    0    0    1    0    0    | 13   
 *   1 1 1 0 | 0    0    0    0    0    0    0    0    0    0    0    0    0    0    1    0    | 14   
 *   1 1 1 1 | 0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    1    | 15  
 */
class Decoder4X16 : public BasicDecoder
{
public:

    Decoder4X16();
    ~Decoder4X16();

    /** Update decoder input
     *  @param [in] input The input byte
     */
    void update(const Byte& input);

    /** Update decoder input
     *  @param [in] A The input bit A
     *  @param [in] B The input bit B
     *  @param [in] C The input bit C
     *  @param [in] D The input bit D
     */        
    void update(const bool A, const bool B, const bool C, const bool D);
};

/*! \class Decoder8X256
 *  \brief Decoder8X256 class.
 */
class Decoder8X256 : public IDecoder
{
public:

    Decoder8X256();
    ~Decoder8X256();

    /** Update decoder input
     *  @param [in] input The input byte
     */
    void update(const Byte& input);

private:

    const int NUM_4X16DECODERS = 16;

    Decoder4X16 decoderSelector_;   ///< Selector decoder
	std::vector<Decoder4X16> decoders4x16_; ///< Internal decoders
    int index_; ///< output bit selected
    
    /// Update internal decoders
    void updateDecoder(bool& a, bool& b, bool& c, bool& d, int decoderIndex, int outputWireStart);
};

#endif // DECODER_H_  