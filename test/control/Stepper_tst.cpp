#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "control/Stepper.h"

#include <iostream>

using ::testing::Return;


class StepperTest : public ::testing::TestWithParam<std::tuple<int, int>>
{
public:
    int getOutput()  
    {
	    for (size_t i = 0; i < 7; ++i) 
        {
		    if (stepper_.output(i))
            {
			    return i + 1;
		    }
	    }
	    return -1;
    }   

protected:

    control::Stepper stepper_;
};

TEST_P(StepperTest, cycle)
{
    int cycles = std::get<0>(GetParam());

    for (int i = 0; i < cycles; ++i)
    {
		stepper_.update(true);
		stepper_.update(false);
    }

    int expectedOutput = std::get<1>(GetParam());

    int output = getOutput();
	EXPECT_EQ(expectedOutput, output);
}

INSTANTIATE_TEST_CASE_P(
        cycle,
        StepperTest,
        ::testing::Values(
                //             cycles expectedOutput 
                //----------------------------
                std::make_tuple(1,    1),
                std::make_tuple(2,    2),
                std::make_tuple(3,    3),
                std::make_tuple(4,    4),
                std::make_tuple(5,    5),
                std::make_tuple(6,    6)
        ));