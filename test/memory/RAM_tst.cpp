#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "memory/RAM.h"
#include <iostream>
#include <memory>

using ::testing::Return;

class RAMTest : public testing::Test 
{
protected:

    void SetUp() override 
    {
        bus_ = std::make_unique<Bus>("bus");
        cell_ = new RAMCell(bus_.get());
    }

    void TearDown() override 
    { 
        delete cell_;
    }
    
    std::unique_ptr<Bus> bus_;
    RAMCell* cell_;

    void updateBus(const Byte value)
    {
        bus_->write(value);
    }

    void updateCellContent(const Byte value)
    {
        updateBus(value);
        // select the cell by address
        cell_->update(true, true);
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
    EXPECT_TRUE(bus_->read() == 0xAB); 
}

TEST_F(RAMTest, cannotReadCellContentIfHasNotBeenSelected) 
{
    updateBus(0xAB);

    // DO not select the cell by address
    cell_->update(true, false);
    // save bus content into the cell 
    cell_->set();

    // now change bus content
    updateBus(0xBB);
    
    // write cell content to the bus
    cell_->enable();

    // check that bus content has not been refreshed with cell's content
    EXPECT_FALSE(bus_->read() == 0xAB); 
}

TEST_F(RAMTest, cannotReadCellContentIfHasNotBeenSet) 
{
    updateBus(0xAB);

    // select the cell by address
    cell_->update(true, true);
    // DO not save bus content into the cell (0xA0)
    cell_->set(false);

    // now change bus content
    updateBus(0xBB);

    // write cell content to the bus
    cell_->enable();

    // check that bus content is refreshed with cell's content
    EXPECT_FALSE(bus_->read() == 0xAB); 
}

TEST_F(RAMTest, cannotReadCellContentIfEnableBitIsZeroed) 
{
    updateCellContent(0xAB);

    // now change bus content
    updateBus(0xBB);

    // write cell content to the bus
    cell_->enable(false);

    // check that bus content is refreshed with cell's content
    EXPECT_FALSE(bus_->read() == 0xAB); 
}

TEST_F(RAMTest, RAM256SingleTest)
{
    RAM256 ram(bus_.get());

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
    EXPECT_TRUE(bus_->read() == 0x22); 

    /* Read the @2 */
    updateBus(0xAC); // set memory address
    ram.setAddress();
    ram.enable();
    EXPECT_TRUE(bus_->read() == 0x23); 
}

TEST_F(RAMTest, RAM256FullTest)
{
    RAM256 ram(bus_.get());

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
        EXPECT_TRUE(bus_->read() == (0xFF-addr)); 
    }
}


TEST_F(RAMTest, RAM65KSingleTest)
{
    RAM65K ram(bus_.get());

    /* Write the @1 */
    updateBus(0xB); // set memory address (low part)
    ram.setS0();
    updateBus(0xA); // set memory address (high part)
    ram.setS1();
    updateBus(0x22); // set data to save in ram
    ram.set();

    /* Write the @2 */
    updateBus(0xB); // set memory address (low part)
    ram.setS0();
    updateBus(0xB); // set memory address (high part)
    ram.setS1();
    updateBus(0x23); // set data to save in ram
    ram.set();

    /* Read the @1 */
    updateBus(0xB); // set memory address (low part)
    ram.setS0();
    updateBus(0xA); // set memory address (high part)
    ram.setS1();
    ram.enable();
    EXPECT_TRUE(bus_->read() == 0x22); 

    /* Read the @2 */
    updateBus(0xB); // set memory address (low part)
    ram.setS0();
    updateBus(0xB); // set memory address (high part)
    ram.setS1();
    ram.enable();
    EXPECT_TRUE(bus_->read() == 0x23); 
}

TEST_F(RAMTest, RAM65KFullTest)
{
    RAM65K ram(bus_.get());

    /* Write the entire RAM */
    for (int i = 0; i < 0xFFFF; ++i)
    {
        updateBus(i & 0x0F); // set memory address (low part)
        ram.setS0();
        updateBus(i & 0xF0); // set memory address (high part)
        ram.setS1();

        updateBus((0xFFFF-i) & 0x00FF); // set data to save in ram
        ram.set();
    }

    /* Read the entire RAM */
    for (int i = 0; i < 0xFFFF; ++i)
    {
        updateBus(i & 0x0F); // set memory address (low part)
        ram.setS0();
        updateBus(i & 0xF0); // set memory address (high part)
        ram.setS1();

        ram.enable();
        EXPECT_TRUE(bus_->read() == ((0xFFFF-i) & 0x00FF)); 
    }
}
