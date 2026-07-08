// --- PINS D'ENTRADA I SORTIDA ---
const int pinLedRoig = 21;
const int pinLedVerd = 20;
const int pinLedBlau = 10;

const int pinBotoEsquerre = 6;  // L'utilitzem per alentIR el pols
const int pinBotoDret = 7;      // l'utilitzem per accelerar el pols

// --- VARIABLES DE TEMPS (MIL·LISEGONS) ---
int tempsBatec = 150;  // Durada fixa del moviment mecànic
int tempsPausa = 500;  // Temps de relaxació variable entre batecs doblegats

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
  digitalWrite(pinLedRoig, 0);
  digitalWrite(pinLedVerd, 0);
  digitalWrite(pinLedBlau, 0);
}

void loop() {
  // --- 1. LECTURA DELS BOTONS ---
  
  // Botó dret -> Accelera el cor (redueix la pausa)
  if (digitalRead(pinBotoDret) == LOW) {
    if (tempsPausa > tempsBatec) { // Límit mínim per simular taquicàrdia
      tempsPausa -= 100; 
      Serial.print("Accelera! Temps de pausa: "); 
      Serial.println(tempsPausa);
    }
  }
  
  // Botó esquerre -> Alenteix el cor (augmenta la pausa)
  if (digitalRead(pinBotoEsquerre) == LOW) {
    if (tempsPausa < 1500) { // Límit màxim per simular relaxació profunda
      tempsPausa += 100;
      Serial.print("Alenteix... Temps de pausa: "); 
      Serial.println(tempsPausa);
    }
  }

  // --- 2. EXECUCIÓ DEL BATEC (SÍSTOLE FIXA, DIÀSTOLE VARIABLE) ---
  
  // El primer "bum" del batec
  digitalWrite(pinLedRoig, HIGH);
  delay(tempsBatec);
  
  digitalWrite(pinLedRoig, LOW);
  delay(tempsBatec);
  
  // El segon "bum" del batec
  digitalWrite(pinLedRoig, HIGH);
  delay(tempsBatec);
  
  // El temps de repòs és el que varia amb els botons
  digitalWrite(pinLedRoig, LOW);
  delay(tempsPausa); 
}
