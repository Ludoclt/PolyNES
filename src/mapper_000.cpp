#include "mappers/mapper_000.h"

Mapper000::Mapper000(uint8_t prgB, uint8_t chrB) : Mapper(prgB, chrB) {}

uint32_t Mapper000::mapCPURead(uint16_t addr)
{
    return addr & (prgBanks > 1 ? 0x7FFF : 0x3FFF);
}

uint32_t Mapper000::mapCPUWrite(uint16_t addr)
{
    return addr & (prgBanks > 1 ? 0x7FFF : 0x3FFF);
}

uint32_t Mapper000::mapPPURead(uint16_t addr)
{
    return addr;
}

uint32_t Mapper000::mapPPUWrite(uint16_t addr)
{
    if (chrBanks == 0)
    {
        return addr;
    }
    return 0x00;
}

void Mapper000::reset() {}