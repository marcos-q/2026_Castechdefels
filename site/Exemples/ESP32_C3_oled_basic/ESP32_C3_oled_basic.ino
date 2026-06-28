// ESPP32_C3_oled_basic.ino

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- CONFIGURACIÓ HARDWARE ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define PIN_SDA 8 // Pins I2C per a l' ESP32-C3 SuperMini
#define PIN_SCL 9

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  Wire.begin(PIN_SDA, PIN_SCL); 

  // Iniciar pantalla
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Fallo al iniciar OLED"));
    for(;;);
  }

  display.setRotation(2); // Rotació de 180 graus. Necessari segons com muntem la pantalla
  display.clearDisplay();      // Esborrem el que hi hagi a la memòria
  display.setTextSize(2);      // Triem mida de lletra (1 a 8)
  display.setTextColor(WHITE); // Color del text
   
  display.setCursor(10, 25);   // On comença a escriure (X, Y)
  display.print("HOLA MON!");  // El text que volem mostrar

  display.display();
}

void loop() {
} 