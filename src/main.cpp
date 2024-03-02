#include <stm32f4xx.h>
#include "clock.h"
#include "tick.h"
#include "debug.h"
// #include "vga.h"
#include "lcd.h"

#define SYSTEM_CLOCK_SPEED 180000000

int main()
{
    // setup
    systemClockInit();
    sysTickInit(SYSTEM_CLOCK_SPEED);
    ioInit();

    // vga
    // VGA vga;

    // lcd
    LCD lcd;

    // loop
    while (1)
    {
    }

    return 0;
}