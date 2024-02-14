#include "delay.h"

#include <stm32f4xx.h>

void sysTickInit(unsigned int ahb_freq)
{
    // reset CTRL
    SysTick->CTRL &= ~(0b111 | (1 << 16));
    // set AHB clock as SysTick source
    SysTick->CTRL |= (1 << 2);
    // set reload value for 1 ms tick
    SysTick->LOAD = ahb_freq / 1000 - 1;
}

void delay_ms(unsigned int time)
{
    // set current value to 0
    SysTick->VAL = 0;
    // enable SysTick
    SysTick->CTRL |= 1;
    while (time)
    {
        while ((SysTick->CTRL & (1 << 16)) == 0)
            ;
        time--;
    }
    // disable SysTick
    SysTick->CTRL &= ~1;
}