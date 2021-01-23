
#ifndef WIRE_H_
#define WIRE_H_

/*! \class Wire
 *  \brief This class is an abstraction of a computer wire.
 * 
 *  When electricity is present, then the wire is 'on', otherwise is 'off'.
 *  The Wire's state is represented with a boolean, where 'on' is true 
 *  and 'off' is false.
 *
 */
class Wire
{
public:
    /** Update wire's state
     *  @param value new wire state
     */
    void update(const bool value);

    /** Get wire's state
     *  @reture current wire state
     */
    bool output();

private:

    bool output_ = false; ///< wire state
};

#endif // WIRE_H_