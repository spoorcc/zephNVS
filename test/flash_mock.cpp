#include <drivers/flash.h>

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C" {

int flash_read(struct device *dev, off_t offset, void *data,
			 size_t len)
{
    return mock().actualCall(__func__).returnIntValueOrDefault(0);
}

int flash_write(struct device *dev, off_t offset, const void *data,
			  size_t len)
{
    return mock().actualCall(__func__).returnIntValueOrDefault(0);
}

int flash_erase(struct device *dev, off_t offset, size_t size)
{
    return mock().actualCall(__func__).returnIntValueOrDefault(0);
}

int flash_write_protection_set(struct device *dev, bool enable)
{
    return mock().actualCall(__func__).returnIntValueOrDefault(0);
}

int flash_get_page_info_by_offs(struct device *dev, off_t offset, struct flash_pages_info *info)
{
    return mock().actualCall(__func__).returnIntValueOrDefault(0);
}

size_t flash_get_write_block_size(struct device *dev)
{
    return mock().actualCall(__func__).returnUnsignedIntValueOrDefault(0U);
}

}