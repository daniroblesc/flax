#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "memory/MemoryBit.h"

using ::testing::Return;

class MemoryBitTest : public testing::Test 
{
protected:
    MemoryBit m_;
};

TEST_F(MemoryBitTest, startInOffState) 
{
    bool O = m_.output(); 
    EXPECT_FALSE(O);
}

TEST_F(MemoryBitTest, saveTrue) 
{
    bool input = true; // bit the we want to remember

    // update input (enable set bit)
    m_.update(input, true);

    bool O = m_.output(); // output of the remembered bit
    EXPECT_TRUE(O);
}

TEST_F(MemoryBitTest, saveFalse) 
{
    bool input = false; // bit the we want to remember

    // update input (enable set bit)
    m_.update(input, true);
    
    bool O = m_.output(); // output of the remembered bit
    EXPECT_FALSE(O);
}

TEST_F(MemoryBitTest, doNotSave) 
{
    ASSERT_FALSE(m_.output());

    // save 1 in m_
    m_.update(true, true);
    ASSERT_TRUE(m_.output());

    // update to 0 but do not set
    m_.update(false, false);
    EXPECT_TRUE(m_.output());
}

TEST_F(MemoryBitTest, djhworld) 
{
    MemoryBit b;
	
	b.update(false, true);
    EXPECT_FALSE(b.output());

	b.update(false, false);
	EXPECT_FALSE(b.output());

	b.update(true, true);
	EXPECT_TRUE(b.output());

	b.update(false, false);
	EXPECT_TRUE(b.output());
}

TEST_F(MemoryBitTest, truthTable) 
{
    MemoryBit b;

    b.update(false, true);
    EXPECT_FALSE(b.output());

    b.update(true, true);
    EXPECT_TRUE(b.output());

    b.update(false, false);
    EXPECT_TRUE(b.output());

    b.update(true, false);
    EXPECT_TRUE(b.output());
}