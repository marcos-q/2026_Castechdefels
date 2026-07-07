intentin canviar la boca de la mascota utilitzant les eines apreses. Per exemple, poden intentar fer una boca trista utilitzant dues línies obliqües formant una fletxa cap amunt, o una boca sorpresa utilitzant un petit drawCircle(64, 45, 5, WHITE). Això els forçarà a calcular mentalment o en paper les coordenades abans de programar-les.


Activitat: La Barra d'Energia Interactiva
La nostra mascota necessita una manera de dir-nos si té gana, si està cansada o si té molta energia. I quina millor manera de fer-ho que amb una barra d'estat com les dels videojocs?

En aquesta activitat aprendrem a combinar les variables numèriques amb el dibuix geomètric. Farem que els botons sumin i restin punts a una variable anomenada energia, i utilitzarem aquesta variable per controlar l'amplada d'un rectangle a la pantalla OLED.

📐 El truc del disseny
Per fer-ho senzill, utilitzarem dues figures superposades:

El contenidor (Buit): Un rectangle fix dibuixat amb drawRect que actuarà de marc exterior.

El farcit (Ple): Un rectangle dibuixat amb fillRect just a dins del contenidor.

Com que la nostra variable d'energia anirà del 0% al 100%, dibuixarem el farcit perquè tingui exactament 100 píxels d'amplada màxima. Així, si l'energia és 50, el rectangle medirà 50 píxels!

💻 El Codi
C++
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pins I2C i Botons
const int PIN_SDA = 3;
const int PIN_SCL = 4;
const int PIN_BTN_A = 6;  // Botó Esquerre (Baixar energia)
const int PIN_BTN_B = 7;  // Botó Dret (Pujar energia)

// Aquesta és la variable clau! Comencem amb l'energia a la meitat.
int energia = 50; 

void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_BTN_A, INPUT_PULLUP);
  pinMode(PIN_BTN_B, INPUT_PULLUP);

  Wire.begin(PIN_SDA, PIN_SCL); 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Error d'OLED"));
    while(true);
  }
}

void loop() {
  // 1. LLEGIM ELS BOTONS
  // Si premem el botó A, restem 5 punts d'energia
  if (digitalRead(PIN_BTN_A) == LOW) {
    energia = energia - 5;
  }
  
  // Si premem el botó B, sumem 5 punts d'energia
  if (digitalRead(PIN_BTN_B) == LOW) {
    energia = energia + 5;
  }

  // 2. POSEM LÍMITS (No podem tenir energia negativa ni més de 100)
  if (energia < 0) {
    energia = 0;
  }
  if (energia > 100) {
    energia = 100;
  }

  // 3. DIBUIXEM A LA PANTALLA
  display.clearDisplay(); // Netegem la pantalla anterior

  // Escrivim el títol i el número exacte
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(12, 10);
  display.print("Nivell d'Energia:");
  display.setCursor(12, 22);
  display.print(energia);
  display.print(" %");

  // Dibuixem el MARC EXTERIOR (Buit)
  // Posició X=12, Y=38. Amplada=104, Alçada=14
  // Ho fem una mica més gran perquè hi càpiga el farcit a dins
  display.drawRect(12, 38, 104, 14, SSD1306_WHITE);

  // DIBUIXEM LA BARRA INTERIOR (Plena)
  // Fixa't bé: l'amplada ve donada per la variable "energia"!
  // Posició X=14, Y=40. Alçada=10
  display.fillRect(14, 40, energia, 10, SSD1306_WHITE);

  // Enviem tot a l'OLED
  display.display();
  
  // Una petita pausa perquè els números no sumin massa ràpid
  delay(100); 
}
🧠 Analitzem el codi
El concepte més important que acabem d'aplicar es troba en aquesta línia de codi:

display.fillRect(14, 40, energia, 10, SSD1306_WHITE);

Normalment, quan dibuixàvem una figura hi posàvem números fixos. Però els ordinadors ens permeten substituir qualsevol número per una variable. Al col·locar la variable energia al lloc on va l'amplada (width), li estem dient a la pantalla que l'amplada del rectangle depèn exclusivament de la salut de la mascota. Com que l'energia puja i baixa, l'amplada puja i baixa!

Aquest format permetrà als estudiants visualitzar com la lògica condicional numèrica es connecta de forma totalment directa amb els gràfics. Un cop dominin això, el següent pas natural serà ensenyar-los com fer que el sensor de temperatura (AHT20) o el sensor de llum controlin automàticament aquesta mateixa barra de gràfics.


🌙 Dibuixant un arc (La màgia de les matemàtiques)
Com que la nostra llibreria de dibuix no té una instrucció com drawArc, ens l'haurem d'inventar nosaltres. Com ho farem? Utilitzant la geometria!

Sabem que un cercle complet té 360 graus. Si volem dibuixar només un tros de cercle (un arc), podem fer servir un bucle for que vagi calculant punt per punt la vora d'aquest cercle, des d'un angle inicial fins a un angle final.

Hem creat una eina personalitzada anomenada dibuixarArc() que podràs fer servir per dibuixar, per exemple, un gran somriure per a la teva mascota.

💻 El Codi per al teu projecte
Pots enganxar aquesta nova funció al final del teu programa i cridar-la quan la necessitis.

C++
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int PIN_SDA = 3;
const int PIN_SCL = 4;

// --- PROTOTIP DE LA NOSTRA NOVA FUNCIÓ ---
void dibuixarArc(int x, int y, int radi, float angleInici, float angleFinal);

void setup() {
  Wire.begin(PIN_SDA, PIN_SCL); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  // Dibuixem uns ulls senzills
  display.fillCircle(45, 25, 5, SSD1306_WHITE);
  display.fillCircle(83, 25, 5, SSD1306_WHITE);

  // ARA FEM SERVIR LA NOSTRA FUNCIÓ PER FER UN SOMRIURE!
  // Centre a X=64, Y=30. Radi=18. 
  // Anem dels 0 graus fins als 180 graus (mitja circumferència inferior)
  dibuixarArc(64, 30, 18, 0, 180);

  display.display();
}

void loop() {
}

// ==========================================
// FUNCIÓ PERSONALITZADA PER DIBUIXAR ARCS
// ==========================================
void dibuixarArc(int centreX, int centreY, int radi, float angleInici, float angleFinal) {
  // Un bucle que avança grau a grau per pintar la corba
  for (float angle = angleInici; angle <= angleFinal; angle += 1.0) {
    
    // Els ordinadors calculen el sinus i cosinus en Radians, no en Graus!
    // Per tant, multipliquem per PI i dividim per 180 per fer la conversió.
    float radians = angle * PI / 180.0;
    
    // Calculem la coordenada (X, Y) d'aquest punt exacte de la corba
    int px = centreX + radi * cos(radians);
    int py = centreY + radi * sin(radians);
    
    // Pintem un píxel en aquesta coordenada calculada
    display.drawPixel(px, py, SSD1306_WHITE);
  }
}
🧠 Com funciona dibuixarArc()?
Aquesta funció que hem creat ens demana 5 dades per funcionar:

centreX i centreY: El punt central imaginari on es clavaria el compàs.

radi: La mida de l'arc.

angleInici: A quants graus comença el traç.

angleFinal: A quants graus acaba el traç.

💡 Un detall molt important sobre els angles:
A les pantalles, com que l'eix Y creix cap a baix (i no cap a dalt com a les classes de matemàtiques), els angles van en el sentit de les agulles del rellotge:

0 graus està a la dreta (a les 3h del rellotge).

90 graus està a sota (a les 6h).

180 graus està a l'esquerra (a les 9h).

270 graus està a dalt (a les 12h).

Per això, si demanem un arc del 0 al 180, ens dibuixa una forma de "U" perfecta per fer una boca feliç! Si, per contra, poséssim del 180 al 360 (o de 180 a 0 sumant en negatiu), tindríem una boca trista o de sorpresa com un arc de Sant Martí.



Aquí tens una proposta de 4 activitats progressives dissenyades per a la teva placa (amb els polsadors i el LDR que ja teniu cablejats):

Activitat 1: El "Punt de Mira" (Introducció a les coordenades)
Objectiu: Comprendre les dimensions de la pantalla (128x64) i situar punts de referència.

Què han de fer: 1. Dibuixar un únic píxel just al centre de la pantalla fent servir display.drawPixel(64, 32, WHITE).
2. Després, fer servir la funció display.drawLine() per traçar una "X" que connecti el centre amb les quatre cantonades de la pantalla.

Aprenentatge: Descobrir on comencen i on acaben els eixos X i Y.

Activitat 2: Disseny d'un "Avatar" o Monstre (Formes geomètriques)
Objectiu: Combinar diferents formes i entendre la diferència entre figures buides (draw) i plenes (fill).

Què han de fer: Dissenyar una cara senzilla a la pantalla. Per exemple:

Un rectangle gran buit per al contorn del cap (drawRect).

Dos cercles plens per als ulls (fillCircle).

Una línia o rectangle buit per a la boca.

Aprenentatge: Mapejar mentalment com se superposen les figures (el que es dibuixa primer pot quedar tapat pel que es dibuixa després).

Activitat 3: El Selector de Formes (Ús dels polsadors)
Objectiu: Fer que el dibuix reaccioni en temps real a les accions de l'usuari.

Què han de fer: Crear un programa on:

Si no es prem res, la pantalla mostra un missatge que diu "Tria una forma".

Si es prem el Botó A (Pin 6), la pantalla s'esborra i dibuixa un quadrat ple al centre.

Si es prem el Botó B (Pin 7), la pantalla s'esborra i dibuixa un cercle ple al centre.

Aprenentatge: Reforçar l'ús dels condicionals if/else aplicats al disseny gràfic i recordar la importància de fer un display.clearDisplay() abans de canviar de dibuix.

Activitat 4: El "Llum-òmetre" (Gràfic de barres analògic)
Objectiu: Representar dades d'un sensor de forma visual en lloc de numèrica.

Què han de fer: Llegir el valor del sensor LDR (Pin 0). En lloc d'escriure el número de llum, han de dibuixar un rectangle a la part inferior de la pantalla que es faci més llarg o més curt tipus "barra de càrrega" segons la llum que rebi el sensor.

Aprenentatge: Introduir la funció map() d'Arduino per convertir el rang del LDR (per exemple, de 0 a 4095 en l'ESP32) al rang de píxels de la pantalla (de 0 a 120 píxels d'ample).

Preguntes per afinar la resposta:
Per poder passar-te els codis d'exemple fets a mida o orientar millor les explicacions per a les teves fitxes de classe, em vindria molt bé saber:

Edat o nivell educatiu: Són alumnes de Secundària (ESO), Batxillerat o Cicles Formatius (FP)? (Això m'ajudarà a calibrar la complexitat matemàtica).

Vols introduir animació? Prefereixes que ens quedem en dibuixos estàtics que canvien amb els botons, o vols que la següent setmana ja aprenguin a moure un objecte per la pantalla (com una pilota que rebota o uns ulls que miren a esquerra i dreta)?

Coneixen la funció map()? L'han utilitzat mai per escalar variables o prefereixes que els plantegi l'activitat del LDR amb una fórmula matemàtica directa més senzilla?



