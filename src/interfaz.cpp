/**************************************************************************************************
 ** (c) Copyright 2024: Jorge Vasquez <jorgefernandov10@gmail.com>
 ** ALL RIGHTS RESERVED, DON'T USE OR PUBLISH THIS FILE WITHOUT AUTORIZATION
 *************************************************************************************************/

/** @file interfaz.cpp
 ** @brief Implementacion de la funcion interfaz de usuario
 **
 **| REV | YYYY.MM.DD | Autor           | Descripción de los cambios                              |
 **|-----|------------|-----------------|---------------------------------------------------------|
 **|   1 | 2024.07.15 | Jorge Vasquez   | Version inicial del archivo                             |
 **
 ** @addtogroup interfaz
 ** @{ */

/* === Inclusiones de cabeceras ================================================================ */

#include "interfaz.h"

/* === Definicion y Macros ===================================================================== */

/* == Declaraciones de tipos de datos internos ================================================= */
int opcion = 0;                   //!< Numero de tecla presionada
const byte fila = 4;              //!< Numero de filas del teclado matricial
const byte columna = 4;           //!< Numero de columnas del teclado matricial
byte pinesFilas[] = {12, 14, 27}; //!< Pines para el manejo de filas del teclado matricial
byte pinesColumnas[] = {13};      //!< Pines para el manejo de columnas del teclado matricial
char teclas[fila][columna] = {{'1'}, {'2'}, {'3'}};
/* === Definiciones de variables internas ====================================================== */

/* === Definiciones de variables externas ====================================================== */

/* === Declaraciones de funciones internas ===================================================== */

/* === Definiciones de funciones internas ====================================================== */

/* === Definiciones de funciones externas ====================================================== */

void configuracion_interfaz() {
    for (int nL = 0; nL <= 2; nL++) {
        pinMode(pinesFilas[nL], OUTPUT);
        digitalWrite(pinesFilas[nL], HIGH);
    }
    for (int nC = 0; nC <= 0; nC++) {
        pinMode(pinesColumnas[nC], INPUT_PULLUP);
    }

    Serial.begin(115200);
}

int interfaz_usuario() {
    // Barrido por las filas
    for (int nL = 0; nL <= 2; nL++) {
        digitalWrite(pinesFilas[nL], LOW);

        // Barrido en columnas buscando un LOW
        for (int nC = 0; nC <= 0; nC++) {
            if (digitalRead(pinesColumnas[nC]) == LOW) {
                Serial.print("Tecla: ");
                Serial.println(teclas[nL][nC]);
                if (teclas[nL][nC] == '1') {
                    return opcion = 1;
                } else if (teclas[nL][nC] == '2') {
                    return opcion = 2;
                } else if (teclas[nL][nC] == '3') {
                    return opcion = 3;
                }
                while (digitalRead(pinesColumnas[nC]) == LOW) {
                }
            }
        }
        digitalWrite(pinesFilas[nL], HIGH);
    }
    return opcion = 0;
}

/* === Ciere de documentacion ================================================================== */

/** @} Final de la definición del modulo para doxygen */
