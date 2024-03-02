#ifndef MAPPER_H
#define MAPPER_H

#include <cstdint>

enum MIRROR
{
    HARDWARE,
    HORIZONTAL,
    VERTICAL,
    ONESCREEN_LO,
    ONESCREEN_HI,
};

class Mapper
{
public:
    Mapper(uint8_t prgBanks, uint8_t chrBanks);
    virtual ~Mapper();

    virtual void reset() = 0;

    virtual MIRROR mirror();

    virtual bool irqState();
    virtual void irqClear();

    virtual void scanline();

    virtual uint32_t mapCPURead(uint16_t addr) = 0;
    virtual uint32_t mapCPUWrite(uint16_t addr) = 0;
    virtual uint32_t mapPPURead(uint16_t addr) = 0;
    virtual uint32_t mapPPUWrite(uint16_t addr) = 0;

protected:
    uint8_t prgBanks = 0;
    uint8_t chrBanks = 0;
};

#endif