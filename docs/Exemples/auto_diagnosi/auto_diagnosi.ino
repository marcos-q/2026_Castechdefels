#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_AHTX0.h> // Librería para el sensor AHT20
#include <RTClib.h>         // Librería para el Reloj de Tiempo Real

// --- CONFIGURACIÓN PANTALLA OLED ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- INICIALIZACIÓN DE SENSORES I2C ---
Adafruit_AHTX0 aht;
RTC_DS3231 rtc; // Cambiar a RTC_PCF8563 o RTC_DS1307 según el chip de tu PCB

// --- ASIGNACIÓN DE PINES (Fiel a tu diseño de PCB) ---
const int PIN_LDR = 0;      
const int PIN_BTN_A = 6;
const int PIN_BTN_B = 7;
const int LED_R = 21;
const int LED_G = 20;
const int LED_B = 10;
const int BUZZER = 5;
const int PIN_SDA = 3;
const int PIN_SCL = 4;

// Variables de control para evitar cuelgues si falla el hardware I2C
bool ahtActivo = false;
bool rtcActivo = false;

void setup() {
  Serial.begin(115200);
  
  // Configuración de entradas y salidas fijas
  pinMode(PIN_BTN_A, INPUT_PULLUP);
  pinMode(PIN_BTN_B, INPUT_PULLUP);
  pinMode(LED_R, OUTPUT); 
  pinMode(LED_G, OUTPUT); 
  pinMode(LED_B, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Aseguramos que los LEDs arranquen apagados
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);

  // Inicialización del canal I2C personalizado de tu placa (SDA=3, SCL=4)
  Wire.begin(PIN_SDA, PIN_SCL); 

  // 1. CONTROL DE CALIDAD: Pantalla OLED
  if(display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("INICIANDO TEST...");
    display.display();
  } else {
    Serial.println(F("Error: OLED no detectado en bus I2C"));
  }

  // 2. CONTROL DE CALIDAD: Sensor de Clima AHT20
  if(aht.begin()) {
    ahtActivo = true;
    Serial.println(F("AHT20 inicializado con exito")); 
  } else {
    Serial.println(F("Error: AHT20 no responde"));
  }

  // 3. CONTROL DE CALIDAD: Reloj en Tiempo Real (RTC)
  if (rtc.begin()) {
    rtcActivo = true;
    Serial.println(F("RTC detectado en bus I2C"));
    // Si el reloj perdió la hora (ej: cambio de pila), se sincroniza con el PC
    if (rtc.lostPower()) {
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
  } else {
    Serial.println(F("Error: RTC no encontrado"));
  }

  // Pitido de confirmación de arranque del test
  tone(BUZZER, 1800, 100); delay(120);
  tone(BUZZER, 2200, 150); delay(150);
  noTone(BUZZER);
}

void loop() {
  // === 1. LECTURA DE SENSÓRICA ===
  int nivelLuz = analogRead(PIN_LDR);
  
  float temp = 0.0;
  float hum = 0.0;
  if (ahtActivo) {
    sensors_event_t sensor_humidity, sensor_temp;
    aht.getEvent(&sensor_humidity, &sensor_temp); // El AHT20 requiere eventos unificados
    temp = sensor_temp.temperature;
    hum = sensor_humidity.relative_humidity;
  }

  String horaText = "Sin RTC";
  if (rtcActivo) {
    DateTime ahora = rtc.now();
    char formatHora[] = "hh:mm:ss";
    horaText = String(ahora.toString(formatHora));
  }

  // === 2. VERIFICACIÓN DE PULSADORES e INTERACCIÓN ===
  bool pulsadoA = (digitalRead(PIN_BTN_A) == LOW);
  bool pulsadoB = (digitalRead(PIN_BTN_B) == LOW);

  if (pulsadoA) {
    digitalWrite(LED_G, HIGH); // Botón A enciende el canal Verde
    tone(BUZZER, 1100);        // Tono medio
  } else if (pulsadoB) {
    digitalWrite(LED_R, HIGH); // Botón B enciende el canal Rojo
    tone(BUZZER, 1600);        // Tono agudo
  } else {
    // Si nadie toca nada, el robot permanece en reposo con iluminación azul tenue
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    analogWrite(LED_B, 25);    
    noTone(BUZZER);
  }

  // === 3. INTERFAZ GRÁFICA DE DIAGNÓSTICO (OLED) ===
  display.clearDisplay();
  
  // Dibujamos un marco estético protector de pantalla
  display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
  
  // Título del banco de pruebas
  display.setTextSize(1);
  display.setCursor(6, 6);
  display.print("PANEL DE DIAGNOSTICO");

  // Mostrar datos de Temperatura y Humedad (AHT20)
  display.setCursor(8, 18);
  if (ahtActivo) {
    display.print("T: "); display.print(temp, 1); display.print(" C  ");
    display.print("H: "); display.print(hum, 0); display.print("%");
  } else {
    display.print("AHT20: ¡FALLO!");
  }

  // Mostrar datos del fotosensor (LDR)
  display.setCursor(8, 29);
  display.print("Sensor LDR: "); display.print(nivelLuz);

  // Mostrar datos del reloj (RTC)
  display.setCursor(8, 40);
  display.print("Hora RTC: "); display.print(horaText);

  // Estado lógico y en tiempo real de los botones integrados
  display.setCursor(8, 51);
  display.print("Puls.: A:[");
  display.print(pulsadoA ? "X" : " ");
  display.print("] B:[");
  display.print(pulsadoB ? "X" : " ");
  display.print("]");

  // Volcamos el buffer a los píxeles físicos de la pantalla
  display.display();
  
  delay(50); // Pequeño retardo de estabilidad para el bus de datos
}