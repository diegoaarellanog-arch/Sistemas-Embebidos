#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include "stm32f7xx.h"

#define PB0 0
void Delay (uint32_t time);
void Init (void);

#define PB0 7
#define LED3 14

//-- Funciones inline
inline void SetOutPin(GPIO_TypeDef* GPIOx, uint16_t pin, bool state) { //SetOutPin(PORT, DATA, 1 o 0);
    if (state) GPIOx->BSRR = (1 << pin);        // Set
    else       GPIOx->BSRR = (1 << (pin + 16)); // Reset
}

#endif