#include "init.h"

void Delay (uint32_t time)
{
	//while (time--);  
	for (int t = 0; (uint32_t)t < time; t++);

}

void Init (void) {
	RCC->AHB1ENR |= (0x7F << 0); 								// Habilitamos puertos C, D, E, F y G
		
	GPIOA->MODER |= 0x55555555 & ~(0x3F << 26); // Puerto A habilitado como salida (ignora PA13-PA15)
	GPIOB->MODER |= 0x55555555 & ~(0xA  <<  6); // Puerto A habilitado como salida (ignora PB3-PB4)
	GPIOC->MODER = 0x55555555; 								// Puerto C habilitado como salida
	GPIOD->MODER = 0x55555555; 								// Puerto D habilitado como salida
	GPIOE->MODER = 0x55555555; 								// Puerto E habilitado como salida
	GPIOF->MODER = 0x55555555;						 			// Puerto F habilitado como salida
	GPIOG->MODER = 0x55555555;						 			// Puerto G habilitado como salida
		
	GPIOA->OTYPER &= 0x0000;  									// Puerto A configurado en salida push-pull
	GPIOB->OTYPER &= 0x0000;						  			// Puerto B configurado en salida push-pull
	GPIOC->OTYPER &= 0x0000;						  			// Puerto C configurado en salida push-pull
	GPIOD->OTYPER &= 0x0000;						  			// Puerto D configurado en salida push-pull
	GPIOE->OTYPER &= 0x0000;  									// Puerto E configurado en salida push-pull
	GPIOF->OTYPER &= 0x0000;						  			// Puerto F configurado en salida push-pull
	GPIOG->OTYPER &= 0x0000;  									// Puerto G configurado en salida push-pull
	
	GPIOA->OSPEEDR = 0xFFFFFFFF;								// Puerto A configurado en muy alta velocidad 
	GPIOB->OSPEEDR = 0xFFFFFFFF;								// Puerto B configurado en muy alta velocidad 
	GPIOC->OSPEEDR = 0xFFFFFFFF;								// Puerto C configurado en muy alta velocidad 
	GPIOD->OSPEEDR = 0xFFFFFFFF;								// Puerto D configurado en muy alta velocidad 
	GPIOE->OSPEEDR = 0xFFFFFFFF;								// Puerto E configurado en muy alta velocidad 
	GPIOF->OSPEEDR = 0xFFFFFFFF;								// Puerto F configurado en muy alta velocidad 
	GPIOG->OSPEEDR = 0xFFFFFFFF;								// Puerto G configurado en muy alta velocidad 
	
	GPIOA->PUPDR = 0;														// Puerto C configurado en no pull-up,pull down
	GPIOB->PUPDR = 0;														// Puerto C configurado en no pull-up,pull down
	GPIOC->PUPDR = 0;														// Puerto C configurado en no pull-up,pull down
	GPIOD->PUPDR = 0;														// Puerto D configurado en no pull-up,pull down
	GPIOE->PUPDR = 0;														// Puerto E configurado en no pull-up,pull down
	GPIOF->PUPDR = 0;														// Puerto F configurado en no pull-up,pull down
	GPIOG->PUPDR = 0;														// Puerto G configurado en no pull-up,pull down
	
	GPIOA->ODR = 0x0;														// 0 logico en puerto A	
	GPIOB->ODR = 0x0;														// 0 logico en puerto B	
	GPIOC->ODR = 0x0;														// 0 logico en puerto C	
	GPIOD->ODR = 0x0;														// 0 logico en puerto D
	GPIOE->ODR = 0x0;														// 0 logico en puerto E
	GPIOF->ODR = 0x0;														// 0 logico en puerto F
	GPIOG->ODR = 0x0;														// 0 logico en puerto G
}
