const int pinBoto = 6;
int estatBoto;

void setup() {
  pinMode(pinBoto, INPUT_PULLUP);       // definim port pinBoto (12) com a port d'entrada pullup
  Serial.begin(115200);
}

void loop() {
  estatBoto = digitalRead(pinBoto);     // consultem estat del boto i el guardem a la variable estatBoto

  if (estatBoto == LOW) {               // si botó premut: 
    Serial.println("Botó premut");      // enviem "Botó premut" pel port sèrie
  }

  else {                                // si botó no premut:
    Serial.print(".");                  // enviem "." pel port sèrie
  }
  delay(100);
}
