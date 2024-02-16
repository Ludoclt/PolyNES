#ifndef LIB_DEFS_H
#define LIB_DEFS_H

/* Definition of project specific functions to implement */

#include <stm32f4xx.h>

#ifdef __cplusplus
extern "C"
{
#endif

    void lib_delay_ms(uint32_t ms);
    void lib_beginCounter(uint32_t ms);
    uint8_t lib_isTimeElapsed(void);

    void lib_println(const char *s, ...);

    void lib_setPinAF(GPIO_TypeDef *port, uint8_t pin, uint8_t af_mode);

#ifdef __cplusplus
}
#endif

#endif