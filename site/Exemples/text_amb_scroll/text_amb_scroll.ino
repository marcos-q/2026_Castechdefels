#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- MATEIXA ASSIGNACIÓ DE PINS ---
const int PIN_SDA = 3;   const int PIN_SCL = 4;
const int PIN_BTN_A = 6; const int PIN_BTN_B = 7;  
const int PIN_LDR = 0;    
const int LED_R = 21;    const int LED_G = 20;    const int LED_B = 10;

void setup() {
  Serial.begin(9600);

  // Configurem pins secundaris
  pinMode(PIN_BTN_A, INPUT_PULLUP);
  pinMode(PIN_BTN_B, INPUT_PULLUP);
  pinMode(LED_R, OUTPUT); pinMode(LED_G, OUTPUT); pinMode(LED_B, OUTPUT);

  // Encenem el LED en color cian per indicar que la marquesina està activa
  digitalWrite(LED_R, LOW); digitalWrite(LED_G, HIGH); digitalWrite(LED_B, HIGH);

  // Inicialització de la pantalla amb els teus pins I2C
  Wire.begin(PIN_SDA, PIN_SCL); 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Error OLED");
    while(true); 
  }

  // Netegem la pantalla abans de començar
  display.clearDisplay();
  
  // --- CONFIGURACIÓ DEL TEXT DE LA MARQUESINA ---
  display.setTextSize(2);          // Mida del text (2 és ideal per a marquesines, es llegeix molt bé)
  display.setTextColor(SSD1306_WHITE); // Text en blanc
  display.setCursor(0, 24);        // El centrem verticalment a la pantalla (la pantalla fa 64 de alt)
  
  // Escrivim el text que volem desplaçar
  display.println("ROBOT ACTIU"); 
  display.display();               // Mostrem el text inicial a la pantalla

  // --- ENGEGAR EL DESPLAÇAMENT (SCROLL) ---
  // display.startscrollright(pàgina_inicial, pàgina_final);
  // La pantalla OLED es divideix en 8 pàgines horitzontals (de la 0 a la 7).
  // Fent scroll de la 0 a la 7 desplacem tota la pantalla sencera.
  display.startscrollright(0x00, 0x07); 
}

void loop() {
  // El loop es queda lliure! El desplaçament es fa automàticament per maquinari.
  // Aquí podries afegir codi per llegir els botons o fer parpellejar els leds
  // sense que afecti gens ni mica a la fluïdesa del text que es mou.
}