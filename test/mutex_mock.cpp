#include <sys/mutex.h>

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C" {

void k_mutex_init(struct k_mutex *mutex)
{
    mock().actualCall(__func__);
}

int k_mutex_lock(struct k_mutex *mutex, s32_t timeout)
{
    return mock().actualCall(__func__).returnIntValueOrDefault(0);
}

void k_mutex_unlock(struct k_mutex *mutex)
{
    mock().actualCall(__func__);
}

}