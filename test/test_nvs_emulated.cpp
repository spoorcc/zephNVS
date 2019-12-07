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

#include "emulator/flash_emulator.h"
#include "mocks/device_mock.hpp"

typedef struct
{
    uint16_t id;
    uint16_t value;
} par_u16_t;

typedef struct
{
    uint16_t id;
    uint32_t value;
} par_u32_t;


#define DEVNAME "MYDEVICE"
TEST_BASE(NvsCore)
{
    struct nvs_fs fs;
    struct device dev;

    void setup()
    {
        std::memset(&fs, 0, sizeof(fs));
        std::memset(&dev, 0, sizeof(dev));

        fs.sector_size = 256U;
        fs.sector_count = 24U;

        mock().ignoreOtherCalls();
        flash_emulator_setup(48U, 256U);
    }

    void teardown()
    {
        mock().checkExpectations();
        mock().clear();
        flash_emulator_teardown();
    }
};

/*------------ Basic -------------------------*/
TEST_GROUP_BASE(NvsHappyFlow, NvsCore)
{

};

TEST(NvsHappyFlow, Basic)
{
    expectDeviceBindingToBeRetrieved(&dev);

    int result = nvs_init(&fs, DEVNAME);
    LONGS_EQUAL(0, result);

    const par_u16_t myPar1 = {1U, 456U};
    const par_u32_t myPar42 = {42U, 123456U};

    LONGS_EQUAL(sizeof(myPar1.value), nvs_write(&fs, myPar1.id, &myPar1.value, sizeof(myPar1.value))); 
    LONGS_EQUAL(sizeof(myPar42.value), nvs_write(&fs, myPar42.id, &myPar42.value, sizeof(myPar42.value)));

    uint16_t buf16;

    LONGS_EQUAL(sizeof(buf16), nvs_read(&fs, myPar1.id, &buf16, sizeof(buf16))); 
    LONGS_EQUAL(myPar1.value, buf16);

    uint32_t buf32;

    LONGS_EQUAL(sizeof(buf32), nvs_read(&fs, myPar42.id, &buf32, sizeof(buf32))); 
    LONGS_EQUAL(myPar42.value, buf32);
}

int main(int ac, char** av)
{
   return CommandLineTestRunner::RunAllTests(ac, av);
}