
# La mascota canvia d'humor: Canvis d'expressió

Fins ara hem aconseguit que la nostra mascota ens miri amb una cara ben desperta i amigable. Però les mascotes reals canvien d'estat d'ànim: tenen son, s'enfaden, s'espanten.

Fins ara hem aconseguit dibuixar una cara fixa a la pantalla. Però les mascotes de veritat tenen sentiments, canvien d'estat d'ànim i reaccionen al que passa al seu voltant!

El veritable poder de la pantalla OLED és que podem canviar el dibuix en qüestió de mil·lisegons si combinem les funcions de dibuix amb els botons i els sensors de la nostra PCB. T'atreveixes amb aquest repte?

- ### La mascota enfadada
    #### Part 1: Dibuixa la cara d'enuig

    La teva primera missió és purament de disseny gràfic. Has de modificar el codi de la cara original per aconseguir que la teva mascota sembli enfadada.

    **Pista de disseny:** Conserva el contorn del cap i els ulls de la mascota, però afegeix dues línies diagonals a sobre dels ulls a mode de celles arrufades utilitzant la instrucció `display.drawLine()`.
    
     A més, recorda canviar la línia del somriure per una línia completament recta o inclinada cap avall.

    *Aconsegueix que la teva mascota faci por abans de passar a la segona part*


    #### Part 2: Canvi d'humor interactiu

    Ara que ja tens guardades  la cara normal i de la cara d'enuig, és el moment de fusionar el codi dels botons amb el de la pantalla.

    Crea un programa on el bucle `loop()` comprovi constantment l'estat dels botons:

      * Si **no prems cap botó**, la pantalla s'ha de netejar i mostrar la **cara normal i feliç**.
      * Si **mantens premut el Botó esquerre**, la pantalla s'ha de netejar immediatament i mostrar la **cara d'enuig** que has dissenyat a la Part 1.

> **Recordatori important:** Dins del `loop()`, abans de dibuixar cada cara, necessitaràs fer un `display.clearDisplay()` perquè les dues expressions no es barregin a la pantalla, i acabar sempre amb un `display.display()`.



- ### La mascota adormida

Si has aconseguit superar les dues parts anteriors, ja ets tot un expert o una experta en controlar la pantalla amb botons. Però... què passa quan es fa fosc a l'aula o a casa teva? Una mascota intel·ligent hauria d'adormir-se automàticament!

Ens cal introduir el següent component de la nostra placa: el **sensor de llum LDR (Fotoresistència)**.

En la pròxima activitat aprendrem a llegir aquest sensor per fer el repte definitiu:

1. Si el sensor detecta llum, la mascota estarà desperta (i podràs fer que s'enfadi amb el botó).
2. Si tapes el sensor de llum amb el dit (simulant que és de nit), la pantalla es redibuixarà sola per mostrar la **cara adormida** (amb línies horitzontals als ulls i unes lletres que diguin "Zzz...").

*Prepara el teu codi, perquè estem a punt de connectar la mascota al món real!*

### Repte avançat:

#### Part 1: Dibuixa la cara d'adormida
En aquesta activitat us facilito el codi d'una **tercera expressió facial**. Analitza el codi abans de pujar-lo a la placa: fixa't com utilitzem línies rectes per fer els ulls tancats, un petit cercle buit per fer una boca que ronca, i hem combinat gràfics amb text per dibuixar unes "Zzz...".

Copia aquest codi i comprova el resultat a la teva OLED:

```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int PIN_SDA = 3;
const int PIN_SCL = 4;

void setup() {
  Wire.begin(PIN_SDA, PIN_SCL); 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while(true);
  }

  // Netejem la pantalla per preparar la nova cara
  display.clearDisplay();
  
  // 1. El contorn del cap (es manté igual)
  display.drawRoundRect(10, 5, 108, 54, 8, SSD1306_WHITE);

  // 2. Ulls tancats (Línies horitzontals en lloc de cercles)
  display.drawLine(30, 25, 45, 25, SSD1306_WHITE); // Ull esquerre tancat
  display.drawLine(83, 25, 98, 25, SSD1306_WHITE); // Ull dret tancat

  // 3. Boca (Un cercle petit dibuixant una "O" de roncar)
  display.drawCircle(64, 40, 4, SSD1306_WHITE);

  // 4. Detall extra: Text combinat amb dibuix
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(95, 10);
  display.print("Zzz...");

  // Mostrem la nova cara!
  display.display(); 
}

void loop() {
  // Animació futura? De moment es queda adormida!
}

```

#### Part 2: És fosc. Bona nit!

Crea el codi de tal manera que,  si tapes el sensor de llum amb el dit (simulant que és de nit), la pantalla es redibuixi sola per mostrar la **cara adormida** de la part 1.
