#ifndef VGA_H
#define VGA_H

#include <stm32f4xx.h>

#define WIDTH ((uint16_t)640)
#define HEIGHT ((uint16_t)480)

#define HSYNC ((uint16_t)96)
#define HBP ((uint16_t)48)
#define HFP ((uint16_t)16)

#define VSYNC ((uint16_t)2)
#define VBP ((uint16_t)33)
#define VFP ((uint16_t)10)

#define SCREEN_WIDTH ((uint16_t)256)
#define SCREEN_HEIGHT ((uint16_t)240)

#define PIXEL_SIZE 4

const uint32_t fb[WIDTH * HEIGHT] = {};

static uint32_t nesPalette[0x40] = {0x656666, 0x002D69, 0x131F7F, 0x3C137C, 0x600B62, 0x730A37, 0x710F07, 0x5A1A00, 0x342800, 0x0B3400, 0x003C00, 0x013D10, 0x013840, 0x0000, 0x0000, 0x0000,
                                    0xAEAEAE, 0x0F63B3, 0x4051D0, 0x7841CC, 0xA736A9, 0xC03470, 0xBD3C30, 0x9F4A00, 0x6D5C01, 0x366D01, 0x077704, 0x00793D, 0x00727D, 0x0000, 0x0000, 0x0000,
                                    0xFEFEFF, 0x5DB3FF, 0x8FA1FF, 0xC890FF, 0xF785FA, 0xFF83C0, 0xFF8B7F, 0xEF9A49, 0xBDAC2C, 0x85BC2F, 0x55C753, 0x3CC98C, 0x3EC2CD, 0x4E4E4D, 0x0000, 0x0000,
                                    0xFEFEFF, 0xBCDFFF, 0xD1D8FF, 0xE8D1FF, 0xFBCDFD, 0xFFCCE5, 0xFFCFCA, 0xF8D5B4, 0xE4DCA8, 0xCCE3A9, 0xB9E8B8, 0xAEE8D0, 0xAFE5EA, 0xB7B6B6, 0x0000, 0x0000};

class VGA
{
public:
    VGA();

    // uint8_t fb[SCREEN_WIDTH * SCREEN_HEIGHT];

    void setPixel(uint16_t x, uint16_t y, uint8_t color_index);
};

#endif