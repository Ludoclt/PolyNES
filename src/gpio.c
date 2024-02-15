#include "gpio.h"

void setPinMode(GPIO_TypeDef *port, uint8_t pin, uint8_t mode)
{
    port->MODER &= ~(0b11 << (pin << 1)); // reset mode
    port->MODER |= (mode << (pin << 1));  // set pin mode
}

void setPinAF(GPIO_TypeDef *port, uint8_t pin, uint8_t af_mode)
{
    port->MODER &= ~(0b11 << (pin << 1));
    port->MODER |= (0b10 << (pin << 1));
    port->OSPEEDR &= ~(0b11 << (pin << 1));
    port->OSPEEDR |= (0b10 << (pin << 1));
    port->AFR[pin > 7 ? 1 : 0] &= ~(0b1111 << (pin << 2));
    port->AFR[pin > 7 ? 1 : 0] |= (af_mode << (pin << 2));
}