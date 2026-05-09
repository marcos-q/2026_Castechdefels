# 🛠️ Tutorial de Programació OLED: Guia de Funcions Principals



En aquesta secció aprendrem a dominar les  instruccions fonamentals per gestionar el text i l'espai visual de la nostra pantalla SSD1306.

**INDEX**
- [🛠️ Tutorial de Programació OLED: Guia de Funcions Principals](#️-tutorial-de-programació-oled-guia-de-funcions-principals)
    - [`display.begin(SSD1306_SWITCHCAPVCC, 0x3C)`](#displaybeginssd1306_switchcapvcc-0x3c)
    - [💡 Consell Didàctic (El "Hardware Hack")](#-consell-didàctic-el-hardware-hack)
  - [`display.clearDisplay();` — L'Esborrador Màgic](#displaycleardisplay--lesborrador-màgic)
    - [1. Com funciona tècnicament?](#1-com-funciona-tècnicament)
    - [2. La importància de l'Ordre (El flux de dibuix)](#2-la-importància-de-lordre-el-flux-de-dibuix)
    - [3. Per què no es veu el parpelleig?](#3-per-què-no-es-veu-el-parpelleig)
    - [🏋️ Repte Pràctic en Aula: "L'Efecte Taca"](#️-repte-pràctic-en-aula-lefecte-taca)
  - [`display.setTextColor();` — Triant el color i el fons](#displaysettextcolor--triant-el-color-i-el-fons)
    - [1. Sintaxi Bàsica (Fons Transparent)](#1-sintaxi-bàsica-fons-transparent)
    - [2. Sintaxi Avançada (Fons Opac / Mode Invertit)](#2-sintaxi-avançada-fons-opac--mode-invertit)
    - [🛠️ Exemple Comparatiu de Dissenys](#️-exemple-comparatiu-de-dissenys)
    - [🏋️ Repte Pràctic en Aula: "El Sensor Fantasma"](#️-repte-pràctic-en-aula-el-sensor-fantasma)
  - [📍 `display.setCursor(x, y);` — Posicionament de Precisió](#-displaysetcursorx-y--posicionament-de-precisió)
    - [1. El Sistema de Coordenades (Eixos X i Y)](#1-el-sistema-de-coordenades-eixos-x-i-y)
    - [2. Sintaxi i Funcionament](#2-sintaxi-i-funcionament)
    - [3. El factor "Mida del Text"](#3-el-factor-mida-del-text)
    - [💡 Exemples Didàctics](#-exemples-didàctics)
    - [🏋️ Repte Pràctic en Aula: "El Centre Exacte"](#️-repte-pràctic-en-aula-el-centre-exacte)
  - [`display.setTextSize(mida);` — Controlant l'escala del text](#displaysettextsizemida--controlant-lescala-del-text)
    - [1. Com funciona l'escala?](#1-com-funciona-lescala)
    - [2. Sintaxi i Funcionament](#2-sintaxi-i-funcionament-1)
    - [3. L'Impacte en les Coordenades (`setCursor`)](#3-limpacte-en-les-coordenades-setcursor)
    - [💡 Exemples Didàctics](#-exemples-didàctics-1)
    - [🏋️ Repte Pràctic en Aula: "El Títol i la Dada"](#️-repte-pràctic-en-aula-el-títol-i-la-dada)
  - [🖨️ `display.println();` vs `display.print();` — El Salt de Línia](#️-displayprintln-vs-displayprint--el-salt-de-línia)
    - [1. La diferència fonamental](#1-la-diferència-fonamental)
    - [2. Què passa exactament amb les coordenades? (Mecànica interna)](#2-què-passa-exactament-amb-les-coordenades-mecànica-interna)
    - [💡 Exemples Didàctics](#-exemples-didàctics-2)
    - [Repte Pràctic en Aula: "El Menú Desalineat"](#repte-pràctic-en-aula-el-menú-desalineat)
  - [`display.setTextWrap();` — El Salt de Línia Automàtic](#displaysettextwrap--el-salt-de-línia-automàtic)
    - [1. Com funciona?](#1-com-funciona)
    - [2. El problema estètic (Per què voldríem desactivar-ho?)](#2-el-problema-estètic-per-què-voldríem-desactivar-ho)
    - [💡 Exemples Didàctics](#-exemples-didàctics-3)
    - [🏋️ Repte Pràctic en Aula: "La Paraula Trencada"](#️-repte-pràctic-en-aula-la-paraula-trencada)
  - [*Nota per al professor: Aquest repte és ideal per introduir el concepte de disseny d'interfícies (UI), on el programador (i no la màquina) ha de decidir on va cada element perquè sigui llegible per a l'usuari.*](#nota-per-al-professor-aquest-repte-és-ideal-per-introduir-el-concepte-de-disseny-dinterfícies-ui-on-el-programador-i-no-la-màquina-ha-de-decidir-on-va-cada-element-perquè-sigui-llegible-per-a-lusuari)
  - [`display.display();` — El Gallet d'Impressió](#displaydisplay--el-gallet-dimpressió)
    - [🏋️ Repte Pràctic en Aula: "El Codi Perfecte i Invisible"](#️-repte-pràctic-en-aula-el-codi-perfecte-i-invisible)
  - [`display.drawRect();` i `display.fillRect();` — Creant Interfícies](#displaydrawrect-i-displayfillrect--creant-interfícies)
    - [1. Sintaxi de Geometria](#1-sintaxi-de-geometria)
    - [Exemples Didàctics](#exemples-didàctics)
    - [Repte Pràctic en Aula: "La Barra de Progrés" (Nivell Avançat)](#repte-pràctic-en-aula-la-barra-de-progrés-nivell-avançat)
  - [`display.drawBitmap();` — Imatges i Icones](#displaydrawbitmap--imatges-i-icones)
    - [1. Com funciona?](#1-com-funciona-1)
    - [2. Sintaxi](#2-sintaxi)
    - [🏋️ Repte Pràctic en Aula: "El Cor Bategant"](#️-repte-pràctic-en-aula-el-cor-bategant)
  - [`display.invertDisplay();` — L'Alarma Visual Ràpida](#displayinvertdisplay--lalarma-visual-ràpida)
    - [1. Funcionament](#1-funcionament)
    - [🏋️ Repte Pràctic en Aula: "Mode Pànic"](#️-repte-pràctic-en-aula-mode-pànic)
  - [🌍 Lletres amb accent i caràcters especials (ç, ñ, º)](#-lletres-amb-accent-i-caràcters-especials-ç-ñ-º)
    - [1. La solució: `display.write();` i el codi secret](#1-la-solució-displaywrite-i-el-codi-secret)
    - [2. Taula ràpida de caràcters (Català / Castellà)](#2-taula-ràpida-de-caràcters-català--castellà)
    - [3. Com s'escriu al codi?](#3-com-sescriu-al-codi)
    - [💡 Exemples Didàctics](#-exemples-didàctics-4)
    - [🏋️ Repte Pràctic en Aula: "El Menú Correcte"](#️-repte-pràctic-en-aula-el-menú-correcte)
  - [🪄 El Truc Màgic: Automatitzar els accents (Nivell Pro)](#-el-truc-màgic-automatitzar-els-accents-nivell-pro)
    - [1. La "Capsa Negra" (La Funció)](#1-la-capsa-negra-la-funció)
    - [2. Com s'utilitza?](#2-com-sutilitza)
    - [🏋️ Repte Pràctic en Aula: "Ampliant el Diccionari"](#️-repte-pràctic-en-aula-ampliant-el-diccionari)
  - [*(Nota per al professor: Si per algun projecte de final de curs un alumne ha de fer interfícies molt complexes o amb altres idiomes, la millor opció és canviar la llibreria `Adafruit_GFX` per una altra anomenada **`U8g2`**. Aquesta llibreria és més complexa d'aprendre al principi, però suporta la codificació moderna UTF-8 de manera nativa).*](#nota-per-al-professor-si-per-algun-projecte-de-final-de-curs-un-alumne-ha-de-fer-interfícies-molt-complexes-o-amb-altres-idiomes-la-millor-opció-és-canviar-la-llibreria-adafruit_gfx-per-una-altra-anomenada-u8g2-aquesta-llibreria-és-més-complexa-daprendre-al-principi-però-suporta-la-codificació-moderna-utf-8-de-manera-nativa)
  - [🤸‍♂️ `display.setRotation();` — Girant la pantalla](#️-displaysetrotation--girant-la-pantalla)
    - [1. Com funciona?](#1-com-funciona-2)
    - [2. On es posa?](#2-on-es-posa)
    - [3. La regla d'or de les coordenades](#3-la-regla-dor-de-les-coordenades)
    - [🏋️ Repte Pràctic en Aula: "El Mode Smartphone"](#️-repte-pràctic-en-aula-el-mode-smartphone)
    - [EXEMPLE marquesina](#exemple-marquesina)
  - [🎞️ Rètols Lluminosos (Scroll) — Animacions sense esforç](#️-rètols-lluminosos-scroll--animacions-sense-esforç)
    - [1. Com funciona?](#1-com-funciona-3)
    - [2. Aturar l'animació](#2-aturar-lanimació)
    - [3. La Regla d'Or del Scroll](#3-la-regla-dor-del-scroll)
    - [🏋️ Repte Pràctic en Aula: "El Rètol Tremolós"](#️-repte-pràctic-en-aula-el-rètol-tremolós)
  - [🎞️ Animacions i Scroll (Desplaçament Automàtic)](#️-animacions-i-scroll-desplaçament-automàtic)
    - [1. Conceptes clau: Les Pàgines](#1-conceptes-clau-les-pàgines)
    - [2. Comandes de Scroll Horitzontal](#2-comandes-de-scroll-horitzontal)
    - [3. Desplaçament Diagonal](#3-desplaçament-diagonal)
    - [4. Aturar l'animació](#4-aturar-lanimació)
    - [⚠️ Regles d'or per a l'ús del Scroll](#️-regles-dor-per-a-lús-del-scroll)
    - [🏋️ Exercici proposat: "L'alerta dinàmica"](#️-exercici-proposat-lalerta-dinàmica)
    - [💡 Consell per al teu repositori](#-consell-per-al-teu-repositori)




---

### `display.begin(SSD1306_SWITCHCAPVCC, 0x3C)`
Aquesta funció és la "clau de contacte". Reserva la memòria RAM (el Buffer) i desperta la pantalla.

#### Paràmetre 1: `SSD1306_SWITCHCAPVCC`
Això sol confondre molt, però és una oportunitat excel·lent per ensenyar una mica d'electrònica real als alumnes.

* **Què significa?** Li estem dient a la pantalla: "Utilitza la teva bomba de càrrega interna per generar voltatge".
* **Per què és necessari?** Els píxels OLED necessiten un voltatge relativament alt per brillar (normalment entre 7V i 9V). No obstant això, nosaltres alimentem la pantalla amb només 3.3V des de l'ESP32. El xip SSD1306 té un circuit intern (un *Charge Pump* o bomba de càrrega amb condensadors) que agafa aquests 3.3V i els eleva màgicament fins als 7-9V necessaris. En passar-li aquest paràmetre, encenem aquest elevador de voltatge.
* **L'alternativa:** Existeix un altre paràmetre anomenat `SSD1306_EXTERNALVCC`, però gairebé mai s'utilitza en aquestes pantalles comercials, ja que implicaria que tu li estàs subministrant aquests 9V externament per un pin, i podries cremar la placa si no està dissenyada per a això.

#### Paràmetre 2: `0x3C` 
Aquesta és l'**adreça I2C** de la pantalla. **0x3C:** és l'adreça I2C per defecte de la majoria de pantalles de 0.96". 

Imagina el bus I2C de l'ESP32 com un passadís llarg amb moltes portes. Cada dispositiu connectat (la pantalla, el sensor de temperatura SHT31, etc.) té un "número de porta" únic escrit en hexadecimal. 

En posar `0x3C`, l'ESP32 crida pel passadís: *"Ei, dispositiu de la porta 0x3C, prepara't que t'enviaré dibuixos!"*.

* **El problema habitual a classe:** El 90% de les pantalles OLED de 0.96" vénen amb l'adreça `0x3C`. Tot i això, algunes pantalles més grans (com les d'1.3") o d'altres fabricants vénen configurades de fàbrica amb l'adreça `0x3D`. Si la pantalla no s'encén, aquest és el primer sospitós.

---
### 💡 Consell Didàctic (El "Hardware Hack")

Si li doneu la volta a la pantalla OLED, veureu que sol tenir unes petites resistències de superfície (SMD) prop d'un text que diu `0x78` i `0x7A` (que són les adreces `0x3C` i `0x3D` desplaçades un bit). 

Podeu ensenyar als alumnes que, movent aquesta resistència amb un soldador d'un punt a l'altre, poden canviar l'adreça física de la pantalla. Això els permet connectar **dues pantalles OLED idèntiques** al mateix ESP32 alhora!

---

##  `display.clearDisplay();` — L'Esborrador Màgic

Neteja el "llenç invisible" de la memòria del microcontrolador. És obligatori cridar-la al principi de cada cicle de dibuix per evitar que les imatges noves se superposin a les antigues.


Imagina que la pantalla OLED és una **pissarra de guix**. Cada vegada que dibuixes alguna cosa (un cercle, una línia o un text), estàs escrivint en aquesta pissarra. Si vols dibuixar quelcom nou al mateix lloc, no pots simplement escriure a sobre, perquè els traços antics seguiran allà i tot es tornarà il·legible.

`display.clearDisplay()` és l'ordre que neteja per complet la pissarra.

### 1. Com funciona tècnicament?
L'ESP32 té un **Buffer** (un llenç invisible a la seva memòria RAM). Aquest buffer és una matriu de bits on cada `1` representa un píxel encès i cada `0` un píxel apagat.

Quan crides a `display.clearDisplay()`:
1. L'ESP32 recorre tota aquesta memòria interna.
2. Posa **tots els bits a 0**.
3. El llenç es queda totalment "negre" (buit).

### 2. La importància de l'Ordre (El flux de dibuix)
És vital recalcar el **cicle de vida d'un fotograma**. L'ordre correcte al `loop()` sempre ha de ser:
1.  **`display.clearDisplay();`** (Esborrar l'anterior).
2.  **`display.draw...`** (Dibuixar les noves formes o textos).
3.  **`display.display();`** (Enviar el resultat a la pantalla física).

### 3. Per què no es veu el parpelleig?
Molts alumnes pregunten: *"Si esborro la pantalla a cada cicle, no hauria de parpellejar?"*. La resposta és **NO**:
* `clearDisplay()` només neteja la memòria de l'ESP32, no toca la pantalla física.
* La pantalla física només canvia quan arriba la instrucció `display.display()`.
* Com que l'ESP32 és extremadament ràpid, l'ull humà no percep el moment de l'actualització; només veu una imatge fluida.

### 🏋️ Repte Pràctic en Aula: "L'Efecte Taca"

**Objectiu:** Entendre visualment què passa si oblidem esborrar la pantalla abans de dibuixar noves dades d'un sensor.

**Instruccions:**
1. Demana als alumnes que comentin la línia `// display.clearDisplay();` en un codi que llegeixi el sensor de llum (LDR) contínuament.
2. Fes que tapin i destapin el sensor ràpidament.
3. **El resultat:** Els números s'aniran escrivint uns sobre els altres. En pocs segons, a la pantalla només es veurà un bloc blanc il·legible. Aquesta és la millor manera de gravar a foc la necessitat d'aquesta instrucció.

---

## `display.setTextColor();` — Triant el color i el fons

Defineix amb quina "tinta" escrivim. 
* `WHITE`: Text blanc sobre fons negre (transparent).
* `BLACK, WHITE`: Mode invertit (text negre sobre bloc blanc). Ideal per a menús seleccionats.

En una pantalla OLED monocromàtica, no tenim colors, però tenim una cosa molt més útil: la capacitat de definir el **color del text** i el **color del fons**.

### 1. Sintaxi Bàsica (Fons Transparent)
```cpp
display.setTextColor(WHITE);
```
És la forma més comuna. El fons de la lletra és **transparent**. El que hi hagi dibuixat a sota es veurà entre els forats de les lletres.

### 2. Sintaxi Avançada (Fons Opac / Mode Invertit)
Aquest és el "secret" per fer menús professionals i evitar errors visuals amb dades dinàmiques:
```cpp
display.setTextColor(BLACK, WHITE); // Lletra negra, fons blanc (ressaltat)
display.setTextColor(WHITE, BLACK); // Lletra blanca, fons negre (esborrat local)
```
* **Primer paràmetre:** Color de la lletra.
* **Segon paràmetre:** Color del fons de la lletra (una "caixa" opaca darrere el text).

### 🛠️ Exemple Comparatiu de Dissenys
```cpp
// Cas A: Text estàndard
display.setTextColor(WHITE);
display.println("Mode Normal");

// Cas B: Text ressaltat (Seleccionat o Alerta)
display.setTextColor(BLACK, WHITE); 
display.println(" SELECCIONAT ");
```

**Valor didàctic:**
* **Llegibilitat:** El contrast és clau. El mode invertit és excel·lent per a missatges d' "ERROR" o "PERILL".
* **Estalvi de codi:** Usar `setTextColor(BLACK, WHITE)` estalvia haver de dibuixar rectangles amb `fillRect()` per crear botons.


### 🏋️ Repte Pràctic en Aula: "El Sensor Fantasma"

**Objectiu:** Solucionar l'error clàssic de les xifres que es queden gravades quan un valor disminueix de longitud.

**Instruccions:**
1. Dibuixeu el valor d'un sensor que doni `1000`. Després, feu que el valor baixi a `90` imprimint-lo a la mateixa coordenada.
2. **El parany didàctic:** Si usen `setTextColor(WHITE)`, el `90` s'escriurà sobre el `10`, però els dos últims zeros del `1000` original seguiran allà. A la pantalla es llegirà `9000`!
3. **La solució:** Canviar la instrucció a `display.setTextColor(WHITE, BLACK)`. La "caixa negra" del fons de les lletres noves esborrarà automàticament les lletres velles, fins i tot si la xifra és més curta.

---

## 📍 `display.setCursor(x, y);` — Posicionament de Precisió

La pantalla OLED és un mapa de coordenades i podem indicar on decidim "posar el llapis".

### 1. El Sistema de Coordenades (Eixos X i Y)
Alerta! En programació visual, l'Eix Y no funciona com a les classes de matemàtiques. L'origen no és al centre ni l'Eix Y creix cap amunt.

```text
(0,0) ------------> Eix X (fins a 127)
  |
  |
  v Eix Y (fins a 63)
```
* **L'origen (0, 0):** És la cantonada superior esquerra.
* **Eix X:** Augmenta cap a la dreta.
* **Eix Y:** Augmenta cap avall.

### 2. Sintaxi i Funcionament
```cpp
display.setCursor(columna, fila);
```
**Important:** El cursor defineix el "sostre" i el "marge esquerre" de la lletra. El text es dibuixarà des d'aquella coordenada cap a la dreta i **cap avall**. No intenteu alinear la base del text amb l'Eix Y o el text sortirà per sota de la pantalla.

### 3. El factor "Mida del Text"
La mida (`setTextSize`) determina l'espai que ocuparà cada caràcter:
* **Mida 1:** Ocupa un bloc de **6x8 píxels** (6 d'amplada per 8 d'alçada, incloent l'espai entre lletres).
* Aquesta constant (6x8) és la clau per poder calcular posicions exactes abans de dibuixar.

### 💡 Exemples Didàctics
```cpp
// A. Escriure a les cantonades (Tenint en compte l'alçada del text!)
display.setCursor(0, 0);   display.print("Dalt");
display.setCursor(0, 56);  display.print("Baix"); // 64 (fons) - 8 (alçada lletra) = 56

// B. Formatar dades separades
display.setCursor(0, 10);
display.print("TEMP:"); 
display.setCursor(60, 10); // Desplacem el cursor a la dreta per posar el valor
display.print(25.4);
```

### 🏋️ Repte Pràctic en Aula: "El Centre Exacte"

**Objectiu:** Fer que la paraula "HOLA" aparegui el més centrada possible a la pantalla OLED, tant verticalment com horitzontalment.

**El parany didàctic:**
Molts alumnes escriuran instintivament `display.setCursor(64, 32);` (la meitat matemàtica de 128 i 64). Quan ho facin, veuran que el text comença des del centre i creix cap a la dreta i cap avall, quedant totalment descentrat.

**Guia de resolució:**
1. Demana'ls que calculin l'amplada total de la paraula: **4 lletres * 6 px = 24 píxels d'amplada**.
2. Identifiqueu l'alçada per defecte: **8 píxels d'alçada**.
3. **Càlcul X:** (Amplada Pantalla - Amplada Text) / 2  -->  (128 - 24) / 2 = **52**
4. **Càlcul Y:** (Alçada Pantalla - Alçada Text) / 2  -->  (64 - 8) / 2 = **28**

**Solució esperada:**
```cpp
display.setCursor(52, 28);
display.print("HOLA");
```
---
## `display.setTextSize(mida);` — Controlant l'escala del text

Si la pantalla OLED fos un document de text, `setTextSize()` seria el menú on triem si volem la lletra a 12 punts per a un paràgraf o a 24 punts per a un títol. Aquesta funció defineix com de gran es dibuixarà el text a partir d'aquest moment.

### 1. Com funciona l'escala?
A la llibreria Adafruit, no triem la mida lliurement en "píxels" d'alçada, sinó que fem servir **multiplicadors** d'una mida base.
La "Mida 1" (la que ve per defecte) és un bloc de **6x8 píxels** (6 d'amplada x 8 d'alçada).

* **`setTextSize(1);`** → 6 x 8 píxels (Lletra normal, caben unes 21 columnes per 8 files a la pantalla).
* **`setTextSize(2);`** → 12 x 16 píxels (El doble de gran).
* **`setTextSize(3);`** → 18 x 24 píxels (El triple de gran).
I així successivament.

### 2. Sintaxi i Funcionament
```cpp
display.setTextSize(2); // A partir d'ara, tot el text serà el doble de gran
display.print("HOLA");
```
**Important:** El canvi de mida es manté fins que tornis a cridar la funció amb un altre valor. Si fas un títol gran i oblides tornar a posar `setTextSize(1)`, la resta de les dades i menús s'imprimiran en lletres gegants i sortiran de la pantalla.

### 3. L'Impacte en les Coordenades (`setCursor`)
Aquest és el concepte de disseny més important per als alumnes: **en canviar la mida del text, canvien les matemàtiques de l'espai**.
Si escrius una línia a la posició `y = 0` amb `setTextSize(1)`, la següent línia pot anar perfectament a `y = 10` (8 px que ocupa la lletra + 2 de marge). 
Però si fas servir `setTextSize(2)`, la teva lletra ara ocupa 16 píxels d'alçada! La següent línia haurà d'anar com a mínim a `y = 18` o els textos se solaparan.

### 💡 Exemples Didàctics
```cpp
// Crear una jerarquia visual (Títol i dada)
display.setTextSize(1);
display.setCursor(0, 0);
display.print("Estat del sistema:"); // Text explicatiu petit

display.setTextSize(2);
display.setCursor(0, 15); // Baixem 15 píxels (els 8 del títol + marge)
display.print("OK");      // Valor destacat en gran
```

### 🏋️ Repte Pràctic en Aula: "El Títol i la Dada"

**Objectiu:** Crear una interfície que mostri la paraula "TEMPERATURA" a la part superior en mida normal (1), i just a sota, perfectament centrat, el valor "25 C" en mida gran (3).

**El parany didàctic:**
Els alumnes solen oblidar com de gran es torna el text en mida 3 (passa a ocupar 18x24 px per lletra). Si posen el cursor del valor a `y = 10` (com feien fins ara), el text gegant "es menjarà" el títol de dalt. A més, per centrar el "25 C" hauran de refer els càlculs d'amplada: cada lletra ja no mesura 6 píxels!

**Guia de resolució:**
1.  **Títol a dalt de tot:** `setTextSize(1)` i `setCursor(30, 0)` (centrat ràpid).
2.  **Nova coordenada Y per a la dada:** El títol de dalt ocupa 8 px d'alçada. Deixem un marge i situem el cursor a **`y = 20`**.
3.  **Càlcul d'amplada per centrar "25 C":** Aquesta dada té 4 caràcters. Com estem en mida 3, cada caràcter mesura 18 px d'ample. -> 4 * 18 px = **72 px d'amplada total**.
4.  **Càlcul X per centrar la dada:** (128 - 72) / 2 = **28**.

**Solució esperada:**
```cpp
display.setTextSize(1);
display.setCursor(30, 0);
display.print("TEMPERATURA");

display.setTextSize(3);
display.setCursor(28, 20); // X centrada matemàticament per a text gran
display.print("25 C");
```
---
## 🖨️ `display.println();` vs `display.print();` — El Salt de Línia

Si pensem en la pantalla OLED com si fos un document de text, usar `display.print()` és com escriure lletres seguides sense parar. En canvi, `display.println()` és l'equivalent a **prémer la tecla "Enter"** al teclat: escriu el text i automàticament prepara el cursor per a la següent línia.

### 1. La diferència fonamental
És crucial que els alumnes entenguin la diferència entre aquestes dues instruccions aparentment idèntiques:
* **`display.print("A");`** → Dibuixa la "A" i deixa el cursor invisible just a la dreta de la lletra. Si fem un altre `print("B")`, sortirà "AB".
* **`display.println("A");`** → Dibuixa la "A" i mou el cursor a la **següent línia**. Un posterior `print("B")` farà que la "B" quedi a sota de la "A".

### 2. Què passa exactament amb les coordenades? (Mecànica interna)
Quan l'ESP32 executa un `println()`, fa dues operacions matemàtiques automàtiques amb el cursor:
1. **L'Eix X torna a 0:** El cursor s'enganxa totalment al marge esquerre de la pantalla.
2. **L'Eix Y augmenta:** El cursor baixa automàticament l'equivalent a l'alçada del text actual (per exemple, baixa 8 píxels si estem a `setTextSize(1)`).

### 💡 Exemples Didàctics
Aquesta instrucció és molt útil per crear llistes ràpides sense haver d'escriure un `setCursor` per a cada línia:

```cpp
// Crear un llistat alineat a l'esquerra ràpidament
display.setCursor(0, 0);

display.println("Llista de sensors:"); // Escriu i baixa de línia
display.println("- Temperatura");      // S'escriu a sota
display.println("- Humitat");          // S'escriu a sota
```

### Repte Pràctic en Aula: "El Menú Desalineat"

**Objectiu:** Crear un menú de tres opcions. Perquè quedi bonic, tot el menú ha de tenir un marge esquerre, és a dir, ha de començar a la posició X = 15.

**El parany didàctic:**
Veient l'exemple anterior de les llistes ràpides, els alumnes pensaran que només han de moure el primer `setCursor` i que `println` farà la resta de la màgia:
```cpp
// L'error típic de l'alumne:
display.setCursor(15, 0);
display.println("1. Jugar");
display.println("2. Opcions");
display.println("3. Sortir");
```
Quan executin això, veuran que "1. Jugar" té el marge correcte (comença a X=15), però "2. Opcions" i "3. Sortir" **s'han enganxat completament al marge esquerre!**

**Guia de resolució:**
Aquest repte serveix perquè l'alumne descobreixi per si mateix la mecànica interna del `println()`. Cal explicar-los que l'"Enter" de la pantalla OLED *sempre* retorna el carro al quilòmetre zero (`X = 0`). 
Si volen una llista indentada, no poden dependre exclusivament del `println()`; hauran de recol·locar manualment la X i la Y de cada línia amb `setCursor()`, o bé fer servir espais en blanc `"   2. Opcions"` (una "trampa" molt habitual i pràctica en programació d'interfícies bàsiques).

**Solució esperada (Mètode del control total):**
```cpp
display.setCursor(15, 0);
display.print("1. Jugar");

display.setCursor(15, 10);
display.print("2. Opcions");

display.setCursor(15, 20);
display.print("3. Sortir");
```
---
## `display.setTextWrap();` — El Salt de Línia Automàtic

Imagina que estàs escrivint un missatge llarg a WhatsApp. Quan arribes al marge dret de la pantalla, el text salta automàticament a la línia de sota perquè puguis continuar llegint. Això és el que coneixem com a "Text Wrap" (Ajustament de text).

A la llibreria Adafruit, aquesta funció **ve activada per defecte**, però tenim el poder de desactivar-la si ens interessa.

### 1. Com funciona?
Aquesta instrucció només accepta dos valors: `true` (cert/activat) o `false` (fals/desactivat).

* **`display.setTextWrap(true);` (Comportament per defecte):** Quan el text topa amb el píxel 127 (el límit dret), el cursor baixa automàticament a la següent línia (`Y` augmenta, `X` torna a 0) i continua dibuixant les lletres.
* **`display.setTextWrap(false);`:** L'ajustament automàtic es desactiva. Si escrius un text més llarg que la pantalla, les lletres sobrants simplement es dibuixaran "fora" de la pantalla, quedant invisibles i tallades de soca-rel.

### 2. El problema estètic (Per què voldríem desactivar-ho?)
La pantalla OLED no entén de gramàtica ni de síl·labes, només de píxels. Si el límit de la pantalla talla la paraula "TEMPERATURA" per la meitat, farà el salt de línia just allà on toqui. A la pantalla es veurà "TEMPERA" a dalt i "TURA" a baix. Això, en una interfície professional, queda molt lleig.

A vegades, preferim fer `setTextWrap(false)` per assegurar-nos que, si una dada es descontrola i és massa llarga, simplement quedi amagada en lloc de destrossar tota l'estructura visual de la pantalla (sobreposant-se a altres textos de sota).

### 💡 Exemples Didàctics
```cpp
// Cas A: Deixem que la pantalla decideixi (pot quedar lleig)
display.setTextWrap(true);
display.setCursor(0, 0);
display.print("Aquest es un text massa llarg per cabre a dalt."); 

// Cas B: Tallem l'excés per protegir el disseny
display.setTextWrap(false);
display.setCursor(0, 0);
display.print("Dada del sensor: 12345678901234567890"); // Els últims números no es veuran
```

### 🏋️ Repte Pràctic en Aula: "La Paraula Trencada"

**Objectiu:** Entendre com gestiona l'OLED l'espai quan les paraules són massa grans i aprendre a solucionar-ho manualment.

**Instruccions prèvies:**
Demana als alumnes que posin el text en **mida 2** (cada lletra ocupa 12 píxels d'ample). 
Si la pantalla té 128 píxels d'amplada, a la pantalla només hi caben **10 lletres** senceres (10 * 12 = 120 px).

**El parany didàctic:**
Fes que imprimeixin la paraula `"TEMPERATURA"` (que té 11 lletres) començant des de `X = 0`.
Com que el `setTextWrap` està en `true` per defecte, l'última lletra (la 'A') no hi cabrà. La pantalla farà un salt automàtic i imprimirà una 'A' solitària i trista a la línia de sota.

**Guia de resolució:**
Planteja'ls el següent: *"Això queda fatal al nostre menú. Com ho solucionem si volem que la paraula 'TEMP' quedi a dalt i 'ERATURA' a baix, de forma controlada?"*.
La solució implica no refiar-se de l'ajustament automàtic i agafar el control manual de les coordenades i els salts.

**Solució esperada (Control manual):**
```cpp
display.setTextSize(2);

// Primer tros controlat manualment
display.setCursor(0, 0);
display.print("TEMP");

// Segon tros on nosaltres decidim que vagi
display.setCursor(0, 20); 
display.print("ERATURA");
```
*Nota per al professor: Aquest repte és ideal per introduir el concepte de disseny d'interfícies (UI), on el programador (i no la màquina) ha de decidir on va cada element perquè sigui llegible per a l'usuari.*
---


---

## `display.display();` — El Gallet d'Impressió

Ho vam mencionar a la secció de l'esborrador màgic, però mereix el seu propi espai. El gran secret de la llibreria Adafruit és que cap instrucció de dibuix (ni textos, ni línies) va directament a la pantalla física. Totes van al buffer invisible.

`display.display()` agafa aquest llenç invisible i l'envia de cop a la pantalla OLED.

### 🏋️ Repte Pràctic en Aula: "El Codi Perfecte i Invisible"
**Objectiu:** Gravar a foc l'ordre lògic d'actualització de la pantalla.
**El parany didàctic:** Fes que els alumnes escriguin un text llarg, el posicionin bé, posin la mida correcta, però demana'ls que esborrin la línia `display.display();` del final del seu `loop()`.
**Guia de resolució:** Passaran minuts revisant les coordenades i els punts i comes. Quan entenguin que l'ESP32 ha dibuixat el text a la seva memòria RAM però ningú li ha donat l'ordre d'"enviar-ho al món real", no ho oblidaran mai més.

---

## `display.drawRect();` i `display.fillRect();` — Creant Interfícies

Escriure números està bé, però la programació visual consisteix en crear gràfics. Dibuixar rectangles permet crear marcs per agrupar informació o botons visuals per als menús.

### 1. Sintaxi de Geometria
Les coordenades d'un rectangle necessiten 4 números clau:
```cpp
// drawRect dibuixa només el contorn (una caixa buida)
display.drawRect(x, y, amplada, alçada, WHITE);

// fillRect dibuixa un rectangle sòlid (ple)
display.fillRect(x, y, amplada, alçada, WHITE);
```
* **`x, y`**: Són la cantonada superior esquerra del rectangle.
* **`amplada, alçada`**: En píxels.

###  Exemples Didàctics
```cpp
// A. Crear un marc al voltant de tota la pantalla
display.drawRect(0, 0, 128, 64, WHITE);

// B. Crear un "botó" seleccionat amb text a sobre
display.fillRect(10, 10, 60, 20, WHITE); 
display.setTextColor(BLACK); // Text negre per llegir-se sobre el fons blanc
display.setCursor(15, 15);
display.print(" BOTON 1 ");
```

### Repte Pràctic en Aula: "La Barra de Progrés" (Nivell Avançat)
**Objectiu:** Convertir un valor numèric d'un sensor (ex: un potenciòmetre) en una barra visual que s'omple.
**Guia de resolució (Pas a pas):**
1. Dibuixem el contenidor de la barra: `display.drawRect(10, 30, 100, 10, WHITE);` (Una caixa de 100 píxels d'amplada).
2. Llegim el potenciòmetre (valors de 0 a 4095 a l'ESP32).
3. Fem servir la funció `map()` de C++ per convertir aquest 0-4095 en píxels de 0 a 100:
   `int amplada_barra = map(valorSensor, 0, 4095, 0, 100);`
4. Dibuixem el farcit interior usant aquesta variable: 
   `display.fillRect(10, 30, amplada_barra, 10, WHITE);`

---

## `display.drawBitmap();` — Imatges i Icones

Quan els alumnes descobreixen aquesta funció, la seva motivació es dispara. Permet mostrar logos, cares de robots o icones de bateries.

### 1. Com funciona?
L'OLED no pot obrir fitxers `.jpg` o `.png`. L'ESP32 només entén dades pures (matrius de bits).
Per usar aquesta funció, l'alumne ha d'anar a una web gratuïta (com *image2cpp*), pujar la seva imatge, i la web generarà un codi estrany (un *Array* de caràcters HEX com `0xFF, 0x00...`) que cal enganxar al principi del codi.

### 2. Sintaxi
```cpp
// Suposem que tenim un array anomenat 'icona_cor' de 16x16 píxels
display.drawBitmap(x, y, icona_cor, amplada_imatge, alçada_imatge, WHITE);
```

### 🏋️ Repte Pràctic en Aula: "El Cor Bategant"
**Objectiu:** Alternar entre dues icones per crear una animació.
**Guia de resolució:** Proporciona als alumnes dos codis array: un d'un cor gran (`cor_gran`) i un d'un cor petit (`cor_petit`). A dins del `loop()`:
1. `clearDisplay()`
2. `drawBitmap(..., cor_gran, ...)`
3. `display()`
4. `delay(500)`
5. `clearDisplay()`
6. `drawBitmap(..., cor_petit, ...)`
7. `display()`
8. `delay(500)`

---

## `display.invertDisplay();` — L'Alarma Visual Ràpida

Una manera espectacular i molt senzilla de cridar l'atenció de l'usuari si un sensor detecta un problema (excés de temperatura, proximitat d'obstacle, etc.).

### 1. Funcionament
Aquesta ordre canvia la configuració física de la pantalla. Tot allò que era negre passa a ser blanc, i el que era blanc passa a ser negre (invertint completament el buffer).

* **`display.invertDisplay(true);`** -> Activa el mode invertit.
* **`display.invertDisplay(false);`** -> Torna la pantalla a la normalitat.

**Anotació vital:** A diferència de les funcions de dibuix, aquesta instrucció té efecte **immediat** sobre la pantalla física, no cal fer un `display.display()` just després.

### 🏋️ Repte Pràctic en Aula: "Mode Pànic"
**Objectiu:** Si el botó d'emergència està premut, la pantalla ha de parpellejar com una alarma sense esborrar la interfície.
**Solució esperada:**
```cpp
if (digitalRead(BOTO_PIN) == HIGH) {
  display.invertDisplay(true);
  delay(100);
  display.invertDisplay(false);
  delay(100);
} else {
  display.invertDisplay(false); // Assegurem que en mode normal es veu bé
}
```
---
## 🌍 Lletres amb accent i caràcters especials (ç, ñ, º)

Segurament ja has intentat escriure la paraula "Menú" i has vist que a la pantalla apareix una cosa semblant a `MenÃº`. Què ha passat? 

Les pantalles OLED parlen un idioma antic anomenat **ASCII**, dissenyat en anglès, on no existeixen els accents ni les ce trencades. L'ESP32 no sap com traduir l'accent del teu teclat a la pantalla de forma directa.

### 1. La solució: `display.write();` i el codi secret
Dins de la memòria de la pantalla hi ha una taula oculta de caràcters (anomenada CP437). Cada lletra especial té un **número assignat**. En lloc de demanar-li que imprimeixi una "ó", li demanarem que imprimeixi el "símbol número 162".

Per imprimir números o textos normals, usem `print()`.
Per imprimir un símbol exacte d'aquesta taula secreta, usem **`write()`**.

### 2. Taula ràpida de caràcters (Català / Castellà)
Apunta't aquests números, els necessitaràs sempre:

* **à** = 133
* **è** = 138
* **é** = 130
* **í** = 161
* **ò** = 149
* **ó** = 162
* **ú** = 163
* **ç** = 135
* **ñ** = 164
* **º** (graus) = 167

### 3. Com s'escriu al codi?
Per escriure una paraula amb accent, hem de "trencar-la" en tres trossos:
1. Imprimir la primera part de la paraula.
2. Imprimir el símbol especial amb `write()`.
3. Imprimir la resta de la paraula.

### 💡 Exemples Didàctics
```cpp
// Volem escriure "Menú"
display.print("Men");   // 1. Text normal
display.write(163);     // 2. Codi de la 'ú'
// Com que és el final de la paraula, no cal el pas 3

// Volem escriure "Opció"
display.print("Opci");
display.write(162);     // Codi de la 'ó'

// Volem escriure "25 ºC" (Temperatura)
display.print("25 ");
display.write(167);     // Símbol de graus (º)
display.print("C");
```

### 🏋️ Repte Pràctic en Aula: "El Menú Correcte"

**Objectiu:** Crear un text centrat que digui "Configuració", escrit perfectament amb l'accent i la ce trencada, sense errors visuals.

**El parany didàctic:**
Molts alumnes intentaran posar `display.println("Configura")` seguit del `write()`. Com ja vam veure abans, el `println` fa un "Enter", de manera que l'accent sortirà a la línia de sota! 
També hauran de buscar els codis de la 'ç' i la 'ó' i assegurar-se de posar-los en l'ordre correcte.

**Guia de resolució:**
Recorda'ls que han de fer servir només `print()` per assegurar-se que el cursor no baixa de línia fins que hagin acabat de construir la paraula completa.

**Solució esperada:**
```cpp
display.setCursor(20, 20); // Centrem el text més o menys
display.print("Configura"); // Tros 1
display.write(135);         // 'ç' (codi 135)
display.print("i");         // Tros 2
display.write(162);         // 'ó' (codi 162)
```
---
## 🪄 El Truc Màgic: Automatitzar els accents (Nivell Pro)

Escriure codis numèrics lletra per lletra cada vegada que volem posar un accent pot ser molt pesat. Per sort, els programadors som mandrosos per naturalesa i ens agrada automatitzar les coses. 

Què et semblaria si poguessis escriure els accents amb normalitat i l'ESP32 els traduís automàticament just abans d'imprimir-los?

Això ho podem aconseguir creant la nostra pròpia instrucció. Li direm **`printCat`** (de *print Català*).

### 1. La "Capsa Negra" (La Funció)
Al final de tot del teu codi (fora del `loop` i del `setup`), copia i enganxa aquest bloc. Aquesta funció agafarà qualsevol text que li passis, buscarà les lletres rebels i les canviarà pel seu codi numèric abans d'enviar-les a la pantalla.

```cpp
// Funció personalitzada per escriure en català/castellà sense patir
void printCat(String text) {
  text.replace("à", String((char)133));
  text.replace("è", String((char)138));
  text.replace("é", String((char)130));
  text.replace("í", String((char)161));
  text.replace("ò", String((char)149));
  text.replace("ó", String((char)162));
  text.replace("ú", String((char)163));
  text.replace("ç", String((char)135));
  text.replace("ñ", String((char)164));
  text.replace("º", String((char)167));
  
  display.print(text); // Un cop corregit, l'imprimim de cop
}
```

### 2. Com s'utilitza?
Ara, a dins del teu `loop()`, pots oblidar-te per sempre del `display.print()` clàssic quan escriguis text normal, i usar la teva nova super-instrucció:

```cpp
display.setCursor(10, 10);
// En lloc de display.print, usem la nostra funció:
printCat("Menú de Configuració"); 

display.setCursor(10, 30);
printCat("Temperatura: 25 ºC");
```

### 🏋️ Repte Pràctic en Aula: "Ampliant el Diccionari"

**Objectiu:** Entendre com funciona la funció i millorar-la per afegir nous caràcters.

**Instruccions:** 1. Demana als alumnes que intentin imprimir el text: `"L'aigua està a 100 °C"`.
2. Hauran de buscar a Google la "Taula ASCII CP437" per descobrir que l'apòstrof invertit no sempre es veu bé o que potser volen afegir caràcters com `¡` o `¿`.
3. Fes que afegeixin noves línies `text.replace(...)` a la funció `printCat` perquè la seva eina sigui cada vegada més potent.

---
*(Nota per al professor: Si per algun projecte de final de curs un alumne ha de fer interfícies molt complexes o amb altres idiomes, la millor opció és canviar la llibreria `Adafruit_GFX` per una altra anomenada **`U8g2`**. Aquesta llibreria és més complexa d'aprendre al principi, però suporta la codificació moderna UTF-8 de manera nativa).*
---
## 🤸‍♂️ `display.setRotation();` — Girant la pantalla

A l'hora de muntar el nostre projecte dins d'una capsa de cartró o una carcassa impresa en 3D, moltes vegades ens adonem que els cables de la pantalla xoquen amb algun altre component i ens veiem obligats a muntar la pantalla de cap per avall. 

Cap problema! No cal que els alumnes llegeixin del revés. L'ESP32 pot girar tota la interfície matemàticament abans d'enviar-la.

### 1. Com funciona?
Aquesta instrucció accepta un únic número del **0 al 3**, que representa girs de 90 graus en el sentit de les agulles del rellotge.

* **`display.setRotation(0);`** → Posició original (Horitzontal).
* **`display.setRotation(1);`** → Gir de 90º (Vertical, tipus telèfon mòbil).
* **`display.setRotation(2);`** → **Gir de 180º (De cap per avall)**. Aquesta és la que necessites!
* **`display.setRotation(3);`** → Gir de 270º (Vertical cap a l'altre costat).

### 2. On es posa?
Com que normalment volem que la pantalla estigui girada des del primer segon i per sempre, aquesta instrucció no es posa al `loop()`, sinó al **`setup()`**, just després del `display.begin()`.

```cpp
void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Error OLED");
    for(;;);
  }
  
  // Girem la pantalla 180 graus perquè hem muntat els pins cap a baix
  display.setRotation(2); 
  
  display.clearDisplay();
  display.display();
}
```

### 3. La regla d'or de les coordenades
És vital explicar això als alumnes: **quan girem la pantalla, l'Eix X i l'Eix Y giren amb ella**.
L'origen `(0, 0)` sempre serà la cantonada superior esquerra del text tal com el llegeixes, independentment de cap a on mirin els pins físics de la placa. No cal recalcular res del disseny si fem servir el gir de 180º (`setRotation(2)`).

### 🏋️ Repte Pràctic en Aula: "El Mode Smartphone"

**Objectiu:** Entendre com canvien les dimensions físiques quan rotem la pantalla 90 graus (Mode Vertical).

**El parany didàctic:**
Demana'ls que girin la pantalla 90 graus amb `display.setRotation(1);` i que intentin dibuixar una línia horitzontal que creui tota la pantalla, de punta a punta, usant `display.drawLine(0, 10, 127, 10, WHITE);`.
El que veuran és que la línia es talla a la meitat i no arriba al final!

**Guia de resolució:**
Aquest repte visual els farà entendre que les matemàtiques de l'espai han canviat. Al girar-la 90 graus, l'amplada màxima ja no és 128, ara és **64**. I l'alçada ja no és 64, ara és **128**! 

Perquè la línia creui la nova pantalla vertical d'esquerra a dreta, hauran de modificar el codi a:
```cpp
display.setRotation(1); // Mode vertical (64x128)
display.drawLine(0, 10, 63, 10, WHITE); // La X només arriba fins a 63!
```
---
### EXEMPLE marquesina
## 🎞️ Rètols Lluminosos (Scroll) — Animacions sense esforç

A vegades volem mostrar un text molt llarg o, simplement, volem donar un efecte espectacular tipus "notícies d'última hora" (el clàssic efecte *Marquee* o rètol lluminós). 

En lloc de fer bucles complicats per anar canviant les coordenades `X` a poc a poc, la pantalla SSD1306 té una funció de hardware integrada que mou la imatge completament sola.

### 1. Com funciona?
Tenim instruccions per moure la pantalla cap a la dreta, cap a l'esquerra i, fins i tot, en diagonal.
L'únic que cal saber és que la pantalla es divideix en **8 "pàgines" horitzontals** (de la 0 a la 7). Cada pàgina té 8 píxels d'alçada.

Per moure tota la pantalla (de dalt a baix), li direm que mogui des de la pàgina 0 (`0x00`) fins a la 7 (`0x07`).

```cpp
// Desplaçament cap a la dreta
display.startscrollright(0x00, 0x07);

// Desplaçament cap a l'esquerra
display.startscrollleft(0x00, 0x07);

// Desplaçament en diagonal
display.startscrolldiagright(0x00, 0x07);
```

### 2. Aturar l'animació
Com que l'OLED fa això de forma autònoma, seguirà movent el text fins a l'infinit. Per aturar-ho, necessitem una instrucció de fre:
```cpp
display.stopscroll();
```

### 3. La Regla d'Or del Scroll
Aquesta és la instrucció més estranya de tota la llibreria: **no es pot dibuixar res de nou a la pantalla mentre el scroll està actiu**. Si vols actualitzar una dada del sensor, l'ordre correcte ha de ser:
1. `display.stopscroll();` (Aturem l'animació)
2. Esborrem i redibuixem els nous valors
3. `display.display();` (Enviem a la pantalla)
4. `display.startscrollleft(0x00, 0x07);` (Tornem a engegar el motor)

### 🏋️ Repte Pràctic en Aula: "El Rètol Tremolós"

**Objectiu:** Crear un text que digui "ATENCIO: PERILL!" i fer que llisqui contínuament cap a l'esquerra.

**El parany didàctic:**
Els alumnes, acostumats a que tot allò que es mou vagi dins del `loop()`, escriuran el codi de la següent manera:
```cpp
// ERROR TÍPIC DE L'ALUMNE
void loop() {
  display.clearDisplay();
  display.setCursor(0, 30);
  display.print("ATENCIO: PERILL!");
  display.display();
  
  display.startscrollleft(0x00, 0x07); // Ordenen fer scroll constantment!
}
```
**Què passarà?** En lloc de lliscar suaument, la pantalla es quedarà quieta, tremolant molt de pressa o parpellejant. Això passa perquè a cada mil·lisegon li estan dient a la pantalla "comença a moure't", reiniciant l'animació contínuament abans que hagi pogut avançar ni un sol píxel.

**Guia de resolució:**
Explica'ls que `startscroll` és com prémer el botó de "Play" d'una cadena de música. Només cal prémer-lo **una vegada**.

**Solució esperada:**
El disseny i l'ordre d'animació han d'anar al `setup()` (si és un text estàtic), o protegit amb condicionals perquè només s'executi una vegada.

```cpp
void setup() {
  // ... (iniciem display) ...
  display.clearDisplay();
  
  display.setTextSize(2);
  display.setCursor(0, 20);
  display.print("PERILL!");
  display.display();
  
  // Premem el botó "Play" només UN COP al setup
  display.startscrollleft(0x00, 0x07); 
}

void loop() {
  // El loop es queda buit. El xip de la pantalla 
  // fa l'animació per nosaltres i l'ESP32 pot descansar.
}
```
## 🎞️ Animacions i Scroll (Desplaçament Automàtic)

Una de les funcions més potents de la pantalla OLED SSD1306 és la seva capacitat de fer **scroll** (desplaçament) per hardware. Això significa que és la mateixa pantalla la que mou els píxels, deixant el processador de la nostra placa lliure per a altres tasques.

### 1. Conceptes clau: Les Pàgines
La pantalla no es mou per píxels individuals, sinó per **pàgines**. La pantalla de 64 píxels d'alçada es divideix en **8 pàgines** (de la 0 a la 7). Cada pàgina té 8 píxels d'alçada.

* **Pàgina 0:** Píxels del 0 al 7 (part superior).
* **Pàgina 7:** Píxels del 56 al 63 (part inferior).

Si volem moure tota la pantalla, haurem de dir-li que vagi de la `0x00` a la `0x07`.

### 2. Comandes de Scroll Horitzontal
Podem moure el text cap a la dreta o cap a l'esquerra amb una sola línia de codi:

```cpp
// Desplaçament cap a la dreta
// Paràmetres: (pàgina_inici, pàgina_final)
display.startscrollright(0x00, 0x07);

// Desplaçament cap a l'esquerra
display.startscrollleft(0x00, 0x07);
```

### 3. Desplaçament Diagonal
També és possible fer que el text pugi o baixi en diagonal. Això és molt útil per a efectes de crèdits o estètica "retro".

```cpp
// Desplaçament diagonal cap a la dreta i amunt
display.startscrolldiagright(0x00, 0x07);

// Desplaçament diagonal cap a l'esquerra i amunt
display.startscrolldiagleft(0x00, 0x07);
```

### 4. Aturar l'animació
És obligatori aturar el moviment si volem escriure coses noves a la pantalla o si volem que el text es quedi quiet:

```cpp
display.stopscroll();
```

### ⚠️ Regles d'or per a l'ús del Scroll
* **El botó "Play":** Les instruccions `startscroll` són com un interruptor. Només cal cridar-les una vegada (normalment al `setup()` o dins d'un `if`). Si les poses al `loop()` sense control, l'animació es reiniciarà constantment i veuràs un parpelleig estrany.
* **Buffer congelat:** Mentre el scroll està actiu, no pots dibuixar coses noves i esperar que es moguin immediatament. L'ordre correcte per actualitzar dades és:
    1.  `display.stopscroll();`
    2.  Modificar el text/dibuix.
    3.  `display.display();`
    4.  Tornar a activar el scroll.

### 🏋️ Exercici proposat: "L'alerta dinàmica"
Intenta programar un codi on el text estigui quiet durant 2 segons, després faci scroll cap a la dreta durant 3 segons, s'aturi, i finalment faci scroll cap a l'esquerra.

> **Pista:** Fes servir la funció `delay(ms);` entre les ordres de scroll.

---

### 💡 Consell per al teu repositori
Si vols que els alumnes visualitzin millor què és una "pàgina" de l'OLED, pots afegir aquesta petita taula de referència ràpida al costat de l'explicació:

| Pàgina (Hex) | Píxels verticals | Zona de la pantalla |
| :--- | :--- | :--- |
| `0x00` | 0 - 7 | Superior (Top) |
| `0x03` | 24 - 31 | Centre |
| `0x07` | 56 - 63 | Inferior (Bottom) |
