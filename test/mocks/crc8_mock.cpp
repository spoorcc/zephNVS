#include <sys/crc.h>

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C" {

u8_t crc8_ccitt(u8_t initial_value, const void *buf, size_t len)
{
    return mock().actualCall(__func__).returnUnsignedIntValueOrDefault(0);
}

}