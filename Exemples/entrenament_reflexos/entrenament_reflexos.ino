// --- PINS D'ENTRADA I SORTIDA ---
const int pinLedRoig = 21;
const int pinLedVerd = 20;
const int pinLedBlau = 10;
const int pinBoto = 7; // Botó dret. Pots canviar-lo pel 6 si ets esquerrà i vols utilitzar el boté esquerre

// --- VARIABLES DEL JOC ---
unsigned long tempsInici;
unsigned long tempsReaccio;

void setup() {
Serial.begin(115200);
pinMode(pinLedRoig, OUTPUT);
pinMode(pinLedVerd, OUTPUT);
pinMode(pinLedBlau, OUTPUT);
pinMode(pinBoto, INPUT_PULLUP);

// Seed per fer que l'atzar sigui realment diferent cada vegada
randomSeed(analogRead(0));

Serial.println("--- JOC DE REFLEXOS INICIAT ---");
Serial.println("Espera que el LED es posi VERMELL...");
}

void loop() {
// 1. MODE ESPERA (Llum blava tènue)
analogWrite(pinLedRoig, 0);
analogWrite(pinLedVerd, 0);
analogWrite(pinLedBlau, 20);

// Esperem un temps aleatori entre 2 i 6 segons
delay(random(2000, 6000));

// 2. SENYAL D'ATAC! (LED Vermell i guardem l'hora)
analogWrite(pinLedBlau, 0);
analogWrite(pinLedRoig, 255);
tempsInici = millis();

// 3. ESPERAR LA REACCIÓ (Bloquegem el codi fins que es premi el botó)
while(digitalRead(pinBoto) == HIGH) {
    // No fem res, només esperar que el botó passi a LOW
}

// 4. CÀLCUL DEL RESULTAT
tempsReaccio = millis() - tempsInici;

Serial.print("Temps de reacció: ");
Serial.print(tempsReaccio);
Serial.println(" ms.");

// 5. FEEDBACK SEGONS EL TEMPS
if (tempsReaccio < 500) {
    Serial.println("Ets un Ninja! Molt bé!");
    analogWrite(pinLedRoig, 0);
    analogWrite(pinLedVerd, 255); // Flaix Verd
} else {
    Serial.println("Massa lent... Has d'entrenar més.");
    analogWrite(pinLedRoig, 255);
    analogWrite(pinLedVerd, 100); // Taronja/Groc
}

delay(3000); // Pausa de 3 segons abans de la següent ronda
}