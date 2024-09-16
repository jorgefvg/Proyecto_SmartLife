/**************************************************************************************************
 ** (c) Copyright 2024: Jorge Vasquez <jorgefernandov10@gmail.com>
 ** ALL RIGHTS RESERVED, DON'T USE OR PUBLISH THIS FILE WITHOUT AUTORIZATION
 *************************************************************************************************/

#ifndef DATOS_H /*! @cond    */
#define DATOS_H /*! @endcond */

/** @file datos.h
 ** @brief Declaracion de la funcion para el envio de datos
 **
 **| REV | YYYY.MM.DD | Autor           | Descripción de los cambios                              |
 **|-----|------------|-----------------|---------------------------------------------------------|
 **|   1 | 2024.08.09 | Jorge Vasquez   | Version inicial del archivo                             |
 **
 ** @addtogroup datos
 ** @{ */

/* === Inclusiones de archivos externos ======================================================== */
#include <Arduino.h>
#include "WiFi.h"
#include <HTTPClient.h>
/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Definicion y Macros ===================================================================== */

/* === Declaraciones de tipos de datos ========================================================= */

/* === Declaraciones de variables externas ===================================================== */

/* === Declaraciones de funciones externas ===================================================== */

/**
 * @brief Funcion para manejo del envio de datos
 *
 * @return void
 */
void configuracion_wifi();

/**
 * @brief Funcion para el envio de datos del oximetro
 *
 * @param  bpm   dato de ritmo cardiaco
 * @param  spo   dato de saturacion de oxigeno
 *
 * @return void
 */
void wifi_oximetro(double bpm, double spo);

/**
 * @brief Funcion para el envio de datos del termometro
 *
 * @param  temp   dato de temperatura
 *
 * @return void
 */
void wifi_termometro(double temp);

/**
 * @brief Funcion para el envio de datos del nivel de estres
 *
 * @param  estres   dato de estres
 *
 * @return void
 */
void wifi_estres(int estres);

/* === Ciere de documentacion ================================================================== */
#ifdef __cplusplus
}
#endif

/** @} Final de la definición del modulo para doxygen */

#endif /* DATOS_H */
