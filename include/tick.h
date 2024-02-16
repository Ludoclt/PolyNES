#ifndef TICK_H
#define TICK_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    static volatile uint32_t counter_time = 0;
    static volatile uint32_t elapsed_time = 0;
    static volatile uint32_t isr_delay = 0;

    void sysTickInit(uint32_t ahb_freq);
    void delay_ms(uint32_t ms);
    void beginCounter(uint32_t ms);
    uint32_t getElapsedTime(void);
    uint8_t isTimeElapsed(void);

#ifdef __cplusplus
}
#endif

#endif