#include "clock.h"

#include <stm32h750xx.h>

void SystemClock_Init(void)
{
    // power boost mode
    PWR->CR3 |= 0b110;
    PWR->D3CR |= (0b11 << 14);
    RCC->APB4ENR |= (1 << 1);
    SYSCFG->PWRCR |= 1;
    while ((PWR->D3CR & (1 << 13)) == 0)
        ;

    RCC->CR |= 1; // enable HSI : 64 mhz
    while ((RCC->CR & (1 << 2)) == 0)
        ;

    RCC->CR |= (0b11 << 3); // HSIDIV 64/8 = 8 mhz

    // setup sysclk PLL
    RCC->PLLCKSELR &= ~(0x3F << 4);
    RCC->PLLCKSELR |= (1 << 4); // DIVM1 no division
    RCC->PLLCFGR &= ~(0b1);     // integer mode
    RCC->PLLCFGR |= (0b11 << 2);
    RCC->PLL1DIVR &= ~(0x1FF);     // reset
    RCC->PLL1DIVR |= (0x3B);       // DIVN 8*60 = 480 mhz
    RCC->PLL1DIVR &= ~(0x7F << 9); // reset DIVP
    RCC->CR |= (1 << 24);          // PLL1 ON
    while ((RCC->CR & (1 << 25)) == 0)
        ;

    RCC->D1CFGR &= ~(0b1111);     // reset HPRE
    RCC->D1CFGR |= 0b1000;        // HPRE /2
    RCC->D1CFGR &= ~(0b111 << 4); // reset D1PPRE
    RCC->D1CFGR |= (0b100 << 4);  // D1PPRE /2
    RCC->D2CFGR &= ~(0b111 << 4); // reset D2PPRE
    RCC->D2CFGR |= (0b100 << 4);  // D2PPRE1 /2
    RCC->D2CFGR &= ~(0b111 << 8); // reset D2PPRE
    RCC->D2CFGR |= (0b100 << 8);  // D2PPRE2 /2
    RCC->D3CFGR &= ~(0b111 << 4); // reset D3PPRE
    RCC->D3CFGR |= (0b100 << 4);  // D3PPRE /2

    RCC->CFGR |= 0b011; // PLL1 as sysclk
    while ((RCC->CFGR & (0b011 << 3)) == 0)
        ;
}