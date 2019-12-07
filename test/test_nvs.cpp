/*!
 * \file
 * \internal
 */


#include <cstring>

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "CppUTest/CommandLineTestRunner.h"

#include "nvs/nvs.h"
#include "device.h"
#include "drivers/flash.h"

#include "mocks/flash_mock.hpp"
#include "mocks/mutex_mock.hpp"
#include "mocks/device_mock.hpp"

#define DEVNAME "MYDEVICE"
TEST_BASE(NvsCore)
{
    struct nvs_fs fs;
    struct device dev;

    void setup()
    {
        std::memset(&fs, 0, sizeof(fs));
        std::memset(&dev, 0, sizeof(dev));
        //mock().ignoreOtherCalls();
    }

    void teardown()
    {
        mock().checkExpectations();
        mock().clear();
    }
};

/*------------ Basic -------------------------*/
TEST_GROUP_BASE(NvsBasicInit, NvsCore)
{

};

TEST(NvsBasicInit, InvalidDeviceBindingResultsInError)
{
    expectMutexToBeInitialized();
    expectDeviceBindingToBeRetrieved(NULL);

    const int result = nvs_init(&fs, DEVNAME);
    LONGS_EQUAL(-ENXIO, result);
}

TEST(NvsBasicInit, InitHapyFlow)
{
    expectMutexToBeInitialized();
    expectDeviceBindingToBeRetrieved(&dev);
    expectFlashWriteBlockSizeToBeRetrieved(8U);

    // TODO: Determine sane values
    fs.sector_size = 256U;
    fs.sector_count = 24U;
    struct flash_pages_info info = {
	    .start_offset = 0U,
	    .size = 16U,
	    .index = 0U
    };

    expectFlashPageInfoByOffset(&info);
    expectMutexToBeUsed();

    // TODO: What is read here
    u8_t data1[8U];
    memset(data1, 0xFF, sizeof(data1));
    expectFlashRead(26U, data1, sizeof(data1));

    u8_t data2[32U];
    memset(data2, 0xFF, sizeof(data2));
    expectFlashRead(8U, data2, sizeof(data2));

    u8_t data3[16U];
    memset(data3, 0xFF, sizeof(data3));
    expectFlashRead(1U, data3, sizeof(data3));

    u8_t data4[32U];
    memset(data4, 0xFF, sizeof(data4));
    expectFlashRead(7U, data4, sizeof(data4));

    const int result = nvs_init(&fs, DEVNAME);
    LONGS_EQUAL(0, result);
}

int main(int ac, char** av)
{
   return CommandLineTestRunner::RunAllTests(ac, av);
}