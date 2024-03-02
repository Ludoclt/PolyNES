#include "lcd.h"
#include "tick.h"

LCD::LCD()
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;

    LCD_PORT->MODER &= ~(0x3FFFFFF);
    LCD_PORT->MODER |= (0x1555555); // data pins output

    LCD_PORT->ODR |= (1 << LCD_RST); // RST high
    delay_ms(5);
    LCD_PORT->ODR &= ~(1 << LCD_RST); // RST low
    delay_ms(15);
    LCD_PORT->ODR |= (1 << LCD_RST); // RST high
    delay_ms(15);

    LCD_PORT->ODR |= ((1 << LCD_CS) | (1 << LCD_WR) | (1 << LCD_RD));
    LCD_PORT->ODR &= ~(1 << LCD_CS);

    sendCommand(0xC5); // VCOM control 1 contrast
    sendData(0x7F);    // VCOM H 1111111
    sendData(0x00);    // VCOM L 0000000

    sendCommand(0x36); // Memory Access Control
    sendData(0x48);

    sendCommand(0x3A); // COLMOD: Pixel Format Set
    sendData(0x55);    // 16 Bit RGB and MCU

    sendCommand(0x11); // Sleep Out
    delay_ms(10);

    sendCommand(0x29); // Display on
    sendCommand(0x2C); // Memory Write
}

void LCD::writeByte(uint8_t data)
{
    LCD_PORT->ODR &= ~(1 << LCD_WR); // WR low

    LCD_PORT->ODR &= ~(0xFF);
    LCD_PORT->ODR |= data;

    LCD_PORT->ODR |= (1 << LCD_WR); // WR high
}

void LCD::sendCommand(uint8_t command)
{
    LCD_PORT->ODR &= ~(1 << LCD_RS); // RS low
    writeByte(command);
}

void LCD::sendData(uint8_t data)
{
    LCD_PORT->ODR |= (1 << LCD_RS); // RS high
    writeByte(data);
}

void LCD::setAddress(uint64_t y1, uint16_t y2, uint16_t x1, uint16_t x2)
{
    sendCommand(0x2A); // Column Address Set
    sendData(y1 >> 8);
    sendData(y1);
    sendData(y2 >> 8);
    sendData(y2);

    sendCommand(0x2B); // Page Address Set
    sendData(x1 >> 8);
    sendData(x1);
    sendData(x2 >> 8);
    sendData(x2);

    sendCommand(0x2C); // REG 2Ch = Memory Write
}

void LCD::drawPixel(uint16_t x, uint16_t y, uint16_t color)
{
    LCD_PORT->ODR &= ~(1 << LCD_CS);
    setAddress(y, y + 1, x, x + 1);
    // sendCommand(0x2C);
    sendData(color >> 8);
    sendData(color);
}