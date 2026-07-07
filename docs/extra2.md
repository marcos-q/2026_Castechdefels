# Bola extra: Repte avançat

- ###  L'Entrenador de reflexos
En aquest repte, convertirem la mascota  en un entrenador de reflexos. El joc posarà a prova la teva velocitat de reacció contra la intel·ligència de la placa.

Les **regles del joc**:
La mascota es queda en "espera" (llum blava tènue) durant un temps aleatori. Mai sabràs quan començarà la prova! De sobte, el led s'encendrà de color VERMELL intens. Aquesta és la teva senyal!Has de prémer el botó esquerre tan ràpid com puguis. El Monitor Sèrie et dirà quants mil·lisegons has trigat a reaccionar. Si ets més ràpid que un ninja (menys de 500 ms), la mascota celebrarà la teva victòria amb un flaix VERD. Si ets massa lent, es tornarà TARONJA.

**Conceptes nous per a aquest repte:**
Per fer aquest joc, necessitem dues eines que encara no coneixíem:
L'Atzar (random): Perquè el joc sigui divertit, el temps d'espera ha de ser impredictible. Farem servir `random(2000, 6000)` perquè la placa esperi entre 2 i 6 segons de manera aleatòria.El Cronòmetre (`millis()`): Fins ara hem fet servir el `delay()` per aturar el temps. Però el delay() "congela" la placa. Per mesurar el temps exacte de reacció, farem servir la funció millis(), que ens diu quants mil·lisegons han passat des que es va engegar la placa.$$ \text{Temps de reacció} = \text{millis de la polsació} - \text{millis de l'encesa del LED} $$

??? tip "Funcionament del cronòmetre: millis()"
    Imagina que millis() és un cronòmetre que s'engega quan la placa rep alimentació i que no s'atura mai.
    Per saber quan triga un procés, llegeixes el cronòmetre quan s'encén la llum vermella i guardes el valor en una variable (per exemple, tempsInici).* Quan prems el botó, tornes a llegir el cronòmetre.
    La diferència entre els dos valors és el teu temps exacte de reacció!
    **Compte:** Com que aquests números poden ser molt grans, la variable per guardar el temps no pot ser un `int` normal; ha de ser de tipus `unsigned long`.

??? example "SOLUCIO: Fes clic aquí per veure la solució al repte"
    Aquí tens el codi complet per al joc de reflexos. Fixa't com fem servir un bucle `while` buit per obligar la placa a quedar-se "esperant" que premis el botó.

    ```arduino title="entrenament_reflexos.ino"
    --8<-- "Exemples/entrenament_reflexos/entrenament_reflexos.ino"
    ```
- ### El semàfor de la salut

Feu servir els led RGB amb els colors verd i blau. Si el cor va molt ràpid (taquicàrdia), enceneu el led Blau (avís). Si va a un ritme normal, enceneu el led Verd. Com a base podeu fer servir l'exemple "Freqüència cardíaca variable" i afegir el comportament del led.

#### Creativitat al poder
- Inventa una activitat que es pugui fer amb el prototipus de la mascota utilitzant únicament el led i els dos polsadors.
- Proposa i programa alguna aplicació que utilitzi la pantalla oled per proporcionar alguna informació. Pots agafar alguns dels programes del Bloc 1 i fer que la informació que enviaves pel port sèrie ara aparegui a la pantalla oled.
- Inventa una activitat que es pugui fer amb el prototipus de la mascota utilitzant únicament el led, els dos polsadors i la pantalla.