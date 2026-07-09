#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- ASSIGNACIÓ DE PINS DE LA PCB ---
const int PIN_SDA = 3;
const int PIN_SCL = 4;
const int PIN_BTN_A = 6;  // Botó esquerre
const int PIN_BTN_B = 7;  // Botó dret
const int PIN_LDR = 0;    // Sensor de llum analògic
const int LED_R = 21;
const int LED_G = 20;
const int LED_B = 10;

// --- DEFINICIÓ DELS ESTATS DE LA MASCOTA ---
const int ESTAT_NORMAL  = 0;
const int ESTAT_ENFADAT = 1;
const int ESTAT_ADORMIT  = 2;

int estatActual = ESTAT_NORMAL; // La mascota comença sempre en mode Normal

// --- TIMERS I CONSTANTS ---
const unsigned long TEMPS_AVORRIMENT = 10000; // 10 segons (en mil·lisegons) per avorrir-se
unsigned long cronometreAvorriment = 0;       // Guarda la marca temporal quan comencem a comptar el temps d'aborriment

void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_BTN_A, INPUT_PULLUP);
  pinMode(PIN_BTN_B, INPUT_PULLUP);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  Wire.begin(PIN_SDA, PIN_SCL); 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while(true);
  }

  // Iniciar el temporitzador d'avorriment a l'arrencada
  cronometreAvorriment = millis();
}

void loop() {
  // Llegim els sensors i botons a cada volta del bucle
  bool pulsatA = (digitalRead(PIN_BTN_A) == LOW);
  bool pulsatB = (digitalRead(PIN_BTN_B) == LOW);
  int valorLDR = analogRead(PIN_LDR);


  // ========================================================
  // 2. MÀQUINA D'ESTATS (Lògica de comportament)
  // ========================================================
  switch (estatActual) {
    
    case ESTAT_NORMAL:
      // Control de Leds: Blau (Benestar)
      digitalWrite(LED_R, LOW);  digitalWrite(LED_G, LOW);  digitalWrite(LED_B, HIGH);
      
      // Dibuixem la cara
      dibuixarCaraNormal();

      //Transició per foscor
      if (valorLDR < 300) {
        estatActual = ESTAT_ADORMIT;
      }
      // Transició per Temps: Si passa el temps d'avorriment, s'enfada
      if (millis() - cronometreAvorriment >= TEMPS_AVORRIMENT) {
        estatActual = ESTAT_ENFADAT;
      }
      break;

    case ESTAT_ENFADAT:
      // Control de Leds: Vermell (Enfadat / Estrès)
      digitalWrite(LED_R, HIGH); digitalWrite(LED_G, LOW);  digitalWrite(LED_B, LOW);
      
      // Dibuixem la cara
      dibuixarCaraEnfada();

      //Transició per foscor
      if (valorLDR < 300) {
        estatActual = ESTAT_ADORMIT;
      }

      // Transició per Botó: Si premem el botó dret (B), es calma
      if (pulsatB) {
        estatActual = ESTAT_NORMAL;
        cronometreAvorriment = millis(); // Reiniciem el comptador de temps
        delay(200);                      // Petit anti-rebot
      }
      break;

    case ESTAT_ADORMIT:
      // Control de Leds: Tot apagat per dormir plàcidament
      digitalWrite(LED_R, LOW);  digitalWrite(LED_G, LOW);  digitalWrite(LED_B, LOW);
      
      // Dibuixem la cara
      dibuixarCaraDormida();

      // Transició per Llum
      if (valorLDR > 400) {
        estatActual = ESTAT_NORMAL;
        cronometreAvorriment = millis(); // Torna sa i estalvi i reinicia el seu temps
      }
      break;
  }
}

// ========================================================
// FUNCIONS DE DIBUIX DE LES CARES
// ========================================================

void dibuixarCaraNormal() {
  display.clearDisplay();
  display.drawRoundRect(10, 5, 108, 54, 8, SSD1306_WHITE); // Cap
  display.fillCircle(40, 25, 8, SSD1306_WHITE);             // Ull esquerre
  display.fillCircle(88, 25, 8, SSD1306_WHITE);             // Ull dret
  display.drawLine(44, 45, 84, 45, SSD1306_WHITE);          // Boca neutra/feliç
  display.display();
}

void dibuixarCaraEnfada() {
  display.clearDisplay();
  display.drawRoundRect(10, 5, 108, 54, 8, SSD1306_WHITE); // Cap
  
  // Ulls amb celles diagonals arrufades
  display.fillCircle(40, 25, 8, SSD1306_WHITE);
  display.drawLine(25, 12, 45, 20, SSD1306_WHITE);         // Cella esquerra \ .
  
  display.fillCircle(88, 25, 8, SSD1306_WHITE);
  display.drawLine(103, 12, 83, 20, SSD1306_WHITE);        // Cella dreta /
  
  // Boca trista / enfadada
  display.drawLine(54, 48, 74, 48, SSD1306_WHITE);
  display.display();
}

void dibuixarCaraDormida() {
  display.clearDisplay();
  display.drawRoundRect(10, 5, 108, 54, 8, SSD1306_WHITE); // Cap
  
  // Ulls tancats (Línies horizontals)
  display.drawLine(32, 25, 48, 25, SSD1306_WHITE);
  display.drawLine(80, 25, 96, 25, SSD1306_WHITE);
  
  // Boca de roncar (Cercle buit)
  display.drawCircle(64, 42, 4, SSD1306_WHITE);
  
  // Text Zzz
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(95, 12);
  display.print("Zzz..");
  display.display();
}