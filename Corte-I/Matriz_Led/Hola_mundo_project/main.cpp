//Ejemplo Hola mundo con led de usuario de la tarjeta
//Fabi�n Barrera Prieto
//Universidad ECCI
//STM32F767ZIT6U
//operation 'or' (|) for set bit and operation 'and' (&) for clear bit

#include <stdio.h>
#include "stm32f7xx.h"
#include "init.h"

int main(){
	Init();

	while(1){
		
		SetOutPin(GPIOB, PB0, 1);
		SetOutPin(GPIOB, LED3, 0);
		//GPIOB->BSRR |= (1<<0); // Set the Pin PB0
		//GPIOB->ODR |= 1<<0; // Set the Pin PB0
		Delay(100000);
		
		SetOutPin(GPIOB, PB0, 0);
		SetOutPin(GPIOB, LED3, 1);
		//GPIOB->BSRR |= (1<<16); // Reset the Pin PB0
		//GPIOB->ODR &= ~(1<<0); // Reset the Pin PB0
		Delay(100000);
	}
}