/*
 * ============================================================================
 * PROYECTO: Reloj Digital RTC con Interfaz OLED y Ajuste por 2 Botones / USB
 * ============================================================================
 * * DESCRIPCIÓN:
 * Este código implementa un reloj digital utilizando un módulo RTC (DS3231) 
 * y una pantalla OLED (SSD1306). Permite ajustar la fecha y hora mediante:
 * * 1. Ajuste Manual (Hardware - 2 BOTONES): 
 * - Pulsación larga (2 segundos) en 'Modo' para entrar al menú de ajuste.
 * - Pulsaciones cortas en 'Modo' para navegar: Hora -> Min -> Día -> Mes -> Año.
 * - Botón '+' para incrementar los valores. Al llegar al máximo, vuelven a 0 (Cíclico).
 * - Barra visual de progreso y salida automática tras 5 segundos de inactividad.
 * * 2. Ajuste por Puerto Serie (USB):
 * - Cadena con el formato: TAAAAMMDDHHMMSS (Ej: T20260327105000)
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

// --- CONFIGURACIÓN DE PINES (SISTEMA DE 2 BOTONES) ---
const int btnModo  = 6; // Cambia de campo (Hora -> Min -> Dia...) / Pulsación larga entra
const int btnMas   = 7; // Incrementa el valor de forma cíclico (bucle)
// El botón Menos (Pin 8) ha sido eliminado por restricciones de hardware

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
const unsigned long TIEMPO_PULSACION_LARGA = 2000; 
bool modoProcesadoLargo = false;

void setup() {
  Serial.begin(9600);
  pinMode(btnModo, INPUT_PULLUP);
  pinMode(btnMas, INPUT_PULLUP);

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
        modoProcesadoLargo = true; 
        Serial.println(F("\n>>> MODO AJUSTE ACTIVADO <<<"));
      }
    }
  } else if (estadoActualModo == HIGH && estadoAnteriorModo == LOW) {
    // Flanco de subida: Soltamos el botón
    if (estadoActual != NORMAL && !modoProcesadoLargo) {
      // Clic corto: pasamos al siguiente parámetro
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

  // --- 3. LÓGICA DEL BOTÓN + (Ajuste de valores por incremento cíclico) ---
  if (estadoActual != NORMAL) {
    bool btnMasPresionado = (digitalRead(btnMas) == LOW);

    if (btnMasPresionado) {
      int y = ahora.year(), m = ahora.month(), d = ahora.day();
      int h = ahora.hour(), mi = ahora.minute();

      if (estadoActual == AJUSTE_HORA) {
        h = (h + 1) % 24; // De 23 pasa a 00 automáticamente
      } 
      else if (estadoActual == AJUSTE_MIN) {
        mi = (mi + 1) % 60; // De 59 pasa a 00 automáticamente
      } 
      else if (estadoActual == AJUSTE_DIA) {
        // Incrementa el día. Al usar TimeSpan, RTClib maneja correctamente los fines de mes.
        DateTime nuevaFecha = ahora + TimeSpan(1,0,0,0);
        y = nuevaFecha.year(); m = nuevaFecha.month(); d = nuevaFecha.day();
      } 
      else if (estadoActual == AJUSTE_MES) {
        m = (m == 12) ? 1 : m + 1; // De 12 pasa a 1 automáticamente
      } 
      else if (estadoActual == AJUSTE_ANO) {
        y = y + 1;
        if (y > 2036) y = 2026; // Si se pasa del 2036, regresa al año base 2026
      }

      rtc.adjust(DateTime(y, m, d, h, mi, 0)); 
      ultimoToqueBoton = millis(); // Resetea el tiempo de inactividad
      ahora = rtc.now(); 
      delay(220); // Anti-rebot de software ligeramente aumentado para pulsaciones cómodas
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