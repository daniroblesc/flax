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
    Bit I(Bit::ONE); // bit the we want to remember
    m_.write(I);
    
    Bit O = m_.read(); // output of the remembered bit
    EXPECT_TRUE(O == Bit::ONE);
}

TEST_F(MemoryBitTest, saveFalse) 
{
    Bit I(Bit::ZERO); // bit the we want to remember
    m_.write(I);
    
    Bit O = m_.read(); // output of the remembered bit
    EXPECT_TRUE(O == Bit::ZERO);
}