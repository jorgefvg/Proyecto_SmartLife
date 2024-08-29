/**************************************************************************************************
 ** (c) Copyright 2024: Jorge Vasquez <jorgefernandov10@gmail.com>
 ** ALL RIGHTS RESERVED, DON'T USE OR PUBLISH THIS FILE WITHOUT AUTORIZATION
 *************************************************************************************************/

/** @file termometro.cpp
 ** @brief Implementacion de la funcion termometro para medir la temperatura corporal en °C
 **
 **| REV | YYYY.MM.DD | Autor           | Descripción de los cambios                              |
 **|-----|------------|-----------------|---------------------------------------------------------|
 **|   1 | 2024.07.15 | Jorge Vasquez   | Version inicial del archivo                             |
 **
 ** @addtogroup termometro
 ** @{ */

/* === Inclusiones de cabeceras ================================================================ */

#include <Adafruit_MLX90614.h>
#include <Wire.h>
#include <Adafruit_SPIDevice.h>
#include "termometro.h"

/* === Definicion y Macros ===================================================================== */

/* == Declaraciones de tipos de datos internos ================================================= */
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

int alarma = 36;     //!< valor de temperatura de alarma
int calibracion = 3; //!< factor de calibracion
/* === Definiciones de variables internas ====================================================== */

/* === Definiciones de variables externas ====================================================== */

/* === Declaraciones de funciones internas ===================================================== */

/* === Definiciones de funciones internas ====================================================== */

/* === Definiciones de funciones externas ====================================================== */

void configuracion_termometro() {
    Serial.begin(115200);
    while (!Serial)
        ;

    if (!mlx.begin()) {
        Serial.println("Error ");
        while (1)
            ;
    };

    // Serial.print("Emisividad = "); Serial.println(mlx.readEmissivity());
    // Serial.println("================================================");
}

void calcular_temperatura() {

    Serial.print("*C\tTemperatura = ");
    Serial.print(mlx.readObjectTempC() + calibracion);
    Serial.println("*C");
    Serial.println();
    if ((mlx.readObjectTempC() + calibracion) > alarma) // si supera el valor definido como alarma
    {
        Serial.println("**** Alerta *****");
        delay(100);
    } else {
        Serial.println("...................");
    }
    delay(1500);
}

/* === Ciere de documentacion ================================================================== */

/** @} Final de la definición del modulo para doxygen */
