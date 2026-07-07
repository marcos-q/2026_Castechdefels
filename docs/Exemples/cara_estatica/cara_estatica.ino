#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int PIN_SDA = 3;
const int PIN_SCL = 4;

void setup() {
  Wire.begin(PIN_SDA, PIN_SCL); 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while(true);
  }

  // Netejem la pantalla per preparar la nova cara
  display.clearDisplay();
  
  // 1. El contorn del cap (es manté igual)
  display.drawRoundRect(10, 5, 108, 54, 8, SSD1306_WHITE);

  // 2. Ulls tancats (Línies horitzontals en lloc de cercles)
  display.drawLine(30, 25, 45, 25, SSD1306_WHITE); // Ull esquerre tancat
  display.drawLine(83, 25, 98, 25, SSD1306_WHITE); // Ull dret tancat

  // 3. Boca (Un cercle petit dibuixant una "O" de roncar)
  display.drawCircle(64, 40, 4, SSD1306_WHITE);

  // 4. Detall extra: Text combinat amb dibuix
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(95, 10);
  display.print("Zzz...");

  // Mostrem la nova cara!
  display.display(); 
}

void loop() {
  // Animació futura? De moment es queda adormida!
}