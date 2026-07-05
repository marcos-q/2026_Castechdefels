//#include <Wire.h>       // les següents llibreries ja criden Wire.h
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definició de pins de la nostrea placa
#define PIN_SDA 3 // Pins I2C per a l' ESP32-C3 SuperMini
#define PIN_SCL 4

const int pinLedRoig = 21;
const int pinLedVerd = 20;
const int pinLedBlau = 10;

// Dimensions de la pantalla OLED
const int amplada = 128;
const int alcada = 64;

// Inicialització del display indicant amplada i alçada (-1 sense pin de reset físic)
Adafruit_SSD1306 display(amplada, alcada, &Wire, -1);

void setup() {
  
  // Configurem i apaguem els LEDs d'inici
  pinMode(pinLedRoig, OUTPUT);
  pinMode(pinLedVerd, OUTPUT);
  pinMode(pinLedBlau, OUTPUT);
  digitalWrite(pinLedRoig, LOW);
  digitalWrite(pinLedVerd, LOW);
  digitalWrite(pinLedBlau, LOW);
  
  Serial.begin(115200);

  //Inicialitzem el bus I2C forçant els pins de la nostra ESP32-C3 SuperMini (SDA, SCL)
  Wire.begin(PIN_SDA, PIN_SCL);

 // Connexió amb el controlador OLED (adreça estàndard 0x3C)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Error: No s'ha trobat la pantalla OLED!");
    while(true); // Bloquegem el programa si no hi ha pantalla
  }

  // Ajustem l'orientació (0= sensr rotació, 1= rotació 90 graus, 2= l'orienta a 180 graus, molt útil segons com s'hagi soldat)
  display.setRotation(0);

  // Netegem la memòria de la pantalla
  display.clearDisplay();

  // --- PREPAREM EL TEXT ---
  display.setTextSize(2);              // Mida del text (1 = petita, 2 = mitjana...)
  display.setTextColor(SSD1306_WHITE); // Color del text (en pantalles monocromes, blanc)
    
  display.setCursor(15, 20);   // Posicionem el cursor a les oordenades X=15, Y=20
  display.print("HOLA MON!");

  display.setCursor(30, 50);          // Baixem una mica més (Y=50)
  display.setTextSize(1);            
  display.print("JA PUC PARLAR");

  // --- DIBUIXEM EL MARC ---
  // drawRect(X_inici, Y_inici, amplada, alçada, color)
  display.drawRect(0, 0, amplada, alcada, SSD1306_WHITE);

  // --- IMPORTANT ---
  // Fins que no cridems a display(), tot el que hEM fet només està a la memòria de la placa.
  // Aquesta instrucció envia les dades reals a la pantalla física.
  display.display();
}

void loop() {
  // En aquest programa no necessitem fer res en el bucle principal.
}