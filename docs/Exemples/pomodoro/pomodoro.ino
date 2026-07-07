#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- CORRESPONDÈNCIA DE PINES DE LA PCB ---
const int PIN_SDA = 3;
const int PIN_SCL = 4;
const int PIN_BTN_A = 6;  // Botó esquerre: Iniciar / Pausar
const int PIN_BTN_B = 7;  // Botó dret: Canviar de Mode / Reiniciar
const int LED_R = 21;
const int LED_G = 20;
const int LED_B = 10;
const int BUZZER = 5;

// --- CONFIGURACIÓ DE TEMPS (En segons per a fer proves ràpides) ---
const int TEMPS_TREBALL = 25; // Canviar a 25 * 60 per a minuts reals
const int TEMPS_DESCANS = 5;  // Canviar a 5 * 60 per a minuts reals

// --- VARIABLES DE CONTROL ---
int tempsInicial = TEMPS_TREBALL;
int tempsRestant = TEMPS_TREBALL;

bool cronometreActiu = false;  // Controla si el temps està corrent o en pausa
bool modeTreball = true;       // true = Mode Treball, false = Mode Descans
unsigned long ultimSegon = 0;  // Guarda el rastre del temps amb millis()

void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_BTN_A, INPUT_PULLUP);
  pinMode(PIN_BTN_B, INPUT_PULLUP);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Wire.begin(PIN_SDA, PIN_SCL); 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Error d'OLED"));
    while(true);
  }

  // Salutació inicial
  tone(BUZZER, 2000, 100);
}

void loop() {
  unsigned long tempsActual = millis();

  // 1. CONTROL DEL BOTÓ A: INICIAR / PAUSAR (Detecció de polsació única)
  static bool estatAnteriorA = HIGH;
  bool estatActualA = digitalRead(PIN_BTN_A);
  if (estatAnteriorA == HIGH && estatActualA == LOW) {
    cronometreActiu = !cronometreActiu; // Commutem l'estat (on/off)
    tone(BUZZER, 1800, 50);            // Feedback sonor curt
    delay(150);                        // Evitem rebots del botó
  }
  estatAnteriorA = estatActualA;

  // 2. CONTROL DEL BOTÓ B: CANVI DE MODE MANUAL
  static bool estatAnteriorB = HIGH;
  bool estatActualB = digitalRead(PIN_BTN_B);
  if (estatAnteriorB == HIGH && estatActualB == LOW) {
    modeTreball = !modeTreball; // Canviem de Treball a Descans o viceversa
    reiniciarTemporitzador();
    tone(BUZZER, 1200, 50);
    delay(150);
  }
  estatAnteriorB = estatActualB;

  // 3. LÒGICA DEL COMPTADOR (Resta 1 segon cada vegada sense bloquejar el codi)
  if (cronometreActiu && (tempsActual - ultimSegon >= 1000)) {
    ultimSegon = tempsActual;
    
    if (tempsRestant > 0) {
      tempsRestant--;
    } else {
      // El temps s'ha acabat!
      cronometreActiu = false;
      executarAlarma();
      
      // Canviem automàticament de mode per al següent cicle
      modeTreball = !modeTreball;
      reiniciarTemporitzador();
    }
  }

  // 4. ACTUALITZACIÓ DELS LEDS I DE LA INTERFICIE GRÀFICA
  gestionarLedsRGB();
  dibuixarInterficie();
}

// --- FUNCIÓ PER REINICIAR EL TEMPS SEGONS EL MODE ---
void reiniciarTemporitzador() {
  cronometreActiu = false;
  if (modeTreball) {
    tempsInicial = TEMPS_TREBALL;
  } else {
    tempsInicial = TEMPS_DESCANS;
  }
  tempsRestant = tempsInicial;
}

// --- FUNCIÓ PER GESTIONAR EL COLOR DEL LED RGB ---
void gestionarLedsRGB() {
  if (!cronometreActiu) {
    // Si està en Pausa: Color Blau
    digitalWrite(LED_R, LOW);  digitalWrite(LED_G, LOW);  digitalWrite(LED_B, HIGH);
  } else if (modeTreball) {
    // Si està Treballant: Color Vermell
    digitalWrite(LED_R, HIGH); digitalWrite(LED_G, LOW);  digitalWrite(LED_B, LOW);
  } else {
    // Si està en Descans: Color Verd
    digitalWrite(LED_R, LOW);  digitalWrite(LED_G, HIGH); digitalWrite(LED_B, LOW);
  }
}

// --- FUNCIÓ DE DIBUIX DE LA INTERFICIE POMODORO ---
void dibuixarInterficie() {
  display.clearDisplay();

  // Marco exterior estètic
  display.drawRoundRect(0, 0, 128, 64, 4, SSD1306_WHITE);

  // Text del Mode Actual
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(12, 10);
  if (modeTreball) {
    display.print("MODE: TREBALL");
  } else {
    display.print("MODE: DESCANS");
  }

  // Calculem els minuts i segons restants per mostrar-los en format rellotge
  int minuts = tempsRestant / 60;
  int segons = tempsRestant % 60;

  // Mostrem el rellotge en mida gran al centre
  display.setTextSize(2);
  display.setCursor(34, 26);
  if (minuts < 10) display.print("0"); // Afegim el zero a l'esquerra si és menor de 10
  display.print(minuts);
  display.print(":");
  if (segons < 10) display.print("0"); // Afegim el zero a l'esquerra si és menor de 10
  display.print(segons);

  // DIBUIX DE LA BARRA DE PROGRÉS
  // Calculem quants píxels ha de mesurar la barra (amplada màxima de 100 píxels)
  int ampladaBarra = (tempsRestant * 100) / tempsInicial;
  
  display.drawRect(14, 48, 102, 8, SSD1306_WHITE); // Marc de la barra
  display.fillRect(15, 49, ampladaBarra, 6, SSD1306_WHITE); // Farcit dynamic

  display.display();
}

// --- MELODIA DE FI DE TEMPS ---
void executarAlarma() {
  for (int i = 0; i < 3; i++) {
    tone(BUZZER, 2500, 150); delay(200);
    tone(BUZZER, 2000, 150); delay(200);
  }
  noTone(BUZZER);
}