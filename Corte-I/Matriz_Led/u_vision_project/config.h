#ifndef CONFIG
#define CONFIG

#include "stm32f7xx.h"	// Placa de desarrollo
#include <stdio.h>  		// Standard Input/Output
#include <stdint.h>			// Standard Integer

//-- Direcciones de registro MAX7219
#define MAX7219_MODE_NOP       0b00000000
#define MAX7219_MODE_DECODE    0b00001001
#define MAX7219_MODE_INTENSITY 0b00001010
#define MAX7219_MODE_SCANLIMIT 0b00001011
#define MAX7219_MODE_SHUTDOWN  0b00001100
#define MAX7219_MODE_TEST      0b00001111

//-- Commandos MAX7219 
#define MAX7219_NO_DECODE      0b00000000
#define MAX7219_7SEG_DECODE    0b11111111

//-- Abreviaciones
#define PORT_CLK  	GPIOC
#define PORT_CS			GPIOC
#define PORT_DATA		GPIOC
#define CLK  				12
#define CS 					11
#define DATA 				10
#define SIZE 				56
#define N_DISPLAYS 	3

#define PB0 0
//-- Funciones inline
inline void SetOutPin(uint16_t pin, bool state) { //SetOutPin(PORT, DATA, 1 o 0);
    if (state) GPIOB->BSRR = (1 << pin);        // Set
    else       GPIOB->BSRR = (1 << (pin + 16)); // Reset
}
#endif