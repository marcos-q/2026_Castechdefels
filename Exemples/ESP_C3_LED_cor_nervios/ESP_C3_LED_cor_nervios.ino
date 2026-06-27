// --- PINS D'ENTRADA I SORTIDA ---
const int pinLedRoig = 21;
const int pinLedVerd = 20;
const int pinLedBlau = 10;

const int pinBotoEsquerre = 6;  // Aquest botó queda lliure per a futurs exercicis
const int pinBotoDret = 7;      // L'utilitzem per donar atenció i calmar la mascota

// --- VARIABLES DE TEMPS (MIL·LISEGONS) ---
const int tempsBatec = 150;     // Durada fixa del moviment mecànic
const int tempsPausaInicial = 700; // Estat de relaxació base inicial
int tempsPausa = tempsPausaInicial;           // Temps que anirà disminuint sol
int ritmeAnsietat = 20;         // Quants mil·lisegons perdem a cada batec

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
  
  Serial.println("Mascota encesa. Estat: Tranquil·la.");
}

void loop() {
  // --- 1. LECTURA DE L'ATENCIÓ (BOTÓ) ---
  
  // Si fem cas a la mascota (Botó dret), es relaxa de cop
  if (digitalRead(pinBotoDret) == LOW) {
    tempsPausa = tempsPausaInicial; 
    Serial.println("Atenció rebuda! La mascota es calma.");
  }

  // --- 2. EVOLUCIÓ DE L'ESTAT (ANSIETAT AUTÒNOMA) ---
  
  // Si no hem polsat el botó, la mascota es va posant nerviosa
  // Reduïm la pausa, però posem un límit perquè el cor no "exploti"
  if (tempsPausa > tempsBatec) { 
    tempsPausa -= ritmeAnsietat;
  }

  // --- 3. EXECUCIÓ DEL BATEC ---
  
  // El primer "bum" del batec
  digitalWrite(pinLedRoig, HIGH);
  delay(tempsBatec);
  
  digitalWrite(pinLedRoig, LOW);
  delay(tempsBatec);
  
  // El segon "bum" del batec
  digitalWrite(pinLedRoig, HIGH);
  delay(tempsBatec);
  
  // El temps de repòs actual (cada cop més curt si no l'atenem)
  digitalWrite(pinLedRoig, LOW);
  delay(tempsPausa); 
  
  // Debug per veure l'estat d'ansietat al Monitor Sèrie
  Serial.print("Nivell de pausa actual: "); 
  Serial.println(tempsPausa);
}