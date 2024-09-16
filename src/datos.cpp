/**************************************************************************************************
 ** (c) Copyright 2024: Jorge Vasquez <jorgefernandov10@gmail.com>
 ** ALL RIGHTS RESERVED, DON'T USE OR PUBLISH THIS FILE WITHOUT AUTORIZATION
 *************************************************************************************************/

/** @file datos.cpp
 ** @brief Implementacion de la funcion para el envio de datos
 **
 **| REV | YYYY.MM.DD | Autor           | Descripción de los cambios                              |
 **|-----|------------|-----------------|---------------------------------------------------------|
 **|   1 | 2024.08.09 | Jorge Vasquez   | Version inicial del archivo                             |
 **
 ** @addtogroup datos
 ** @{ */

/* === Inclusiones de cabeceras ================================================================ */

#include "datos.h"

/* === Definicion y Macros ===================================================================== */
#define On_Board_LED_PIN 2 // Led de la placa ESP32
/* == Declaraciones de tipos de datos internos ================================================= */
//----------------------------------------SSID and PASSWORD of your WiFi network.
const char * ssid = "BRENDA VASQUEZ";       //--> Your wifi name
const char * password = "18defebrero1989H"; //--> Your wifi password
//----------------------------------------

// Google script Web_App_URL.
String Web_App_URL =
    "https://script.google.com/macros/s/"
    "AKfycbzFiT2oEtI6HlEr237O6qSqXLJBgySA8P6WNOjqPGnGfizO-MiU9Pb2WipFe8xb2PFBKg/exec";

String nivel_estres = "";

String Status_Read_Sensor = "Success";

int fc = 0;
int spo2 = 0;
int temperatura = 0;
/* === Definiciones de variables internas ====================================================== */

/* === Definiciones de variables externas ====================================================== */

/* === Declaraciones de funciones internas ===================================================== */

/* === Definiciones de funciones internas ====================================================== */

/* === Definiciones de funciones externas ====================================================== */

void configuracion_wifi() {
    pinMode(On_Board_LED_PIN, OUTPUT);

    //----------------------------------------Set Wifi to STA mode
    Serial.println();
    Serial.println("-------------");
    Serial.println("WIFI mode : STA");
    WiFi.mode(WIFI_STA);
    Serial.println("-------------");
    //----------------------------------------

    //----------------------------------------Connect to Wi-Fi (STA).
    Serial.println();
    Serial.println("------------");
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    // The process of connecting ESP32 with WiFi Hotspot / WiFi Router.
    //  The process timeout of connecting ESP32 with WiFi Hotspot / WiFi Router is 20 seconds.
    //  If within 20 seconds the ESP32 has not been successfully connected to WiFi, the ESP32 will
    //  restart. I made this condition because on my ESP32, there are times when it seems like it
    //  can't connect to WiFi, so it needs to be restarted to be able to connect to WiFi.

    int connecting_process_timed_out = 20; //--> 20 = 20 seconds.
    connecting_process_timed_out = connecting_process_timed_out * 2;
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        digitalWrite(On_Board_LED_PIN, HIGH);
        delay(250);
        digitalWrite(On_Board_LED_PIN, LOW);
        delay(250);
        if (connecting_process_timed_out > 0)
            connecting_process_timed_out--;
        if (connecting_process_timed_out == 0) {
            delay(1000);
            ESP.restart();
        }
    }

    digitalWrite(On_Board_LED_PIN, LOW);

    Serial.println();
    Serial.println("WiFi connected");
    Serial.println("------------");
    //::::::::::::::::::
    //----------------------------------------

    delay(100);
}

void wifi_oximetro(double bpm, double spo) {

    fc = (int)bpm;
    spo2 = (int)spo;
    //----------------------------------------Conditions that are executed when WiFi is connected.
    // This condition is the condition for sending or writing data to Google Sheets.
    if (WiFi.status() == WL_CONNECTED) {
        digitalWrite(On_Board_LED_PIN, HIGH);

        // Create a URL for sending or writing data to Google Sheets.
        String Send_Data_URL = Web_App_URL + "?sts=write";
        Send_Data_URL += "&srs=" + Status_Read_Sensor;
        Send_Data_URL += "&fc=" + String(fc);
        Send_Data_URL += "&spo=" + String(spo2);

        Serial.println();
        Serial.println("-------------");
        Serial.println("Send data to Google Spreadsheet...");
        Serial.print("URL : ");
        Serial.println(Send_Data_URL);

        //::::::::::::::::::The process of sending or writing data to Google Sheets.
        // Initialize HTTPClient as "http".
        HTTPClient http;

        // HTTP GET Request.
        http.begin(Send_Data_URL.c_str());
        http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

        // Gets the HTTP status code.
        int httpCode = http.GET();
        Serial.print("HTTP Status Code : ");
        Serial.println(httpCode);

        // Getting response from google sheets.
        String payload;
        if (httpCode > 0) {
            payload = http.getString();
            Serial.println("Payload : " + payload);
        }

        http.end();
        //::::::::::::::::::

        digitalWrite(On_Board_LED_PIN, LOW);
        Serial.println("-------------");
    }
    //----------------------------------------

    delay(10000);
}

void wifi_termometro(double temp) {

    temperatura = (int)temp;
    //----------------------------------------Conditions that are executed when WiFi is connected.
    // This condition is the condition for sending or writing data to Google Sheets.
    if (WiFi.status() == WL_CONNECTED) {
        digitalWrite(On_Board_LED_PIN, HIGH);

        // Create a URL for sending or writing data to Google Sheets.
        String Send_Data_URL = Web_App_URL + "?sts=write";
        Send_Data_URL += "&srs=" + Status_Read_Sensor;
        Send_Data_URL += "&temp=" + String(temperatura);

        Serial.println();
        Serial.println("-------------");
        Serial.println("Send data to Google Spreadsheet...");
        Serial.print("URL : ");
        Serial.println(Send_Data_URL);

        //::::::::::::::::::The process of sending or writing data to Google Sheets.
        // Initialize HTTPClient as "http".
        HTTPClient http;

        // HTTP GET Request.
        http.begin(Send_Data_URL.c_str());
        http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

        // Gets the HTTP status code.
        int httpCode = http.GET();
        Serial.print("HTTP Status Code : ");
        Serial.println(httpCode);

        // Getting response from google sheets.
        String payload;
        if (httpCode > 0) {
            payload = http.getString();
            Serial.println("Payload : " + payload);
        }

        http.end();
        //::::::::::::::::::

        digitalWrite(On_Board_LED_PIN, LOW);
        Serial.println("-------------");
    }
    //----------------------------------------

    delay(10000);
}

void wifi_estres(int estres) {

    //----------------------------------------Conditions that are executed when WiFi is connected.
    // This condition is the condition for sending or writing data to Google Sheets.
    if (WiFi.status() == WL_CONNECTED) {
        digitalWrite(On_Board_LED_PIN, HIGH);

        // Create a URL for sending or writing data to Google Sheets.
        String Send_Data_URL = Web_App_URL + "?sts=write";
        Send_Data_URL += "&srs=" + Status_Read_Sensor;

        if (estres <= 2 && estres >= 0) {
            nivel_estres = "Alto";
            Send_Data_URL += "&estres=" + nivel_estres;
        } else if (estres <= 10 && estres >= 3) {
            nivel_estres = "Moderado";
            Send_Data_URL += "&estres=" + nivel_estres;
        } else if (estres >= 11) {
            nivel_estres = "Normal";
            Send_Data_URL += "&estres=" + nivel_estres;
        }

        Serial.println();
        Serial.println("-------------");
        Serial.println("Send data to Google Spreadsheet...");
        Serial.print("URL : ");
        Serial.println(Send_Data_URL);

        //::::::::::::::::::The process of sending or writing data to Google Sheets.
        // Initialize HTTPClient as "http".
        HTTPClient http;

        // HTTP GET Request.
        http.begin(Send_Data_URL.c_str());
        http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

        // Gets the HTTP status code.
        int httpCode = http.GET();
        Serial.print("HTTP Status Code : ");
        Serial.println(httpCode);

        // Getting response from google sheets.
        String payload;
        if (httpCode > 0) {
            payload = http.getString();
            Serial.println("Payload : " + payload);
        }

        http.end();
        //::::::::::::::::::

        digitalWrite(On_Board_LED_PIN, LOW);
        Serial.println("-------------");
    }
    //----------------------------------------

    delay(10000);
}
/* === Ciere de documentacion ================================================================== */

/** @} Final de la definición del modulo para doxygen */
