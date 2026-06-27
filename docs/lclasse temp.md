# Pràctica: Simulador de Batec Cardíac amb Arduino

En aquesta lliçó crearem un **simulador de batec cardíac (pum-pum)** utilitzant un LED i dos botons. L'objectiu és treballar conceptes clau d'electrònica i programació que podreu aplicar directament a l'aula amb els vostres alumnes de secundària o batxillerat.

## 🎯 Objectius didàctics
* Comprendre el funcionament de les resistències internes `INPUT_PULLUP`.
* Treballar amb estructures condicionals (`if`) per controlar límits d'una variable.
* Relacionar conceptes de biologia (sístole, diàstole, taquicàrdia) amb la programació.

---

## 🛠️ Components necessaris
* 1x Placa compatible amb Arduino (comprovat amb pins 21, 20, 10, 6 i 7).
* 1x LED (farem servir el canal Roig).
* 2x Botons (pulsadors).
* Cables de connexió.

---

## 💻 El Codi Font

Copieu i enganxeu el següent codi a l'IDE d'Arduino:

```cpp
// --- PINS D'ENTRADA I SORTIDA ---
const int pinLedRoig = 21;
const int pinLedVerd = 20;
const int pinLedBlau = 10;

const int pinBotoEsquerre = 6;  // L'utilitzem per alentir el pols
const int pinBotoDret = 7;      // L'utilitzem per accelerar el pols

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
  analogWrite(pinLedRoig, 0);
  analogWrite(pinLedVerd, 0);
  analogWrite(pinLedBlau, 0);
}

void loop() {
  // --- 1. LECTURA DELS BOTONS ---
  
  // Botó dret -> Accelera el cor (redueix la pausa)
  if (digitalRead(pinBotoDret) == LOW) {
    if (tempsPausa > tempsBatec) { // Límit mínim per simular taquicàrdia
      tempsPausa -= 50; 
      Serial.print("Accelera! Temps de pausa: "); 
      Serial.println(tempsPausa);
    }
  }
  
  // Botó esquerre -> Alenteix el cor (augmenta la pausa)
  if (digitalRead(pinBotoEsquerre) == LOW) {
    if (tempsPausa < 1500) { // Límit màxim per simular relaxació profunda
      tempsPausa += 50;
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
```

---

## 🔍 Conceptes clau per explicar a l'aula

### 1. Per què usem `INPUT_PULLUP`?
Quan configurem un botó com a `INPUT_PULLUP`, Arduino activa una resistència interna connectada a POSITIU (5V o 3.3V). 
* **Botó en repòs (sense prémer):** El pin llegeix un estat alt (`HIGH`).
* **Botó premut:** El corrent va a terra (GND) i el pin llegeix un estat baix (`LOW`).
* **Avantatge pedagògic:** No necessitem connectar resistències físiques a la protoboard. Menys cables, menys errors del vostre alumnat!

### 2. Control de límits de seguretat
Fixeu-vos en aquesta línia de control:
```cpp
if (tempsPausa > tempsBatec)
```
Això evita que, per molts cops que premem el botó d'accelerar, el temps de pausa baixi de 150 ms. Sense aquest límit, el cor virtual entraria en "aturada cardíaca" i el codi deixaria de simular un batec real.

---

## 🚀 Reptes i variacions propostes (Per als alumnes)

Si els vostres alumnes avancen ràpid, podeu proposar-los els següents reptes de programació:

1. **Semàfor de salut (Multidisciplinar Biologia):** Feu servir els LEDs verd i blau que hem configurat. Si el cor va molt ràpid (taquicàrdia), enceneu el LED Blau (avís). Si va a un ritme normal, enceneu el LED Verd.
2. **Alarma sonora:** Connecteu un brunzidor (buzzer) i feu que emeti un so curt a cada "bum" mecànic.
3. **El problema del rebot (*Debounce*):** Demaneu-los que mantinguin el botó premut. Què passa? Com que el codi s'executa molt ràpid a cada volta del `loop`, el temps canvia a tota velocitat. Com ho podríem solucionar?
