
#ifndef FLASH_EMULATOR_H__
#define FLASH_EMULATOR_H__

#ifdef __cplusplus
extern "C" {
#endif

void flash_emulator_setup(size_t pageCount, size_t pageSize);
void flash_emulator_teardown();

#ifdef __cplusplus
}
#endif

#endif // FLASH_EMULATOR_H__