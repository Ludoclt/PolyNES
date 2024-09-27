#include <stm32h750xx.h>
#include "clock.h"
#include "tick.h"

#define SYSTEM_CLOCK_SPEED 480

int main()
{
    SystemClock_Init();
    SysTick_Init(SYSTEM_CLOCK_SPEED);

    RCC->AHB4ENR |= (1 << 2);             // enable GPIOC
    GPIOC->MODER &= ~(0b11 << (13 << 1)); // reset pin PC13
    GPIOC->MODER |= (0b01 << (13 << 1));
    GPIOC->OSPEEDR &= ~(0b11 << (13 << 1));
    GPIOC->OSPEEDR |= (0b10 << (13 << 1));

    while (1)
    {
        // GPIOC->BSRR |= ((1 << 15) << 13); // reset
        // Delay_ms(1000);
        // GPIOC->BSRR |= (1 << 13); // set
        // Delay_ms(1000);

        GPIOC->ODR &= ~(1 << 13); // reset
        Delay_ms(1000);
        GPIOC->ODR |= (1 << 13); // set
        Delay_ms(1000);
    }

    return 0;
}
