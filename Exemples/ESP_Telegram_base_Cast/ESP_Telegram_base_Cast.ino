#include <WiFi.h>

#include "WIFI_config.h" //Configureu les dades de la vostra xarxa
#include "WIFI_funcions.hpp"

#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>

// Inicialització bot de Telegram
// Cal que aneu al buscador de xats de Telegram, busqueu el vostre bot i li envieu "/start" per iniciar la ocnnexió Telegram - ESP32

#define BOTtoken "8105450952:AAHlgilkgRunKVKrK4BKcTAlD7nTb2WmpfA"  // Codi que hem obtingut en la conversa amb BotFather
#define CHAT_ID "182953264"   // ID del nostre usuari de Telegram (codi obtngut amb IDBot)



//Inicialització client WiFi i creació objecte bot
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// El bot consultarà si hi ha missatges nous cada 1 segon
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

const int ledPin = 10;
bool ledState = LOW;

// Processament dels missatges nous rebuts
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    // Mostra pel port sèrie el missatge rebut via Telegram
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    // Definició diferents accions del bot en funció de quina comanda rebi via Telegram
    if (text == "/start") {
      String welcome = "Hola, " + from_name + ".\n";
      welcome += "Utilitza les següents comandes per controlar els pins de sortida de la teva ESP32.\n\n";
      welcome += "/on per encendre el LED \n";
      welcome += "/off per apagar el LED \n";
      welcome += "/estat per consultar l'estat del LED \n";
      bot.sendMessage(chat_id, welcome, "");
    }

    // Encendre LED
    if (text == "/on") {
      bot.sendMessage(chat_id, "LED encès", "");
      ledState = HIGH;
      digitalWrite(ledPin, ledState);
    }
    
    // Apagar LED
    if (text == "/off") {
      bot.sendMessage(chat_id, "LED apagat", "");
      ledState = LOW;
      digitalWrite(ledPin, ledState);
    }
    
    // Consultar estat del LED
    if (text == "/estat") {
      if (digitalRead(ledPin)){
        bot.sendMessage(chat_id, "El LED es troba en estat encès", "");
      }
      else{
        bot.sendMessage(chat_id, "El LED es troba en estat apagat", "");
      }
    }
  }
}

void setup() {
  Serial.begin(115200);                           // Inicialització port sèrie
  delay(100)    ;
  pinMode(ledPin, OUTPUT);                        // Configuració pin del LED
  digitalWrite(ledPin, ledState);                 // Definició estat del LED
  
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  #endif
  WIFI_connecta();                                // Establiment i configuració connexió WiFi
}

void loop() {
  if (millis() - lastTimeBotRan > botRequestDelay)  {  //millor que if (millis() > lastTimeBotRan + botRequestDelay) 
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}