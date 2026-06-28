# LED, sortida analògica (PWM)

Fins ara hem vist com encendre (1) i apagar (0) un LED. Però, què passa si volem que el LED brilli a la meitat de la seva capacitat? Els microcontroladors són dispositius digitals i només permeten sortides ON/OFF,  0 volts o el màxim voltatge (3,3V/5V). No poden activar una sortida digital a "mig gas", a "la meitat" del voltatge màxim.

Per resoldre aquesta qûestió, utilitzem el **PWM** (*Pulse Width Modulation* o Modulació per Amplada de Pols). La instrucció per fer-ho és `analogWrite(pin, valor)` on el valor pot anar de `0` (0% encès) a `255` (100% encès).

## Exemples 



- ### Exemple bàsic: 4 nivells de brillantor

    Exemple bàsic per encendre un led amb diferents nivells de lluentor progressivament.
  
    ??? example "EXEMPLE: Fes clic aquí per desplegar i llegir el codi sencer"

        ```Arduino title="led_4_nivells.ino"
        --8<-- "Exemples/led_4_nivells/led_4_nivells.ino"
        ```
 
-  ### Efecte respiració
    En aquest exemple, encendrem el led de la mascota, augmentant i disminuint la seva lluentor repetidament, per simular l'efecte de la reswpiració.

    
    ??? example "EXEMPLE: Fes clic aquí per desplegar i llegir el codi sencer"


        ```Arduino title="respiracio_delay.ino"
        --8<-- "Exemples/respiracio_delay/respiracio_delay.ino"
        ```

> **Observació important:**  En aquest exemple continuem fent servir la instrucció `delay()` per marcar la temporització. Són notables els seus inconvenients. Ens queda pendent mostrar una tècnica per resoldre'ls.


## Reptes

Ara que la nostra mascota ja sap respirar amb tranquil·litat, és el moment de donar-li una personalitat visual complexa a través del color!
Els següents reptes ens permetran explorar algunes possibilitats del led RGB.

- ### Paleta cromàtica

Imagina la teva mascota virtual com el llenç d'un pintor: combinant els tres colors primaris de la llum (Vermell, Verd i Blau, o RGB) en diferents quantitats, podem crear qualsevol color de l'univers!

El teu objectiu és programar un algorisme capaç de recórrer de forma automàtica totes les combinacions de colors possibles (RGB) del led. Per aconseguir-ho, hauràs de crear tres bucles `for` imbricats (un dins de l'altre), on cada bucle s'encarregui de controlar el nivell d'intensitat (de 0 a 255) d'un dels tres canals RGB. 

??? tip "PISTA: El parany del temps (Llegeix abans de programar!)"
        
    Si fessis augmentar els colors d'1 en 1 (i++), la teva mascota hauria de processar $256 \times 256 \times 256 = 16,7$ milions de colors. Si posessis un sol mil·lisegon de repòs per poder veure el canvi, la placa trigaria gairebé 5 hores a fer una sola volta al codi i mostrar la paleta completa!
    **Consell:** Perquè el canvi sigui visible i fluid, farem que els bucles avancin fent salts més grans (per exemple, de 10 en 10) fent servir l'operador += 10.?

??? example "SOLUCIÓ: Fes clic aquí per desplegar i llegir el codi sencer"

    ```Arduino title="paleta_cromatica.ino"
    --8<-- "Exemples/paleta_cromatica./paleta_cromatica.ino"
    ```  

- ### L'espectre emocional
   

En el repte anterior de la *Paleta cromàtica*, hem après a recórrer de manera matemàtica i seqüencial milers de colors fent salts d'intensitat. Però en el món de la robòtica i el disseny d'interaccions, els canvis bruscos poden semblar artificials o "robots de pel·lícula antiga".
   
Volem crear **l'espectre emocional** de la mascota, creant una transició suau i contínua de color que reflecteixi els seus canvis d'humor. 
  
El repte consisteix a escriure un programa que vagi canviant el color del led de forma suau, passant pels tons principals (de vermell a verd, de verd a blau i de blau a vermell),creant una transició contínua i infinita de color, tal com si fos una roda emocional orgànica.

??? tip "PISTA 1: La lògica de la transició de colors (Cross-fading)"
    Perquè el canvi de color no tingui cap salt, no podem apagar un LED de cop i encendre'n un altre. Han de treballar en equip! Mentre un color s'apaga progressivament, el següent s'ha d'anar encenent al mateix ritme.

    **Fase 1:** El Vermell disminueix ($255 \to 0$) mentre el Verd augmenta ($0 \to 255$).

    **Fase 2:** El Verd disminueix ($255 \to 0$) mentre el Blau augmenta ($0 \to 255$).

    **Fase 3:** El Blau disminueix ($255 \to 0$) mentre el Vermell torna a augmentar ($0 \to 255$).

    D'aquesta manera, el cicle es tanca en un cercle perfecte i infinit!. 
    
    **El teu primer objectiu:** Aconsegueix passar de manera completament suau del vermell pur al verd pur. Quan dominis aquest camí, la resta serà bufar i fer ampolles.

??? tip "PISTA 2: Una pista per al codi"
    Pots resoldre cada fase amb un único bucle for que vagi de 0 a 255. Dins del bucle, utilitza una variable comptadora (per exemple, i).
    Si fas que un LED rebi el valor de i (anirà pujant) i l'altre rebi el valor de 255 - i (anirà baixant), faràs la barreja perfecta en temps real!  

??? example "SOLUCIÓ: Fes clic aquí per desplegar i llegir el codi sencer"
    Aquí tens el codi complet per programar aquest comportament emocional i fluid en el LED RGB:

    ```arduino title="espectre_emocional.ino"
    // --- PINS D'ENTRADA I SORTIDA ---
    const int pinLedRoig = 21;
    const int pinLedVerd = 20;
    const int pinLedBlau = 10;

    // --- CONFIGURACIÓ DE TEMPS (MIL·LISEGONS) ---
    const int pausaTransicio = 15; // Controla la velocitat del canvi de color (més baix = més ràpid)

    void setup() {
    Serial.begin(115200);
    
    pinMode(pinLedRoig, OUTPUT);
    pinMode(pinLedVerd, OUTPUT);
    pinMode(pinLedBlau, OUTPUT);
    
    // Comencem amb el Vermell encès al 100% com a pt de inici
    analogWrite(pinLedRoig, 255);
    analogWrite(pinLedVerd, 0);
    analogWrite(pinLedBlau, 0);
    
    Serial.println("Mascota encesa. Estat: Espectre emocional actiu.");
    }

    void loop() {
    // --- 1. TRANSICIÓ: DE VERMELL A VERD ---
    Serial.println("[Humor] Passant de Vermell a Verd...");
    for (int i = 0; i <= 255; i++) {
        analogWrite(pinLedRoig, 255 - i);
        analogWrite(pinLedVerd, i);
        delay(pausaTransicio);
    }

    // --- 2. TRANSICIÓ: DE VERD A BLAU ---
    Serial.println("[Humor] Passant de Verd a Blau...");
    for (int i = 0; i <= 255; i++) {
        analogWrite(pinLedVerd, 255 - i);
        analogWrite(pinLedBlau, i);
        delay(pausaTransicio);
    }

    // --- 3. TRANSICIÓ: DE BLAU A VERMELL ---
    Serial.println("[Humor] Passant de Blau a Vermell...");
    for (int i = 0; i <= 255; i++) {
        analogWrite(pinLedBlau, 255 - i);
        analogWrite(pinLedRoig, i);
        delay(pausaTransicio);
    }
    }
    ```    

- ### Ampliació
   
Sabies que barrejant les intensitats de només tres llums (vermell, verd i blau) pots arribar a crear més de 16 milions de tons diferents? Aquesta és la mateixa tècnica que fan servir les pantalles dels mòbils o de TV per mostrar imatges reals.


