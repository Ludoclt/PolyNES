#include <stm32f4xx.h>
#include "clock.h"
#include "debug.h"
#include "delay.h"

int main()
{
    // setup
    systemClockInit();
    debugInit();

    // loop
    while (1)
    {
        println("test");
        delay(5000);
        println("autre test");
        delay(5000);
    }

    return 0;
}