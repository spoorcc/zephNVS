#include <device.h>

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C" {

struct device *device_get_binding(const char *name)
{
    return (device*) mock().actualCall(__func__).returnPointerValueOrDefault(NULL);
}

}