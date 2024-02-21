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

#define PIXEL_SIZE 4

// const uint32_t fb[WIDTH * HEIGHT] = {};

class VGA
{
public:
    VGA();

    void setPixel(uint16_t x, uint16_t y, uint32_t color);
};

#endif