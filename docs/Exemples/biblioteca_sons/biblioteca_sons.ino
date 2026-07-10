#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- CONFIGURACIÓN HARDWARE ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define i2c_Address 0x3C 

// Declaración para la pantalla SSD1306
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pin del buzzer para ESP32-C3 SuperMini
const int BUZZER = 5;

// --- PROTOTIPOS DE FUNCIONES DE SONIDO ---
void sonidoContento();
void sonidoError();
void sonidoAsustado();
void sonidoRonquido();
void sonidoSaludoR2D2();
void mostrarEstado(const char* texto);

void setup() {
  Serial.begin(115200);
  
  pinMode(BUZZER, OUTPUT);

  // Inicializar I2C para la ESP32-C3 (Pines 4 y 3)
  Wire.begin(4, 3); 
  
  // Inicialización específica para SSD1306
  if(!display.begin(SSD1306_SWITCHCAPVCC, i2c_Address)) {
    Serial.println("SSD1306 fallo");
    while(1); // Detener si no hay pantalla
  }

  display.clearDisplay();
  display.setRotation(2); // Ajuste de 180 grados
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  
  Serial.println("--- TEST DE AUDIO INICIADO (SSD1306) ---");
}

void loop() {
  // 1. Saludo inicial
  mostrarEstado("SALUDO");
  sonidoSaludoR2D2();
  delay(2000);

  // 2. Estado contento
  mostrarEstado("CONTENTO");
  sonidoContento();
  delay(2000);

  // 3. Estado asustado
  mostrarEstado("ASUSTADO");
  sonidoAsustado();
  delay(2000);

  // 4. Estado error/hambre
  mostrarEstado("ERROR");
  sonidoError();
  delay(2000);

  // 5. Estado durmiendo (ronquido)
  mostrarEstado("RONQUIDO");
  sonidoRonquido();
  delay(3000);
}

// --- FUNCIONES DE APOYO ---

void mostrarEstado(const char* texto) {
  display.clearDisplay();
  // Dibujar un recuadro estético
  display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
  
  // Centrar texto (aproximado)
  display.setCursor(15, 25);
  display.print(texto);
  display.display();
  Serial.print("Reproduciendo: ");
  Serial.println(texto);
}

// --- LIBRERÍA DE SONIDOS ---

void sonidoContento() {
  tone(BUZZER, 1500, 100); delay(100);
  tone(BUZZER, 2000, 100); delay(100);
  tone(BUZZER, 2500, 150); delay(150);
  noTone(BUZZER);
}

void sonidoError() {
  tone(BUZZER, 400, 300);  delay(350);
  tone(BUZZER, 300, 500);  delay(500);
  noTone(BUZZER);
}

void sonidoAsustado() {
  for (int i = 0; i < 5; i++) {
    tone(BUZZER, 4000, 50); delay(50);
    tone(BUZZER, 2500, 50); delay(50);
  }
  noTone(BUZZER);
}

void sonidoRonquido() {
  // Inhalación
  for (int f = 100; f < 300; f += 5) {
    tone(BUZZER, f, 20); delay(20);
  }
  delay(250); 
  // Exhalación
  for (int f = 300; f > 100; f -= 5) {
    tone(BUZZER, f, 30); delay(30);
  }
  noTone(BUZZER);
}

void sonidoSaludoR2D2() {
  for (int f = 1000; f < 3000; f += 50) {
    tone(BUZZER, f, 10); delay(10);
  }
  for (int i = 0; i < 3; i++) {
    tone(BUZZER, 3500, 20); delay(30);
    tone(BUZZER, 4000, 20); delay(30);
  }
  for (int f = 3000; f > 1500; f -= 100) {
    tone(BUZZER, f, 15); delay(15);
  }
  noTone(BUZZER);
}