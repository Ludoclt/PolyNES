#ifndef MAPPER_000_H
#define MAPPER_000_H

#include "mapper.h"

class Mapper000 : public Mapper
{
public:
    Mapper000(uint8_t prgBanks, uint8_t chrBanks);

    uint32_t mapCPURead(uint16_t addr) override;
    uint32_t mapCPUWrite(uint16_t addr) override;
    uint32_t mapPPURead(uint16_t addr) override;
    uint32_t mapPPUWrite(uint16_t addr) override;
    void reset() override;
};

#endif