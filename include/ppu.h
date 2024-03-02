#ifndef PPU_H
#define PPU_H

#include <cstdint>
#include "cartridge.h"

#define RENDER_WIDTH 256
#define RENDER_HEIGHT 240

class PPU
{
public:
    PPU();

    Cartridge *cartridge;

    bool frame_complete = false;
    bool nmi = false;
    bool scanline_trigger = false;

    uint8_t *OAMptr = (uint8_t *)OAM;

    void onClock();
    void reset();

    uint8_t *getFrameBuffer();
    uint8_t getColorIndex(uint8_t palette, uint8_t pixel);

    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);

    uint8_t readMem(uint16_t addr);
    void writeMem(uint16_t addr, uint8_t data);

private:
    uint8_t palette[32];
    uint8_t nameTable[2][1024];

    uint16_t systemPalette[0x40] = {0x632c, 0x16d, 0x10ef, 0x388f, 0x604c, 0x7046, 0x7060, 0x58c0, 0x3140, 0x9a0, 0x1e0, 0x1e2, 0x1c8, 0x0, 0x0, 0x0, 0xad75, 0xb16, 0x429a, 0x7a19, 0xa1b5, 0xc1ae, 0xb9e6, 0x9a40, 0x6ae0, 0x3360, 0x3a0, 0x3c7, 0x38f, 0x0, 0x0, 0x0, 0xffff, 0x5d9f, 0x8d1f, 0xcc9f, 0xf43f, 0xfc18, 0xfc4f, 0xecc9, 0xbd65, 0x85e5, 0x562a, 0x3e51, 0x3e19, 0x4a69, 0x0, 0x0, 0xffff, 0xbeff, 0xd6df, 0xee9f, 0xfe7f, 0xfe7c, 0xfe79, 0xfeb6, 0xe6f5, 0xcf15, 0xbf57, 0xaf5a, 0xaf3d, 0xb5b6, 0x0, 0x0};

    uint8_t frameBuffer[RENDER_WIDTH * RENDER_HEIGHT];

    union PPUSTATUS
    {
        struct
        {
            uint8_t unused : 5;
            uint8_t sprite_overflow : 1;
            uint8_t sprite_zero_hit : 1;
            uint8_t vertical_blank : 1;
        };

        uint8_t reg;
    } status;

    union PPUMASK
    {
        struct
        {
            uint8_t grayscale : 1;
            uint8_t render_background_left : 1;
            uint8_t render_sprites_left : 1;
            uint8_t render_background : 1;
            uint8_t render_sprites : 1;
            uint8_t enhance_red : 1;
            uint8_t enhance_green : 1;
            uint8_t enhance_blue : 1;
        };

        uint8_t reg;
    } mask;

    union PPUCTRL
    {
        struct
        {
            uint8_t nametable_x : 1;
            uint8_t nametable_y : 1;
            uint8_t increment_mode : 1;
            uint8_t pattern_sprite : 1;
            uint8_t pattern_background : 1;
            uint8_t sprite_size : 1;
            uint8_t slave_mode : 1;
            uint8_t enable_nmi : 1;
        };

        uint8_t reg;
    } control;

    union loopy_register
    {
        struct
        {
            uint16_t coarse_x : 5;
            uint16_t coarse_y : 5;
            uint16_t nametable_x : 1;
            uint16_t nametable_y : 1;
            uint16_t fine_y : 3;
            uint16_t unused : 1;
        };

        uint16_t reg = 0x0000;
    };

    loopy_register vram_addr;
    loopy_register tram_addr;

    uint8_t fine_x = 0x00;

    uint8_t address_latch = 0x00;
    uint8_t ppu_data_buffer = 0x00;

    int16_t scanline = 0;
    int16_t cycle = 0;
    bool odd_frame = false;

    uint8_t bg_next_tile_id = 0x00;
    uint8_t bg_next_tile_attrib = 0x00;
    uint8_t bg_next_tile_lsb = 0x00;
    uint8_t bg_next_tile_msb = 0x00;

    uint16_t bg_shifter_pattern_lo = 0x0000;
    uint16_t bg_shifter_pattern_hi = 0x0000;
    uint16_t bg_shifter_attrib_lo = 0x0000;
    uint16_t bg_shifter_attrib_hi = 0x0000;

    struct Sprite
    {
        uint8_t y;
        uint8_t id;
        uint8_t attribute;
        uint8_t x;
    } OAM[64];

    uint8_t oam_addr = 0x00;

    Sprite spriteScanline[8];
    uint8_t sprite_count;
    uint8_t sprite_shifter_pattern_lo[8];
    uint8_t sprite_shifter_pattern_hi[8];

    bool spriteZeroHitPossible = false;
    bool spriteZeroBeingRendered = false;
};

#endif