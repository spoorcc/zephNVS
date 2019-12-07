#include <string.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>

#include <drivers/flash.h>

#include <drivers/flash.h>
#include <device.h>

#include "flash_emulator.h"

typedef struct {
    uint8_t* data;
    size_t pageCount;
    size_t pageSize;
    size_t readBlockSize;
    size_t writeBlockSize;
    bool writeProtected;
} flashEmulator_t;

static flashEmulator_t this;


void flash_emulator_setup(size_t pageCount, size_t pageSize)
{
    this.pageCount = pageCount;
    this.pageSize = pageSize;

    this.data = malloc(this.pageCount * this.pageSize);
    assert(this.data);
    memset(this.data, 0xFFu, this.pageCount * this.pageSize);
    this.writeProtected = 0u;
    this.readBlockSize = 1u;
    this.writeBlockSize = 4u;
}

void flash_emulator_teardown()
{
    assert(this.data != NULL);
    free(this.data);
}

int flash_read(struct device *dev, off_t offset, void *data, size_t len)
{
    if (offset % this.readBlockSize != 0 || len % this.readBlockSize != 0 || offset + len >= this.pageCount * this.pageSize)
    {
        return -ENXIO;
    }

    memcpy(data, this.data + offset, len);

    return 0;
}

int flash_write(struct device *dev, off_t offset, const void *data, size_t len)
{
    if (this.writeProtected || offset % this.writeBlockSize != 0 || len % this.writeBlockSize != 0 || offset + len >= this.pageCount * this.pageSize)
    {
        return -ENXIO;
    }
    
    for (size_t i = 0; i < len / this.writeBlockSize; ++i)
    {
        for (size_t j = 0; j < this.writeBlockSize; ++j)
        {
            uint8_t src = ((uint8_t*)data)[i * this.writeBlockSize + j];
            uint8_t* dst = this.data + offset + i * this.writeBlockSize + j;

            /* Flash can only set bits to 0 */
            if (((~*dst) & src) != 0)
            {
                return -ENXIO;
            }

            *dst = src;
        }
    }

    return 0;
}

int flash_erase(struct device *dev, off_t offset, size_t size)
{
    if (this.writeProtected || offset % this.pageSize != 0)
    {
        return -ENXIO;
    }

    memset(this.data + offset, 0xFFu, this.pageSize);

    return 0;
}

int flash_write_protection_set(struct device *dev, bool enable)
{
    this.writeProtected = enable;
    return 0;
}

int flash_get_page_info_by_offs(struct device *dev, off_t offset, struct flash_pages_info *info)
{
    if (offset >= this.pageCount * this.pageSize)
    {
        return -ENXIO;
    }

    info->index = offset / this.pageSize;
    info->start_offset = info->index * this.pageSize;
    info->size = this.pageSize;

    return 0;
}

size_t flash_get_write_block_size(struct device *dev)
{
    return this.writeBlockSize;
}