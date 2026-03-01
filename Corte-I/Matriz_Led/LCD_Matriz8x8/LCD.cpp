#include "init.h"
#include "config.h"
#include "LCD.h"
#include "stm32f7xx.h"

void LCD_Init_GPIO(void) {
    // 1. Habilitar todos los relojes de los puertos
    RCC->AHB1ENR |= 0x7F; 

    // 2. Configurar como salidas (MODER = 01)
    // Datos: E3, E5, F1, F0 | Control: D4 (E), G2 (RS)
    GPIOE->MODER |= (1 << (3*2)) | (1 << (5*2));
    GPIOF->MODER |= (1 << (1*2)) | (1 << (0*2));
    GPIOD->MODER |= (1 << (4*2));
    GPIOG->MODER |= (1 << (2*2));

    // 3. VELOCIDAD MEDIA (01) - Crucial para evitar ruido
    GPIOE->OSPEEDR |= (1 << (3*2)) | (1 << (5*2));
    GPIOF->OSPEEDR |= (1 << (1*2)) | (1 << (0*2));
    GPIOD->OSPEEDR |= (1 << (4*2));
    GPIOG->OSPEEDR |= (1 << (2*2));
}

void LCD_Enviar_Nibble(uint8_t nibble) {
    // Limpiamos los bits antes de escribir (Reset de pines)
    GPIOE->BSRR = (1 << (3 + 16)) | (1 << (5 + 16)); // Limpiar E3, E5
    GPIOF->BSRR = (1 << (1 + 16)) | (1 << (0 + 16)); // Limpiar F1, F0

    // Escribimos bit a bit según tu hardware:
    if (nibble & 0x01) GPIOE->BSRR = (1 << 3); // D4 -> E3
    if (nibble & 0x02) GPIOE->BSRR = (1 << 5); // D5 -> E5
    if (nibble & 0x04) GPIOF->BSRR = (1 << 1); // D6 -> F1
    if (nibble & 0x08) GPIOF->BSRR = (1 << 0); // D7 -> F0

    // ESPERA DE ASENTAMIENTO: Fundamental a 216MHz
    for(volatile int i = 0; i < 5000; i++); 

    // PULSO ENABLE
    GPIOD->BSRR = (1 << 4);              // EN = 1
    for(volatile int i = 0; i < 15000; i++); // Pulso ancho
    GPIOD->BSRR = (1 << (4 + 16));        // EN = 0
    
    for(volatile int i = 0; i < 5000; i++); // Hold time
}

void LCD_Comando(uint8_t cmd) {
    GPIOG->BSRR = (1 << (2+16)); // RS = 0 (Modo Comando)
    LCD_Enviar_Nibble(cmd >> 4);   // Parte alta
    LCD_Enviar_Nibble(cmd & 0x0F); // Parte baja
    for(volatile int i=0; i<100000; i++); // Espera procesamiento
}

void LCD_Arrancar(void) {
    // 1. ESPERA DE ARRANQUE MASIVA
    for(volatile int i = 0; i < 15000000; i++); // Casi medio segundo

    // 2. SECUENCIA DE FUERZA BRUTA (Asegura modo 8-bit antes de pasar a 4-bit)
    // Esto limpia cualquier comando "a medias" del reinicio anterior
    LCD_Enviar_Nibble(0x03); for(volatile int i = 0; i < 1000000; i++);
    LCD_Enviar_Nibble(0x03); for(volatile int i = 0; i < 500000; i++);
    LCD_Enviar_Nibble(0x03); for(volatile int i = 0; i < 500000; i++);
    
    // 3. AHORA SÍ: Pasamos a modo 4-bits
    LCD_Enviar_Nibble(0x02); 
    for(volatile int i = 0; i < 500000; i++);

    // 4. CONFIGURACIÓN (Comandos de 2 nibbles)
    LCD_Comando(0x28); // 2 líneas, 5x8
    LCD_Comando(0x0C); // Display ON, Cursor OFF
    LCD_Comando(0x01); // CLEAR
    for(volatile int i = 0; i < 4000000; i++); // Espera larga de borrado
    LCD_Comando(0x06); // Entry mode: incremento
}

void LCD_Escribir_Caracter(char c) {
    GPIOG->BSRR = (1 << 2); // RS = 1 (G2)
    for(volatile int i=0; i<2000; i++); // Pequeña espera de asentamiento

    // Enviar parte alta
    LCD_Enviar_Nibble(c >> 4);
    // Enviar parte baja
    LCD_Enviar_Nibble(c & 0x0F);

    // ESPERA CLAVE: La LCD tarda unos 40us en procesar cada letra
    // A 216MHz, necesitamos un for generoso
    for(volatile int i=0; i<15000; i++); 
}

void LCD_Imprimir(const char* mensaje) {
    while(*mensaje) {
        LCD_Escribir_Caracter(*mensaje++);
    }
}