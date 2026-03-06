// Taller 1 – LCD Y MATRIZ DE LEDS 8x8 
// Arellano Diego & Fajardo JeanPierre
// Universidad ECCI
// STM32F767ZIT6U

#include <stdio.h>
#include "stm32f7xx.h"
#include "config.h"
#include "init.h"
#include "LCD.h"
#include "Matrix8x8.h"

uint8_t bufferMensaje[200] = {0};			// El texto completo 
uint8_t bufferPantalla[24] = {0};     // Lo que se ve impreso
int longitudMensaje = 0;              // Cuántas columnas ocupa la frase
int b = 0;

extern "C"{
	void EXTI15_10_IRQHandler(void){
		EXTI->PR |= (1<<13); //Down flag
		if(((GPIOC->IDR & (1<<13)) >> 13) == 1){//Read PC13 pin
			if (b == 1){
				prepararMensaje("Aguas y Universidades");
				b = 0;
			}
			else {
				prepararMensaje("Marly y Calle 45");
				b = 1;
			}
		}
	}
}

int main(){
	
	Init(); // GPIOs
  LCD_Init();
	PrintDataLCD("Aguas y Universidades");
  DisplayShiftRight();
  DisplayShiftLeft();
	
	prepararMensaje("Proximas paradas: Aguas y Universidades");
	int miOffset = -24; // Empezamos desde fuera de la pantalla (derecha)
	
	while (1) {
		// 1. Actualizar qué parte del mensaje se ve
    actualizarScroll(miOffset);
		
		// 2. Refrescar la pantalla muchas veces para que el ojo lo vea
		// Entre más veces lo hagas, más lento se moverá el texto
		for(int velocidad = 0; velocidad < 150; velocidad++) {
			refrescarPantalla(); // La función que te pasé antes
		}

		// 3. Mover el texto a la izquierda
		miOffset++;
        
    // 4. Reiniciar si el mensaje ya pasó todo
		if (miOffset > longitudMensaje) {
			miOffset = -24;
		}
    }
}
