#include <WiFi.h>
#include "WIFI_config.h" // Configureu les dades de la vostra xarxa en aquest arxiu<
#include "WIFI_funcions.hpp"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_AHTX0.h>

#include <ThingSpeak.h>


WiFiClient  client;

unsigned long canal = 1;
//const char * writeAPIKey = "/*XXX escriviu la vostra Write API Key aquí XXX*/";
const char * writeAPIKey = "xxx";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 60000;

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
   
  display.setCursor(5, 25);   // On comença a escriure (X, Y)
  display.print("Connectant");  // El text que volem mostrar

  display.display();
  
  WIFI_connecta();  
  ThingSpeak.begin(client);  // Inicialitza ThingSpeak amb el client wifi definit adalt
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
  if ((millis() - lastTime) > timerDelay) {
  
    // Reconnecta WiFi, en cas que connexió perduda o desactivada
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Connectant...\n");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnectat.");
    }

  
    Serial.println(temp.temperature);

     Serial.println(humidity.relative_humidity);
 
    // Carreguem noves lectures als fields corresponents
    ThingSpeak.setField(1, temp.temperature);
    ThingSpeak.setField(2, humidity.relative_humidity);
    
    // Enviem dades a Thingspeak
    int codiHttp = ThingSpeak.writeFields(canal, writeAPIKey);

    // Detecció d'errors HTTP
    if(codiHttp == 200) Serial.println("Canal actualitzat correctament.");
    else Serial.println("Problema actualitzant correctament. Codi error HTTP:  " + String(codiHttp));

    lastTime = millis();  
  }
  delay (100);
}
