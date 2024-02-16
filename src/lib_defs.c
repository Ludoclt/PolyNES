#include <lib_defs.h>

#include "tick.h"
#include "debug.h"
#include "gpio.h"

// Tick
void lib_delay_ms(uint32_t ms)
{
    delay_ms(ms);
}

void lib_beginCounter(uint32_t ms)
{
    beginCounter(ms);
}

uint8_t lib_isTimeElapsed(void)
{
    return isTimeElapsed();
}

// Debug
void lib_println(const char *s, ...)
{
    println(s);
}

// GPIO
void lib_setPinAF(GPIO_TypeDef *port, uint8_t pin, uint8_t af_mode)
{
    setPinAF(port, pin, af_mode);
}