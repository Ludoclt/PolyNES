#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <cstdint>
#include <string>

#include "mappers/mapper_000.h"

class Cartridge
{
public:
    Cartridge(const std::string &filePath);
    ~Cartridge();

    MIRROR Mirror();
    Mapper *getMapper() { return mapper; }

    void reset();

    uint8_t readFromCPU(uint16_t addr);
    void writeFromCPU(uint16_t addr, uint8_t data);

    uint8_t readFromPPU(uint16_t addr);
    void writeFromPPU(uint16_t addr, uint8_t data);

private:
    uint8_t *prgRom;
    uint8_t *chrRom;

    uint8_t mapperId;
    uint8_t prgBanks;
    uint8_t chrBanks;

    MIRROR mirror = HORIZONTAL;
    Mapper *mapper;
};

#endif