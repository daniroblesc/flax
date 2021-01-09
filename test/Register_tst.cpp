#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Register.h"
#include "Bus.h"

using ::testing::Return;

class RegisterTest : public testing::Test 
{

protected:
  // Remember that SetUp() is run immediately before a test starts.
  void SetUp() override 
  {
    // init bus
    Byte value = 0xA0;
    bus_.set(value);
  }

  // TearDown() is invoked immediately after a test finishes.  
  void TearDown() override 
  { 
  }

  Bus bus_;
};

TEST_F(RegisterTest, basic_operation) 
{
    Register reg(&bus_);

    reg.set();    // reg content is refreshed with the bus content
    EXPECT_TRUE(bus_.get() == 0xA0);

    bus_.set(0xA1); // someone refresh bus content
    reg.enable(); // register's content is written to the bus
    EXPECT_TRUE(bus_.get() == 0xA0); // check that bus content is refreshed with register's content
}