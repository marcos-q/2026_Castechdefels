// --- PINS D'ENTRADA I SORTIDA ---
const int pinLedRoig = 21;
const int pinLedVerd = 20;
const int pinLedBlau = 10;

// --- configuració dels pemps
const int pausaInspiracio = 8; //retard en el bucle d'inspiració
const int pausaExpiracio = 10; //retard en el bucle d'expiració. COMPTE amb expiración i espiración si feu servir variables en castellà ;-)
const int pausaPlena = 150;    //temps que mantenim la respiració amb els pulmons plens
const int pausaBuida = 600;    //temps que mantenim la respiració amb els pulmons buits
void setup() {
  // Configuració de les sortides dels LEDs
  pinMode(pinLedRoig, OUTPUT);
  pinMode(pinLedVerd, OUTPUT);
  pinMode(pinLedBlau, OUTPUT);

  // Apaguem els LEDs roig i verd (lògica normal: 0 = apagat)
  analogWrite(pinLedRoig, 0);
  analogWrite(pinLedVerd, 0);
}

void loop() {
  // --- 1. INSPIRACIÓ (De fosc a brillant) ---
  // Anem augmentant el valor de 0 a 255
  for (int brillantor = 0; brillantor <= 255; brillantor++) {
    analogWrite(pinLedBlau, brillantor);
    delay(pausaInspiracio); // Controla la velocitat de la inspiració 
  }

  // --- 2. PAUSA PLENA (Mantenint l'aire) ---
  delay(pausaPlena);

  // --- 3. EXPIRACIÓ (De brillant a fosc) ---
  // Anem reduint el valor de 255 a 0
  for (int brillantor = 255; brillantor >= 0; brillantor--) {
    analogWrite(pinLedBlau, brillantor);
    delay(pausaExpiracio); // L'expiració és una mica més lenta per ser més natural (Compte amb expirar si feu servir castellà)
  }

  // --- 4. PAUSA BUIDA (En repòs) ---
  delay(pausaBuida); // Pausa abans de tornar a començar el cicle de respiració
}