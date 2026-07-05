const int pinBotoEsq = 6;

const int LED_R = 21;

int estatBoto;

void setup() {
  pinMode(pinBotoEsq, INPUT_PULLUP);       // definim port pinBoto (12) com a port d'entrada pullup
  pinMode(LED_R,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  estatBoto = digitalRead(pinBotoEsq);     // consultem estat del boto i el guardem a la variable estatBoto

  if (estatBoto == LOW) {               // si botó premut: 
    Serial.println("Botó premut");      // enviem "Botó premut" pel port sèrie
    digitalWrite(LED_R,1);
  }

  else {                                // si botó no premut:
    Serial.print(".");                  // enviem "." pel port sèrie
    digitalWrite(LED_R,0);
  }
  delay(100);
}
