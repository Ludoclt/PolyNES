#ifndef LCD_H
#define LCD_H

#include <stm32f4xx.h>

#define LCD_PORT GPIOF

#define LCD_RST 8
#define LCD_CS 9
#define LCD_RS 10
#define LCD_WR 11
#define LCD_RD 12

class LCD
{
public:
    LCD();

    void writeByte(uint8_t data);
    void sendCommand(uint8_t command);
    void sendData(uint8_t data);
    void setAddress(uint64_t y1, uint16_t y2, uint16_t x1, uint16_t x2);
    void drawPixel(uint16_t x, uint16_t y, uint16_t color);
};

#endif