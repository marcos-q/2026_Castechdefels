#include <WiFi.h>
#include "WIFI_config.h" // Configureu les dades de la vostra xarxa en aquest arxiu<
#include "WIFI_funcions.hpp"
#include <HTTPClient.h>

#include <DHT.h>           // Llibreria sensor
 

WiFiClient  client;

// Variables de control de temps
unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

// Creació objecte sensor per poder fer servir funcions llibreria DHT
#define DHTTYPE  DHT22   // Definició del model de sensor DHT22
#define DHTPIN    4     // Es defineix el pin D4 del ESP32 per connectar el sensor DHT22
DHT dht(DHTPIN, DHTTYPE); // Defineix port on connectarem el sensor, el model que farem servir i el nombre de sensors que té el mòdul

// Substituir les XXXXXXXXX per l'adreça que heu obtingut del tipus https://script.google.com/macros/s/BCD_sheb7645_cbwpVlmgsyn_iSXbB5dRgy1YOsyn_2aS5Dy4ir/exec
String Web_App_URL = "XXXXXXXXX";                             

// Declaració de variables generals
float temperatura = 0.00; 
float humitat = 0.00; 

String ultima_data_hora = " ******* ";
int ultim_registre = 0;
float ultima_temperatura = 0.00;
float ultima_humitat_relativa = 0.00;
  

String obtenir_valors(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;
  
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}


void setup() {
  Serial.begin(115200);  
  dht.begin();           // Inicialitzem sensor
  
  WIFI_connecta();
  
  delay (1000);  
}

void loop() {
  // Condicional que espara el temps especificat entre mostra i mostra
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

    // Obtenim una nova lectura de temperatura
    temperatura = dht.readTemperature();
    Serial.print("Temperatura : ");
    Serial.print(temperatura);
    Serial.print(" ºC");

    // Obtenim una nova lectura d'humitat
    humitat = dht.readHumidity();
    Serial.print("  | Humitat relativa : ");
    Serial.print(humitat);
    Serial.println (" %");
 
    // Creació de la trama.
    String trama1 = Web_App_URL + "?tasca=escriptura";
    trama1 += "&temp=" + String(temperatura);
    trama1 += "&hr=" + String(humitat);
    

    Serial.println("-------------");
    Serial.print("S'enviarà la petició:  ");
    Serial.println(trama1);

    // Execució del protocol per l'enviament de dades a Google Sheets 
    HTTPClient http;
  
    http.begin(trama1.c_str());
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = http.GET(); 
    Serial.print("HTTP Status Code : ");
    Serial.println(httpCode);
  
    // Getting response from google sheets.
    String payload;
    if (httpCode > 0) {
      payload = http.getString();
      Serial.println("Càrrega : " + payload);    
    }  
      
    http.end();

    if(httpCode == 200) Serial.println("Canal actualitzat correctament.");
    else Serial.println("Problema d'actualització. Codi error HTTP:  " + String(httpCode));

    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Connectant...\n");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnectat.");
    }

    String trama2 = Web_App_URL + "?tasca=lectura";

    Serial.println("-------------");
    Serial.print("S'enviarà la petició:  ");
    Serial.println(trama2);

    // Execució del protocol per la recepció de dades de Google Sheets
    HTTPClient http2;
    http2.begin(trama2.c_str());
    http2.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode2 = http2.GET(); 
    Serial.print("HTTP Status Code : ");
    Serial.println(httpCode2);
  
    String payload2;
    if (httpCode2 > 0) {
        payload2 = http2.getString();
        Serial.println("Càrrega : " + payload2);  
    }
  
    http2.end();

    // Si el codi indica que s'ha fet correctament...
    if (httpCode2 == 200) {
      // Separació de dades
      ultima_data_hora = obtenir_valors(payload2, ',', 0);
      ultim_registre = obtenir_valors(payload2, ',', 1).toInt();
      ultima_temperatura = obtenir_valors(payload2, ',', 2).toFloat();
      ultima_humitat_relativa = obtenir_valors(payload2, ',', 3).toFloat();
    } 
    
    Serial.println("-------------");
    Serial.print("Recuperat el : ");
    Serial.print(ultima_data_hora);
    Serial.print("  | Registre nº : ");
    Serial.print(ultim_registre);
    Serial.print("  | Temperatura : ");
    Serial.print(ultima_temperatura);
    Serial.print(" ºC");
    Serial.print("  | Humitat relativa : ");
    Serial.print(ultima_humitat_relativa);
    Serial.println (" %");
    
    Serial.println ("");


    lastTime = millis();  
  }
}
