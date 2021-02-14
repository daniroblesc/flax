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
        systemBus_ = std::make_unique<Bus>("system");
        MAROutputBus_ = std::make_unique<Bus>("MAR_out");
        MAR_ = std::make_unique<Register>("MAR", systemBus_.get(), MAROutputBus_.get());

        cell_ = new RAMCell(systemBus_.get());
    }

    void TearDown() override 
    { 
        delete cell_;
    }
    
    std::unique_ptr<Bus> systemBus_;
    std::unique_ptr<Bus> MAROutputBus_;
    std::unique_ptr<Register> MAR_;
    RAMCell* cell_;

    void updateSystemBus(const Byte value)
    {
        systemBus_->write(value);
    }

    void updateCellContent(const Byte value)
    {
        updateSystemBus(value);
        // select the cell by address
        cell_->update();
        // save bus content into the cell
        cell_->set();
    }
  
};

TEST_F(RAMTest, saveByteInACell) 
{
    updateCellContent(0xAB);

    // now change bus content
    updateSystemBus(0xBB);

    // write cell content to the bus
    cell_->enable();

    // check that bus content is refreshed with cell's content
    EXPECT_TRUE(systemBus_->read() == 0xAB); 
}

TEST_F(RAMTest, cannotReadCellContentIfHasNotBeenSelected) 
{
    updateSystemBus(0xAB);

    // DO not select the cell by address
    cell_->update(true, false);
    // save bus content into the cell 
    cell_->set();

    // now change bus content
    updateSystemBus(0xBB);
    
    // write cell content to the bus
    cell_->enable();

    // check that bus content has not been refreshed with cell's content
    EXPECT_FALSE(systemBus_->read() == 0xAB); 
}

TEST_F(RAMTest, cannotReadCellContentIfHasNotBeenSet) 
{
    updateSystemBus(0xAB);

    // select the cell by address
    cell_->update(true, true);
    // DO not save bus content into the cell (0xA0)
    cell_->set(false);

    // now change bus content
    updateSystemBus(0xBB);

    // write cell content to the bus
    cell_->enable();

    // check that bus content is refreshed with cell's content
    EXPECT_FALSE(systemBus_->read() == 0xAB); 
}

TEST_F(RAMTest, cannotReadCellContentIfEnableBitIsZeroed) 
{
    updateCellContent(0xAB);

    // now change bus content
    updateSystemBus(0xBB);

    // write cell content to the bus
    cell_->enable(false);

    // check that bus content is refreshed with cell's content
    EXPECT_FALSE(systemBus_->read() == 0xAB); 
}

TEST_F(RAMTest, RAM256SingleTest)
{
    RAM256 ram(systemBus_.get(), MAR_.get());

    /* Write the @1 */
    updateSystemBus(0xAB); // set memory address
    MAR_->set();
    updateSystemBus(0x22); // set data to save in ram
    ram.set();

    /* Write the @2 */
    updateSystemBus(0xAC); // set memory address
    MAR_->set();
    updateSystemBus(0x23); // set data to save in ram
    ram.set();

    /* Read the @1 */
    updateSystemBus(0xAB); // set memory address
    MAR_->set();
    ram.enable();
    EXPECT_TRUE(systemBus_->read() == 0x22); 

    /* Read the @2 */
    updateSystemBus(0xAC); // set memory address
    MAR_->set();
    ram.enable();
    EXPECT_TRUE(systemBus_->read() == 0x23); 
}

TEST_F(RAMTest, RAM256FullTest)
{
    RAM256 ram(systemBus_.get(), MAR_.get());

    /* Write the entire RAM */
    for (int addr=0; addr < 0xFF; ++addr)
    {
        updateSystemBus(addr); // set memory address
        MAR_->set();
        updateSystemBus((0xFF-addr)); // set data to save in ram
        ram.set();
    }

    /* Read the entire RAM */
    for (int addr=0; addr < 0xFF; ++addr)
    {
        updateSystemBus(addr); // set memory address
        MAR_->set();
        ram.enable();
        EXPECT_TRUE(systemBus_->read() == (0xFF-addr)); 
    }
}


TEST_F(RAMTest, RAM65KSingleTest)
{
    RAM65K ram(systemBus_.get());

    /* Write the @1 */
    updateSystemBus(0xB); // set memory address (low part)
    ram.setS0();
    updateSystemBus(0xA); // set memory address (high part)
    ram.setS1();
    updateSystemBus(0x22); // set data to save in ram
    ram.set();

    /* Write the @2 */
    updateSystemBus(0xB); // set memory address (low part)
    ram.setS0();
    updateSystemBus(0xB); // set memory address (high part)
    ram.setS1();
    updateSystemBus(0x23); // set data to save in ram
    ram.set();

    /* Read the @1 */
    updateSystemBus(0xB); // set memory address (low part)
    ram.setS0();
    updateSystemBus(0xA); // set memory address (high part)
    ram.setS1();
    ram.enable();
    EXPECT_TRUE(systemBus_->read() == 0x22); 

    /* Read the @2 */
    updateSystemBus(0xB); // set memory address (low part)
    ram.setS0();
    updateSystemBus(0xB); // set memory address (high part)
    ram.setS1();
    ram.enable();
    EXPECT_TRUE(systemBus_->read() == 0x23); 
}

TEST_F(RAMTest, RAM65KFullTest)
{
    RAM65K ram(systemBus_.get());

    /* Write the entire RAM */
    for (int i = 0; i < 0xFFFF; ++i)
    {
        updateSystemBus(i & 0x0F); // set memory address (low part)
        ram.setS0();
        updateSystemBus(i & 0xF0); // set memory address (high part)
        ram.setS1();

        updateSystemBus((0xFFFF-i) & 0x00FF); // set data to save in ram
        ram.set();
    }

    /* Read the entire RAM */
    for (int i = 0; i < 0xFFFF; ++i)
    {
        updateSystemBus(i & 0x0F); // set memory address (low part)
        ram.setS0();
        updateSystemBus(i & 0xF0); // set memory address (high part)
        ram.setS1();

        ram.enable();
        EXPECT_TRUE(systemBus_->read() == ((0xFFFF-i) & 0x00FF)); 
    }
}


class RAMCellTest : public testing::Test 
{
protected:

    void SetUp() override 
    {
        systemBus_ = std::make_unique<Bus>("system", Bus::VERBOSE);
    }
    void TearDown() override 
    { 
    }
 
    std::unique_ptr<Bus> systemBus_;
};

TEST_F(RAMCellTest, setTrue)
{
    RAMCell cell(systemBus_.get(), 77);
   
    systemBus_->write(88);

    cell.update();
    cell.set();

    EXPECT_TRUE(cell.output() == 88); 
}

TEST_F(RAMCellTest, setFalse)
{
    RAMCell cell(systemBus_.get(), 77);
   
    systemBus_->write(88);

    cell.update();
    cell.set(false);

    EXPECT_TRUE(cell.output() == 77); 
}

TEST_F(RAMCellTest, enableTrue)
{
    RAMCell cell(systemBus_.get(), 77);
   
    systemBus_->write(88);

    cell.update();
    cell.enable();

    EXPECT_TRUE(systemBus_->read() == 77); 
}

TEST_F(RAMCellTest, enableFalse)
{
    RAMCell cell(systemBus_.get(), 77);
   
    systemBus_->write(88);

    cell.update();
    cell.enable(false);

    EXPECT_TRUE(systemBus_->read() == 88); 
}