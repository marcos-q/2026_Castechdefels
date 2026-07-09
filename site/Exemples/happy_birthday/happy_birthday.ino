// --- ASSIGNACIÓ DE PINS ---
const int PIN_BUZZER = 5; 

// --- DEFINICIÓ DE LES NOTES MUSICALS (Freqüències en Hz) ---
#define NOTE_C4  262  // Do
#define NOTE_D4  294  // Re
#define NOTE_E4  330  // Mi
#define NOTE_F4  349  // Fa
#define NOTE_G4  392  // Sol
#define NOTE_A4  440  // La
#define NOTE_AS4 466  // La# / Sib
#define NOTE_C5  523  // Do (octava superior)

// --- LA MELODIA (Llista de notes consecutives) ---
int melodia[] = {
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4,        // Happy Birthday to you
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4,        // Happy Birthday to you
  NOTE_C4, NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4, // Happy Birthday dear Mascota...
  NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4       // Happy Birthday to you!
};

// --- LA DURADA DE CADA NOTA (en mil·lisegons) ---
int durades[] = {
  200, 200, 400, 400, 400, 800,
  200, 200, 400, 400, 400, 800,
  200, 200, 400, 400, 400, 400, 800,
  200, 200, 400, 400, 400, 800
};

// Calculem automàticament quantes notes té la cançó
int totalNotes = sizeof(melodia) / sizeof(melodia[0]);

void setup() {
  pinMode(PIN_BUZZER, OUTPUT);

  // Un bucle "for" que recorre la llista nota per nota
  for (int i = 0; i < totalNotes; i++) {
    
    // Toquem la nota actual amb la seva durada corresponent
    tone(PIN_BUZZER, melodia[i], durades[i]);
    
    // IMPORTANT: Deixem un petit silenci entre nota i nota (un 30% més de la seva durada)
    // Si no ho fessim, les notes es col·lapsarien i sonaria com un xiulet continu sense ritme
    int pausaEntreNotes = durades[i] * 1.30;
    delay(pausaEntreNotes);
    
    // Apaguem el so abans de la següent nota
    noTone(PIN_BUZZER);
  }
}

void loop() {
  // El loop queda buit perquè la cançó ja ha sonat un cop al setup i ha acabat.
}