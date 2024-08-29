/**************************************************************************************************
 ** (c) Copyright 2024: Jorge Vasquez <jorgefernandov10@gmail.com>
 ** ALL RIGHTS RESERVED, DON'T USE OR PUBLISH THIS FILE WITHOUT AUTORIZATION
 *************************************************************************************************/

#ifndef INTERFAZ_H /*! @cond    */
#define INTERFAZ_H /*! @endcond */

/** @file interfaz.h
 ** @brief Declaracion de la funcion interfaz de usuario
 **
 **| REV | YYYY.MM.DD | Autor           | Descripción de los cambios                              |
 **|-----|------------|-----------------|---------------------------------------------------------|
 **|   1 | 2024.07.15 | Jorge Vasquez   | Version inicial del archivo                             |
 **
 ** @addtogroup interfaz de usuario
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
 * @brief Funcion de configuracion de interfaz de usuario
 *
 * @return void
 */
void configuracion_interfaz();

/**
 * @brief Funcion para manejo de interfaz de usuario
 *
 * @return int Devuelve un nemero entero para indicar que medicion debe realizarce
 */
int interfaz_usuario();

/* === Ciere de documentacion ================================================================== */
#ifdef __cplusplus
}
#endif

/** @} Final de la definición del modulo para doxygen */

#endif /* INTERFAZ_H */
