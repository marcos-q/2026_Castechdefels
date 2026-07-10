#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SHT31.h>

/* =========================================================
 * TUTORIAL: ROBOT CON EXPRESIONES OLED (ESTILO COZMO)
 * Plataforma: ESP32-C3 SuperMini
 * =========================================================
 * NOTA PARA EL PROFESOR: 
 * Si no ves mensajes en el Monitor Serie del ESP32-C3:
 * 1. Ve a Herramientas -> USB CDC On Boot y ponlo en "Enabled".
 * 2. Asegúrate de que la velocidad sea 115200 baudios.
 * =========================================================
 */

// --- CONFIGURACIÓN HARDWARE ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_SHT31 sht31 = Adafruit_SHT31();

// --- PINES PARA ESP32-C3 SUPERMINI ---
const int PIN_LDR = 0;      
const int PIN_BTN_A = 6;
const int PIN_BTN_B = 7;
//const int PIN_BTN_C = 8;
const int LED_R = 21;
const int LED_G = 20;
const int LED_B = 10;
const int BUZZER = 5;
const int PIN_SDA = 3;
const int PIN_SCL = 4;

// --- VARIABLES DE ESTADO Y TIEMPO ---
enum Estado { DESPIERTO, DURMIENDO, ASUSTADO, FELIZ };
Estado estadoActual = DESPIERTO;

int umbralOscuridad = 300; 
unsigned long tiempoUltimoRonquido = 0;
unsigned long ultimoParpadeo = 0;
bool parpadeando = false;

// --- PROTOTIPOS DE FUNCIONES ---
void actualizarPantalla(int luz);
void actualizarLED();
void sonidoContento();
void sonidoAsustado();
void sonidoRonquido();
void sonidoSaludoR2D2();

// ================= SETUP =================
void setup() {
  Serial.begin(115200);
  
  // Configuración de pines
  pinMode(PIN_BTN_A, INPUT_PULLUP);
  pinMode(PIN_BTN_B, INPUT_PULLUP);
  //pinMode(PIN_BTN_C, INPUT_PULLUP);
  pinMode(LED_R, OUTPUT); 
  pinMode(LED_G, OUTPUT); 
  pinMode(LED_B, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Inicialización I2C y Sensores/Pantalla
  Wire.begin(PIN_SDA, PIN_SCL); 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Fallo al iniciar OLED"));
  }
  if(!sht31.begin(0x44)) {
    Serial.println(F("Fallo al iniciar SHT31")); 
  }

  // Limpiar pantalla inicial y ajustar orientación
  display.clearDisplay();
  //display.setRotation(2); // Gira la pantalla 180 grados si está invertida

  // Saludo inicial
  sonidoSaludoR2D2();
}

// ================= LOOP =================
void loop() {
  // 1. LECTURA DE SENSORES
  int nivelLuz = analogRead(PIN_LDR);
  bool btnPulsado = (digitalRead(PIN_BTN_A) == LOW || digitalRead(PIN_BTN_B) == LOW);

  // 2. LÓGICA DE TRANSICIÓN DE ESTADOS
  if (nivelLuz < umbralOscuridad) {
    if (estadoActual != DURMIENDO) {
      estadoActual = DURMIENDO;
      tone(BUZZER, 440, 500); // Sonido de bostezo/despedida
    }
    // Ronquido periódico no bloqueante
    if (millis() - tiempoUltimoRonquido > 10000) {
      sonidoRonquido();
      tiempoUltimoRonquido = millis();
    }
  } 
  else if (nivelLuz > umbralOscuridad && estadoActual == DURMIENDO) {
    // Si despierta de golpe por la luz
    estadoActual = ASUSTADO; 
    actualizarPantalla(nivelLuz); // Forzamos actualización para ver la cara de susto
    digitalWrite(LED_R, HIGH); 
    sonidoAsustado(); 
    digitalWrite(LED_R, LOW);
    estadoActual = DESPIERTO;
  }
  
  if (btnPulsado && estadoActual != DURMIENDO) {
    // Reacción a las caricias (botones)
    estadoActual = FELIZ;
    actualizarPantalla(nivelLuz); // Dibujamos la cara feliz al instante
    sonidoContento(); 
  }

  // 3. ACTUALIZACIÓN DE ACTUADORES (Pantalla y LEDs)
  actualizarPantalla(nivelLuz);
  actualizarLED();
  
  // 4. RETORNOS DE ESTADO (Salir de estados temporales)
  if (estadoActual == FELIZ) { 
    delay(1000); // Mantenemos la sonrisa un segundo
    estadoActual = DESPIERTO; 
  }
  
  delay(50); // Pequeña pausa para no saturar el bus I2C ni el procesador
}

// ================= CONTROL DE PANTALLA OLED =================
void actualizarPantalla(int luz) {
  display.clearDisplay();
  display.setTextColor(WHITE);
  
  // Imprimir sensor de luz en la esquina
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("LUZ: "); display.print(luz);
  
  // Dibujar Expresiones según el estado
  switch(estadoActual) {
    
    case DURMIENDO:
      // Ojos como líneas horizontales cerradas
      display.drawFastHLine(30, 35, 25, WHITE); 
      display.drawFastHLine(73, 35, 25, WHITE);
      display.setCursor(95, 20);
      display.print("zZz");
      break;

    case FELIZ:
      // Ojos hacia arriba (estilo ^ ^)
      display.fillRoundRect(30, 20, 25, 20, 5, WHITE);
      display.fillRoundRect(73, 20, 25, 20, 5, WHITE);
      // "Boca" de felicidad
      display.drawCircleHelper(64, 45, 10, 4, WHITE); 
      display.drawCircleHelper(64, 45, 10, 8, WHITE);
      break;

    case ASUSTADO:
      // Ojos muy abiertos, temblando
      display.drawRoundRect(30, 15, 25, 35, 8, WHITE); 
      display.drawRoundRect(73, 15, 25, 35, 8, WHITE);
      display.fillCircle(42, 32, 4, WHITE); // Pupilas contraídas
      display.fillCircle(85, 32, 4, WHITE);
      break;

    case DESPIERTO:
    default:
      // --- LÓGICA DE PARPADEO (Blink) ---
      // Si han pasado 3 segundos, iniciamos el parpadeo
      if (millis() - ultimoParpadeo > 3000) {
        parpadeando = true;
        ultimoParpadeo = millis();
      }
      // El parpadeo dura solo 150 milisegundos
      if (parpadeando && (millis() - ultimoParpadeo > 150)) {
        parpadeando = false;
      }

      if (parpadeando) {
        // Ojos cerrados por una fracción de segundo
        display.drawFastHLine(30, 35, 25, WHITE); 
        display.drawFastHLine(73, 35, 25, WHITE);
      } else {
        // Ojos normales abiertos
        display.fillRoundRect(30, 20, 25, 30, 8, WHITE); 
        display.fillRoundRect(73, 20, 25, 30, 8, WHITE);
        // Pupilas
        display.fillCircle(42, 32, 3, BLACK); 
        display.fillCircle(85, 32, 3, BLACK);
      }
      break;
  }

  // ¡Enviamos el buffer a la pantalla!
  display.display(); 
}

// ================= CONTROL DE LEDS RGB =================
void actualizarLED() {
  digitalWrite(LED_R, LOW); 
  digitalWrite(LED_G, LOW); 
  digitalWrite(LED_B, LOW);
  
  if (estadoActual == DURMIENDO) analogWrite(LED_B, 10);  // Azul muy suave
  if (estadoActual == FELIZ) digitalWrite(LED_G, HIGH);     // Verde fuerte
  if (estadoActual == ASUSTADO) digitalWrite(LED_R, HIGH);  // Rojo (por si acaso no se apaga)
  if (estadoActual == DESPIERTO) analogWrite(LED_B, 100);   // Azul medio
}

// ================= BIBLIOTECA DE SONIDOS =================
void sonidoContento() {
  tone(BUZZER, 1500, 100); delay(100);
  tone(BUZZER, 2000, 100); delay(100);
  tone(BUZZER, 2500, 150); delay(150);
  noTone(BUZZER);
}

void sonidoAsustado() {
  for (int i = 0; i < 6; i++) {
    tone(BUZZER, 4000, 40); delay(40);
    tone(BUZZER, 2000, 40); delay(40);
  }
  noTone(BUZZER);
}

void sonidoRonquido() {
  for (int f = 200; f < 350; f += 5) {
    tone(BUZZER, f, 20); delay(20);
  }
  delay(200); 
  for (int f = 350; f > 200; f -= 5) {
    tone(BUZZER, f, 25); delay(25);
  }
  noTone(BUZZER);
}

void sonidoSaludoR2D2() {
  for (int f = 1000; f < 3000; f += 80) {
    tone(BUZZER, f, 15); delay(15);
  }
  for (int i = 0; i < 2; i++) {
    tone(BUZZER, 3500, 30); delay(40);
    tone(BUZZER, 4000, 30); delay(40);
  }
  noTone(BUZZER);
}