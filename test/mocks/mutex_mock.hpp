
#ifndef MUTEX_MOCK_HPP__
#define MUTEX_MOCK_HPP__

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

inline void expectMutexToBeInitialized()
{
    mock().expectOneCall("k_mutex_init");
}

inline void expectMutexToBeUsed()
{
    mock().expectOneCall("k_mutex_lock");
    mock().expectOneCall("k_mutex_unlock");
}

#endif // MUTEX_MOCK_HPP__