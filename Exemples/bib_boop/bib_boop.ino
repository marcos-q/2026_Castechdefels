// --- ASSIGNACIÓ DE PINS ---
// (Modifica el número de pin si a la teva PCB el brunzidor està connectat a un altre lloc)
const int PIN_BUZZER = 5; 

void setup() {
  // Nota: La funció tone() ja configura el pin com a OUTPUT automàticament,
  // però és una bona pràctica deixar-ho apuntat.
  pinMode(PIN_BUZZER, OUTPUT);

  // 1. Fem el "BIP" (So agut de 2000 Hz que dura 100 mil·lisegons)
  tone(PIN_BUZZER, 2000, 100);
  delay(150); // Esperem que acabi el so i deixem un petit silenci

  // 2. Fem el "BOOP" (So greu de 1000 Hz que dura 200 mil·lisegons)
  tone(PIN_BUZZER, 1000, 200);
  delay(250); // Esperem que acabi el so

  // Un cop fet el tancament de la salutació al setup(), el brunzidor callarà
}

void loop() {
  // Deixem el loop buit perquè no volem que el so es repeteixi de forma infinita
  // i ens torni bojos a classe!
}