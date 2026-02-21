#include "main_init.h"	// Configuracion e inicializacion de placa 
#include "MAX7219.h"		// Control Display Driver 

void main_init(void){
	//-- Configuracion de pines
	GPIOC->MODER = 0x00000000; 					// Reset value 
	//GPIOC->MODER &= ~(0x3F << 20);		// Alterniativa para limpiar unicamente PC12,PC11 y PC10 bits[25:20]
	GPIOC->MODER |= 0x15;								// Pines PC12,PC11 y PC10 como salida (01)
	GPIOC->OTYPER &= ~(0x7 << 10);  		// Pines PC12,PC11 y PC10 como salida push pull (HIGH or LOW)
	GPIOC->OSPEEDR |= (0x3F << 20);			// Pines PC12,PC11 y PC10 en muy alta velocidad
	
	//-- Inicializacion MAX7219
	for(int i = 0; i < N_DISPLAYS; i++) 
	MAX7219_send(MAX7219_MODE_SCANLIMIT, 7); 
	MAX7219_update();										// Escanea las 8 filas conectadas al driver  
	
	for(int i = 0; i < N_DISPLAYS; i++) 
	MAX7219_send(MAX7219_MODE_DECODE, MAX7219_NO_DECODE);
	MAX7219_update();										// Deshabilitamos el decodificador inteligente de números (BCD-Code B)
	
	for(int i = 0; i < N_DISPLAYS; i++) 
	MAX7219_send(MAX7219_MODE_SHUTDOWN, 1);
	MAX7219_update();										// Encendido

	for(int i = 0; i < 8; i++) {
	for(int j = 0; j < N_DISPLAYS; j++) 
	MAX7219_send(i + 1, 0);
	MAX7219_update();										// Limpiamos las pantallas matriciales
	}
}