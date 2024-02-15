#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    static volatile uint32_t start_time = 0;
    static uint8_t counter_started = 0;
    static volatile uint32_t isr_delay = 0;

    void sysTickInit(uint32_t ahb_freq);
    void delay_ms(uint32_t time);
    void beginCounter(uint32_t time);
    uint8_t isTimeElapsed(void);

#ifdef __cplusplus
}
#endif

#endif