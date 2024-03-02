#include "bus.h"

Bus::Bus() : cpu(this)
{
    for (int i = 0; i < 2048; i++)
        internalRam[i] = 0x00;
}

uint8_t Bus::read(uint64_t addr)
{
    if (addr >= 0x0000 && addr <= 0x1FFF)
        return internalRam[addr & 0x07FF];
    else if (addr >= 0x2000 && addr <= 0x3FFF)
        return ppu.read(addr & 0x0007);
    else if (addr >= 0x4016 && addr <= 0x4017)
    {
        uint8_t state = (controller_state[addr & 0x0001] & 0x80) > 0;
        controller_state[addr & 0x0001] <<= 1;
        return state;
    }
    else if (addr >= 0x8000 && addr <= 0xFFFF)
    {
        return cartridge->readFromCPU(addr);
    }

    return 0x00;
}

void Bus::write(uint16_t addr, uint8_t data)
{
    if (addr >= 0x0000 && addr <= 0x1FFF)
        internalRam[addr & 0x07FF] = data; // Mirror
    else if (addr >= 0x2000 && addr <= 0x3FFF)
        ppu.write(addr & 0x0007, data);
    else if (addr == 0x4014)
    {
        dma_page = data;
        dma_addr = 0x00;
        dma_transfer = true;
    }
    else if (addr >= 0x4016 && addr <= 0x4017)
        controller_state[addr & 0x0001] = controller[addr & 0x0001];
    else if (addr >= 0x8000 && addr <= 0xFFFF)
    {
        cartridge->writeFromCPU(addr, data);
    }
}
