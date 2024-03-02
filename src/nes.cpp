#include "nes.h"

NES::NES() : bus() {}

void NES::clock()
{
    bus.ppu.onClock();
    if (clockCounter % 3 == 0)
    {
        if (bus.dma_transfer)
        {
            if (bus.dma_dummy)
            {
                if (clockCounter % 2 == 1)
                {
                    bus.dma_dummy = false;
                }
            }
            else
            {
                if (clockCounter % 2 == 0)
                {
                    bus.dma_data = bus.read(bus.dma_page << 8 | bus.dma_addr);
                }
                else
                {
                    bus.ppu.OAMptr[bus.dma_addr] = bus.dma_data;
                    bus.dma_addr++;
                    if (bus.dma_addr == 0x00)
                    {
                        bus.dma_transfer = false;
                        bus.dma_dummy = true;
                    }
                }
            }
        }
        else
        {
            bus.cpu.onClock();
        }
    }

    if (bus.ppu.nmi)
    {
        bus.ppu.nmi = false;
        bus.cpu.nmi();
    }

    // Check if cartridge is requesting IRQ
    if (bus.cartridge->getMapper()->irqState())
    {
        bus.cartridge->getMapper()->irqClear();
        bus.cpu.irq();
    }

    clockCounter++;
}

void NES::reset()
{
    bus.cartridge->reset();
    bus.cpu.reset();
    bus.ppu.reset();
    clockCounter = 0;
    bus.dma_page = 0x00;
    bus.dma_addr = 0x00;
    bus.dma_data = 0x00;
    bus.dma_dummy = true;
    bus.dma_transfer = false;
}

void NES::insertCartridge(Cartridge *cart)
{
    bus.cartridge = cart;
    bus.ppu.cartridge = cart;
}