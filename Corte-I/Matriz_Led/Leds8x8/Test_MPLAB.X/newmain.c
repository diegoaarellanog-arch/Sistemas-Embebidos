/*
 * File:   main.c
 * Proyecto: Control Matriz 8x24 (3 x MAX7219)
 */

#include <xc.h>
#include <stdint.h>

// --- CONFIGURACIÓN DEL MICRO (PIC16F1455) ---
#pragma config FOSC = INTOSC, WDTE = OFF, PWRTE = OFF, MCLRE = OFF, CP = OFF
#pragma config BOREN = OFF, CLKOUTEN = OFF, IESO = OFF, FCMEN = OFF
#pragma config WRT = OFF, CPUDIV = CLKDIV6, USBLSCLK = 48MHz, PLLMULT = 3x
#pragma config PLLEN = ENABLED, STVREN = ON, BORV = LO, LPBOR = OFF, LVP = OFF

#define _XTAL_FREQ 48000000 // Frecuencia de trabajo para retardos

// --- MAPEO DE PINES (Basado en tu esquema de Proteus) ---
#define DATA LATCbits.LATC5   // Pin RC5 -> DIN
#define LOAD LATCbits.LATC4   // Pin RC4 -> LOAD/CS
#define CLK  LATCbits.LATC3   // Pin RC3 -> CLK

// Registros de control del MAX7219
#define REG_DECODE    0x09
#define REG_INTENSITY 0x0A
#define REG_SCANLIMIT 0x0B
#define REG_SHUTDOWN  0x0C

// --- FUNCIONES DE COMUNICACIÓN ---

// Envía un paquete de 16 bits (8 dir + 8 datos)
void MAX_Send(uint8_t address, uint8_t data) {
    uint16_t packet = ((uint16_t)address << 8) | data;
    for (int i = 15; i >= 0; i--) {
        DATA = (packet >> i) & 1;
        CLK = 1;
        __delay_us(1); // Pulso pequeño de reloj
        CLK = 0;
    }
}

// Pulso en LOAD para aplicar los datos en toda la cadena (cascada)
void MAX_Update(void) {
    LOAD = 1;
    __delay_us(1);
    LOAD = 0;
}

// Inicializa los 3 chips en la cadena
void Init_Matrix(void) {
    for(int i=0; i<3; i++) MAX_Send(REG_SCANLIMIT, 0x07); // Escanear 8 filas
    MAX_Update();
    for(int i=0; i<3; i++) MAX_Send(REG_DECODE, 0x00);    // Modo matriz (no 7-seg)
    MAX_Update();
    for(int i=0; i<3; i++) MAX_Send(REG_INTENSITY, 0x07); // Brillo medio
    MAX_Update();
    for(int i=0; i<3; i++) MAX_Send(REG_SHUTDOWN, 0x01);  // Encender
    MAX_Update();
}

void main(void) {
    // Configuración de puertos
    TRISC = 0x00;   // Todo puerto C como salida
    ANSELC = 0;     // Desactivar funciones analógicas
    TRISA = 0xFF;   // Puerto A como entrada
    ANSELA = 0;

    Init_Matrix();

    while (1) {
        // Ejemplo: Encender una diagonal que recorre las 3 matrices
        for (uint8_t f = 1; f <= 8; f++) {
            MAX_Send(f, (1 << (f-1))); // Datos para Panel 3 (último)
            MAX_Send(f, (1 << (f-1))); // Datos para Panel 2 (medio)
            MAX_Send(f, (1 << (f-1))); // Datos para Panel 1 (primero)
            MAX_Update();
            __delay_ms(50);
        }
    }
}