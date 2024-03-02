#ifndef INES_FILE_H
#define INES_FILE_H

#include <cstdint>

#define TRAINER 0x04
#define PRG_ROM_UNIT 16384
#define CHR_ROM_UNIT 8192

struct Header
{
    uint8_t constant[4];
    uint8_t prg_rom_size;
    uint8_t chr_rom_size;
    uint8_t flags6;
    uint8_t flags7;
    uint8_t flags8;
    uint8_t flags9;
    uint8_t flags10;
    uint8_t unused[5];
};

#endif