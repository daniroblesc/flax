#ifndef COMPUTER_H_
#define COMPUTER_H_

#include "control/ControlUnit.h"
#include "components/Register.h"
#include "ALU/ALU.h"
#include "circuit/Bus.h"
#include "memory/RAM.h"

#include <memory>
#include <map>

/*! \class Computer
 *  \brief This class implements a ...
 */ 
class Computer
{
public:

    Computer();
    ~Computer();

    void initialize();
    void start();
    void shutdown();

private:

    std::unique_ptr<control::ControlUnit> controlUnit_;
    std::shared_ptr<ALU> ALU_;
    std::shared_ptr<RAM256> RAM_;
    
    std::shared_ptr<Register> R0_;
    std::shared_ptr<Register> R1_;
    std::shared_ptr<Register> R2_;
    std::shared_ptr<Register> R3_;
    std::shared_ptr<Register> TMP_;
    std::shared_ptr<Register> ACC_;
    std::shared_ptr<Register> IAR_;
    std::shared_ptr<Register> IR_;
    std::shared_ptr<Register> MAR_;

    typedef std::map<std::string, std::shared_ptr<Bus>> BusCollection;
    BusCollection buses_;
};


#endif // COMPUTER_H_