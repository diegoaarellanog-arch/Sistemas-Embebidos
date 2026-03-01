#include "init.h"

void Delay(uint32_t ms) {
    // 216000 es aprox 1ms si el reloj es 216MHz
    // Ajusta este valor según tu velocidad real
    uint32_t ciclos = ms * 54000; 
    for (volatile uint32_t i = 0; i < ciclos; i++);
}

void Delay_LCD(uint32_t ms) {
    // Multiplicamos por un valor mucho más alto para asegurar que la LCD respire
    uint32_t ciclos = ms * 100000; 
    for(volatile int i = 0; i < ms; i++); // Un mini delay manual sin usar tu función ms
}

void Init (void) {
	RCC->AHB1ENR |= (0x7F << 0); 								// Habilitamos puertos C, D, E, F y G
	RCC->APB2ENR |= (1<<14); 										//Enable the SYSCFG clock (EXTI)
		
	GPIOA->MODER |= 0x55555555 & ~(0x3F << 26); // Puerto A habilitado como salida (ignora PA13-PA15)
	GPIOB->MODER |= 0x55555555 & ~(0xA  <<  6); // Puerto A habilitado como salida (ignora PB3-PB4)
	GPIOC->MODER = 0x55555555; 									// Puerto C habilitado como salida
	GPIOD->MODER = 0x55555555; 									// Puerto D habilitado como salida
	GPIOE->MODER = 0x55555555; 									// Puerto E habilitado como salida
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
	

	SYSCFG->EXTICR[3] &= ~(0b1111<<4); //Clear bits [7:0] (Px13)
	SYSCFG->EXTICR[3] |= (1<<5); //Select the pin 13 on port C like interrupt [7:0]=0010 (PC13)
	EXTI->IMR |= (1<<13); //Enable the interrupt on pin 13
	EXTI->RTSR |= (1<<13); //Select rising edge for interrupt
	NVIC_EnableIRQ(EXTI15_10_IRQn); //Enable the interrupt function on the NVIC module
}
