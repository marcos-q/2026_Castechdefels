#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- ASSIGNACIÓ DE PINS DE LA PCB-
const int PIN_SDA = 3;
const int PIN_SCL = 4;
const int PIN_BTN_A = 6;  
const int PIN_BTN_B = 7;  
const int PIN_LDR = 0;    
const int LED_R = 21;
const int LED_G = 20;
const int LED_B = 10;

// ========================================================
// BITMAPS DE L'ANIMACIÓ
// ========================================================
// Els Bitmaps són matrius de punts convertides a nombres Hexadecimals.
// Es guarden a la memòria PROGMEM (Flash) perquè no ocupin memòria RAM.

// Cor Petit (16x16 píxels)
const unsigned char corPetit [] PROGMEM = {
  0x00, 0x00, 0x1C, 0x38, 0x3E, 0x7C, 0x7F, 0xFE, 
  0x7F, 0xFE, 0x7F, 0xFE, 0x7F, 0xFE, 0x3F, 0xFC, 
  0x1F, 0xF8, 0x0F, 0xF0, 0x07, 0xE0, 0x03, 0xC0, 
  0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Cor Gran (24x24 píxels)
const unsigned char corGran [] PROGMEM = {
  0x00, 0x00, 0x00, 0x07, 0x00, 0xE0, 0x1F, 0x81, 0xF8, 0x3F, 0xC3, 0xFC, 
  0x7F, 0xE7, 0xFE, 0x7F, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFE, 0x3F, 0xFF, 0xFC, 
  0x1F, 0xFF, 0xF8, 0x0F, 0xFF, 0xF0, 0x07, 0xFF, 0xE0, 0x03, 0xFF, 0xC0, 
  0x01, 0xFF, 0x80, 0x00, 0xFF, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x3C, 0x00, 
  0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// --- CONTROL DE TEMPS (Mètode millis) ---
unsigned long tempsAnterior = 0;
const int INTERVAL_BATEC = 350; // Temps en mil·lisegons entre cada canvi de mida
bool mostrarCorGran = true;     // Variable que ens diu quin cor toca dibuixar

void setup() {
  // Configuració de pins (per si després voleu afegir interacció)
  pinMode(PIN_BTN_A, INPUT_PULLUP);
  pinMode(PIN_BTN_B, INPUT_PULLUP);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  // Inicialització de la pantalla
  Wire.begin(PIN_SDA, PIN_SCL); 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while(true); // Si falla la pantalla, el programa s'atura aquí
  }
}

void loop() {
  // Comprovem si ha passat prou temps per canviar el fotograma
  if (millis() - tempsAnterior >= INTERVAL_BATEC) {
    
    // 1. Guardem l'hora actual per al proper canvi
    tempsAnterior = millis();
    
    // 2. Canviem l'estat (Si era cert, passa a fals. Si era fals, passa a cert)
    mostrarCorGran = !mostrarCorGran; 
    
    // 3. Esborrem la pantalla per dibuixar el nou fotograma
    display.clearDisplay();
    
    // 4. Dibuixem el cor que toqui al centre de la pantalla
    if (mostrarCorGran) {
      // Coordenades X i Y calculades per centrar un dibuix de 24x24 en una pantalla de 128x64
      // X = (128 - 24) / 2 = 52  |  Y = (64 - 24) / 2 = 20
      display.drawBitmap(52, 20, corGran, 24, 24, SSD1306_WHITE);
    } else {
      // Coordenades X i Y calculades per centrar un dibuix de 16x16 en una pantalla de 128x64
      // X = (128 - 16) / 2 = 56  |  Y = (64 - 16) / 2 = 24
      display.drawBitmap(56, 24, corPetit, 16, 16, SSD1306_WHITE);
    }
    
    // 5. Enviem la imatge a la pantalla perquè es vegi
    display.display();
  }
  
  // Gràcies a no fer servir delay(), aquí podríem seguir llegint el botó A, 
  // encenent leds o consultant sensors al mateix temps que el cor batega.
}