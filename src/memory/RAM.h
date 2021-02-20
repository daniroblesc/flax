#ifndef RAM_H_
#define RAM_H_

#include "circuit/BitGates.h"
#include "circuit/Bus.h"
#include "components/Register.h"
#include "components/Decoder.h"
#include <memory>

/*! \class RAMCell
 *  \brief This class implements a memory cell
 * 
 *  The memory cell is the fundamental building block of computer memory. 
 *  The memory cell stores one byte of binary information from the given Bus.
 *  Its value is maintained/stored until it is changed by the set/reset process. 
 *  The value in the memory cell can be accessed by reading it.
 * 
 */ 
class RAMCell 
{
public:
    /** Constructor
     *  @param [in] bus system bus where the memory is connected
     *  @param [in] defaultValue the default value 
     */
    RAMCell(const std::shared_ptr<Bus>& bus, const Byte& defaultValue = 0);
    
    /** Destructor
     */ 
    ~RAMCell() = default;

    /** update cell's input with address bits
     *  @param [in] a1 bit address #1
     *  @param [in] a2 bit address #2
     */
    void update(const bool a1 = true, const bool a2 = true);

    /** write cell's content to the bus
     *  @param [in] e content is written to the bus if e=true
     */
    void enable(const bool e = true);  

    /** update cell's content with data from the bus
     *  @param [in] s content is updated from the bus if s=true
     */
    void set(const bool s = true); 

    /** Get cell's register output (for debugging purposes)
     *  @return the saved byte
     */
    Byte output(); 

private:
    
    /// AND gates
    ANDGate X0_;
    ANDGate X1_;
    ANDGate X2_;

    std::shared_ptr<Register> R_; ///< register where data is saved
    std::shared_ptr<Bus> bus_; ///< system bus
};

/*! \class RAMCellGrid
 *  \brief This class implements a grid of memory cells
 * 
 */  
class RAMCellGrid
{
public:
    /** Constructor
     *  @param [in] bus system bus where the memory is connected
     *  @param [in] gridSize the grid size
     *  @param [in] defaultValue the default value 
     */
    RAMCellGrid(const std::shared_ptr<Bus>& bus, const int gridSize, const Byte& defaultValue = 0);

    /** Destructor
     */ 
    virtual ~RAMCellGrid() = default;

    /** Select a memory cell
     *  @param [in] col grid's column number
     *  @param [in] row grid's row number
     *  @return the selected memory cell
     */
    const std::shared_ptr<RAMCell>& getCell(int col, int row);

private:

    int gridSize_ = 16; ///< the grid size
    std::shared_ptr<Bus> bus_;    ///< system bus
    
    typedef std::vector<std::shared_ptr<RAMCell>> RamCellArray;
    std::vector<RamCellArray> grid_;   ///< the grid of memory cells
};

/*! \class IRAM
 *  \brief This is a interface for a "8-bit" RAM component
 * 
 *  RAM is a form of computer memory that can be read and changed in any order, 
 *  typically used to store working data and machine code.
 *  
 *  A random-access memory device allows data items to be read or written in almost
 *  the same amount of time irrespective of the physical location of data inside the 
 *  memory. 
 *  
 *  RAM contains multiplexing and demultiplexing circuitry, to connect the data lines 
 *  to the addressed storage for reading or writing the entry. Usually more than one 
 *  bit of storage is accessed by the same address, and RAM devices often have multiple 
 *  data lines and are said to be "8-bit" or "16-bit", etc. devices.
 * 
 */ 
class IRAM
{
public:
    /** Constructor
     *  @param [in] systemBus system bus where the memory is connected
     */
    IRAM(const std::shared_ptr<Bus>& systemBus);

    /** Destructor
     */     
    virtual ~IRAM();
    
    /** write memory cell's content to the bus
     *  @param [in] e content is written to the bus if e=true
     */    
    virtual void enable(const bool e = true) = 0;

    /** update memory cell's content with data from the bus
     *  @param [in] s content is updated from the bus if s=true
     */
    virtual void set(const bool s = true) = 0; 

protected:

    std::shared_ptr<Bus> systemBus_;  ///< system bus

    /// Convert input bool stream to a string of chars 
    std::string toString(const std::vector<bool>& v);
};

/*! \class RAM256
 *  \brief This class implements a RAM of 256 bytes
 */ 
class RAM256 : public IRAM, public IBusNode, public control::IControllableUnit
{
public:
    /** Constructor
     *  @param [in] systemBus system bus where the memory is connected
     *  @param [in] MAR the memory address register
     *  @param [in] defaultValue the default value  
     */
    RAM256(const std::shared_ptr<Bus>& systemBus, const std::shared_ptr<Register>& MAR, const Byte& defaultValue = 0);

    /** Destructor
     */ 
    virtual ~RAM256() = default;

    /** write memory cell's content to the bus
     *  @param [in] e content is written to the bus if e=true
     */ 
    void enable(const bool e = true);

    /** update memory cell's content with data from the bus
     *  @param [in] s content is updated from the bus if s=true
     */
    void set(const bool s = true); 

    /** implements control::IControllableUnit method
     *  Signal received from the Control Unit
     *  @param [in] type signal's type
     *  @param [in] value signal value
     */
    void signal(const control::signalType type, const control::SignalCollection& value) override;

private:
    
    std::shared_ptr<Bus> MAROutputBus_;   ///< bus from MAR's output
    std::shared_ptr<Register> MAR_;   ///< memory address register
    Decoder4X16 selectCol_; ///< decoder to select grid's col
    Decoder4X16 selectRow_; ///< decoder to select grid's row
    std::shared_ptr<RAMCellGrid> cellGrid_; ///< memory cell grid

    /// get the selected memory cell
    const std::shared_ptr<RAMCell>& getSelectedCell();
};

/*! \class RAM65K
 *  \brief This class implements a RAM of 65K bytes
 */ 
class RAM65K : public IRAM, public IBusNode 
{
public:
    /** Constructor
     *  @param [in] bus system bus where the memory is connected
     */
    RAM65K(const std::shared_ptr<Bus>& bus);

    /** Destructor
     */ 
    virtual ~RAM65K() = default;

    /** select memory cell low address with data from the bus
     *  @param [in] s0 memory cell is selected with address from the bus if s0=true
     */ 
    void setS0(const bool s0 = true);

    /** select memory cell high address with data from the bus
     *  @param [in] s1 memory cell is selected with address from the bus if s1=true
     */ 
    void setS1(const bool s1 = true);

    /** write memory cell's content to the bus
     *  @param [in] e content is written to the bus if e=true
     */ 
    void enable(const bool e = true);

    /** update memory cell's content with data from the bus
     *  @param [in] s content is updated from the bus if s=true
     */
    void set(const bool s = true); 

private:

    std::shared_ptr<Bus> MAROutputBus0_;  ///< internal bus #0
    std::shared_ptr<Bus> MAROutputBus1_;  ///< internal bus #1
    std::shared_ptr<Register> MAR0_;  ///< memory address register #0
    std::shared_ptr<Register> MAR1_;  ///< memory address register #1
    Decoder8X256 selectCol_;    ///< decoder to select grid's col
    Decoder8X256 selectRow_;    ///< decoder to select grid's row
    std::shared_ptr<RAMCellGrid> cellGrid_;   ///< memory cell grid
    
    /// get the selected memory cell
    const std::shared_ptr<RAMCell>& getSelectedCell();
};


#endif // RAM_H_
