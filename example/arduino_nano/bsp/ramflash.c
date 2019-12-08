#include <string.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>

#include <drivers/flash.h>

#include <device.h>

#include "ramflash.h"

typedef struct {
    uint8_t data[FLASH_PAGE_COUNT * FLASH_PAGE_SIZE];
    bool writeProtected;
} flashEmulator_t;

static flashEmulator_t this;

void ramflash_init()
{
    memset(this.data, 0xFFu, FLASH_PAGE_COUNT * FLASH_PAGE_SIZE);
    this.writeProtected = 0u;
}

int flash_read(struct device *dev, off_t offset, void *data, size_t len)
{
    if (offset % FLASH_READ_BLOCK_SIZE != 0 || len % FLASH_READ_BLOCK_SIZE != 0 || offset + len >= FLASH_PAGE_COUNT * FLASH_PAGE_SIZE)
    {
        return -ENXIO;
    }

    memcpy(data, this.data + offset, len);

    return 0;
}

int flash_write(struct device *dev, off_t offset, const void *data, size_t len)
{
    if (this.writeProtected || offset % FLASH_WRITE_BLOCK_SIZE != 0 || len % FLASH_WRITE_BLOCK_SIZE != 0 || offset + len >= FLASH_PAGE_COUNT * FLASH_PAGE_SIZE)
    {
        return -ENXIO;
    }
    
    for (size_t i = 0; i < len / FLASH_WRITE_BLOCK_SIZE; ++i)
    {
        for (size_t j = 0; j < FLASH_WRITE_BLOCK_SIZE; ++j)
        {
            uint8_t src = ((uint8_t*)data)[i * FLASH_WRITE_BLOCK_SIZE + j];
            uint8_t* dst = this.data + offset + i * FLASH_WRITE_BLOCK_SIZE + j;

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
    if (this.writeProtected || offset % FLASH_PAGE_SIZE != 0)
    {
        return -ENXIO;
    }

    memset(this.data + offset, 0xFFu, FLASH_PAGE_SIZE);

    return 0;
}

int flash_write_protection_set(struct device *dev, bool enable)
{
    this.writeProtected = enable;
    return 0;
}

int flash_get_page_info_by_offs(struct device *dev, off_t offset, struct flash_pages_info *info)
{
    if (offset >= FLASH_PAGE_COUNT * FLASH_PAGE_SIZE)
    {
        return -ENXIO;
    }

    info->index = offset / FLASH_PAGE_SIZE;
    info->start_offset = info->index * FLASH_PAGE_SIZE;
    info->size = FLASH_PAGE_SIZE;

    return 0;
}

size_t flash_get_write_block_size(struct device *dev)
{
    return FLASH_WRITE_BLOCK_SIZE;
}