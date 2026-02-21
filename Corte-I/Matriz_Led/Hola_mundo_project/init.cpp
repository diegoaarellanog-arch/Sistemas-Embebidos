#include "init.h"

void Delay (uint32_t time)
{
	//while (time--);  
	for (uint32_t t = 0; t < time; t++);
}

void Init (void) {
	RCC->AHB1ENR |= (1<<1); //Enable the GPIOB clock (user led LD1 is connected to PB0)
	//RCC->AHB1ENR |= (1<<2); //Enable the GPIOC clock (user push button B1 is connected to PC13)
	
	GPIOB->MODER &= ~(0b11<<14); //clear (00) pin PB0(bits 1:0) and set as Input (00) for default 
	GPIOB->MODER |= (1<<14); //pin PB0(bits 1:0) as Output (01)
	GPIOB->MODER |= (1<<28); //pin PB0(bits 1:0) as Output (01)
	
	GPIOB->OTYPER &= ~(1<<7);  // clear (0) pin PB0 (bit 0) --> Output push pull (HIGH or LOW)
	GPIOB->OTYPER &= ~(1<<14);  // clear (0) pin PB0 (bit 0) --> Output push pull (HIGH or LOW)
	GPIOB->OSPEEDR |= ((1<<15)|(1<<14));//(0b11<<0)  // Pin PB0 (bits 1:0) as Very High Speed (11)
	GPIOB->OSPEEDR |= ((1<<28)|(1<<29));//(0b11<<0)  // Pin PB0 (bits 1:0) as Very High Speed (11)
	GPIOB->PUPDR &= ~(0b11<<14); //~((1<<1)|(1<<0)) // Pin PB0 (bits 1:0) are 0:0 --> no pull up or pull down
	GPIOB->PUPDR &= ~(0b11<<28); //~((1<<1)|(1<<0)) // Pin PB0 (bits 1:0) are 0:0 --> no pull up or pull down
}