# Afegim sons: Bips & Boops! (La mascota es fa sentir)

Fins ara, la nostra mascota virtual s'ha comunicat amb nosaltres a través de colors (amb el LED RGB) i d'expressions facials (amb la pantalla OLED). Però estava completament muda. Perquè tingui una personalitat rodona, necessitem que pugui **emetre sons**: que es queixi en veu alta quan s'avorreixi o s'enfadi, que faci un xiulet alegre quan la calmem i que ronqui quan estigui adormida.

Per aconseguir-ho, farem servir un **brunzidor** (també anomenat *buzzer*).

---

## Què és un brunzidor i com funciona?

Un brunzidor piezoelèctric és un component electrònic molt simple que converteix l'energia elèctrica en so. A dins té una petita làmina metàl·lica que, quan rep un pols elèctric, es deforma i vibra. **Aquesta vibració empeny l'aire i genera el so.**

Hi ha dos tipus de brunzidors: els actius (que sempre fan el mateix xiulet fix) i els **passius**, que és el que tenim a la nostra placa. El brunzidor passiu és com un instrument musical: si li enviem electricitat a batzegades molt ràpides, podem controlar com de ràpid vibra la làmina.

* Si la fem vibrar **molt ràpid** (alta freqüència), el so serà **agut** (un *bip*).
* Si la fem vibrar **més a poc a poc** (baixa freqüència), el so serà **greu** (un *boop*).

La freqüència d'un so es mesura en **Hertzs (Hz)**. L'oïda humana pot escoltar sons d'entre 20 Hz i 20.000 Hz.

---

## Una nova instrucció: La funció `tone()`

Per fer sonar el brunzidor no farem servir `digitalWrite()`, ja que seria una bogeria haver d'activar i desactivar el pin milers de vegades per segon "a mà". L'entorn d'Arduino té una funció específica per a això:

```cpp
tone(pin, freqüència, durada);

```

* **pin:** El pin de la PCB on està connectat el brunzidor.
* **freqüència:** La freqüència del so en Hz (per exemple, 440 Hz és la nota La).
* **durada:** El temps que ha de durar el so en mil·lisegons (opcional).

Quan volem que el brunzidor calli immediatament, utilitzarem l'ordre: `noTone(pin);`

---

##  El primer "Bip & Boop"

Copia aquest codi per comprovar que el brunzidor de la teva PCB funciona correctament. El programa farà una salutació robòtica clàssica ("Bip" agut i "Boop" greu) només arrencar.

??? example "EXEMPLE: Fes clic aquí per desplegar i llegir el codi sencer"
    Aquest és el codi. Pots copiar-lo in engangar-lo al teu editor fent clic a la icona de copiar, adalt a la dreta d'aquesta caixa.

    ```Arduino title="bbib_boop.ino"
    --8<-- "Exemples/bib_boop/bib_boop.ino"
    ```

---

## Més sons

Abans d'ajuntar els sons amb les cares de la mascota, farem una petita prova de laboratori musical. Modifica el codi per aconseguir tres sons totalment diferents:

1. **El xiulet d'alerta:** Fes que el brunzidor repeteixi 3 bips molt ràpids i aguts (de 3000 Hz) consecutius dins del `setup()`.
2. **L'efecte caiguda (Laser de videojoc):** Què passa si fessis un bucle `for` que baixés la freqüència des de 2000 Hz fins a 500 Hz molt ràpid? Prova-ho!
3. **El ronc:** Troba una freqüència molt i molt baixa (per sota de 150 Hz) combinada amb un `delay` llarg per simular el so d'un motor o d'un ronc profund.

??? example "EXEMPLE: Fes clic aquí per desplegar i llegir el codi sencer"
    Aquest és el codi. Pots copiar-lo in engangar-lo al teu editor fent clic a la icona de copiar, adalt a la dreta d'aquesta caixa.

    ```Arduino title="xiulet_laser_ronc.ino"
    --8<-- "Exemples/xiulet_laser_ronc/xiulet_laser_ronc.ino"
    ```