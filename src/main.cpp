#include <stm32f4xx.h>
#include "clock.h"
#include "debug.h"
#include "delay.h"

#define SYSTEM_CLOCK_SPEED 180000000

#define FNAME "test.txt"

int main()
{
    // setup
    systemClockInit();
    sysTickInit(SYSTEM_CLOCK_SPEED);
    debugInit();

    // loop
    while (1)
    {
        println("test");
        delay_ms(1000);
        println("autre test");
        delay_ms(1000);
    }

    return 0;
}