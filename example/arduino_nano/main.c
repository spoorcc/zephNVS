
#include <bsp/enc28j60.h>
#include <bsp/led.h>

int main(void)
{
    Led_Init();

    const uint8_t mac[6u] = {0x00u, 0x00u, 0x00u, 0xA1u, 0x2Bu, 0xCCu};
    enc28j60_Init(mac);

    Led_Blink(1000u, 0u);
}
