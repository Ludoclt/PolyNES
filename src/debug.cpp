#include "debug.h"

#include <stm32f4xx.h>

void debugInit()
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN; // enable USART3

    GPIOD->MODER |= (0b10 << (8 << 1));
    GPIOD->MODER |= (0b10 << (9 << 1));

    GPIOD->OSPEEDR |= (0b11 << (8 << 1)) | (0b11 << (9 << 1));
    GPIOD->AFR[1] |= (7 << (0 << 2)); // PD8 TX
    GPIOD->AFR[1] |= (7 << (1 << 2)); // PD9 RX

    USART3->BRR = (7 << 0) | (24 << 4); // Baud rate of 115200, PCLK1 at 45MHz
    USART3->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

char getChar()
{
    while ((USART3->SR & USART_SR_RXNE) == 0)
        ;
    return USART3->DR;
}

void sendChar(char c)
{
    while ((USART3->SR & USART_SR_TXE) == 0)
        ;
    USART3->DR = c;
}

void print(const char *s)
{
    while (*s)
        sendChar(*s++);
}

void println(const char *s)
{
    print(s);
    sendChar('\n');
}