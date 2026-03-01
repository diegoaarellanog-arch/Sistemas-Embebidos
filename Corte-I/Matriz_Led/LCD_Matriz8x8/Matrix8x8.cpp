#include "Matrix8x8.h"
#include "init.h"
#include "config.h"

void prepararMensaje(const char* frase) {
    longitudMensaje = 0;
    // Limpiar buffer de mensaje
    for(int i = 0; i < MAX_MSG; i++) bufferMensaje[i] = 0;

    while (*frase && longitudMensaje < (MAX_MSG - 8)) {
        Letra l = Fuente4x8[(uint8_t)*frase];
        
        // Copiar los bytes de la letra al buffer largo
        for (int i = 0; i < l.ancho; i++) {
            bufferMensaje[longitudMensaje++] = l.datos[i];
        }
        
        // Espacio de 1 columna entre letras
        bufferMensaje[longitudMensaje++] = 0x00;
        frase++;
    }
}

void actualizarScroll(int offset) {
    for (int i = 0; i < 24; i++) {
        // Si el offset + i está dentro del mensaje, copiar; si no, dejar en negro
        if ((offset + i) < longitudMensaje && (offset + i) >= 0) {
            bufferPantalla[i] = bufferMensaje[offset + i];
        } else {
            bufferPantalla[i] = 0;
        }
    }
}

void refrescarPantalla(void) {
    for (uint8_t fila = 0; fila < 8; fila++) {
        // 1. Apagar todas las filas (evitar fantasmas)
        M_FIL(0); 

        // 2. Cargar datos de las 24 columnas para esa fila específica
        // Usamos una máscara de bits para extraer el brillo de la fila actual
        uint8_t datosM1 = 0, datosM2 = 0, datosM3 = 0;

        for (int c = 0; c < 8; c++) {
            if (bufferPantalla[c]    & (1 << fila)) datosM1 |= (1 << c);
            if (bufferPantalla[c+8]  & (1 << fila)) datosM2 |= (1 << c);
            if (bufferPantalla[c+16] & (1 << fila)) datosM3 |= (1 << c);
        }

        M1_COL(datosM1);
        M2_COL(datosM2);
        M3_COL(datosM3);

        // 3. Encender la fila actual (Lógica inversa si usas ULN2803)
        M_FIL(1 << fila); 

        for (int t = 0; t < 100;t++);
    }
}