#define pinLedR 21
#define pinLedG 20
#define pinLedB 10

void setup() {
  pinMode(pinLedR, OUTPUT);
  pinMode(pinLedG, OUTPUT);
  pinMode(pinLedB, OUTPUT);

  // Apagaguem leds verd i blau
  analogWrite(pinLedG, 0);
  analogWrite(pinLedB, 0);
}

void loop() {
digitalWrite(pinLedR,1);
delay(100);
digitalWrite(pinLedR,0);
delay (100);
digitalWrite(pinLedR,1);
delay(100);
digitalWrite(pinLedR,0);
delay (500);
}
