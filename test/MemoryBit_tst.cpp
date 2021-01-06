#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "MemoryBit.h"

using ::testing::Return;

class MemoryBitTest : public testing::Test 
{
protected:
    // Remember that SetUp() is run immediately before a test starts.
    void SetUp() override 
    {
    }

    // TearDown() is invoked immediately after a test finishes.  
    void TearDown() override 
    { 
    }    

    MemoryBit m_;
};

TEST_F(MemoryBitTest, saveTrue) 
{
    Bit I(true); // bit the we want to remember
    m_.save(I);
    
    Bit O = m_.get(); // output of the remembered bit
    EXPECT_TRUE(O == true);
}

TEST_F(MemoryBitTest, saveFalse) 
{
    Bit I(false); // bit the we want to remember
    m_.save(I);
    
    Bit O = m_.get(); // output of the remembered bit
    EXPECT_TRUE(O == false);
}