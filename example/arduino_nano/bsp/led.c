
#include <avr/io.h>
#include "led.h"

void Led_Init(void)
{
    DDRB |= (1 << PIN5);
    Led_Off();
}

void Led_On(void)
{
    PORTB |= (1 << PIN5);
}

void Led_Off(void)
{
    PORTB &= ~(1 << PIN5);
}

void Led_Toggle(void)
{
    PORTB ^= (1 << PIN5);
}


