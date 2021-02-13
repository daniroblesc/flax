#ifndef COMPUTER_H_
#define COMPUTER_H_

#include "control/ControlUnit.h"
#include "components/Register.h"
#include "ALU/ALU.h"
#include "circuit/Bus.h"
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

    control::ControlUnit controlUnit_;
    std::unique_ptr<ALU> ALU_;
    
    std::unique_ptr<Register> R1_;
    std::unique_ptr<Register> R0_;
    std::unique_ptr<Register> TMP_;
    std::unique_ptr<Register> ACC_;

    typedef std::map<std::string, std::shared_ptr<Bus>> BusCollection;
    BusCollection buses_;
};


#endif // COMPUTER_H_