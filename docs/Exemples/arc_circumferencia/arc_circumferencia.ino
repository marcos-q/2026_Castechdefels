#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 pantalla(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int PIN_SDA = 3;
const int PIN_SCL = 4;

// --- PROTOTIP DE LA NOSTRA NOVA FUNCIÓ ---
void dibuixarArc(int x, int y, int radi, float angleInici, float angleFinal);

void setup() {
  Wire.begin(PIN_SDA, PIN_SCL); 
  pantalla.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pantalla.clearDisplay();

  // Dibuixem uns ulls senzills
  pantalla.fillCircle(45, 25, 5, SSD1306_WHITE);
  pantalla.fillCircle(83, 25, 5, SSD1306_WHITE);

  // ARA FEM SERVIR LA NOSTRA FUNCIÓ PER FER UN SOMRIURE!
  // Centre a X=64, Y=30. Radi=18. 
  // Anem dels 0 graus fins als 180 graus (mitja circumferència inferior)
  dibuixarArc(64, 30, 18, 0, 180);

  pantalla.display();
}

void loop() {
}

// ==========================================
// FUNCIÓ PERSONALITZADA PER DIBUIXAR ARCS
// ==========================================
void dibuixarArc(int centreX, int centreY, int radi, float angleInici, float angleFinal) {
  // Un bucle que avança grau a grau per pintar la corba
  for (float angle = angleInici; angle <= angleFinal; angle += 1.0) {
    
    // La funció utilitza radians com a unitats, no graus
    // Per tant, multipliquem per PI i dividim per 180 per fer la conversió.
    float radians = angle * PI / 180.0;
    
    // Calculem la coordenada (X, Y) d'aquest punt exacte de la corba
    int px = centreX + radi * cos(radians);
    int py = centreY + radi * sin(radians);
    
    // Pintem un píxel en aquesta coordenada calculada
    pantalla.drawPixel(px, py, SSD1306_WHITE);
  }
}