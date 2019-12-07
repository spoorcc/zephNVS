
#ifndef FLASH_MOCK_HPP__
#define FLASH_MOCK_HPP__

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

inline void expectFlashRead(const size_t count, void * const data, size_t len)
{
    mock().expectNCalls(count, "flash_read")
          .withOutputParameterReturning("data", data, len)
          .withParameter("len", len);
}
inline void expectFlashWrite()
{
    mock().expectOneCall("flash_write");
}
inline void expectFlashErase()
{
    mock().expectOneCall("flash_erase");
}
inline void expectFlashWriteProtection()
{
    mock().expectOneCall("flash_write_protection_set");
}
inline void expectFlashPageInfoByOffset(struct flash_pages_info const * const info)
{
    mock().expectOneCall("flash_get_page_info_by_offs").withOutputParameterReturning("info", info, sizeof(flash_pages_info));
}
inline void expectFlashWriteBlockSizeToBeRetrieved(const size_t write_block_size)
{
    mock().expectOneCall("flash_get_write_block_size").andReturnValue(write_block_size);
}

#endif // FLASH_MOCK_HPP__