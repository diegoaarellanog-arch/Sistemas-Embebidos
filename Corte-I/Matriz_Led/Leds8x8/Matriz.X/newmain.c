/*
 * File:   main.c
 * Author: boos
 *
 * Created on 17. September 2021, 03:49
 */

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover Mode (Internal/External Switchover Mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config CPUDIV = CLKDIV6 // CPU System Clock Selection Bit (CPU system clock divided by 6)
#pragma config USBLSCLK = 48MHz // USB Low SPeed Clock Selection bit (System clock expects 48 MHz, FS/LS USB CLKENs divide-by is set to 8.)
#pragma config PLLMULT = 3x     // PLL Multipler Selection Bit (3x Output Frequency Selected)
#pragma config PLLEN = ENABLED  // PLL Enable Bit (3x or 4x PLL Enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

#include <xc.h>

// define MAX7219 register addresses (for convenience)
#define MAX7219_MODE_NOP       0b00000000
#define MAX7219_MODE_DECODE    0b00001001
#define MAX7219_MODE_INTENSITY 0b00001010
#define MAX7219_MODE_SCANLIMIT 0b00001011
#define MAX7219_MODE_SHUTDOWN  0b00001100
#define MAX7219_MODE_TEST      0b00001111

// define MAX7219 commands (for convenience)
#define MAX7219_NO_DECODE      0b00000000
#define MAX7219_7SEG_DECODE    0b11111111

// define functions
void MAX7219_send (unsigned char a, unsigned char d);
void MAX7219_update (void);

// default brightness
unsigned char brt = 15;

// abbreviations for convenience
#define SW1  RA5
#define LED  RC2
#define DATA RC5
#define LOAD RC4
#define CLK  RC3
#define SIZE 56
#define NDISPLAYS 3



// main function
void main (void) {
    // Variable que contiene tus datos exactos para 4 matrices en cascada
    const unsigned char imagen_8x32[SIZE] = {
        // {Matriz_4,  Matriz_3,  Matriz_2,  Matriz_1}
        0b00001111, 0b00000111, 0b00000011, 0b11111111, 0b11111111, 0b00001111, 0b00000111, // Fila 8
        0b00001111, 0b00000111, 0b00000011, 0b01111111, 0b11111110, 0b00001111, 0b00000111,// Fila 7
        0b00001111, 0b00000111, 0b00000011, 0b00111111, 0b11111100, 0b00001111, 0b00000111,// Fila 6
        0b00001111, 0b00000111, 0b00000011, 0b00011111, 0b11111000, 0b00001111, 0b00000111, // Fila 5
        0b00001111, 0b00000111, 0b00000011, 0b00001111, 0b11110000, 0b00001111, 0b00000111,// Fila 4
        0b00001111, 0b00000111, 0b00000011, 0b00000111, 0b11100000, 0b00001111, 0b00000111,// Fila 3
        0b00001111, 0b00000111, 0b00000011, 0b00000011, 0b11000000, 0b00001111, 0b00000111,// Fila 2
        0b00001111, 0b00000111, 0b00000011, 0b00000001, 0b10000000, 0b00001111, 0b00000111 // Fila 1
    };
    
	// set up port RA5 for the pushbutton
	
	// it is an input
    TRISA5 = 1;
	
	// enable weak pull-up resistors
    WPUA5 = 1;
    nWPUEN = 0;
    
	
	// set up ports RC2, RC3, RC4, and RC5 to control the MAX7219
	
	// they are all outputs
    TRISC5 = 0;
    TRISC4 = 0;
    TRISC3 = 0;
    TRISC2 = 0;
    
	// disable analog features on ports RC2 and RC3
    ANSC2 = 0;
    ANSC3 = 0;
    
	
	// set up the four MAX7219's of the 8x32 dot matrix module
	
    // scan all eight rows
    MAX7219_send(MAX7219_MODE_SCANLIMIT, 7);
	MAX7219_send(MAX7219_MODE_SCANLIMIT, 7);
	MAX7219_send(MAX7219_MODE_SCANLIMIT, 7);
	MAX7219_send(MAX7219_MODE_SCANLIMIT, 7);
    MAX7219_update();
    
    // set MAX7219 to no-decoding mode
	// (we are specifying the pattern manually)
    MAX7219_send(MAX7219_MODE_DECODE, MAX7219_NO_DECODE);
	MAX7219_send(MAX7219_MODE_DECODE, MAX7219_NO_DECODE);
	MAX7219_send(MAX7219_MODE_DECODE, MAX7219_NO_DECODE);
	MAX7219_send(MAX7219_MODE_DECODE, MAX7219_NO_DECODE);
    MAX7219_update();
    
    // set MAX7219 brightness to maximum
    // (any number from 0-15 works)
    MAX7219_send(MAX7219_MODE_INTENSITY, 15);
	MAX7219_send(MAX7219_MODE_INTENSITY, 15);
	MAX7219_send(MAX7219_MODE_INTENSITY, 15);
	MAX7219_send(MAX7219_MODE_INTENSITY, 15);
    MAX7219_update();
    
    // turn ON
    MAX7219_send(MAX7219_MODE_SHUTDOWN, 1);
	MAX7219_send(MAX7219_MODE_SHUTDOWN, 1);
	MAX7219_send(MAX7219_MODE_SHUTDOWN, 1);
	MAX7219_send(MAX7219_MODE_SHUTDOWN, 1);
    MAX7219_update();

    // clear all dot matrix displays
    MAX7219_send(1, 0); MAX7219_send(1, 0); MAX7219_send(1, 0); MAX7219_send(1, 0); MAX7219_update();
    MAX7219_send(2, 0); MAX7219_send(2, 0); MAX7219_send(2, 0); MAX7219_send(2, 0); MAX7219_update();
    MAX7219_send(3, 0); MAX7219_send(3, 0); MAX7219_send(3, 0); MAX7219_send(3, 0); MAX7219_update();
    MAX7219_send(4, 0); MAX7219_send(4, 0); MAX7219_send(4, 0); MAX7219_send(4, 0); MAX7219_update();
    MAX7219_send(5, 0); MAX7219_send(5, 0); MAX7219_send(5, 0); MAX7219_send(5, 0); MAX7219_update();
    MAX7219_send(6, 0); MAX7219_send(6, 0); MAX7219_send(6, 0); MAX7219_send(6, 0); MAX7219_update();
    MAX7219_send(7, 0); MAX7219_send(7, 0); MAX7219_send(7, 0); MAX7219_send(7, 0); MAX7219_update();
    MAX7219_send(8, 0); MAX7219_send(8, 0); MAX7219_send(8, 0); MAX7219_send(8, 0); MAX7219_update();
    
    
    uint8_t registro = 0;
    unsigned char idx = 0;
    int pos = 0, corrimiento = 0, duracion = 0, n_columnas = (SIZE/8), desplazamiento;
        
    // main loop
    while (1) {
    
	
		// increase brightness if the button is pressed
        if (!SW1) {
            LED = 1;
            brt += 1;
            if (brt > 15) {
                brt = 0;
            }
        } else {
            LED = 0;
        }
    
	
        // update the brightness
        MAX7219_send(MAX7219_MODE_INTENSITY, brt);
		MAX7219_send(MAX7219_MODE_INTENSITY, brt);
		MAX7219_send(MAX7219_MODE_INTENSITY, brt);
		MAX7219_send(MAX7219_MODE_INTENSITY, brt);
        MAX7219_update();
    
		/*
        // send out sample data
        MAX7219_send(8, 0b00001111); MAX7219_send(8, 0b00000111); MAX7219_send(8, 0b00000011); MAX7219_send(8, 0b11111111); MAX7219_update();
        MAX7219_send(7, 0b00001111); MAX7219_send(7, 0b00000111); MAX7219_send(7, 0b00000011); MAX7219_send(7, 0b01111111); MAX7219_update();
		MAX7219_send(6, 0b00001111); MAX7219_send(6, 0b00000111); MAX7219_send(6, 0b00000011); MAX7219_send(6, 0b00111111); MAX7219_update();
		MAX7219_send(5, 0b00001111); MAX7219_send(5, 0b00000111); MAX7219_send(5, 0b00000011); MAX7219_send(5, 0b00011111); MAX7219_update();
		MAX7219_send(4, 0b00001111); MAX7219_send(4, 0b00000111); MAX7219_send(4, 0b00000011); MAX7219_send(4, 0b00001111); MAX7219_update();
		MAX7219_send(3, 0b00001111); MAX7219_send(3, 0b00000111); MAX7219_send(3, 0b00000011); MAX7219_send(3, 0b00000111); MAX7219_update();
		MAX7219_send(2, 0b00001111); MAX7219_send(2, 0b00000111); MAX7219_send(2, 0b00000011); MAX7219_send(2, 0b00000011); MAX7219_update();
        MAX7219_send(1, 0b00001111); MAX7219_send(1, 0b00000111); MAX7219_send(1, 0b00000011); MAX7219_send(1, 0b00000001); MAX7219_update();
       */
        /**/
            
        for(int i = 0; i < 8; i++)
        {
            registro = 8 - i;
            desplazamiento = i*n_columnas;
            
            for(int j = 0; j < NDISPLAYS; j++) 
            {
                idx = desplazamiento + j + pos;
                MAX7219_send(registro, (imagen_8x32[idx] << corrimiento) | (imagen_8x32[idx+ 1] >> 8 - corrimiento) );
            }   
            MAX7219_update();
        }
        if(duracion <= 2) {
            duracion++;
        }
        else {
            duracion = 0;
            corrimiento++; // Aumentamos el bit de desplazamiento

            if(corrimiento >= 8) { // ¡Cambiamos de byte!
                corrimiento = 0;
                pos++; 

                // Si llegamos al final del mensaje, reiniciamos pos
                if(pos > (7 - NDISPLAYS)) { 
                    pos = 0;
                }
            }
        }
        
    }
    
    return;
    
}

// This function sends out the address byte "a" and the data byte "d" in the MAX7219 format
// (Sequence of bits is a7-a6-a5-a4-a3-a2-a1-a0-d7-d6-d5-d4-d3-d2-d1-d0.)
void MAX7219_send (unsigned char a, unsigned char d) {

	// send out address byte, start with most significant bit and work backwards
    for (int i=7; i>=0; i--) {
        DATA = (a >> i) & 1;
        CLK = 1;
        CLK = 0;
    }
	
	// send out data byte, start with most significant bit and work backwards
    for (int i=7; i>=0; i--) {
        DATA = (d >> i) & 1;
        CLK = 1;
        CLK = 0;
    }
	
	// reset the data pin back to zero
	// (so that it is not left ON if the last sent bit was a 1)
    DATA = 0;

}

// This function pulls the LOAD pin high and then back to zero, so that the transmitted data
// appears in the MAX7219's output stage.
void MAX7219_update (void) {
	
    LOAD = 1;
    LOAD = 0;
	
}