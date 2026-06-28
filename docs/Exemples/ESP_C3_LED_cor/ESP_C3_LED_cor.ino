// --- PINS D'ENTRADA I SORTIDA ---
const int pinLedRoig = 21;
const int pinLedVerd = 20;
const int pinLedBlau = 10;

// --- VARIABLES DE TEMPS (MIL·LISEGONS) ---
const int tempsBatec = 150;     // Durada fixa de la contracció ("bum")
const int tempsPausa = 700;     // Temps de repòs fix entre batecs (ara és constant)

void setup() {
  Serial.begin(115200);
  
  // Configuració de les sortides dels LEDs
  pinMode(pinLedRoig, OUTPUT);
  pinMode(pinLedVerd, OUTPUT);
  pinMode(pinLedBlau, OUTPUT);
  
  // Configuració dels botons amb resistència pull-up interna
  pinMode(pinBotoEsquerre, INPUT_PULLUP);
  pinMode(pinBotoDret, INPUT_PULLUP);

  // Apaguem tots els LEDs a l'inici
  digitalWrite(pinLedRoig, LOW);
  digitalWrite(pinLedVerd, LOW);
  digitalWrite(pinLedBlau, LOW);
  
  Serial.println("Mascota en marxa. Estat: Batec constant i tranquil.");
}

void loop() {
  // --- EXECUCIÓ DEL BATEC ---
  
  // El primer "bum" del batec
  digitalWrite(pinLedRoig, HIGH);
  delay(tempsBatec);
  
  digitalWrite(pinLedRoig, LOW);
  delay(tempsBatec);
  
  // El segon "bum" del batec
  digitalWrite(pinLedRoig, HIGH);
  delay(tempsBatec);
  
  // El temps de repòs constant
  digitalWrite(pinLedRoig, LOW);
  delay(tempsPausa); 
}