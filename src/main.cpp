/**************************************************************************************************
 ** (c) Copyright 2024: Jorge Vasquez <jorgefernandov10@gmail.com>
 ** ALL RIGHTS RESERVED, DON'T USE OR PUBLISH THIS FILE WITHOUT AUTORIZATION
 *************************************************************************************************/

/** @file main.cpp
 ** @brief Definicion de la funcion principal del programa
 **
 **| REV | YYYY.MM.DD | Autor           | Descripción de los cambios                              |
 **|-----|------------|-----------------|---------------------------------------------------------|
 **|   1 | 2024.07.15 | Jorge Vasquez   | Version inicial del archivo                             |
 **
 */

/* === Inclusiones de cabeceras ================================================================ */

#include "main.h"
#include "interfaz.h"
#include "oximetro.h"
#include "termometro.h"

/* === Definicion y Macros ===================================================================== */

/* == Declaraciones de tipos de datos internos ================================================= */
int medicion = 0;
/* === Definiciones de variables internas ====================================================== */

/* === Definiciones de variables externas ====================================================== */

/* === Declaraciones de funciones internas ===================================================== */

/* === Definiciones de funciones internas ====================================================== */

/* === Definiciones de funciones externas ====================================================== */

void setup() {
    configuracion_interfaz();
    configuracion_oximetro();
    configuracion_termometro();
}

void loop() {
    medicion = interfaz_usuario();
    switch (medicion) {
    case 1:
        calcular_bpm_spo2();
        break;

    case 2:
        calcular_temperatura();
        break;

    default:
        break;
    }
}

/* === Ciere de documentacion ================================================================== */

/** @} Final de la definición del modulo para doxygen */
