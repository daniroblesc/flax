#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "memory/MemoryBit.h"

using ::testing::Return;

class MemoryBitTest : public testing::Test 
{
protected:
    MemoryBit m_;
};

TEST_F(MemoryBitTest, saveTrue) 
{
    bool input = true; // bit the we want to remember

    // update input
    m_.update(input);
    // enable set bit
    m_.set();

    bool O = m_.output(); // output of the remembered bit
    EXPECT_TRUE(O);
}

TEST_F(MemoryBitTest, saveFalse) 
{
    bool input = false; // bit the we want to remember

    // update input
    m_.update(input);
    // enable set bit
    m_.set();
    
    bool O = m_.output(); // output of the remembered bit
    EXPECT_FALSE(O);
}