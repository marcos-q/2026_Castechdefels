#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h> // Necessària per a la funció sin() del LED

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- MATEIXA ASSIGNACIÓ DE PINS ---
const int PIN_SDA = 3;   const int PIN_SCL = 4;
const int PIN_BTN_A = 6; const int PIN_BTN_B = 7;  
const int PIN_LDR = 0;    
const int LED_R = 21;    const int LED_G = 20;    const int LED_B = 10;

// --- CONFIGURACIÓ DE L'ANIMACIÓ DE L'ESPAI ---
const int NUM_ESTRELLES = 35; // Nombre d'estrelles simultànies a la pantalla
struct Estrella {
  float x; // Posició horitzontal respecte al centre
  float y; // Posició vertical respecte al centre
  float z; // Profunditat (distància). Més a prop = Z més petita.
};
Estrella estrelles[NUM_ESTRELLES];

// Control de velocitat
float velocitat = 3.0; // Velocitat inicial del viatge
const float VEL_MIN = 0.5;
const float VEL_MAX = 12.0;

// Temporitzadors per al loop i els botons (No bloquejants)
unsigned long tempsUltimFrame = 0;
const int INTERVAL_FRAME = 20; // ~50 imatges per segon (molt fluid)
unsigned long tempsUltimBoto = 0;

void setup() {
  Serial.begin(9600);

  // Pins d'entrada i sortida
  pinMode(PIN_BTN_A, INPUT_PULLUP);
  pinMode(PIN_BTN_B, INPUT_PULLUP);
  pinMode(LED_R, OUTPUT); pinMode(LED_G, OUTPUT); pinMode(LED_B, OUTPUT);

  Wire.begin(PIN_SDA, PIN_SCL); 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Error OLED");
    while(true); 
  }

  // --- INICIALITZACIÓ DE LES ESTRELLES ---
  // Repartim les estrelles aleatòriament per l'espai 3D inicial
  for (int i = 0; i < NUM_ESTRELLES; i++) {
    reiniciarEstrella(i);
    // Inicialment, els donem una profunditat aleatòria perquè no surtin totes alhora
    estrelles[i].z = random(1, SCREEN_WIDTH);
  }

  tempsUltimFrame = millis();
}

void loop() {
  unsigned long tempsActual = millis();

  // --- 1. LECTURA DE BOTONS (AMB ANTIREBOTS DE 200ms) ---
  if (tempsActual - tempsUltimBoto > 200) {
    if (digitalRead(PIN_BTN_A) == LOW) { // Botó A: Frena
      velocitat -= 1.0;
      if (velocitat < VEL_MIN) velocitat = VEL_MIN;
      Serial.print("Velocitat reduïda a: "); Serial.println(velocitat);
      tempsUltimBoto = tempsActual;
    }
    if (digitalRead(PIN_BTN_B) == LOW) { // Botó B: Accelera
      velocitat += 1.0;
      if (velocitat > VEL_MAX) velocitat = VEL_MAX;
      Serial.print("Velocitat augmentada a: "); Serial.println(velocitat);
      tempsUltimBoto = tempsActual;
    }
  }

  // --- 2. EFECTE RESPIRACIÓ LED RGB (Sincronitzat amb la velocitat) ---
  // Fem servir una ona sinusoïdal basada en el temps actual.
  // Multipliquem per la velocitat perquè el LED "respiri" més ràpid si anem més de pressa.
  float factorVelocitatLED = 0.001 + (velocitat * 0.0005);
  float angle = tempsActual * factorVelocitatLED;
  
  // sin() va de -1 a 1. El passem a un rang de 0 a 255 per al control de brillantor.
  int brillantor = (sin(angle) + 1.0) * 127.5;
  
  // Apliquem la brillantor (en aquest exemple al color Cian: Verd + Blau)
  analogWrite(LED_R, 0);
  analogWrite(LED_G, brillantor);
  analogWrite(LED_B, brillantor);


  // --- 3. ACTUALITZACIÓ I DIBUIX DEL CAMP D'ESTRELLES ---
  if (tempsActual - tempsUltimFrame >= INTERVAL_FRAME) {
    tempsUltimFrame = tempsActual;

    display.clearDisplay();

    // Centre de la pantalla
    int centreX = SCREEN_WIDTH / 2;
    int centreY = SCREEN_HEIGHT / 2;

    for (int i = 0; i < NUM_ESTRELLES; i++) {
      // L'estrella s'apropa a nosaltres (la seva Z disminueix)
      estrelles[i].z -= velocitat;

      // Si l'estrella ens ha passat de llarg (Z <= 0), la tornem a enviar al fons
      if (estrelles[i].z <= 0) {
        reiniciarEstrella(i);
      }

      // Projecció 3D matemàtica a 2D (Perspectiva)
      // Dividir X i Y per Z fa que les coses llunyanes es vegin petites i centrades,
      // i les properes es moguin ràpidament cap als extrems.
      int screenX = (estrelles[i].x * 50) / estrelles[i].z + centreX;
      int screenY = (estrelles[i].y * 50) / estrelles[i].z + centreY;

      // Si l'estrella surt dels marges de la pantalla física, la reiniciem
      if (screenX < 0 || screenX >= SCREEN_WIDTH || screenY < 0 || screenY >= SCREEN_HEIGHT) {
        reiniciarEstrella(i);
      } else {
        // DIBUIX DE L'ESTRELLA SEGONS LA DISTÀNCIA
        // Si està lluny (Z gran) dibuixem 1 sol píxel. Si està a prop (Z petita) un quadrat de 2x2.
        if (estrelles[i].z > 40) {
          display.drawPixel(screenX, screenY, SSD1306_WHITE);
        } else {
          display.fillRect(screenX, screenY, 2, 2, SSD1306_WHITE);
        }
      }
    }

    display.display();
  }
}

// Funció auxiliar per col·locar una estrella al fons de l'espai
void reiniciarEstrella(int index) {
  // Generem coordenades a l'atzar al voltant del centre (poden ser negatives o positives)
  estrelles[index].x = random(-60, 60);
  estrelles[index].y = random(-30, 30);
  // La enviem al fons del tot de l'eix Z
  estrelles[index].z = SCREEN_WIDTH;
}