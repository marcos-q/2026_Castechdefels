// --- PINS D'ENTRADA I SORTIDA ---
const int pinLedRoig = 21;
const int pinLedVerd = 20;
const int pinLedBlau = 10;

void setup() {
  Serial.begin(115200);
  
  pinMode(pinLedRoig, OUTPUT);
  pinMode(pinLedVerd, OUTPUT);
  pinMode(pinLedBlau, OUTPUT);
  
  Serial.println("Mascota encesa. Generant totes les combinacions RGB...");
}

void loop() {
  // Bucle 1: Controla el Vermell
  for (int r = 0; r <= 255; r = r + 10) { //Pots provar a començar en 90
    
    // Bucle 2: Controla el Verd
    for (int g = 0; g <= 255; g += 10) { //Pots provar a començar en 90
      
      // Bucle 3: Controla el Blau
      for (int b = 0; b <= 255; b += 10) { //Pots provar a començar en 90
        
        // Apliquem la combinació actual de colors
        analogWrite(pinLedRoig, r);
        analogWrite(pinLedVerd, g);
        analogWrite(pinLedBlau, b);

        Serial.print(r);Serial.print(", ");
        Serial.print(g);Serial.print(", ");
        Serial.println(b);
        
        delay(10);
      }
    }
  }
}