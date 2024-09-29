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
 */

/* === Inclusiones de cabeceras ================================================================ */

#include "main.h"
#include "interfaz.h"
#include "oximetro.h"
#include "termometro.h"
#include "pantalla.h"
#include "datos.h"
#include <math.h>

/* === Definicion y Macros ===================================================================== */

/* == Declaraciones de tipos de datos internos ================================================= */
int medicion = 0;
double temp = 0;
double bpm = 0;
double spo = 0;
double bpm_inicial = 0;
double bpm_final = 0;
int calculo_estres = 0;
int estres = 0;
int numero = 0;
double calcular = 0;
double promedio = 0;
int numero_bpm = 0;
double calcular_bpm = 0;
double promedio_bpm = 0;
int numero_spo = 0;
double calcular_spo = 0;
double promedio_spo = 0;
const int max_bpm = 180;
const int min_bpm = 30;
const int max_spo = 100;
const int min_spo = 70;
const double max_temp = 42;
const double min_temp = 32;

const int wakeupPin = 25;        // GPIO 25 para activación externa
RTC_DATA_ATTR int bootCount = 0; // Número de reinicios

/* === Definiciones de variables internas ====================================================== */

/* === Definiciones de variables externas ====================================================== */

/* === Declaraciones de funciones internas ===================================================== */

/* === Definiciones de funciones internas ====================================================== */

/* === Definiciones de funciones externas ====================================================== */

void setup() {
    Serial.begin(115200);             // Iniciar el puerto serial a una velocidad de 115200 baudios
    pinMode(wakeupPin, INPUT_PULLUP); // Declarar el pin con el botón pulsador como INPUT_PULLUP
    bootCount++;                      // Incrementa el número de arranques en 1
    Serial.println("Número de arranque: " + String(bootCount)); // Imprime el número de arranque
    esp_sleep_enable_ext0_wakeup((gpio_num_t)wakeupPin, LOW);   // Configurar la activación externa
    delay(1000); // Añadiendo un retraso de 1 segundo para evitar pulsaciones múltiples

    configuracion_wifi();
    configuracion_interfaz();
    configuracion_pantalla();
    configuracion_oximetro();
    configuracion_termometro();
}

void loop() {
    menu_principal();
    medicion = interfaz_usuario();

    switch (medicion) {

    case 1:
        estres_espera();
        for (int v = 0; v < 50; v++) {
            calcular_bpm_spo2(&bpm, &spo);
        }
        Serial.println("--");

        for (int r = 0; r < 200; r++) {
            calcular_bpm_spo2(&bpm, &spo);
            if (bpm > 0) {
                calcular = calcular + bpm;
                numero++;
            }
        }
        promedio = calcular / numero;
        Serial.println(promedio);
        bpm_inicial = promedio;
        calcular = 0;
        numero = 0;
        promedio = 0;

        for (int q = 0; q < 200; q++) {
            calcular_bpm_spo2(&bpm, &spo);
            if (bpm > 0) {
                calcular = calcular + bpm;
                numero++;
            }
        }

        promedio = calcular / numero;
        Serial.println(promedio);
        bpm_final = promedio;
        calcular = 0;
        numero = 0;
        promedio = 0;

        if (bpm_inicial <= max_bpm && bpm_inicial >= min_bpm && bpm_final <= max_bpm &&
            bpm_final >= min_bpm) {
            calculo_estres = bpm_final - bpm_inicial;
            estres = fabs(calculo_estres);
            Serial.println(estres);
            if (estres <= 2 && estres >= 0) {
                Serial.println("Estres alto");
            } else if (estres <= 10 && estres >= 3) {
                Serial.println("Estres Moderado");
            } else if (estres >= 11) {
                Serial.println("Estres Normal");
            }
            menu_estres(estres);
            wifi_estres(estres);
        } else {
            menu_estres_error();
        }
        bpm = 0;
        bpm_inicial = 0;
        bpm_final = 0;
        calculo_estres = 0;
        estres = 0;

        Serial.println("Me voy a dormir ahora.");
        esp_deep_sleep_start();
        break;

    case 2:
        termometro_espera();
        calcular_temperatura(&temp);
        if (temp <= max_temp && temp >= min_temp) {
            menu_termometro(temp);
            wifi_termometro(temp);
        } else {
            menu_termometro_error(temp);
        }
        Serial.println("Me voy a dormir ahora.");
        esp_deep_sleep_start();
        break;

    case 3:
        oximetro_espera();
        for (int v = 0; v < 50; v++) {
            calcular_bpm_spo2(&bpm, &spo);
        }
        Serial.println("--");

        for (int i = 0; i < 150; i++) {
            calcular_bpm_spo2(&bpm, &spo);
            if (bpm > 0) {
                calcular_bpm = calcular_bpm + bpm;
                numero_bpm++;
            }
            if (spo > 0) {
                calcular_spo = calcular_spo + spo;
                numero_spo++;
            }
        }

        promedio_bpm = calcular_bpm / numero_bpm;
        promedio_spo = calcular_spo / numero_spo;
        Serial.println(promedio_bpm);
        Serial.println(promedio_spo);
        if (promedio_bpm <= max_bpm && promedio_bpm >= min_bpm && promedio_spo <= max_spo &&
            promedio_spo >= min_spo) {
            menu_oximetro(promedio_bpm, promedio_spo);
            wifi_oximetro(promedio_bpm, promedio_spo);
        } else {
            menu_oximetro_error();
        }
        calcular_bpm = 0;
        calcular_spo = 0;
        numero_bpm = 0;
        numero_spo = 0;
        promedio_bpm = 0;
        promedio_spo = 0;
        Serial.println("Me voy a dormir ahora."); // Imprime una declaración antes de entrar
                                                  // en un sueño profundo
        esp_deep_sleep_start();                   // Entrar en modo de sueño profundo
        break;

    default:
        break;
    }
}

/* === Ciere de documentacion ================================================================== */

/** @} Final de la definición del modulo para doxygen */
