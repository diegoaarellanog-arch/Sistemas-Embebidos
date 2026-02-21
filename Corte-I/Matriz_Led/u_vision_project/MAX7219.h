#ifndef MAX7219_H
#define MAX7219_H

#include "config.h"			// Hardward y preferencias
#include "stm32f7xx.h"	// Placa de desarrollo

// Funciones (Prototipos)
void MAX7219_send (unsigned char a, unsigned char d);
void MAX7219_update (void);

#endif






