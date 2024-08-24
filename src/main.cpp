#include <Arduino.h>
#include <Wire.h> // llamar librería para comunicación I2C
#include "MAX30105.h" // llamar la librería del sensor MAX30102
#include <movingAvg.h> // Calcular promedios
MAX30105 Sensor; // nombrar Sensor al MAX30105
//------ Definición constantes
const uint32_t TH_dedo = 7000; // Umbral de si se coloca o no el dedo
const int32_t TH_CP = 300; // Cantidad de cambio detectada es el punto de inicio del pulso
const int32_t MIN_INIT = 9999999; //Valor inicial del valor mínimo
const int32_t MAX_INIT = 0; //Valor inicial de valor máximo
//Frecuencia cardíaca y SpO2 mostrados (cambie según corresponda según la aplicación)
const uint32_t DISP_MIN_HR = 30; // valor mínimo de frecuencia cardiaca
const uint32_t DISP_MAX_HR = 180; // valor máximo de frecuencia cardiaca
const uint32_t DISP_MIN_SPO2 = 70; // saturación de oxígeno mínimo
const uint32_t DISP_MAX_SPO2 = 100; // saturación de oxígeno máximo
// Variable de retención de detección de pulso
long l_time = millis(); //Retención del tiempo de detección del último pulso
int32_t Ult_ir_v = 0; //Mantenga el último valor de ir_v
int32_t R_diff = 0; // Reteniendo la última diferencia
long pulse_interval = -1; // Tiempo de intervalo de pulso
//Retención de los valores máximos y mínimos de los datos brutos en un pulso
int32_t min_ir_v = MIN_INIT , max_ir_v = MAX_INIT;
int32_t min_red_v= MIN_INIT, max_red_v = MAX_INIT;
//Media móvil (IR_DC, RED_DC) 30 (20-50) muestras
movingAvg avgIr_v (30);
movingAvg avgRed_v (30);
// Promedio móvil (la frecuencia cardíaca es el promedio de los últimos 3 latidos, SPO2 es
//el promedio de 5 latidos)
movingAvg avgHR (3);
movingAvg avgSPO2 (5);

void setup()
{ Wire.begin(); // Configuración de pines I2C
 Serial.begin(115200); // Usar el puerto serial.
 // Inicialización del sensor
 while(!Sensor.begin(Wire, I2C_SPEED_FAST))
 { Serial.print("."); // sensor no encotrado
 }
 //******************Configuración del sensor MAX30102 *********************
 byte ledBrightness = 0x1F; // Options: 0=Off to 255=50mA
 byte diffmpleAverage = 8; //Options: 1, 2, 4, 8, 16, 32
 byte ledMode = 2; // (que led usar): 1 = Rojo, 2 = R + IR, 3 = R + IR+ verde
 int diffmpleRate = 400; // Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
 int pulse_intervalWidth = 411; //Options: 69, 118, 215, 411
 int adcRange = 4096; //Options: 2048, 4096, 8192, 16384
Sensor.setup(ledBrightness, diffmpleAverage, ledMode, diffmpleRate, pulse_intervalWidth,
adcRange); //ingresar los datos de la configuración
//**********************************************************************
 //Leer una vez como valor inicial (use ir_v para medir el pulso)
 Ult_ir_v = Sensor.getRed();
 //Inicialización del tiempo de adquisición final del pulso
 l_time = millis();
 //Inicialización de la biblioteca movingAvg.h
 avgIr_v.begin();
 avgRed_v.begin();
 avgHR.begin();
 avgSPO2.begin();
}
void loop()
{
 //Es al revés. Dado que el sensor está devolviendo lo contrario, verifique cada uno
 uint32_t red_v = Sensor.getIR(); // leer la señal del led infrarrojo
 uint32_t ir_v = Sensor.getRed(); // leer la señal del led Rojo

//Pones tu dedo
 if(red_v< TH_dedo || ir_v < TH_dedo) return; // reconocer que el dedo esta en el sensor
 //Media móvil (cálculo de IR_DC RED_DC)
 double ir_v_dc = avgIr_v.reading(ir_v);
 double red_v_dc = avgRed_v.reading(red_v);
 //Actualice los valores máximo e inicial para encontrar la CA (arterial pulsátil) de IR y
//ROJO
 if(ir_v<min_ir_v) min_ir_v = ir_v;
 if(ir_v>max_ir_v) max_ir_v = ir_v;
 if(red_v<min_red_v) min_red_v = red_v;
 if(red_v>max_red_v) max_red_v = red_v;
 //Utilice ir_v para la detección de pulsos.
 //Encuentra la diferencia (cambiar valor) de la vez anterior
 int32_t diff =Ult_ir_v- ir_v;
 //Si hay un cambio de TH_CP o más, será el punto de inicio del pulso.
 if(R_diff < TH_CP && diff > TH_CP)
 {
 //Calcule el tiempo de un pulso
 pulse_interval = millis() - l_time;
 l_time = millis();
 //La frecuencia cardíaca se calcula a partir del momento de un pulso.
 //Dado que avgHR es solo un número entero,
 //multiplíquelo por 1000 y divídalo por 1000 para mantener un número pequeño.
 double hr = (double)avgHR.reading(60000*1000/pulse_interval) / 1000.0;
 //Cálculo de SPO2
 //Encuentre CA de IR / RED (Amplitud máxima-Amplitud mínima)
 int32_t ir_v_ac = max_ir_v-min_ir_v;
 int32_t red_v_ac = max_red_v-min_red_v;
 // De la fórmula de R = (AC_RED / DC_RED) / (AC_IR / DC_IR)
 double red_div = double(red_v_ac)/red_v_dc;
 double ir_div = double(ir_v_ac)/ir_v_dc;
 double R = red_div / ir_div;
 // SPO2 = -45.060*R^2 + 30.354*R + 94.845

 //Esto se aplica mutatis mutandis a lo que estaba en spo2_algorithm.cpp
 // Multiplicar y dividir 1000 es para tener un número pequeño
 double spo2 = (double)avgSPO2.reading((-45.060*R*R + 30.354*R + 94.845)*1000.0) /
1000.0;
 //Inicialización de valores máximos y mínimos
 min_ir_v = MIN_INIT;
 max_ir_v = MAX_INIT;
 min_red_v = MIN_INIT;
 max_red_v = MAX_INIT;
 //Pantalla de frecuencia cardíaca y SPO2 (el rango se puede cambiar por definición)
 if(hr <= DISP_MAX_HR && hr >= DISP_MIN_HR && spo2 <= DISP_MAX_SPO2 &&
spo2 >= DISP_MIN_SPO2)
 {
 Serial.print("Frecuencia Cardiaca =");
 Serial.print(hr);
 Serial.print("Ppm");
 Serial.print(" ");
 Serial.print("Saturación de oxígeno =");
 Serial.print(spo2);
 Serial.println("%");
 }
 }
 //Retención del valor de detección de pulso
 Ult_ir_v = ir_v;
 R_diff = diff;
}