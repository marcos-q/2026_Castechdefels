#define pinLedR 21
#define pinLedG 20

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(pinLedR, OUTPUT);
  pinMode(pinLedG, OUTPUT);
}

void loop() {
  digitalWrite(pinLedR, HIGH);  // encèn el LED vermell
  digitalWrite(pinLedG, LOW);  // apaga el LED verd

  delay(1000);                 // espera 1 segon

  digitalWrite(pinLedR, LOW);   // apaga el LED vermell
  digitalWrite(pinLedG, HIGH);  // encèn el LED verd

  delay(1000);                 // espera 1 segon
}
