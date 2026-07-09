// ESPP32_C3_oled_basic.ino

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_AHTX0.h>

// --- CONFIGURACIÓ HARDWARE ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define PIN_SDA 3 // Pins I2C per a l' ESP32-C3 SuperMini
#define PIN_SCL 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_AHTX0 aht;

void setup() {
  Serial.begin(115200);
  Wire.begin(PIN_SDA, PIN_SCL); 

  // Iniciar pantalla
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Fallo al iniciar OLED"));
    for(;;);
  }

    if (!aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1)
      delay(10);
  }

  display.setRotation(0); // Rotació de 180 graus. Necessari segons com muntem la pantalla
  display.clearDisplay();      // Esborrem el que hi hagi a la memòria
  display.setTextSize(2);      // Triem mida de lletra (1 a 8)
  display.setTextColor(WHITE); // Color del text
   
  display.setCursor(10, 25);   // On comença a escriure (X, Y)
  display.print("HOLA MON!");  // El text que volem mostrar

  display.display();
}

void loop() {
    display.clearDisplay();
  sensors_event_t humidity, temp;

  aht.getEvent(&humidity,
               &temp); // populate temp and humidity objects with fresh data
  display.setCursor(0, 20);
  
  
  display.print("Tmp:");
  display.print(temp.temperature,1);
  display.println(" C");
  display.setCursor(0, 40);
  display.print("Hum: ");
  display.print(humidity.relative_humidity,0);
  display.println(" %");
  Serial.print("Temperature: ");
  Serial.print(temp.temperature,1);
  Serial.println(" degrees C");
  Serial.print("Pressure: ");
  Serial.print(humidity.relative_humidity,0);
  Serial.println(" RH %");

 
  display.display();
  delay(100);
} 