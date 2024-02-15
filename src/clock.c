#include "clock.h"

#include <stm32f4xx.h>

void systemClockInit(void)
{
    FLASH->ACR |= 0b011; // flash memory delay : 3 wait state

    RCC->CR |= (1 << 16); // enable HSE : 8 mhz
    while ((RCC->CR & (1 << 17)) == 0)
        ;
    RCC->PLLCFGR |= (1 << 22); // HSE as PLL clock entry

    // PLL clock configuration
    RCC->PLLCFGR &= ~0x3F; // reset PLLM
    RCC->PLLCFGR |= 8;     // PLLM : HSE (8) / 8 = 1 mhz

    RCC->PLLCFGR &= ~0x7FC0;    // reset PLLN
    RCC->PLLCFGR |= (360 << 6); // PLLN : 360 mhz VCO = 360 mhz

    // system clock divider
    RCC->PLLCFGR &= ~(0b11 << 16); // reset PLLP
    RCC->PLLCFGR |= (0b00 << 16);  // div factor 2, useless, just a reminder

    // USB frequency
    RCC->PLLCFGR &= ~(0b1111 << 24); // reset
    RCC->PLLCFGR |= (8 << 24);       // PLLQ: 360/8 = 45 mhz

    RCC->CR |= (1 << 24); // enable PLL
    while ((RCC->CR & (1 << 25)) == 0)
        ;

    // clock for bus
    RCC->CFGR &= ~(0b1111 << 4);                // no division on AHB
    RCC->CFGR |= (0b101 << 10) | (0b100 << 13); // APB1 div: 180/4 = 45 mhz APB2 div: 180/2 = 90 mhz

    RCC->CFGR |= 0b10; // set PLL as source of the system frequency
    while ((RCC->CFGR & (0b10 << 2)) != (0b10 << 2))
        ;
}