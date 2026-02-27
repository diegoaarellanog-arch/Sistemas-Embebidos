// Taller 1 – LCD Y MATRIZ DE LEDS 8x8 
// Arellano Diego & Fajardo JeanPierre
// Universidad ECCI
// STM32F767ZIT6U

#include <stdio.h>
#include "stm32f7xx.h"
#include "init.h"
#include "Matrix8x8.h"


int main(){
	Init(); 									// Configuracion de puertos GPIOs

	unsigned char txt = 'i'; 	// Texto a imprimir
	int posicion = 0; 				// Posicion del texto a imprimier 
	int	repeticion = 0; 			// # Repetiociones por impresion, 
	
	while(1){
		for(int i = 0; i < Fuente4x8[txt].ancho; i++){
			M_FIL(Fuente4x8[txt].datos[i]);
			M2_COL((0b01 << i) << posicion);
			M3_COL(((0b01 << i) << posicion) >> 8);
			Delay(50);
			M_FIL(0); M3_COL(0);
		}
		
		if(repeticion >10000) { // modifica la velocidad de desplazamiento del texto
			repeticion = 0;

			if (posicion < BUFFER)
				posicion ++;
			else
				posicion = 0;
		}
		else {
			repeticion++;
		}
		
		
	}
}
