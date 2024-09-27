#include "tick.h"

#include <stm32h750xx.h>

void SysTick_Handler(void)
{
    if (counter_value <= 0)
    {
        SysTick->CTRL &= ~(0b11);
    }
    else
    {
        counter_value--;
        elapsed_time++;
    }
}

void SysTick_Init(uint32_t cpu_freq)
{
    SysTick->CTRL &= ~(0b111);
    SysTick->CTRL |= (1 << 2); // cpu clock as source
    SysTick->LOAD &= ~(0xFFFFFF);
    SysTick->LOAD |= (cpu_freq * 0x3E8 - 1); // set reload value for 1 ms tick
}

void Begin_Counter(uint32_t ms)
{
    counter_value = ms;
    elapsed_time = 0;
    SysTick->VAL &= ~(0xFFFFFF);
    SysTick->CTRL |= 0b11; // enable counter
}

uint32_t Get_Elapsed_Time(void)
{
    return elapsed_time;
}

uint8_t Is_Time_Elapsed()
{
    return counter_value <= 0 ? 1 : 0;
}

void Delay_ms(uint32_t ms)
{
    Begin_Counter(ms);
    while (!Is_Time_Elapsed())
        ;
}