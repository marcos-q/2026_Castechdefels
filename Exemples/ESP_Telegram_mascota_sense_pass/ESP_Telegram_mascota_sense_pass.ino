#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- LLIBRERIES DE WI-FI I TELEGRAM ---
#include <WiFi.h>
#include "WIFI_config.h"      // Configureu les dades de la vostra xarxa aquí
#include "WIFI_funcions.hpp"  // Conté la funció WIFI_connecta()
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h> 
#include <ArduinoJson.h>

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

// --- CONFIGURACIÓ DE TELEGRAM ---
#define BOTtoken "xxxxxx"  // Token de BotFather
#define CHAT_ID "xxxxx"                                       // ID d'usuari de IDBot

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int botRequestDelay = 1000; // El bot consultarà Telegram cada 1 segon
unsigned long lastTimeBotRan;

// --- DEFINICIÓ DELS ESTATS DE LA MASCOTA ---
const int ESTAT_NORMAL  = 0;
const int ESTAT_ENFADAT = 1;
const int ESTAT_ADORMIT  = 2;

int estatActual = ESTAT_NORMAL; // La mascota comença sempre en mode Normal

// --- TIMERS I CONSTANTS ---
const unsigned long TEMPS_AVORRIMENT = 10000; // 10 segons per avorrir-se
unsigned long cronometreAvorriment = 0;       // Guarda la marca temporal de l'avorriment

// ========================================================
// 1. PROCESSAMENT DE MISSATGES DE TELEGRAM
// ========================================================
void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    
    // Filtre de seguretat: Només responem al nostre CHAT_ID
    if (chat_id != CHAT_ID) {
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;

    // Comanda de benvinguda i ajuda
    if (text == "/start") {
      String welcome = "Hola, " + from_name + ".\n";
      welcome += "Sóc la teva mascota virtual de l'aula de Tecnologia!\n\n";
      welcome += "Comandes disponibles:\n";
      welcome += "/calma - Per tranquil·litzar-me quan estic enfadat.\n";
      bot.sendMessage(chat_id, welcome, "");
    }

    // INTERACCIÓ VIRTUAL: Ordre de calmar la mascota via Telegram
    if (text == "/calma") {
      if (estatActual == ESTAT_ENFADAT) {
        estatActual = ESTAT_NORMAL;
        cronometreAvorriment = millis(); // Reiniciem el comptador d'avorriment
        bot.sendMessage(chat_id, "Gràcies per calmar-me des del mòbil! 🥰", "");
      } else {
        bot.sendMessage(chat_id, "Ara mateix ja estic tranquil o adormit. No em cal calma!", "");
      }
    }
  }
}

// ========================================================
// 2. CONFIGURACIÓ INICIAL (SETUP)
// ========================================================
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

  // Connexió Wi-Fi utilitzant les teves funcions modulars
  WIFI_connecta(); 
  
  // Assignació del certificat de seguretat de Telegram per a l'ESP32
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  #endif

  // Iniciar el temporitzador d'avorriment a l'arrencada
  cronometreAvorriment = millis();
}

// ========================================================
// 3. BUCLE PRINCIPAL (LOOP)
// ========================================================
void loop() {
  // Llegim els sensors i botons a cada volta del bucle
  bool pulsatA = (digitalRead(PIN_BTN_A) == LOW);
  bool pulsatB = (digitalRead(PIN_BTN_B) == LOW);
  int valorLDR = analogRead(PIN_LDR);

  // --- REVISIÓ DE MISSATGES DE TELEGRAM (Cada 1 segon amb millis) ---
  if (millis() - lastTimeBotRan > botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }

  // --- MÀQUINA D'ESTATS (Lògica de comportament) ---
  switch (estatActual) {

    case ESTAT_NORMAL:
      // Control de Leds: Blau (Benestar)
      digitalWrite(LED_R, LOW);  digitalWrite(LED_G, LOW);  digitalWrite(LED_B, HIGH);

      // Dibuixem la cara
      dibuixarCaraNormal();

      // Transició per foscor
      if (valorLDR < 300) {
        estatActual = ESTAT_ADORMIT;

        //  ACCIÓ IOT AMB TELEGRAM: Enviem el missatge només EN EL MOMENT de canviar d'estat
        bot.sendMessage(CHAT_ID, "Bona nit!", "");
      }
      
      // Transició per Temps: Si passa el temps d'avorriment, s'enfada
      if (millis() - cronometreAvorriment >= TEMPS_AVORRIMENT) {
        estatActual = ESTAT_ENFADAT;
        
        //  ACCIÓ IOT AMB TELEGRAM: Enviem el missatge només EN EL MOMENT de canviar d'estat
        bot.sendMessage(CHAT_ID, "M'avorreixo!! Vine a jugar o envia'm un /calma!", "");
      }
      break;

    case ESTAT_ENFADAT:
      // Control de Leds: Vermell (Enfadat / Estrès)
      digitalWrite(LED_R, HIGH); digitalWrite(LED_G, LOW);  digitalWrite(LED_B, LOW);

      // Dibuixem la cara
      dibuixarCaraEnfada();

      // Transició per foscor
      if (valorLDR < 300) {
        estatActual = ESTAT_ADORMIT;
      }

      // INTERACCIÓ FÍSICA: Transició per Botó dret (B)
      if (pulsatB) {
        estatActual = ESTAT_NORMAL;
        cronometreAvorriment = millis(); // Reiniciem el comptador de temps
        bot.sendMessage(CHAT_ID, "M'has calmat prement el Botó B.", "");
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
// 4. FUNCIONS DE DIBUIX DE LES CARES
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
  display.drawLine(25, 12, 45, 20, SSD1306_WHITE);         // Cella esquerra

  display.fillCircle(88, 25, 8, SSD1306_WHITE);
  display.drawLine(103, 12, 83, 20, SSD1306_WHITE);        // Cella dreta

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