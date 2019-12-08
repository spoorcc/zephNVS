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

const size_t PAR_COUNT = 400U;

#define DEVNAME "MYDEVICE"
TEST_BASE(NvsCore)
{
    struct nvs_fs fs;
    struct device dev;

    par_u16_t par16Bytes[PAR_COUNT];

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

    void init_nvs()
    {
        expectDeviceBindingToBeRetrieved(&dev);
        nvs_init(&fs, DEVNAME);
    }

    void init_parameters()
    {
        for (size_t i = 0U; i < PAR_COUNT; ++i)
        {
            par16Bytes[i].id = i;
            par16Bytes[i].value = i;
        }
    }

    template <class T>
    void given_parameter_is_written(T const * const par)
    {
        LONGS_EQUAL(sizeof(par->value), nvs_write(&fs, par->id, &par->value, sizeof(par->value))); 
    }

    template <class T>
    void value_can_be_retrieved(T const * const expectedPar)
    {
        typedef typeof(T::value) buf_t;

        buf_t buf;

        LONGS_EQUAL(sizeof(expectedPar->value), nvs_read(&fs, expectedPar->id, &buf, sizeof(buf)));
        LONGS_EQUAL(expectedPar->value, buf);
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

    given_parameter_is_written<par_u16_t>(&myPar1);
    given_parameter_is_written<par_u32_t>(&myPar42);

    value_can_be_retrieved<par_u16_t>(&myPar1);
    value_can_be_retrieved<par_u32_t>(&myPar42);
}

TEST_GROUP_BASE(NvsInitialized, NvsCore)
{
    void setup()
    {
        NvsCore::setup();

        init_parameters();
        init_nvs();
    }
};

TEST(NvsInitialized, ManyParameters)
{
    for (size_t i = 0U; i < PAR_COUNT; ++i)
    {
        given_parameter_is_written<par_u16_t>(par16Bytes + i);
    }

    for (size_t i = 0U; i < PAR_COUNT; ++i)
    {
        value_can_be_retrieved<par_u16_t>(par16Bytes + i);
    }
}

int main(int ac, char** av)
{
   return CommandLineTestRunner::RunAllTests(ac, av);
}