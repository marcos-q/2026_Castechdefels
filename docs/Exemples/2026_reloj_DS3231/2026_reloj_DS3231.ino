/*
 * ============================================================================
 * PROYECTO: Reloj Digital RTC con Interfaz OLED y Ajuste por Botones/USB
 * ============================================================================
 * * DESCRIPCIÓN:
 * Este código implementa un reloj digital utilizando un módulo RTC (ej. DS3231) 
 * y una pantalla OLED (SSD1306 de 128x64 píxeles). Permite la visualización 
 * de la fecha y la hora, así como su ajuste mediante dos vías:
 * * 1. Ajuste Manual (Hardware): 
 * - Utiliza 3 botones físicos configurados con resistencias PULL-UP internas.
 * - Pulsación larga (2 segundos) en el botón 'Modo' para entrar al menú de ajuste.
 * - Pulsaciones cortas en 'Modo' para navegar: Hora -> Min -> Día -> Mes -> Año.
 * - Botones '+' y '-' para modificar los valores seleccionados.
 * - Barra visual de progreso y salida automática tras 5 segundos de inactividad.
 * * 2. Ajuste por Puerto Serie (USB):
 * - Escucha el puerto serie a 9600 baudios.
 * - Sincroniza la hora enviando una cadena con el formato: TAAAAMMDDHHMMSS
 * (Ejemplo: T20260327105000 para el 27 de Marzo de 2026 a las 10:50:00).
 * * HARDWARE Y CONEXIONES:
 * - Pantalla OLED (I2C): SDA -> Pin SDA, SCL -> Pin SCL
 * - Módulo RTC (I2C):    SDA -> Pin SDA, SCL -> Pin SCL
 * - Botón Modo / Siguiente:  Pin Digital 4  (conectar el otro extremo a GND)
 * - Botón Más (+):           Pin Digital 2  (conectar el otro extremo a GND)
 * - Botón Menos (-):         Pin Digital 3  (conectar el otro extremo a GND)
 * * LIBRERÍAS REQUERIDAS:
 * - Adafruit GFX Library
 * - Adafruit SSD1306
 * - RTClib (de Adafruit)
 * ============================================================================
 */
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
RTC_DS3231 rtc;

// --- CONFIGURACIÓN DE PINES ---
const int btnModo  = 6; // Cambia de campo (Hora -> Min -> Dia...)
const int btnMas   = 7; // Incrementa el valor
const int btnMenos = 8; // Decrementa el valor

// --- PINES PARA ESP32-C3 SUPERMINI ---
const int PIN_LDR = 0;      

const int LED_R = 9;
const int LED_G = 10;
const int LED_B = 20;
const int BUZZER = 5;
const int PIN_SDA = 3;
const int PIN_SCL = 4;


// --- MÁQUINA DE ESTADOS ---
enum EstadoAjuste { NORMAL, AJUSTE_HORA, AJUSTE_MIN, AJUSTE_DIA, AJUSTE_MES, AJUSTE_ANO };
EstadoAjuste estadoActual = NORMAL;

unsigned long ultimoToqueBoton = 0;
int ultimoSegundoSerial = -1;
const unsigned long TIMEOUT_AJUSTE = 5000; // 5 segundos de inactividad para salir

// --- VARIABLES PARA PULSACIÓN LARGA ---
bool estadoAnteriorModo = HIGH;
unsigned long tiempoInicioModo = 0;
const unsigned long TIEMPO_PULSACION_LARGA = 2000; // 2000 milisegundos = 2 segundos
bool modoProcesadoLargo = false;

void setup() {
  Serial.begin(9600);
  pinMode(btnModo, INPUT_PULLUP);
  pinMode(btnMas, INPUT_PULLUP);
  pinMode(btnMenos, INPUT_PULLUP);

  Wire.begin(PIN_SDA, PIN_SCL); 

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) for(;;);
  display.clearDisplay();
  display.setTextColor(WHITE);

  if (!rtc.begin()) while (1);
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime ahora = rtc.now();

  // --- 1. LÓGICA DEL BOTÓN MODO (Pulsación Larga vs Corta) ---
  bool estadoActualModo = digitalRead(btnModo);

  if (estadoActualModo == LOW && estadoAnteriorModo == HIGH) {
    // Flanco de bajada: Empezamos a pulsar el botón
    tiempoInicioModo = millis();
    modoProcesadoLargo = false;
  }

  if (estadoActualModo == LOW) {
    // El botón se mantiene pulsado
    if (estadoActual == NORMAL) {
      if (!modoProcesadoLargo && (millis() - tiempoInicioModo >= TIEMPO_PULSACION_LARGA)) {
        estadoActual = AJUSTE_HORA;
        ultimoToqueBoton = millis();
        modoProcesadoLargo = true; // Marcamos para no seguir disparando esto
        Serial.println(F("\n>>> MODO AJUSTE ACTIVADO <<<"));
      }
    }
  } else if (estadoActualModo == HIGH && estadoAnteriorModo == LOW) {
    // Flanco de subida: Soltamos el botón
    if (estadoActual != NORMAL && !modoProcesadoLargo) {
      // Si ya estábamos en ajuste y ha sido un clic corto, pasamos al siguiente menú
      estadoActual = static_cast<EstadoAjuste>((estadoActual + 1) % 6);
      ultimoToqueBoton = millis();
      if (estadoActual == NORMAL) {
         Serial.println(F(">>> MODO AJUSTE FINALIZADO (SALIDA MANUAL) <<<\n"));
      }
    }
  }
  estadoAnteriorModo = estadoActualModo;

  // --- 2. TIMEOUT DE INACTIVIDAD ---
  if (estadoActual != NORMAL && (millis() - ultimoToqueBoton >= TIMEOUT_AJUSTE)) {
    estadoActual = NORMAL;
    Serial.println(F(">>> MODO AJUSTE FINALIZADO (INACTIVIDAD) <<<\n"));
  }

  // --- 3. LÓGICA DE LOS BOTONES + Y - (Ajuste de valores) ---
  if (estadoActual != NORMAL) {
    bool btnMasPresionado = (digitalRead(btnMas) == LOW);
    bool btnMenosPresionado = (digitalRead(btnMenos) == LOW);

    if (btnMasPresionado || btnMenosPresionado) {
      int y = ahora.year(), m = ahora.month(), d = ahora.day();
      int h = ahora.hour(), mi = ahora.minute();

      if (estadoActual == AJUSTE_HORA) {
        h = btnMasPresionado ? (h + 1) % 24 : (h + 23) % 24;
      } 
      else if (estadoActual == AJUSTE_MIN) {
        mi = btnMasPresionado ? (mi + 1) % 60 : (mi + 59) % 60;
      } 
      else if (estadoActual == AJUSTE_DIA) {
        DateTime nuevaFecha = btnMasPresionado ? ahora + TimeSpan(1,0,0,0) : ahora - TimeSpan(1,0,0,0);
        y = nuevaFecha.year(); m = nuevaFecha.month(); d = nuevaFecha.day();
      } 
      else if (estadoActual == AJUSTE_MES) {
        m = btnMasPresionado ? (m == 12 ? 1 : m + 1) : (m == 1 ? 12 : m - 1);
      } 
      else if (estadoActual == AJUSTE_ANO) {
        y = btnMasPresionado ? y + 1 : y - 1;
      }

      rtc.adjust(DateTime(y, m, d, h, mi, 0)); 
      ultimoToqueBoton = millis();
      ahora = rtc.now(); 
      delay(200); 
    }
  }

  // --- 4. SINCRONIZACIÓN USB ---
  if (Serial.available() >= 15) {
    if (Serial.read() == 'T') {
      char buffer[15];
      Serial.readBytes(buffer, 14);
      buffer[14] = '\0'; 

      int y  = (String(buffer).substring(0, 4)).toInt();
      int m  = (String(buffer).substring(4, 6)).toInt();
      int d  = (String(buffer).substring(6, 8)).toInt();
      int h  = (String(buffer).substring(8, 10)).toInt();
      int mi = (String(buffer).substring(10, 12)).toInt();
      int s  = (String(buffer).substring(12, 14)).toInt();

      rtc.adjust(DateTime(y, m, d, h, mi, s));
      Serial.print(F("Nueva hora grabada por USB: "));
      Serial.println(buffer);
    }
  }

  // --- 5. REFRESCO DE PANTALLA Y PUERTO SERIE ---
  if (ahora.second() != ultimoSegundoSerial) {
    imprimirSerial(ahora);
    ultimoSegundoSerial = ahora.second();
  }
  dibujarOLED(ahora);
}

void imprimirSerial(DateTime t) {
  char buffer[25];
  sprintf(buffer, "%02d/%02d/%04d %02d:%02d:%02d", t.day(), t.month(), t.year(), t.hour(), t.minute(), t.second());
  Serial.println(buffer);
}

void dibujarOLED(DateTime t) {
  display.clearDisplay();

  // --- CABECERA DE ESTADO ---
  display.setTextSize(1);
  display.setCursor(0, 0);
  switch(estadoActual) {
    case NORMAL:      
      // display.setCursor(30, 0); display.print(F("RELOJ RTC")); 
      break;
    case AJUSTE_HORA: display.print(F(">> AJUSTANDO HORA")); break;
    case AJUSTE_MIN:  display.print(F(">> AJUSTANDO MINUTOS")); break;
    case AJUSTE_DIA:  display.print(F(">> AJUSTANDO DIA")); break;
    case AJUSTE_MES:  display.print(F(">> AJUSTANDO MES")); break;
    case AJUSTE_ANO:  display.print(F(">> AJUSTANDO ANO")); break;
  }

  // --- DIBUJAR FECHA ---
  display.setCursor(30, 15);
  char dateBuf[11];
  sprintf(dateBuf, "%02d/%02d/%04d", t.day(), t.month(), t.year());
  display.print(dateBuf);

  // --- DIBUJAR HORA ---
  display.setTextSize(2);
  display.setCursor(15, 35);
  char timeBuf[9];
  sprintf(timeBuf, "%02d:%02d:%02d", t.hour(), t.minute(), t.second());
  display.print(timeBuf);

  // --- BARRA INFERIOR DE TIMEOUT ---
  if (estadoActual != NORMAL) {
    int barWidth = map(millis() - ultimoToqueBoton, 0, TIMEOUT_AJUSTE, 128, 0);
    display.fillRect(0, 60, barWidth, 4, WHITE);
  }

  display.display();
}