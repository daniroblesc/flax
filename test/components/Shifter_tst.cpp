#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "components/Shifter.h"

using ::testing::Return;

class ShifterTest : public testing::Test 
{};

TEST_F(ShifterTest, rightShifterWithShiftOutFalse) 
{
    /*
        0100 0010 -> 0010 0001
    */
    RShifter SHR;
    SHR.update(0x42, false); 

    Byte retval;
    bool shiftOut;
    SHR.output(retval, shiftOut);

    EXPECT_EQ(retval, 0x21);
    EXPECT_FALSE(shiftOut);
}

TEST_F(ShifterTest, rightShifterWithShiftOutTrue) 
{
    /*
        0100 0011 -> 0010 0001
    */
    RShifter SHR;
    SHR.update(0x43, false); 

    Byte retval;
    bool shiftOut;
    SHR.output(retval, shiftOut);

    EXPECT_EQ(retval, 0x21);
    EXPECT_TRUE(shiftOut);
}

TEST_F(ShifterTest, rightShifterWithShiftInTrue) 
{
    /*
        0100 0010 -> 1010 0001
    */
    RShifter SHR;
    SHR.update(0x42, true); 

    Byte retval;
    bool shiftOut;
    SHR.output(retval, shiftOut);

    EXPECT_EQ(retval, 0xA1);
    EXPECT_FALSE(shiftOut);
}

TEST_F(ShifterTest, leftShifterWithShiftOutFalse) 
{
    /*
        0100 0010 -> 1000 0100
    */
    LShifter SHL;
    SHL.update(0x42, false); 

    Byte retval;
    bool shiftOut;
    SHL.output(retval, shiftOut);

    EXPECT_EQ(retval, 0x84);
    EXPECT_FALSE(shiftOut);
}

TEST_F(ShifterTest, leftShifterWithShiftOutTrue) 
{
    /*
        1100 0010 -> 1000 0100
    */
    LShifter SHL;
    SHL.update(0xC2, false); 

    Byte retval;
    bool shiftOut;
    SHL.output(retval, shiftOut);

    EXPECT_EQ(retval, 0x84);
    EXPECT_TRUE(shiftOut);
}

TEST_F(ShifterTest, leftShifterWithShiftInTrue) 
{
    /*
        0100 0010 -> 1000 0101
    */
    LShifter SHL;
    SHL.update(0x42, true); 

    Byte retval;
    bool shiftOut;
    SHL.output(retval, shiftOut);

    EXPECT_EQ(retval, 0x85);
    EXPECT_FALSE(shiftOut);
}