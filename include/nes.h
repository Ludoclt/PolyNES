#ifndef NES_H
#define NES_H

#include "bus.h"

#define WINDOW_WIDTH 768
#define WINDOW_HEIGHT 720

class NES
{
public:
    NES();

    Bus bus;

    void clock();
    void reset();
    void insertCartridge(Cartridge *cart);

private:
    uint32_t clockCounter;
};

#endif