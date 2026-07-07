#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;

Adafruit_SSD1306 pantalla(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pins I2C  de la nostra placa
const int PIN_SDA = 3;
const int PIN_SCL = 4;

void setup() {
  Serial.begin(115200);
  
  Wire.begin(PIN_SDA, PIN_SCL); 

  if(!pantalla.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Error d'OLED"));
    while(true);
  }

  // 1. Esborrem la pantalla per tenir un llenç net
  pantalla.clearDisplay();
  
  // 2. Dibuixem tots els elements de la cara a la memòria
  
  // Cap (Rectangle arrodonit)
  pantalla.drawRoundRect(10, 5, 108, 54, 8, SSD1306_WHITE);
  
  // Ulls (Cercles)
  pantalla.fillCircle(40, 20, 10, SSD1306_WHITE); // Ull esquerre ple
  pantalla.drawCircle(88, 20, 10, SSD1306_WHITE); // Ull dret buit
  
  // Nas (Un sol píxel)
  pantalla.drawPixel(64, 32, SSD1306_WHITE);
  
  // Boca (Línia)
  pantalla.drawLine(44, 45, 84, 45, SSD1306_WHITE);
  
  // 3. ENVIEM EL DIBUIX A LA PANTALLA!
  pantalla.display(); 
}

void loop() {
  // Com que és un dibuix fix, no fem res al loop.
}