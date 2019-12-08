
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

#include <bsp/led.h>
#include <bsp/ramflash.h>
#include <nvs/nvs.h>

typedef struct
{
    uint16_t id;
    uint16_t value;
} par_u16_t;

typedef struct
{
    uint16_t id;
    uint32_t value;
} par_u32_t;

static struct nvs_fs myNvs;

int main(void)
{
    Led_Init();
    ramflash_init();
    Led_Blink(1000u, 0u);

    myNvs.sector_count = 1U;
    myNvs.sector_count = 1U;

    nvs_init(&myNvs, "MyRamFS");

    const par_u16_t myPar1 = {1U, 456U};
    const par_u32_t myPar42 = {42U, 123456U};

    nvs_write(&myNvs, myPar1.id, &myPar1.value, sizeof(myPar1.value)); 
    nvs_write(&myNvs, myPar42.id, &myPar42.value, sizeof(myPar42.value));

    uint16_t buf16;
    uint32_t buf32;

    nvs_read(&myNvs, myPar1.id, &buf16, sizeof(buf16)); 
    nvs_read(&myNvs, myPar42.id, &buf32, sizeof(buf32));

    assert(buf16 == myPar1.value);
    assert(buf32 == myPar42.value);
}
