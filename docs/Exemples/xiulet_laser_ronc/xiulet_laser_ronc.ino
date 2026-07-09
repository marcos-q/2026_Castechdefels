#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- ASSIGNACIÓ DE PINS DE LA PCB ---
const int PIN_SDA = 3;
const int PIN_SCL = 4;
const int PIN_BUZZER = 5; 

void setup() {
  pinMode(PIN_BUZZER, OUTPUT);

  // Inicialització de la pantalla OLED
  Wire.begin(PIN_SDA, PIN_SCL); 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while(true); // Si falla la pantalla, es queda bloquejat aquí
  }
}

void loop() {
  // 1. Executem el Xiulet i mostrem el text
  mostrarTextOLED("Xiulet");
  generarSoxiulet();
  delay(1500); // Pausa de seguretat entre sons perquè els alumnes ho apreciïn

  // 2. Executem el Làser i mostrem el text
  mostrarTextOLED("Laser");
  generarSoLaser();
  delay(1500);

  // 3. Executem el Ronc i mostrem el text
  mostrarTextOLED("Ronc");
  generarSoRonc();
  delay(2000); // Una pausa una mica més llarga abans de tornar a començar el loop
}

// ========================================================
// FUNCIÓ AUXILIAR PER MOSTRAR TEXT GRAN A LA PANTALLA
// ========================================================
void mostrarTextOLED(String text) {
  display.clearDisplay();
  display.setTextSize(2);             // Mida de lletra gran i clara
  display.setTextColor(SSD1306_WHITE);
  
  // Centrem una mica el text a la pantalla de 128x64
  display.setCursor(25, 24); 
  display.print(text);
  
  display.display();
}

// ========================================================
// FUNCIONS GENERADORES DE SO
// ========================================================

void generarSoxiulet() {
  // 3 bips ràpids i aguts de 3000 Hz
  for (int i = 0; i < 3; i++) {
    tone(PIN_BUZZER, 3000, 80); // So de 3000Hz que dura 80ms
    delay(150);                 // Silenci entre cada bip
  }
}

void generarSoLaser() {
  // Un bucle "for" que baixa la freqüència des de 2200 Hz fins a 400 Hz molt ràpid
  for (int freq = 2200; freq >= 400; freq -= 20) {
    tone(PIN_BUZZER, freq);
    delay(6); // Temps que passa a cada freqüència (controla la velocitat de caiguda)
  }
  noTone(PIN_BUZZER); // Apaguem el brunzidor en acabar el recorregut
}

void generarSoRonc() {
  // So molt greu (120 Hz) que dura gairebé un segon simulant una respiració profunda
  tone(PIN_BUZZER, 120, 800); 
  delay(900); // Esperem que acabi el so abans de continuar
}