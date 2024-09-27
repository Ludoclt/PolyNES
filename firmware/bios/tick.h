#ifndef TICK_H
#define TICK_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    static uint32_t counter_value = 0;
    static uint32_t elapsed_time = 0;

    void SysTick_Init(uint32_t cpu_freq);
    void Begin_Counter(uint32_t ms);
    uint32_t Get_Elapsed_Time(void);
    uint8_t Is_Time_Elapsed(void);
    void Delay_ms(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif