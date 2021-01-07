#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Register.h"

using ::testing::Return;

class RegisterTest : public testing::Test 
{};

TEST_F(RegisterTest, write) 
{
    Register r;

    Byte input = 0xAB;
    r.write(input);

    Byte output = r.read();
    EXPECT_TRUE(output == 0xAB);

    r.write(Byte(0xCC));
    output = r.read();
    EXPECT_TRUE(output == 0xCC);
}