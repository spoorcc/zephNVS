
#ifndef DEVICE_MOCK_HPP__
#define DEVICE_MOCK_HPP__

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

inline void expectDeviceBindingToBeRetrieved()
{
    mock().expectOneCall("device_get_binding");
}

inline void expectDeviceBindingToBeRetrieved(struct device* device)
{
    mock().expectOneCall("device_get_binding").andReturnValue(device);
}

#endif // DEVICE_MOCK_HPP__