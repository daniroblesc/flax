#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "ALU/ALU.h"

using ::testing::Return;

class ALUTest : public testing::Test 
{
public:

    void selectCMP()
    {
        // CMP = 000
        op_[0].update(0);
        op_[1].update(0);
        op_[2].update(0);
    }

    void selectOR()
    {
        // OR = 001
        op_[0].update(1);
        op_[1].update(0);
        op_[2].update(0);
    }

    void selectAND()
    {
        // OR = 010
        op_[0].update(0);
        op_[1].update(1);
        op_[2].update(0);
    }

    void selectNOT()
    {
        // NOT = 011
        op_[0].update(1);
        op_[1].update(1);
        op_[2].update(0);
    }

    void selectSHL()
    {
        // SHL = 100
        op_[0].update(0);
        op_[1].update(0);
        op_[2].update(1);        
    }

    void selectSHR()
    {
        // SHR = 101
        op_[0].update(1);
        op_[1].update(0);
        op_[2].update(1);
    }

    void selectADD()
    {
        // ADD = 110
        op_[0].update(0);
        op_[1].update(1);
        op_[2].update(1);
    }


    ALU alu_; // code under test
    bool carryIn_ = false;

    Wire op_[3]; // selected ALU's operation

protected:
};


TEST_F(ALUTest, ComparatorAGreaterThanB) 
{
    selectCMP();
    alu_.update(0xA1, 0x02, carryIn_, op_);

    Byte c;
    bool carryOut, equal, a_larger, zero;
    alu_.output(c, carryOut, equal, a_larger, zero);

    EXPECT_FALSE(equal);
    EXPECT_TRUE(a_larger);
    EXPECT_EQ(0xA3, c.toInt());
}

TEST_F(ALUTest, ComparatorBGreaterThanA) 
{
    selectCMP();
    alu_.update(0x31, 0xE2, carryIn_, op_);

    Byte c;
    bool carryOut, equal, a_larger, zero;
    alu_.output(c, carryOut, equal, a_larger, zero);

    EXPECT_FALSE(equal);
    EXPECT_FALSE(a_larger);
    EXPECT_EQ(0xD3, c.toInt());
}

TEST_F(ALUTest, ComparatorAEqualB) 
{
    selectCMP();
    alu_.update(0x31, 0x31, carryIn_, op_);

    Byte c;
    bool carryOut, equal, a_larger, zero;
    alu_.output(c, carryOut, equal, a_larger, zero);


    EXPECT_TRUE(equal);
    EXPECT_FALSE(a_larger);
    EXPECT_EQ(0x0, c.toInt());
}

TEST_F(ALUTest, OR) 
{
    Byte a = 0xAA; // 1010 1010
    Byte b = 0xEB; // 1110 1011
    
    selectOR();
    alu_.update(a, b, carryIn_, op_);

    Byte c;
    bool carryOut, equal, a_larger, zero;
    alu_.output(c, carryOut, equal, a_larger, zero);

    EXPECT_EQ(c, 0xEB);
}

TEST_F(ALUTest, AND) 
{
    Byte a = 0xAA; // 1010 1010
    Byte b = 0xEB; // 1110 1011

    selectAND();
    alu_.update(a, b, carryIn_, op_);

    Byte c;
    bool carryOut, equal, a_larger, zero;
    alu_.output(c, carryOut, equal, a_larger, zero);

    EXPECT_EQ(c, 0xAA);
}

TEST_F(ALUTest, NOT) 
{
    Byte a = 0xBB; // 1011 1011

    selectNOT();
    alu_.update(a, a, carryIn_, op_);

    Byte c;
    bool carryOut, equal, a_larger, zero;
    alu_.output(c, carryOut, equal, a_larger, zero);

    EXPECT_EQ(c, 0x44);
}


TEST_F(ALUTest, SHRWithShiftOutFalse) 
{
    /*
        0100 0010 -> 0010 0001
    */
    Byte a = 0x42;
    carryIn_ = false;

    selectSHR();
    alu_.update(a, a, carryIn_, op_);

    Byte c;
    bool carryOut, equal, a_larger, zero;
    alu_.output(c, carryOut, equal, a_larger, zero);

    EXPECT_EQ(c, 0x21);
    EXPECT_FALSE(carryOut);
}

TEST_F(ALUTest, SHRWithShiftOutTrue) 
{
    /*
        0100 0011 -> 0010 0001
    */
    Byte a = 0x43;
    carryIn_ = false;

    selectSHR();
    alu_.update(a, a, carryIn_, op_);

    Byte c;
    bool carryOut, equal, a_larger, zero;
    alu_.output(c, carryOut, equal, a_larger, zero);

    EXPECT_EQ(c, 0x21);
    EXPECT_TRUE(carryOut);
}

TEST_F(ALUTest, SHRWithShiftInTrue) 
{
    /*
        0100 0010 -> 1010 0001
    */
    Byte a = 0x42;
    carryIn_ = true;

    selectSHR();
    alu_.update(a, a, carryIn_, op_);

    Byte c;
    bool carryOut, equal, a_larger, zero;
    alu_.output(c, carryOut, equal, a_larger, zero);

    EXPECT_EQ(c, 0xA1);
    EXPECT_FALSE(carryOut);
}


TEST_F(ALUTest, SHLWithShiftOutFalse) 
{
    /*
        0100 0010 -> 1000 0100
    */
    Byte a = 0x42;
    carryIn_ = false;

    selectSHL();
    alu_.update(a, a, carryIn_, op_);

    Byte c;
    bool carryOut, equal, a_larger, zero;
    alu_.output(c, carryOut, equal, a_larger, zero);

    EXPECT_EQ(c, 0x84);
    EXPECT_FALSE(carryOut);
}

TEST_F(ALUTest, SHLWithShiftOutTrue) 
{
    /*
        1100 0010 -> 1000 0100
    */
    Byte a = 0xC2;
    carryIn_ = false;

    selectSHL();
    alu_.update(a, a, carryIn_, op_);

    Byte c;
    bool carryOut, equal, a_larger, zero;
    alu_.output(c, carryOut, equal, a_larger, zero);

    EXPECT_EQ(c, 0x84);
    EXPECT_TRUE(carryOut);
}

TEST_F(ALUTest, SHLWithShiftInTrue) 
{
    /*
        0100 0010 -> 1000 0101
    */
    Byte a = 0x42;
    carryIn_ = true;

    selectSHL();
    alu_.update(a, a, carryIn_, op_);

    Byte c;
    bool carryOut, equal, a_larger, zero;
    alu_.output(c, carryOut, equal, a_larger, zero);

    EXPECT_EQ(c, 0x85);
    EXPECT_FALSE(carryOut);
}

TEST_F(ALUTest, ADDCalcDoubleWithOutCarryOut) 
{
    selectADD();

    for (int a = 0x00; a < 0x7F; ++a)
    {
        carryIn_ = false;
        alu_.update(Byte(a), Byte(a), carryIn_, op_);

        Byte c;
        bool carryOut, equal, a_larger, zero;
        alu_.output(c, carryOut, equal, a_larger, zero);

        int expectedSum = a + a;

        EXPECT_EQ(expectedSum, c.toInt());
        EXPECT_FALSE(carryOut);
    }
}

TEST_F(ALUTest, ADDWithOutCarryOut) 
{
    selectADD();

    for (int a = 0x00; a < 0x7F; ++a)
    {
        for (int b = 0x7f; b >= 0x00; --b)
        {
            carryIn_ = false;
            alu_.update(Byte(a), Byte(b), carryIn_, op_);

            Byte c;
            bool carryOut, equal, a_larger, zero;
            alu_.output(c, carryOut, equal, a_larger, zero);

            int expectedSum = a + b;

            EXPECT_EQ(expectedSum, c.toInt());
            EXPECT_FALSE(carryOut);
        }
    }
}

TEST_F(ALUTest, ADDWithCarryOut) 
{
    selectADD();

    carryIn_ = false;

    alu_.update(Byte(0xF1), Byte(0xF1), carryIn_, op_);

    Byte c;
    bool carryOut, equal, a_larger, zero;
    alu_.output(c, carryOut, equal, a_larger, zero);

    EXPECT_EQ(0xE2, c.toInt());
    EXPECT_TRUE(carryOut);
}