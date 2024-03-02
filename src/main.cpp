#include <stm32f4xx.h>
#include "clock.h"
#include "tick.h"
#include "debug.h"
#include "lcd.h"
#include "nes.h"

#define SYSTEM_CLOCK_SPEED 180000000

#define LCD_OFFSET_X 32

int main()
{
    // setup
    systemClockInit();
    sysTickInit(SYSTEM_CLOCK_SPEED);
    ioInit();

    // lcd
    LCD lcd;

    NES nes;
    Cartridge cartridge("donkey.nes");
    nes.insertCartridge(&cartridge);
    nes.reset();

    nes.bus.controller[0] = 0x00;

    // loop
    while (1)
    {
        // event
        // nes.bus.controller[0] = (1 << 5);

        // logic
        if (isTimeElapsed())
        {
            do
            {
                nes.clock();
            } while (!nes.bus.ppu.frame_complete);
            nes.bus.ppu.frame_complete = false;
            beginCounter(17); // 60 fps
        }

        // drawing
        for (int y = 0; y < RENDER_HEIGHT; y++)
        {
            for (int x = 0; x < RENDER_WIDTH; x++)
            {
                lcd.drawPixel(LCD_OFFSET_X + x, y, (nes.bus.ppu.getFrameBuffer())[y * RENDER_WIDTH + x]);
            }
        }
    }

    return 0;
}