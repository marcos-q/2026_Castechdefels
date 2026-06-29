// --- PINS D'ENTRADA I SORTIDA ---
const int pinLedRoig = 21;
const int pinLedVerd = 20;
const int pinLedBlau = 10;

const int pinBotoSelector = 6;  // Botó Esquerre
const int pinBotoIncrement = 7; // Botó Dret

// --- VARIABLES D'ESTAT ---
int nivellR = 0;
int nivellG = 0;
int nivellB = 0;

int canalSeleccionat = 0; // 0 = Vermell, 1 = Verd, 2 = Blau

void setup() {
Serial.begin(115200);

pinMode(pinLedRoig, OUTPUT);
pinMode(pinLedVerd, OUTPUT);
pinMode(pinLedBlau, OUTPUT);

pinMode(pinBotoSelector, INPUT_PULLUP);
pinMode(pinBotoIncrement, INPUT_PULLUP);

// Iniciem apagats
analogWrite(pinLedRoig, 0);
analogWrite(pinLedVerd, 0);
analogWrite(pinLedBlau, 0);

Serial.println("Sintetitzador d'Emocions iniciat.");
Serial.println("Canal actual: VERMELL");
}

void loop() {
// --- 1. LECTURA DEL BOTÓ SELECTOR ---
if (digitalRead(pinBotoSelector) == LOW) {
    canalSeleccionat++; // Passem al següent color

    // Si ens passem del Blau (2), tornem al Vermell (0)
    if (canalSeleccionat > 2) {
    canalSeleccionat = 0; 
    }

    // Avisem per pantalla
    Serial.print("Canal seleccionat: ");
    if (canalSeleccionat == 0) Serial.println("VERMELL");
    if (canalSeleccionat == 1) Serial.println("VERD");
    if (canalSeleccionat == 2) Serial.println("BLAU");

    delay(200); // Pausa per evitar el rebot mecànic del botó
}

// --- 2. LECTURA DEL BOTÓ D'INCREMENT ---
if (digitalRead(pinBotoIncrement) == LOW) {

    // Sumem 10 al color que estigui seleccionat actualment
    if (canalSeleccionat == 0) {
    nivellR += 10;
    if (nivellR > 255) nivellR = 0;
    } 
    else if (canalSeleccionat == 1) {
    nivellG += 10;
    if (nivellG > 255) nivellG = 0;
    } 
    else if (canalSeleccionat == 2) {
    nivellB += 10;
    if (nivellB > 255) nivellB = 0;
    }

    // Imprimim la nova recepta d'estat d'ànim
    Serial.print("Nova emoció -> R: ");
    Serial.print(nivellR);
    Serial.print(" | G: ");
    Serial.print(nivellG);
    Serial.print(" | B: ");
    Serial.println(nivellB);

    delay(200); // Pausa per evitar sumar massa ràpid
}

// --- 3. ACTUALITZAR EL COLOR DEL LED ---
analogWrite(pinLedRoig, nivellR);
analogWrite(pinLedVerd, nivellG);
analogWrite(pinLedBlau, nivellB);
}