#include "vga.h"

#include "gpio.h"

VGA::VGA()
{
    // clock init
    RCC->APB2ENR |= RCC_APB2ENR_LTDCEN; // enable LTDC clock

    // PLLSAI (pixel clock) configuration
    RCC->PLLSAICFGR |= (200 << 6);    // PLLSAIN *200
    RCC->PLLSAICFGR |= (0b010 << 28); // PLLSAIR /2
    RCC->DCKCFGR &= ~(0b11 << 16);    // reset
    RCC->DCKCFGR |= (0b01 << 16);     // /4

    RCC->CR |= RCC_CR_PLLSAION; // enable PLLSAI
    while ((RCC->CR & RCC_CR_PLLSAIRDY) == 0)
        ;

    // port setup
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;

    setPinAF(GPIOA, 3, 0b1110);  // LCD_B5
    setPinAF(GPIOA, 4, 0b1110);  // LCD_VSYNC
    setPinAF(GPIOA, 6, 0b1110);  // LCD_G2
    setPinAF(GPIOA, 8, 0b1110);  // LCD_R6
    setPinAF(GPIOA, 11, 0b1110); // LCD_R4
    setPinAF(GPIOA, 12, 0b1110); // LCD_R5

    setPinAF(GPIOB, 0, 0b1001);  // LCD_R3
    setPinAF(GPIOB, 8, 0b1110);  // LCD_B6
    setPinAF(GPIOB, 9, 0b1110);  // LCD_B7
    setPinAF(GPIOB, 10, 0b1110); // LCD_G4
    setPinAF(GPIOB, 11, 0b1110); // LCD_G5

    setPinAF(GPIOC, 6, 0b1110); // LCD_HSYNC
    setPinAF(GPIOC, 7, 0b1110); // LCD_G6
    // setPinAF(GPIOC, 10, 0b1110); // LCD_R2 missing pin on nucleo 144 board

    setPinAF(GPIOD, 3, 0b1110);  // LCD_G7
    setPinAF(GPIOD, 6, 0b1110);  // LCD_B2
    setPinAF(GPIOD, 10, 0b1110); // LCD_B3

    setPinAF(GPIOE, 4, 0b1110);  // LCD_B0
    setPinAF(GPIOE, 5, 0b1110);  // LCD_G0
    setPinAF(GPIOE, 6, 0b1110);  // LCD_G1
    setPinAF(GPIOE, 11, 0b1110); // LCD_G3
    setPinAF(GPIOE, 12, 0b1110); // LCD_B4
    setPinAF(GPIOE, 13, 0b1110); // LCD_DE
    setPinAF(GPIOE, 14, 0b1110); // LCD_CLK
    setPinAF(GPIOE, 15, 0b1110); // LCD_R7

    setPinAF(GPIOG, 12, 0b1110); // LCD_B1

    setPinAF(GPIOH, 2, 0b1110); // LCD_R0
    // setPinAF(GPIOH, 3, 0b1110); // LCD_R1 missing pin on nucleo 144 board

    // timing setup
    LTDC->SSCR |= (((HSYNC - 1) << 16) | (VSYNC - 1));
    LTDC->BPCR |= (((HSYNC + HBP - 1) << 16) | (VSYNC + VBP - 1));
    LTDC->AWCR |= (((HSYNC + HBP + WIDTH - 1) << 16) | (VSYNC + VBP + HEIGHT - 1));
    LTDC->TWCR |= (((HSYNC + HBP + WIDTH + HFP - 1) << 16) | (VSYNC + VBP + HEIGHT + VFP - 1));
    // polarity
    LTDC->GCR &= ~(1 << 31); // HSYNC negative
    LTDC->GCR &= ~(1 << 30); // VSYNC negative

    // bg color
    LTDC->BCCR = 0xFFFFFF;

    // layer setup
    LTDC_Layer1->WHPCR |= (((HSYNC + HBP + SCREEN_WIDTH - 1) << 16) | (HSYNC + HBP));
    LTDC_Layer1->WVPCR |= (((VSYNC + VBP + SCREEN_HEIGHT - 1) << 16) | (VSYNC + VBP));

    // LTDC_Layer1->PFCR |= 0b001; // RGB888

    LTDC_Layer1->CFBAR = (uint32_t)fb;

    LTDC_Layer1->CACR = 255;

    LTDC_Layer1->CFBLR |= (((SCREEN_WIDTH * PIXEL_SIZE) << 16) | (SCREEN_WIDTH * PIXEL_SIZE + 3));
    LTDC_Layer1->CFBLNR |= SCREEN_HEIGHT;

    // CLUT
    // for (int i = 0; i < 0x40; i++)
    // {
    //     // Adress
    //     LTDC_Layer2->CLUTWR &= ~(0xFF << 24);
    //     LTDC_Layer2->CLUTWR |= (i << 24);
    //     // Color
    //     LTDC_Layer2->CLUTWR &= ~(0xFFFFFF);
    //     LTDC_Layer2->CLUTWR |= (nesPalette[i] & 0xFFFFFF);
    // }

    LTDC_Layer1->DCCR = 0xFF0000FF;
    // LTDC_Layer1->BFCR &= ~(0b111);
    // LTDC_Layer1->BFCR |= 0b101; // BF2
    // LTDC_Layer1->BFCR &= ~(0b111 << 8);
    // LTDC_Layer1->BFCR |= (0b100 << 8); // BF1

    // enable layer and LTDC activation
    LTDC_Layer1->CR |= 1;
    // LTDC_Layer1->CR |= (1 << 4); // enable CLUT
    LTDC->GCR |= LTDC_GCR_LTDCEN;
}

void VGA::setPixel(uint16_t x, uint16_t y, uint8_t color_index)
{
    // fb[y * (WIDTH - 1) + x] = color_index;
}