#include "MAX7219.h"		// Control Display Driver 

void MAX7219_send (unsigned char a, unsigned char d) {
	for (int i = 7; i >= 0; i--) {
		SetOutPin(PORT_CS, CS, (a >> i) & 1);			// Enviamos byte de direccion, MSB hacia LSB
		SetOutPin(PORT_CLK, CLK, 1); 							// Pulso de reloj
		SetOutPin(PORT_CLK, CLK, 0);
	}
	
	for (int i=7; i>=0; i--) {
		SetOutPin(PORT_DATA, DATA, (d >> i) & 1);	// Enviamos byte de datos, MSB hacia LSB
    SetOutPin(PORT_CLK, CLK, 1); 							// Pulso de reloj
		SetOutPin(PORT_CLK, CLK, 0);
	}
	
	SetOutPin(PORT_DATA, DATA, 0);							// Limpiamos el pin asignado a DATA
}

void MAX7219_update (void) {
	SetOutPin(PORT_CS, CS, 1); 									// Pulso para imprimir en el/los display/s
	SetOutPin(PORT_CS, CS, 0);
}