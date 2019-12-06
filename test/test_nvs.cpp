/*!
 * \file
 * \internal
 */


#include <cstring>

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "CppUTest/CommandLineTestRunner.h"

#include "nvs/nvs.h"

TEST_BASE(NvsCore)
{
    void setup()
    {
        mock().clear();
        mock().ignoreOtherCalls();
    }

    void teardown()
    {
        mock().checkExpectations();
    }
};

/*------------ Basic -------------------------*/
TEST_GROUP_BASE(NvsBasic, NvsCore)
{

};

TEST(NvsBasic, test_basic)
{
    UNSIGNED_LONGS_EQUAL(1U, 1U)
}

int main(int ac, char** av)
{
   return CommandLineTestRunner::RunAllTests(ac, av);
}