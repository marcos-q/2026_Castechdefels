// --- PINS D'ENTRADA I SORTIDA ---
const int pinLedRoig = 21;
const int pinLedVerd = 20;
const int pinLedBlau = 10;

void setup() {
  Serial.begin(115200);
  
  // Configuració de les sortides dels LEDs
  pinMode(pinLedRoig, OUTPUT);
  pinMode(pinLedVerd, OUTPUT);
  pinMode(pinLedBlau, OUTPUT);

  // Ens assegurem que el roig i el verd estiguin apagats
  digitalWrite(pinLedRoig, LOW);
  digitalWrite(pinLedVerd, LOW);
  
  Serial.println("Iniciant test de brillantor (PWM)...");
}

void loop() {
  // 1. Nivell 0: Totalment apagat
  Serial.println("Brillantor: 0 (Apagat)");
  analogWrite(pinLedBlau, 0);
  delay(2000); // Esperem 2 segons

  // 2. Nivell Baix: Brillantor molt suau (aprox. 10%)
  Serial.println("Brillantor: 25 (Fluix)");
  analogWrite(pinLedBlau, 25);
  delay(2000);

  // 3. Nivell Mitjà: Meitat de potència (50%)
  Serial.println("Brillantor: 127 (Mitjà)");
  analogWrite(pinLedBlau, 127);
  delay(2000);

  // 4. Nivell Màxim: Tota la potència (100%)
  Serial.println("Brillantor: 255 (Màxim)");
  analogWrite(pinLedBlau, 255);
  delay(2000);
  
  Serial.println("--- Tornem a començar ---");
}