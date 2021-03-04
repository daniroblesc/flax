
#ifndef WIRE_H_
#define WIRE_H_

#include <memory>
#include <vector>
#include "misc/Byte.h"

/*! \class Wire
 *  \brief This class is an abstraction of a computer wire.
 * 
 *  When electricity is present, then the wire is 'on' or 'high', 
 *  otherwise is 'off' or 'low'.
 *  The Wire's state is represented with a boolean, where 'on' is true 
 *  and 'off' is false.
 *
 */
class Wire
{
public:

    Wire() = default;
    Wire(const bool state);

    ~Wire() = default;

    /** Update wire's state
     *  @param state new wire state
     */
    void update(const bool state);
    
    void set(const bool state);
    void low();
    void high();

    /** Get wire's state
     *  @reture current wire state
     */
    bool output();
    
    bool get();

private:

    bool state_ = false; ///< wire state
};

/*
 * This is a pointer to a Wire object
 */
typedef std::shared_ptr<Wire> pWire;

/*! \class WireCollection
 *  \brief This class is an abstraction of a collection of eight computer wire.
 * 
 *  When electricity is present, then the wire is 'on', otherwise is 'off'.
 *  The Wire's state is represented with a boolean, where 'on' is true 
 *  and 'off' is false.
 *
 */
class WireCollection
{
public:
    WireCollection();
    WireCollection(const Byte& byte);

    // Read wires status
    bool output(int wire); 
    Byte output();

    // Update wire status
    void on(const int wire);
    void off(const int wire);
    void set(const Byte& byte);

private:

    std::vector<Wire> wires_;
};

/*
 * This is a pointer to a WireCollection object
 */
typedef std::shared_ptr<WireCollection> pWireCollection;


#endif // WIRE_H_