#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Dimensions de la pantalla
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;

// Inicialitzem l'objecte de la pantalla
Adafruit_SSD1306 pantalla(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pins I2C del nostre ESP32-C3 SuperMini
const int PIN_SDA = 3;
const int PIN_SCL = 4;

void setup() {
  Serial.begin(115200);
  
  // Iniciem el bus I2C amb els nostres pins
  Wire.begin(PIN_SDA, PIN_SCL); 

  // Iniciem la pantalla OLED a la direcció 0x3C
  if(!pantalla.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Error: No es troba la pantalla OLED"));
    while(true); // Ens aturem aquí si falla
  }

  // Esborrem qualsevol cosa que hi hagués a la pantalla
  pantalla.clearDisplay();
  
  // Cridem a la nostra funció de dibuix
  dibuixarCaraMascota();
  
  // Enviem el dibuix a la pantalla perquè es mostri!
  pantalla.display(); 
}

void loop() {
  // En aquest exemple el dibuix és estàtic, 
  // així que no necessitem posar res al loop de moment.
}

// --- FUNCIÓ PER DIBUIXAR LA CARA ---
void dibuixarCaraMascota() {
  
  // 1. RECTANGLES: El contorn de la cara
  // drawRoundRect(X, Y, Amplada, Alçada, Radi_Cantons, Color)
  // Fem un rectangle amb els cantons arrodonits perquè sembli més amigable
  pantalla.drawRoundRect(10, 5, 108, 54, 8, SSD1306_WHITE);

  // 2. CERCLES: Els ulls (un de buit i un de ple)
  // fillCircle(Centre_X, Centre_Y, Radi, Color) -> Cercle ple
  pantalla.fillCircle(40, 26, 10, SSD1306_WHITE); 
  
  // drawCircle(Centre_X, Centre_Y, Radi, Color) -> Cercle només el contorn
  pantalla.drawCircle(88, 26, 10, SSD1306_WHITE); 
  // Afegim una petita pupil·la a l'ull dret
  pantalla.fillCircle(88, 26, 3, SSD1306_WHITE);

  // 3. LÍNIES: La boca i uns bigotets
  // drawLine(Inici_X, Inici_Y, Final_X, Final_Y, Color)
  
  // Una boca recta (línia horitzontal)
  pantalla.drawLine(44, 45, 84, 45, SSD1306_WHITE);
  
  // Uns petits "bigotets" a les galtes (línies diagonals)
  pantalla.drawLine(15, 30, 25, 35, SSD1306_WHITE); // Bigoti esquerre 1
  pantalla.drawLine(15, 38, 25, 35, SSD1306_WHITE); // Bigoti esquerre 2
  
  pantalla.drawLine(113, 30, 103, 35, SSD1306_WHITE); // Bigoti dret 1
  pantalla.drawLine(113, 38, 103, 35, SSD1306_WHITE); // Bigoti dret 2
}