#include "cartridge.h"

#include "ines_file.h"
#include "donkey.h"
#include <cstring>

Cartridge::Cartridge(const std::string &filePath)
{
    Header header;
    unsigned int read_pos = 0;

    memcpy((char *)&header, donkey_rom, sizeof(Header));
    read_pos += sizeof(Header);

    if (header.flags6 & TRAINER)
        // ignore
        read_pos = 512;

    uint8_t fileType = ((header.flags7 & 0x0C) == 0x08 ? 2 : 1);

    if (fileType == 1)
    {
        prgBanks = header.prg_rom_size;
        prgRom = new uint8_t[PRG_ROM_UNIT * prgBanks];
        memcpy((char *)prgRom, donkey_rom + read_pos, PRG_ROM_UNIT * prgBanks);
        read_pos += PRG_ROM_UNIT * prgBanks;

        chrBanks = header.chr_rom_size;
        size_t chr_size = chrBanks ? CHR_ROM_UNIT * chrBanks : CHR_ROM_UNIT;
        chrRom = new uint8_t[chr_size];
        memcpy((char *)chrRom, donkey_rom + read_pos, chr_size);
        read_pos += chr_size;
    }
    else
    {
        prgBanks = ((header.flags8 & 0x07) << 8) | header.prg_rom_size;
        prgRom = new uint8_t[PRG_ROM_UNIT * prgBanks];
        memcpy((char *)prgRom, donkey_rom + read_pos, PRG_ROM_UNIT * prgBanks);
        read_pos += PRG_ROM_UNIT * prgBanks;

        chrBanks = ((header.flags8 & 0x38) << 8) | header.chr_rom_size;
        chrRom = new uint8_t[CHR_ROM_UNIT * chrBanks];
        memcpy((char *)chrRom, donkey_rom + read_pos, CHR_ROM_UNIT * chrBanks);
        read_pos += CHR_ROM_UNIT * chrBanks;
    }

    mirror = (header.flags6 & 0x01) ? VERTICAL : HORIZONTAL;
    mapperId = (header.flags7 & 0xF0) | (header.flags6 >> 4);

    switch (mapperId)
    {
    case 0:
        mapper = new Mapper000(prgBanks, chrBanks);
        break;

    default:
        break;
    }
}

Cartridge::~Cartridge()
{
    delete mapper;
    delete prgRom;
    delete chrRom;
}

uint8_t Cartridge::readFromCPU(uint16_t addr)
{
    uint32_t mapped_addr = mapper->mapCPURead(addr);
    if (mapped_addr == 0xFFFFFFFF)
    {
        return 0x00;
    }
    else
        return prgRom[mapped_addr];
}

void Cartridge::writeFromCPU(uint16_t addr, uint8_t data)
{
    uint32_t mapped_addr = mapper->mapCPUWrite(addr);
    if (mapped_addr != 0xFFFFFFFF)
    {
        prgRom[mapped_addr] = data;
    }
}

uint8_t Cartridge::readFromPPU(uint16_t addr)
{
    return chrRom[mapper->mapPPURead(addr)];
}

void Cartridge::writeFromPPU(uint16_t addr, uint8_t data)
{
    chrRom[mapper->mapPPUWrite(addr)] = data;
}

void Cartridge::reset()
{
    if (mapper != nullptr)
        mapper->reset();
}

MIRROR Cartridge::Mirror()
{
    MIRROR m = mapper->mirror();
    return (m == MIRROR::HARDWARE ? mirror : m);
}