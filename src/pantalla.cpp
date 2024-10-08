/**************************************************************************************************
 ** (c) Copyright 2024: Jorge Vasquez <jorgefernandov10@gmail.com>
 ** ALL RIGHTS RESERVED, DON'T USE OR PUBLISH THIS FILE WITHOUT AUTORIZATION
 *************************************************************************************************/

/** @file pantalla.cpp
 ** @brief Implementacion de la funcion interfaz de pantalla
 **
 **| REV | YYYY.MM.DD | Autor           | Descripción de los cambios                              |
 **|-----|------------|-----------------|---------------------------------------------------------|
 **|   1 | 2024.07.31 | Jorge Vasquez   | Version inicial del archivo                             |
 **
 ** @addtogroup interfaz
 ** @{ */

/* === Inclusiones de cabeceras ================================================================ */

#include <Adafruit_SSD1306.h> //pantalla
#include "pantalla.h"

/* === Definicion y Macros ===================================================================== */
#define ANCHO      128
#define ALTO       64
#define RESET_OLED -1
Adafruit_SSD1306 display(ANCHO, ALTO, &Wire, RESET_OLED); // Objeto de la clase
/* == Declaraciones de tipos de datos internos ================================================= */
int frecuencia_cardiaca = 0;
int saturacion_oxigeno = 0;
int temperatura_corporal = 0;
/* === Definiciones de variables internas ====================================================== */

/* === Definiciones de variables externas ====================================================== */

/* === Declaraciones de funciones internas ===================================================== */

/* === Definiciones de funciones internas ====================================================== */

/* === Definiciones de funciones externas ====================================================== */

void configuracion_pantalla() {
    Wire.begin();                              // Configuración de pines I2C
    Serial.begin(115200);                      // Usar el puerto serial.
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // llamar al Oled
    display.clearDisplay();                    // Limpiar buffer (pantalla)
    display.setTextColor(WHITE);               // Color del texto
}

void menu_principal() {
    display.clearDisplay(); // Limpiar buffer (pantalla)

    display.setCursor(2, 8); // Posición del texto
    display.setTextSize(2);  // Tamaño del texto
    display.print("1.OXIMETRO");

    display.setCursor(2, 28); // Posición del texto
    display.setTextSize(2);   // Tamaño del texto
    display.print("2.TEMP");

    display.setCursor(2, 48); // Posición del texto
    display.setTextSize(2);   // Tamaño del texto
    display.print("3.ESTRES");
    display.display();
}

void oximetro_espera() {
    display.clearDisplay(); // Limpiar buffer (pantalla)

    display.setCursor(2, 0); // Posición del texto
    display.setTextSize(2);  // Tamaño del texto
    display.print("Calculando");

    display.setCursor(2, 28); // Posición del texto
    display.setTextSize(2);   // Tamaño del texto
    display.print("FC y Spo2");

    display.setCursor(2, 48); // Posición del texto
    display.setTextSize(2);   // Tamaño del texto
    display.print("Espere...");
    display.display();
}

void termometro_espera() {
    display.clearDisplay(); // Limpiar buffer (pantalla)

    display.setCursor(2, 0); // Posición del texto
    display.setTextSize(2);  // Tamaño del texto
    display.print("Calculando");

    display.setCursor(2, 28); // Posición del texto
    display.setTextSize(2);   // Tamaño del texto
    display.print("Temp");

    display.setCursor(2, 48); // Posición del texto
    display.setTextSize(2);   // Tamaño del texto
    display.print("Espere...");
    display.display();
}

void estres_espera() {
    display.clearDisplay(); // Limpiar buffer (pantalla)

    display.setCursor(2, 0); // Posición del texto
    display.setTextSize(2);  // Tamaño del texto
    display.print("Calculando");

    display.setCursor(2, 28); // Posición del texto
    display.setTextSize(2);   // Tamaño del texto
    display.print("Estres");

    display.setCursor(2, 48); // Posición del texto
    display.setTextSize(2);   // Tamaño del texto
    display.print("Espere...");
    display.display();
}

void menu_oximetro(double bpm, double spo) {
    frecuencia_cardiaca = (int)bpm;
    saturacion_oxigeno = (int)spo;

    display.clearDisplay(); // Limpiar buffer (pantalla)
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(45, 2);
    display.setRotation(3);
    display.println("FC");
    display.setRotation(0);
    display.setTextSize(3);
    display.setCursor(20, 5);
    display.println(frecuencia_cardiaca, 0);
    display.setCursor(88, 5);
    display.setTextSize(2);
    display.print("bpm");

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setRotation(3);
    display.setCursor(5, 2);
    display.println("spo2");
    display.setTextSize(3);
    display.setRotation(0);
    display.setCursor(20, 35);
    display.println(saturacion_oxigeno, 0);
    display.setCursor(112, 35);
    display.setTextSize(2);
    display.print("%");
    display.display();
}

void menu_termometro(double temp) {
    temperatura_corporal = (int)temp;

    display.clearDisplay(); // Limpiar buffer (pantalla)
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(36, 2);
    display.setRotation(3);
    display.println("temp");
    display.setRotation(0);
    display.setTextSize(3);
    display.setCursor(20, 5);
    display.println(temperatura_corporal, 0);
    display.setCursor(88, 5);
    display.setTextSize(2);
    display.print("*C");
    display.display();
}

void menu_estres(int estres) {
    display.clearDisplay(); // Limpiar buffer (pantalla)
    display.setRotation(0);
    display.setTextSize(2);
    display.setCursor(5, 5);
    if (estres <= 2 && estres >= 0) {
        display.println("Estres");

        display.setTextSize(2);
        display.setRotation(0);
        display.setCursor(5, 35);
        display.println("Alto");
        display.display();
    } else if (estres <= 10 && estres >= 3) {
        display.println("Estres");

        display.setTextSize(2);
        display.setRotation(0);
        display.setCursor(5, 35);
        display.println("Moderado");
        display.display();
    } else if (estres >= 11) {
        display.println("Estres");

        display.setTextSize(2);
        display.setRotation(0);
        display.setCursor(5, 35);
        display.println("Normal");
        display.display();
    }
}

void menu_oximetro_error() {

    display.clearDisplay(); // Limpiar buffer (pantalla)
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(45, 2);
    display.setRotation(3);
    display.println("FC");
    display.setRotation(0);
    display.setTextSize(3);
    display.setCursor(20, 5);
    display.println("---");
    display.setCursor(88, 5);
    display.setTextSize(2);
    display.print("bpm");

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setRotation(3);
    display.setCursor(5, 2);
    display.println("spo2");
    display.setTextSize(3);
    display.setRotation(0);
    display.setCursor(20, 35);
    display.println("---");
    display.setCursor(112, 35);
    display.setTextSize(2);
    display.print("%");
    display.display();
}

void menu_estres_error() {
    display.clearDisplay(); // Limpiar buffer (pantalla)
    display.setRotation(0);
    display.setTextSize(2);
    display.setCursor(5, 5);
    display.println("Estres");
    display.setTextSize(2);
    display.setRotation(0);
    display.setCursor(5, 35);
    display.println("---");
    display.display();
}

void menu_termometro_error(double temp) {
    temperatura_corporal = (int)temp;

    display.clearDisplay(); // Limpiar buffer (pantalla)
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(36, 2);
    display.setRotation(3);
    display.println("temp");
    display.setRotation(0);
    display.setTextSize(3);
    display.setCursor(20, 5);
    if (temperatura_corporal < 32) {
        display.println("LO");
    } else if (temperatura_corporal > 42) {
        display.println("HI");
    }
    display.setCursor(88, 5);
    display.setTextSize(2);
    display.print("*C");
    display.display();
}
/* === Ciere de documentacion ================================================================== */

/** @} Final de la definición del modulo para doxygen */
