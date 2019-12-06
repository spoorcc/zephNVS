
#ifndef LED_H__
#define LED_H__

#include <util/delay.h>

void Led_Init(void);

void Led_On(void);
void Led_Off(void);
void Led_Toggle(void);

void Led_Blink(uint32_t delay_ms, uint8_t nr_of_times);

#define Led_Blink(_delay_, _iterations_)                                          \
        do                                                                        \
        {                                                                         \
            for(uint8_t i = 0u; (i < (_iterations_*2u))||(_iterations_==0u); ++i) \
            {                                                                     \
                Led_Toggle();                                                     \
                _delay_ms(_delay_);                                               \
            }                                                                     \
            break;                                                                \
        } while(0u);


#endif /* !LED_H__ */