#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "control/Clock.h"

#include <iostream>
#include <chrono>         // std::chrono::seconds

using ::testing::Return;


class ClockTest : public testing::Test 
{};

TEST_F(ClockTest, x) 
{
    /*
    control::Clock clk(1);

    std::cout << "main (start)\n";

    clk.start();

    std::this_thread::sleep_for (std::chrono::milliseconds(3000));

    clk.shutdown();

    std::cout << "main (end)\n";    
    */
}