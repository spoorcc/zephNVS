
#ifndef RAM_FLASH_H__
#define RAM_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

#define FLASH_PAGE_COUNT        (4U)
#define FLASH_PAGE_SIZE         (256U)
#define FLASH_READ_BLOCK_SIZE   (1U)
#define FLASH_WRITE_BLOCK_SIZE  (4U)

void ramflash_init();

#ifdef __cplusplus
}
#endif

#endif // RAM_FLASH_H__