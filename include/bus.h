#ifndef BUS_H
#define BUS_H

#include <cstdint>
#include "cpu.h"
#include "ppu.h"
#include "cartridge.h"

class Bus
{
public:
    Bus();

    CPU cpu;
    PPU ppu;
    Cartridge *cartridge;
    uint8_t internalRam[2048];
    uint8_t controller[2];
    uint8_t controller_state[2];

    uint8_t dma_page = 0x00;
    uint8_t dma_addr = 0x00;
    uint8_t dma_data = 0x00;

    bool dma_transfer = false;
    bool dma_dummy = true;

    uint8_t read(uint64_t addr);
    void write(uint16_t addr, uint8_t data);
};

#endif