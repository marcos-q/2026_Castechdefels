// ==========================================
// REPTE FLASH: Mode benestar, placidesa i alarma
// ==========================================

// --- ASIGNACIÓ DE PINS DE LA PCB ---
const int PIN_BTN_A = 6;
const int PIN_BTN_B = 7;
const int LED_R = 21;
const int LED_G = 20;
const int LED_B = 10;

bool polsatA = false;
bool polsatB = false;

void setup() {
  // Configurem els botons com a entrades amb resistència interna (pull-up)
  pinMode(PIN_BTN_A, INPUT_PULLUP);
  pinMode(PIN_BTN_B, INPUT_PULLUP);
  
  // Configurem els canals del LED RGB com a sortides
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  // Assegurem que la mascota arrenqui totalment apagada
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);
}

void loop() {
  // Llegim l'estat dels botons (Recordatori: LOW vol dir que s'està prement)
  if (digitalRead(PIN_BTN_A) == LOW) polsatA = true;
   else polsatA = false;
  if (digitalRead(PIN_BTN_B) == LOW) polsatB = true;
   else polsatB = false;

  // COMPROVEM L'ESTAT DELS BOTONS I ACTUEM EN CONSEQüiÈNCIA
  if (polsatA && polsatB){
    // Els dos botons premuts alhora -> MODE ESTRÉS (Alarma vermella)
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
    
    // Fem les pampallugues ràpides
    digitalWrite(LED_R, HIGH);
    delay(100);
    digitalWrite(LED_R, LOW);
    delay(100);
  }
  else if (polsatA) {
    // Si es manté premut el Botó A
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_G, LOW); // Ens assegurem que la resta de colors estiguin apagats
    digitalWrite(LED_R, LOW); 
  } else if (polsatB) {
      //Si es manté premut el Botó B
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_R, LOW); // Ens assegurem d'apagar el vermell i el blau
      digitalWrite(LED_B, LOW);
    } else {
      //Si ningú toca cap botó, la mascota "dorm" (tot apagat)
      digitalWrite(LED_R, LOW);
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_B, LOW);
    }
}