#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "ALU/ALU.h"
#include <memory>

using ::testing::Return;

class ALUTest : public testing::Test 
{
protected:    
    void SetUp() override 
    {
        inputBusA_ = std::make_unique<Bus>("inA");
        inputBusB_ = std::make_unique<Bus>("inB");
        outputBus_ = std::make_unique<Bus>("out");
        
        alu_ = std::make_unique<ALU>(inputBusA_.get(), inputBusB_.get(), outputBus_.get());
    }

    void TearDown() override 
    {}    

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


    bool carryIn_ = false;

    Wire op_[3]; // selected ALU's operation
    
    // buses
    std::unique_ptr<Bus> inputBusA_;
    std::unique_ptr<Bus> inputBusB_;
    std::unique_ptr<Bus> outputBus_;

    // the code under test
    std::unique_ptr<ALU> alu_;
};


TEST_F(ALUTest, ComparatorAGreaterThanB) 
{
    inputBusA_->write(0xA1);   
    inputBusB_->write(0x02);   

    selectCMP();
    alu_->update(carryIn_, op_);

    bool carryOut, equal, a_larger, zero;
    alu_->output(carryOut, equal, a_larger, zero);

    EXPECT_FALSE(equal);
    EXPECT_TRUE(a_larger);
    EXPECT_EQ(0xA3, outputBus_->read().toInt());
}

TEST_F(ALUTest, ComparatorBGreaterThanA) 
{
    inputBusA_->write(0x31);   
    inputBusB_->write(0xE2);   

    selectCMP();
    alu_->update(carryIn_, op_);

    Byte c;
    bool carryOut, equal, a_larger, zero;
    alu_->output(carryOut, equal, a_larger, zero);

    EXPECT_FALSE(equal);
    EXPECT_FALSE(a_larger);
    EXPECT_EQ(0xD3, outputBus_->read().toInt());
}

TEST_F(ALUTest, ComparatorAEqualB) 
{
    inputBusA_->write(0x31);   
    inputBusB_->write(0x31);   

    selectCMP();
    alu_->update(carryIn_, op_);

    bool carryOut, equal, a_larger, zero;
    alu_->output(carryOut, equal, a_larger, zero);

    EXPECT_TRUE(equal);
    EXPECT_FALSE(a_larger);
    EXPECT_EQ(0x0, outputBus_->read().toInt());
}

TEST_F(ALUTest, OR) 
{
    inputBusA_->write(0xAA); // 1010 1010
    inputBusB_->write(0xEB); // 1110 1011
    
    selectOR();
    alu_->update(carryIn_, op_);

    bool carryOut, equal, a_larger, zero;
    alu_->output(carryOut, equal, a_larger, zero);

    EXPECT_EQ(outputBus_->read().toInt(), 0xEB);
}

TEST_F(ALUTest, AND) 
{
    inputBusA_->write(0xAA); // 1010 1010
    inputBusB_->write(0xEB); // 1110 1011

    selectAND();
    alu_->update(carryIn_, op_);

    bool carryOut, equal, a_larger, zero;
    alu_->output(carryOut, equal, a_larger, zero);

    EXPECT_EQ(outputBus_->read().toInt(), 0xAA);
}

TEST_F(ALUTest, NOT) 
{
    inputBusA_->write(0xBB); // 1011 1011
    inputBusB_->write(0xBB); // 1011 1011

    selectNOT();
    alu_->update(carryIn_, op_);

    bool carryOut, equal, a_larger, zero;
    alu_->output(carryOut, equal, a_larger, zero);

    EXPECT_EQ(outputBus_->read().toInt(), 0x44);
}

TEST_F(ALUTest, SHRWithShiftOutFalse) 
{
    /*
        0100 0010 -> 0010 0001
    */
    inputBusA_->write(0x42);
    inputBusB_->write(0x42);
    carryIn_ = false;

    selectSHR();
    alu_->update(carryIn_, op_);

    bool carryOut, equal, a_larger, zero;
    alu_->output(carryOut, equal, a_larger, zero);
    EXPECT_EQ(outputBus_->read().toInt(), 0x21);
    EXPECT_FALSE(carryOut);
}

TEST_F(ALUTest, SHRWithShiftOutTrue) 
{
    /*
        0100 0011 -> 0010 0001
    */
    inputBusA_->write(0x43);
    inputBusB_->write(0x43);
    carryIn_ = false;

    selectSHR();
    alu_->update(carryIn_, op_);

    bool carryOut, equal, a_larger, zero;
    alu_->output(carryOut, equal, a_larger, zero);

    EXPECT_EQ(outputBus_->read().toInt(), 0x21);
    EXPECT_TRUE(carryOut);
}

TEST_F(ALUTest, SHRWithShiftInTrue) 
{
    /*
        0100 0010 -> 1010 0001
    */
    inputBusA_->write(0x42);
    inputBusB_->write(0x42);
    carryIn_ = true;

    selectSHR();
    alu_->update(carryIn_, op_);

    bool carryOut, equal, a_larger, zero;
    alu_->output(carryOut, equal, a_larger, zero);

    EXPECT_EQ(outputBus_->read().toInt(), 0xA1);
    EXPECT_FALSE(carryOut);
}

TEST_F(ALUTest, SHLWithShiftOutFalse) 
{
    /*
        0100 0010 -> 1000 0100
    */
    inputBusA_->write(0x42);
    inputBusB_->write(0x42);
    carryIn_ = false;

    selectSHL();
    alu_->update(carryIn_, op_);

    bool carryOut, equal, a_larger, zero;
    alu_->output(carryOut, equal, a_larger, zero);

    EXPECT_EQ(outputBus_->read().toInt(), 0x84);
    EXPECT_FALSE(carryOut);
}

TEST_F(ALUTest, SHLWithShiftOutTrue) 
{
    /*
        1100 0010 -> 1000 0100
    */
    inputBusA_->write(0xC2);
    inputBusB_->write(0xC2);
    carryIn_ = false;

    selectSHL();
    alu_->update(carryIn_, op_);

    bool carryOut, equal, a_larger, zero;
    alu_->output(carryOut, equal, a_larger, zero);

    EXPECT_EQ(outputBus_->read().toInt(), 0x84);
    EXPECT_TRUE(carryOut);
}

TEST_F(ALUTest, SHLWithShiftInTrue) 
{
    /*
        0100 0010 -> 1000 0101
    */
    inputBusA_->write(0x42);
    inputBusB_->write(0x42);
    carryIn_ = true;

    selectSHL();
    alu_->update(carryIn_, op_);

    bool carryOut, equal, a_larger, zero;
    alu_->output(carryOut, equal, a_larger, zero);

    EXPECT_EQ(outputBus_->read().toInt(), 0x85);
    EXPECT_FALSE(carryOut);
}

TEST_F(ALUTest, ADDCalcDoubleWithOutCarryOut) 
{
    selectADD();

    for (int a = 0x00; a < 0x7F; ++a)
    {
        inputBusA_->write(Byte(a));
        inputBusB_->write(Byte(a));

        carryIn_ = false;
        alu_->update(carryIn_, op_);

        bool carryOut, equal, a_larger, zero;
        alu_->output(carryOut, equal, a_larger, zero);

        int expectedSum = a + a;

        EXPECT_EQ(expectedSum, outputBus_->read().toInt());
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
            inputBusA_->write(Byte(a));
            inputBusB_->write(Byte(b));

            carryIn_ = false;
            alu_->update(carryIn_, op_);

            bool carryOut, equal, a_larger, zero;
            alu_->output(carryOut, equal, a_larger, zero);

            int expectedSum = a + b;

            EXPECT_EQ(expectedSum, outputBus_->read().toInt());
            EXPECT_FALSE(carryOut);
        }
    }
}

TEST_F(ALUTest, ADDWithCarryOut) 
{
    selectADD();

    carryIn_ = false;

    inputBusA_->write(Byte(0xF1));
    inputBusB_->write(Byte(0xF1));

    alu_->update(carryIn_, op_);

    bool carryOut, equal, a_larger, zero;
    alu_->output(carryOut, equal, a_larger, zero);

    EXPECT_EQ(0xE2, outputBus_->read().toInt());
    EXPECT_TRUE(carryOut);
}
