#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "MemoryBit.h"

using ::testing::Return;

class MemoryBitTest : public testing::Test 
{
protected:
    MemoryBit m_;
};

TEST_F(MemoryBitTest, saveTrue) 
{
    Bit input(Bit::ONE); // bit the we want to remember

    // update input
    m_.update(input);
    // enable set bit
    m_.set();

    Bit O = m_.output(); // output of the remembered bit
    EXPECT_TRUE(O == Bit::ONE);
}

TEST_F(MemoryBitTest, saveFalse) 
{
    Bit input(Bit::ZERO); // bit the we want to remember

    // update input
    m_.update(input);
    // enable set bit
    m_.set();
    
    Bit O = m_.output(); // output of the remembered bit
    EXPECT_TRUE(O == Bit::ZERO);
}