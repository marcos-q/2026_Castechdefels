#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pins I2C i Botons
const int PIN_SDA = 3;
const int PIN_SCL = 4;
const int PIN_BTN_A = 6;  // Botó Esquerre (Baixar energia)
const int PIN_BTN_B = 7;  // Botó Dret (Pujar energia)

// Aquesta és la variable clau! Comencem amb l'energia a la meitat.
int energia = 50; 

void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_BTN_A, INPUT_PULLUP);
  pinMode(PIN_BTN_B, INPUT_PULLUP);

  Wire.begin(PIN_SDA, PIN_SCL); 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Error d'OLED"));
    while(true);
  }
}

void loop() {
  // 1. LLEGIM ELS BOTONS
  // Si premem el botó A, restem 5 punts d'energia
  if (digitalRead(PIN_BTN_A) == LOW) {
    energia = energia - 5;
  }
  
  // Si premem el botó B, sumem 5 punts d'energia
  if (digitalRead(PIN_BTN_B) == LOW) {
    energia = energia + 5;
  }

  // 2. POSEM LÍMITS (No podem tenir energia negativa ni més de 100)
  if (energia < 0) {
    energia = 0;
  }
  if (energia > 100) {
    energia = 100;
  }

  // 3. DIBUIXEM A LA PANTALLA
  display.clearDisplay(); // Netegem la pantalla anterior

  // Escrivim el títol i el número exacte
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(12, 10);
  display.print("Nivell d'Energia:");
  display.setCursor(12, 22);
  display.print(energia);
  display.print(" %");

  // Dibuixem el MARC EXTERIOR (Buit)
  // Posició X=12, Y=38. Amplada=104, Alçada=14
  // Ho fem una mica més gran perquè hi càpiga el farcit a dins
  display.drawRect(12, 38, 104, 14, SSD1306_WHITE);

  // DIBUIXEM LA BARRA INTERIOR (Plena)
  // Fixa't bé: l'amplada ve donada per la variable "energia"!
  // Posició X=14, Y=40. Alçada=10
  display.fillRect(14, 40, energia, 10, SSD1306_WHITE);

  // Enviem tot a l'OLED
  display.display();
  
  // Una petita pausa perquè els números no sumin massa ràpid
  delay(100); 
}