/**************************************************************************************************
 ** (c) Copyright 2024: Jorge Vasquez <jorgefernandov10@gmail.com>
 ** ALL RIGHTS RESERVED, DON'T USE OR PUBLISH THIS FILE WITHOUT AUTORIZATION
 *************************************************************************************************/

#ifndef TERMOMETRO_H /*! @cond    */
#define TERMOMETRO_H /*! @endcond */

/** @file termometro.h
 ** @brief Declaracion de la funcion termometro para medir la temperatura corporal en °C
 **
 **| REV | YYYY.MM.DD | Autor           | Descripción de los cambios                              |
 **|-----|------------|-----------------|---------------------------------------------------------|
 **|   1 | 2024.07.15 | Jorge Vasquez   | Version inicial del archivo                             |
 **
 ** @addtogroup termometro
 ** @{ */

/* === Inclusiones de archivos externos ======================================================== */
#include <Arduino.h>
/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Definicion y Macros ===================================================================== */

/* === Declaraciones de tipos de datos ========================================================= */

/* === Declaraciones de variables externas ===================================================== */

/* === Declaraciones de funciones externas ===================================================== */

/**
 * @brief Funcion de configuracion del termometro
 *
 * @return void
 */
void configuracion_termometro();

/**
 * @brief Funcion para calcular la temperatura corporal
 *
 * @return void
 */
void calcular_temperatura();

/* === Ciere de documentacion ================================================================== */
#ifdef __cplusplus
}
#endif

/** @} Final de la definición del modulo para doxygen */

#endif /* TERMOMETRO_H */
