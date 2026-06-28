// --- PINS D'ENTRADA I SORTIDA ---
const int pinLedRoig = 21;
const int pinLedVerd = 20;
const int pinLedBlau = 10;

// --- CONFIGURACIÓ DE TEMPS (MIL·LISEGONS) ---
const int pausaTransicio = 15; // Controla la velocitat del canvi de color (més baix = més ràpid)

void setup() {
Serial.begin(115200);

pinMode(pinLedRoig, OUTPUT);
pinMode(pinLedVerd, OUTPUT);
pinMode(pinLedBlau, OUTPUT);

// Comencem amb el Vermell encès al 100% com a pt de inici
analogWrite(pinLedRoig, 255);
analogWrite(pinLedVerd, 0);
analogWrite(pinLedBlau, 0);

Serial.println("Mascota encesa. Estat: Espectre emocional actiu.");
}

void loop() {
// --- 1. TRANSICIÓ: DE VERMELL A VERD ---
Serial.println("[Humor] Passant de Vermell a Verd...");
for (int i = 0; i <= 255; i++) {
    analogWrite(pinLedRoig, 255 - i);
    analogWrite(pinLedVerd, i);
    delay(pausaTransicio);
}

// --- 2. TRANSICIÓ: DE VERD A BLAU ---
Serial.println("[Humor] Passant de Verd a Blau...");
for (int i = 0; i <= 255; i++) {
    analogWrite(pinLedVerd, 255 - i);
    analogWrite(pinLedBlau, i);
    delay(pausaTransicio);
}

// --- 3. TRANSICIÓ: DE BLAU A VERMELL ---
Serial.println("[Humor] Passant de Blau a Vermell...");
for (int i = 0; i <= 255; i++) {
    analogWrite(pinLedBlau, 255 - i);
    analogWrite(pinLedRoig, i);
    delay(pausaTransicio);
}
}