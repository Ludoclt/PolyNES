#include "tick.h"

#include <stm32f4xx.h>

void SysTick_Handler(void)
{
    if (elapsed_time != counter_time)
        elapsed_time++;
    else
    {
        // stop counter
        SysTick->CTRL &= ~1;        // disable SysTick
        SysTick->CTRL &= ~(1 << 1); // disable interrupt
        elapsed_time = 0;
        counter_time = 0;
        isr_delay = 0;
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

void delay_ms(uint32_t ms)
{
    if (counter_time == 0)
    {
        SysTick->VAL = 0;   // set current value to 0
        SysTick->CTRL |= 1; // enable SysTick
        while (ms)
        {
            while ((SysTick->CTRL & (1 << 16)) == 0)
                ;
            ms--;
        }
        SysTick->CTRL &= ~1; // disable SysTick
    }
    else
    {
        isr_delay = ms;
        while (isr_delay != 0)
            ;
    }
}

void beginCounter(uint32_t ms)
{
    counter_time = ms;
    SysTick->VAL = 0;          // set current value to 0
    SysTick->CTRL |= (1 << 1); // enable interrupt
    SysTick->CTRL |= 1;        // enable SysTick
}

uint32_t getElapsedTime(void)
{
    return elapsed_time;
}

uint8_t isTimeElapsed(void)
{
    return counter_time == 0 ? 1 : 0;
}