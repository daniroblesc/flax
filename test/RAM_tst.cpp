#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "RAM.h"
#include <iostream>

using ::testing::Return;

class RAMTest : public testing::Test 
{
protected:

    void SetUp() override 
    {
        cell_ = new RAMCell(&bus_);
    }

    void TearDown() override 
    { 
        delete cell_;
    }

    Bus bus_;   
    RAMCell* cell_;

    void updateBus(const Byte value)
    {
        bus_.set(value);
    }

    void updateCellContent(const Byte value)
    {
        updateBus(value);
        // select the cell by address
        cell_->update(Bit::ONE, Bit::ONE);
        // save bus content into the cell
        cell_->set();
    }
};

TEST_F(RAMTest, saveByteInACell) 
{
    updateCellContent(0xAB);

    // now change bus content
    updateBus(0xBB);

    // write cell content to the bus
    cell_->enable();

    // check that bus content is refreshed with cell's content
    EXPECT_TRUE(bus_.get() == 0xAB); 
}

TEST_F(RAMTest, cannotReadCellContentIfHasNotBeenSelected) 
{
    updateBus(0xAB);

    // DO not select the cell by address
    cell_->update(Bit::ONE, Bit::ZERO);
    // save bus content into the cell 
    cell_->set();

    // now change bus content
    updateBus(0xBB);
    
    // write cell content to the bus
    cell_->enable();

    // check that bus content has not been refreshed with cell's content
    EXPECT_FALSE(bus_.get() == 0xAB); 
}

TEST_F(RAMTest, cannotReadCellContentIfHasNotBeenSet) 
{
    updateBus(0xAB);

    // select the cell by address
    cell_->update(Bit::ONE, Bit::ONE);
    // DO not save bus content into the cell (0xA0)
    cell_->set(Bit::ZERO);

    // now change bus content
    updateBus(0xBB);

    // write cell content to the bus
    cell_->enable();

    // check that bus content is refreshed with cell's content
    EXPECT_FALSE(bus_.get() == 0xAB); 
}

TEST_F(RAMTest, cannotReadCellContentIfEnableBitIsZeroed) 
{
    updateCellContent(0xAB);

    // now change bus content
    updateBus(0xBB);

    // write cell content to the bus
    cell_->enable(Bit::ZERO);

    // check that bus content is refreshed with cell's content
    EXPECT_FALSE(bus_.get() == 0xAB); 
}

TEST_F(RAMTest, RAMSingleTest)
{
    RAM ram(&bus_);

    /* Write the @1 */
    updateBus(0xAB); // set memory address
    ram.setAddress();
    updateBus(0x22); // set data to save in ram
    ram.set();

    /* Write the @2 */
    updateBus(0xAC); // set memory address
    ram.setAddress();
    updateBus(0x23); // set data to save in ram
    ram.set();

    /* Read the @1 */
    updateBus(0xAB); // set memory address
    ram.setAddress();
    ram.enable();
    EXPECT_TRUE(bus_.get() == 0x22); 

    /* Read the @2 */
    updateBus(0xAC); // set memory address
    ram.setAddress();
    ram.enable();
    EXPECT_TRUE(bus_.get() == 0x23); 
}

TEST_F(RAMTest, RAMFullTest)
{
    RAM ram(&bus_);

    /* Write the entire RAM */
    for (int addr=0; addr < 0xFF; ++addr)
    {
        updateBus(addr); // set memory address
        ram.setAddress();
        updateBus((0xFF-addr)); // set data to save in ram
        ram.set();
    }

    /* Read the entire RAM */
    for (int addr=0; addr < 0xFF; ++addr)
    {
        updateBus(addr); // set memory address
        ram.setAddress();
        ram.enable();
        EXPECT_TRUE(bus_.get() == (0xFF-addr)); 
    }
}