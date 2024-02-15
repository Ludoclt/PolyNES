#include "tick.h"

#include <stm32f4xx.h>

void SysTick_Handler(void)
{
    if (start_time != 0)
        start_time--;
    else
    {
        // stop counter
        SysTick->CTRL &= ~1;        // disable SysTick
        SysTick->CTRL &= ~(1 << 1); // disable interrupt
        counter_started = 0;
    }

    if (isr_delay != 0)
        isr_delay--;
}

void sysTickInit(uint32_t ahb_freq)
{
    // reset CTRL
    SysTick->CTRL &= ~(0b111 | (1 << 16));
    // set AHB clock as SysTick source
    SysTick->CTRL |= (1 << 2);
    // set reload value for 1 ms tick
    SysTick->LOAD = ahb_freq / 1000 - 1;
}

void delay_ms(uint32_t time)
{
    if (!counter_started)
    {
        SysTick->VAL = 0;   // set current value to 0
        SysTick->CTRL |= 1; // enable SysTick
        while (time)
        {
            while ((SysTick->CTRL & (1 << 16)) == 0)
                ;
            time--;
        }
        SysTick->CTRL &= ~1; // disable SysTick
    }
    else
    {
        isr_delay = time;
        while (isr_delay != 0)
            ;
    }
}

void beginCounter(uint32_t time)
{
    start_time = time;
    SysTick->VAL = 0;          // set current value to 0
    SysTick->CTRL |= (1 << 1); // enable interrupt
    SysTick->CTRL |= 1;        // enable SysTick
    counter_started = 1;
}

uint8_t isTimeElapsed(void)
{
    return start_time == 0 ? 1 : 0;
}