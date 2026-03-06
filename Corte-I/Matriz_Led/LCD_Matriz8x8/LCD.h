#ifndef LCD
#define LCD

#include <stdio.h>
#include "init.h"
#include "stm32f7xx.h"

void SettingsLCD(unsigned char word);
void LCDdata(unsigned char data);
void WriteLCD(unsigned char word);
void DisplayShiftRight(void);
void DisplayShiftLeft(void);
void LCD_Init(void);
void PrintDataLCD(const char* string);
	
#define MAP_BITS_L(val, p0, b0, p1, b1, p2, b2, p3, b3) do { \
	(val & 0x01) ? (p0->BSRR = (1 << b0)) : (p0->BSRR = (1 << (b0 + 16))); \
	(val & 0x02) ? (p1->BSRR = (1 << b1)) : (p1->BSRR = (1 << (b1 + 16))); \
	(val & 0x04) ? (p2->BSRR = (1 << b2)) : (p2->BSRR = (1 << (b2 + 16))); \
	(val & 0x08) ? (p3->BSRR = (1 << b3)) : (p3->BSRR = (1 << (b3 + 16))); \
} while(0)

#define LCD_DATA(v) MAP_BITS_L(v, GPIOE, 3, GPIOE, 5, GPIOF, 1, GPIOF, 0)
//#define LCD_DATA(v) MAP_BITS_L(v, GPIOA, 1, GPIOA,0, GPIOC, 13, GPIOB, 7)
#endif 

