/* Taller I Sistemas Embebidos
 * LCD Y MATRIZ DE LEDS 8x8 
 * Diego Alejandro Arellano Gutierrez 
 * Universidad ECCI
 * STM32F767ZIT6U
 */

/**********************************************************************
 * LIBRERIAS
 **********************************************************************/
#include <stdio.h>  		// Standard Input/Output
#include <stdint.h>			// Standard Integer
#include "config.h"			// Hardward y preferencias
#include "MAX7219.h"		// Control Display Driver 
#include "stm32f7xx.h"	// Placa de desarrollo
#include "main_init.h"	// Configuracion e inicializacion de placa y perifericos

/**********************************************************************
 * PARAMETROS (CONSTANTES Y VARIABLES)
 **********************************************************************/
const unsigned char imagen_8x32[SIZE] = {
		0b00001111, 0b00000111, 0b00000011, 0b11111111, 0b11111111, 0b00001111, 0b00000111, // Fila 8
		0b00001111, 0b00000111, 0b00000011, 0b01111111, 0b11111110, 0b00001111, 0b00000111,// Fila 7
		0b00001111, 0b00000111, 0b00000011, 0b00111111, 0b11111100, 0b00001111, 0b00000111,// Fila 6
		0b00001111, 0b00000111, 0b00000011, 0b00011111, 0b11111000, 0b00001111, 0b00000111, // Fila 5
		0b00001111, 0b00000111, 0b00000011, 0b00001111, 0b11110000, 0b00001111, 0b00000111,// Fila 4
		0b00001111, 0b00000111, 0b00000011, 0b00000111, 0b11100000, 0b00001111, 0b00000111,// Fila 3
		0b00001111, 0b00000111, 0b00000011, 0b00000011, 0b11000000, 0b00001111, 0b00000111,// Fila 2
		0b00001111, 0b00000111, 0b00000011, 0b00000001, 0b10000000, 0b00001111, 0b00000111 // Fila 1
};

/**********************************************************************
 * MAIN
 **********************************************************************/
int main(){
	main_init();
	uint8_t registro = 0;
	unsigned char idx = 0;
	int pos = 0, corrimiento = 0, duracion = 0, n_columnas = (SIZE/8), desplazamiento;
	
	// Main loop
	while (1) {
		for(int i = 0; i < 8; i++) {
			registro = 8 - i;
			desplazamiento = i*n_columnas;
			
			for(int j = 0; j < N_DISPLAYS; j++) {
				idx = desplazamiento + j + pos;
				MAX7219_send(registro, (imagen_8x32[idx] << corrimiento) | (imagen_8x32[idx+ 1] >> (8 - corrimiento)) );
			}
			
			MAX7219_update();
		}
		
		if(duracion <= 2) {
			duracion++;
		}
		else {
			duracion = 0;
			corrimiento++; // Aumentamos el bit de desplazamiento
			
			if(corrimiento >= 8) { // ¡Cambiamos de byte!
				corrimiento = 0;
				pos++; 
				
				// Si llegamos al final del mensaje, reiniciamos pos
				if(pos > (7 - N_DISPLAYS)) { 
					pos = 0;
				}
			}
		}
	}
}