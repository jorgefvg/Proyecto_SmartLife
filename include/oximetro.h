/**************************************************************************************************
 ** (c) Copyright 2024: Jorge Vasquez <jorgefernandov10@gmail.com>
 ** ALL RIGHTS RESERVED, DON'T USE OR PUBLISH THIS FILE WITHOUT AUTORIZATION
 *************************************************************************************************/

#ifndef OXIMETRO_H /*! @cond    */
#define OXIMETRO_H /*! @endcond */

/** @file oximetro.h
 ** @brief Declaracion de la funcion oximetro para medir el bpm y spo2
 **
 **| REV | YYYY.MM.DD | Autor           | Descripción de los cambios                              |
 **|-----|------------|-----------------|---------------------------------------------------------|
 **|   1 | 2024.07.15 | Jorge Vasquez   | Version inicial del archivo                             |
 **
 ** @addtogroup oximetro
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
 * @brief Funcion de configuracion del oximetro
 *
 * @return void
 */
void configuracion_oximetro();

/**
 * @brief Funcion para calcular el bpm y spo2
 *
 * @return void
 */
void calcular_bpm_spo2();

/* === Ciere de documentacion ================================================================== */
#ifdef __cplusplus
}
#endif

/** @} Final de la definición del modulo para doxygen */

#endif /* OXIMETRO_H */
