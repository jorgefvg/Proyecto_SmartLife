/**************************************************************************************************
 ** (c) Copyright 2024: Jorge Vasquez <jorgefernandov10@gmail.com>
 ** ALL RIGHTS RESERVED, DON'T USE OR PUBLISH THIS FILE WITHOUT AUTORIZATION
 *************************************************************************************************/

#ifndef PANTALLA_H /*! @cond    */
#define PANTALLA_H /*! @endcond */

/** @file pantalla.h
 ** @brief Declaracion de la funcion interfaz de pantalla
 **
 **| REV | YYYY.MM.DD | Autor           | Descripción de los cambios                              |
 **|-----|------------|-----------------|---------------------------------------------------------|
 **|   1 | 2024.07.31 | Jorge Vasquez   | Version inicial del archivo                             |
 **
 ** @addtogroup interfaz
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
 * @brief Funcion de configuracion de interfaz de pantalla
 *
 * @return void
 */
void configuracion_pantalla();

/**
 * @brief Funcion para manejo del menu principal
 *
 * @return void
 */
void menu_principal();

/**
 * @brief Funcion para manejo de la edad del usuario
 *
 * @return void
 */
void menu_edad();

/**
 * @brief Funcion para manejo del menu de oximetro
 *
 * @return void
 */
void menu_oximetro(double bpm, double spo);

/**
 * @brief Funcion para manejo del menu del termometro
 *
 * @return void
 */
void menu_termometro(double temp);

/**
 * @brief Funcion para manejo del menu de estres
 *
 * @return void
 */
void menu_estres(int estres);

/* === Ciere de documentacion ================================================================== */
#ifdef __cplusplus
}
#endif

/** @} Final de la definición del modulo para doxygen */

#endif /* PANTALLA_H */
