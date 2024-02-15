#ifndef GPIO_H
#define GPIO_H

#include <stm32f4xx.h>

#ifdef __cplusplus
extern "C"
{
#endif

    void setPinMode(GPIO_TypeDef *port, uint8_t pin, uint8_t mode);
    void setPinAF(GPIO_TypeDef *port, uint8_t pin, uint8_t af_mode);

#ifdef __cplusplus
}
#endif

#endif