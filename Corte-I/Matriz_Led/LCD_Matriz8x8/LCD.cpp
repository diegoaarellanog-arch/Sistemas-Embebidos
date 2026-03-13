#include "init.h"
#include "config.h"
#include "LCD.h"
#include "stm32f7xx.h"
#include <string.h>



void LCDdata(unsigned char data){
    // LIMPIEZA ATÓMICA: Bajamos los 4 pines de datos antes de cargar el nuevo nibble
    D4P->BSRR = (1 << (D4 + 16)); 
    D5P->BSRR = (1 << (D5 + 16)); 
    D6P->BSRR = (1 << (D6 + 16)); 
    D7P->BSRR = (1 << (D7 + 16)); 

    // CARGA DE DATOS
    if (data & 0x01) D4P->BSRR = (1 << D4);
    if (data & 0x02) D5P->BSRR = (1 << D5);
    if (data & 0x04) D6P->BSRR = (1 << D6);
    if (data & 0x08) D7P->BSRR = (1 << D7);
    
    // TIEMPO DE ASENTAMIENTO (Setup time)
    Delay(DELAY); 
    
    SetOutPin(EP, E, 1);  
    Delay(DELAY);   // Pulso de Enable
    SetOutPin(EP, E, 0);  
    Delay(DELAY);   // Hold time
}

void SettingsLCD(unsigned char word){
	SetOutPin(RSP, RS, 0);
	
	LCDdata(word >> 4); //4MSB
	LCDdata(word & 0x0F); //4LSB
}

void WriteLCDdata(unsigned char word){
	SetOutPin(RSP, RS, 1);
	
	LCDdata(word >> 4); //4MSB
	LCDdata(word & 0x0F); //4LSB
}

void PrintDataLCD(const char* string, int a){
    SettingsLCD(RAW1 + a);
    for(int i = 0; i < strlen(string); i++) {
        WriteLCDdata(string[i]);
    }
}
void DisplayShiftRight(void){
	for(int i = 0; i <= 3; i++){
		SettingsLCD(DSr);
		Delay(DELAY*10);
  }
}

void DisplayShiftLeft(void){
	for(int i = 0; i <= 3; i++){
		SettingsLCD(DSl);
		Delay(DELAY*10);
	}
}

void LCD_Init(void) {
    // 1. Dale un respiro al encender
    Delay(DELAY * 100); 

    // 2. Triple Reset (Sincronización en modo 8-bits)
    LCDdata(0x03); Delay(DELAY * 20);
    LCDdata(0x03); Delay(DELAY * 10);
    LCDdata(0x03); Delay(DELAY * 10);

    // 3. PASO CRÍTICO: Entrar a modo 4-bits
    // Usamos LCDdata directamente porque la LCD espera UN SOLO nibble aquí
    LCDdata(0x02); 
    Delay(DELAY * 10);

    // 4. A partir de aquí, la LCD ya entiende nibbles dobles
    SettingsLCD(FS);   // Function Set (ej. 0x28)
    SettingsLCD(EMS);  // Entry Mode Set
    SettingsLCD(DC);   // Display Control
    SettingsLCD(CD);   // Clear Display
    Delay(DELAY * 100); // El borrado necesita mucho más tiempo
}