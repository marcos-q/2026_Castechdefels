const int pinLed = 8;

void setup() {
  // initializem digital pin LED_BUILTIN as an output.
  pinMode(pinLed, OUTPUT);
  Serial.begin(115200);        // configurem el port sèrie
} 

void loop() {
  digitalWrite(pinLed, HIGH);  // encèn el LED (HIGH representa voltatge)
  Serial.println("LED on");    // enviem "LED on" al port sèrie

  delay(1000);                 // espera 1 segon

  digitalWrite(pinLed, LOW);   // apaga el LED (LOW representa tensió 0)
  Serial.println("LED off");   // enviem "LED off" al port sèrie

  delay(1000);                 // espera 1 segon
}
