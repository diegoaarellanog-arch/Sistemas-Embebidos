#ifndef MATRIZ8X8
#define MATRIZ8X8

#include <stdio.h>
#include "stm32f7xx.h"


//--
void prepararMensaje(const char* frase);
void actualizarScroll(int offset);
void refrescarPantalla(void);
	
//-- Mapeo conexiones fisicas
#define MAP_BITS_M(val, p0, b0, p1, b1, p2, b2, p3, b3, p4, b4, p5, b5, p6, b6, p7, b7) do { \
	(val & 0x01) ? (p0->BSRR = (1 << b0)) : (p0->BSRR = (1 << (b0 + 16))); \
	(val & 0x02) ? (p1->BSRR = (1 << b1)) : (p1->BSRR = (1 << (b1 + 16))); \
	(val & 0x04) ? (p2->BSRR = (1 << b2)) : (p2->BSRR = (1 << (b2 + 16))); \
	(val & 0x08) ? (p3->BSRR = (1 << b3)) : (p3->BSRR = (1 << (b3 + 16))); \
	(val & 0x10) ? (p4->BSRR = (1 << b4)) : (p4->BSRR = (1 << (b4 + 16))); \
	(val & 0x20) ? (p5->BSRR = (1 << b5)) : (p5->BSRR = (1 << (b5 + 16))); \
	(val & 0x40) ? (p6->BSRR = (1 << b6)) : (p6->BSRR = (1 << (b6 + 16))); \
	(val & 0x80) ? (p7->BSRR = (1 << b7)) : (p7->BSRR = (1 << (b7 + 16))); \
} while(0)
#define M_FIL(v) MAP_BITS_M(v, GPIOG, 15, GPIOG, 1, GPIOG, 13, GPIOE, 1, GPIOF, 8, GPIOG, 10, GPIOF, 9, GPIOE, 6)
#define M3_COL(v) MAP_BITS_M(v, GPIOF, 12, GPIOF, 13, GPIOG, 14, GPIOD, 10, GPIOG, 4, GPIOG, 7, GPIOE, 13, GPIOE, 15)
#define M2_COL(v) MAP_BITS_M(v, GPIOA, 10, GPIOA, 4, GPIOG, 3, GPIOD, 13, GPIOC, 0, GPIOA, 3, GPIOB, 5, GPIOB, 10)
#define M1_COL(v) MAP_BITS_M(v, GPIOB, 9, GPIOB, 6, GPIOC, 7, GPIOA, 6, GPIOA, 9, GPIOA, 5, GPIOB, 8, GPIOC, 9)


#endif

