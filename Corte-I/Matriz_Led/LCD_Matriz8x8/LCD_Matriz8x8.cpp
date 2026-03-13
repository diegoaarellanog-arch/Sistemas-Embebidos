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
int b = 2;

extern "C"{
	void EXTI15_10_IRQHandler(void){
		Delay(DELAY*3);
		EXTI->PR |= (1<<13); //Down flag
		if(((GPIOC->IDR & (1<<13)) >> 13) == 1){//Read PC13 pin
			if (b == 1){
				b = 2;
				
				SettingsLCD(CD);
				Delay(DELAY * 10);
				prepararMensaje("G43 SAN MATEO");
				PrintDataLCD("G43 SAN MATEO",0);
				b = 2;
				
			}
			else if (b == 2) {
				b = 0;
				
				SettingsLCD(CD);
				Delay(DELAY * 10);
				prepararMensaje("Leon XII");
				PrintDataLCD("Leon XIII",0);
			}
			else {
				b = 1;
				
				SettingsLCD(CD);
				Delay(DELAY * 10);
				prepararMensaje("Terreros");
				PrintDataLCD("Terreros",0);
				
			}
		}
	}
}


int main(){
	
	Init(); // GPIOs
  LCD_Init();
	PrintDataLCD("G43 SAN MATEO",0);
  DisplayShiftRight();
  DisplayShiftLeft();
	
	prepararMensaje("G43 SAN MATEO");
	int miOffset = -24; // Empezamos desde fuera de la pantalla (derecha)
	
	while (1) {
		// 1. Actualizar qué parte del mensaje se ve
    actualizarScroll(miOffset);
		
		// 2. Refrescar la pantalla muchas veces para que el ojo lo vea
		// Entre más veces lo hagas, más lento se moverá el texto
		for(int velocidad = 0; velocidad < 40; velocidad++) {
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
