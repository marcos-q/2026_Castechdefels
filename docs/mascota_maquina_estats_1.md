
# La Personalitat de la Mascota

Fins ara hem après a dibuixar diferents expressions a la pantalla, llegir els botons i mesurar la llum de l'aula. Ara farem el pas definitiu: **unirem totes aquestes peces per crear la personalitat autònoma de la nostra mascota virtual**. Per fer-ho, utilitzarem una *Màquina d'Estats*.

Aquesta activitat consisteix a programar el comportament de la mascota perquè reaccioni al temps, a les nostres accions i a l'entorn seguint unes regles molt concretes.

---

## Els 3 estats d'ànim de la mascota

La teva mascota ha de poder passar per tres estats diferents. Cada estat té associat un dibuix a la pantalla i un color al LED RGB de la PCB:

1. **Mode NORMAL (`ESTAT_NORMAL`):** Mostra la cara feliç/normal a la pantalla i el LED RGB s'encén de color **Blau** (benestar).
2. **Mode ENFADAT (`ESTAT_ENFADAT`):** Mostra la cara d'enuig a la pantalla i el LED RGB s'encén de color **Vermell** (estrès).
3. **Mode ADORMIT (`ESTAT_ADORMIT`):** Mostra la cara adormida ("Zzz..") a la pantalla i el LED RGB es queda **totalment apagat** per no molestar.

---

### Les regles del joc (Transicions)

La teva feina dins del `loop()` serà comprovar constantment en quin estat es troba la mascota i aplicar les següents regles de comportament:

* **A l'arrencar:** La mascota sempre comença en estat **NORMAL** i es posa en marxa un cronòmetre.
* ⏳ **L'avorriment:** Si la mascota està en estat **NORMAL** i passen **10 segons** sense que passi res, s'avorreix de no fer res i passa automàticament a l'estat **ENFADAT**.
* **Calmar la mascota:** Si la mascota està **ENFADADA**, l'única manera de calmar-la és **prémer el Botó Dret (B)**. Si ho fem, tornarà a l'estat **NORMAL** i el cronòmetre de l'avorriment es reiniciarà des de zero.
* **La son:** Tant si la mascota està **NORMAL** com si està **ENFADADA**, si el sensor de llum (LDR) detecta que es fa fosc (un valor **inferior a 300** per exemple, però ajusteu el llindar segons us convingui, segons la iluminació de la vostra sala), la mascota ha de passar immediatament a l'estat **ADORMIT**.
* **El Despertador:** Si la mascota està **ADORMIDA**, només es despertarà i tornarà a l'estat **NORMAL** (reiniciant també el cronòmetre de l'avorriment) quan detecti que hi ha prou llum a l'aula (un valor **superior a 400**).

---

### Pistes de programació

* Crea tres constants al principi del codi per definir els estats: `0` per a normal, `1` per a enfadat i `2` per a adormit.
* Fes servir una variable `int estatActual` per saber en quin mode estàs a cada moment.
* Implementa una estructura `switch(estatActual)` dins del `loop()` per separar clarament què fa la mascota en cada situació.
* Recorda utilitzar la funció `millis()` i una variable `unsigned long cronometreAvorriment` per controlar el pas dels 10 segons sense fer servir `delay()`, ja que si aturessis el programa amb un `delay` massiu, la mascota no podria llegir correctament l'LDR ni els botons en temps real!

    ??? example "EXEMPLE: Fes clic aquí per desplegar i llegir el codi sencer"

        Aquest és el codi. Pots copiar-lo in engangar-lo al teu editor fent clic a la icona de copiar, adalt a la dreta d'aquesta caixa.

        ```Arduino title="mascota_maquina_estats_basica.ino"
        --8<-- "Exemples/mascota_maquina_estats_basica/mascota_maquina_estats_basica.ino"
        ```


---

## Repte: Canviant el caràcter de la mascota

Ara que la nostra mascota ja té un "cervell" propi i canvia d'estat d'ànim, és hora de donar-li un toc més realista. Penseu-hi: a qui li agrada que el despertin de cop quan està dormint plàcidament? 

A la versió anterior, quan la mascota es despertava, tornava directament a l'estat NORMAL (feliç i contenta). Fer que la mascota es llevi de mal humor (`ESTAT_ENFADAT`) si la desperteu sobtadament, en lloc de llevar-se feliç, li dona un toc de personalitat molt més humà i divertit. Això ens ens obliga a repensar les rutes de la seva màquina d'estats.

### Les noves regles de joc

Modifica la màquina d'estats del teu codi (dins la funció `loop()`) per afegir aquests nous trets al comportament de la mascota:

1. **Dificultats per a dormir:** Si lamascota està nerviosa o enfadada ('**`ESTAT_ENFADAT`**), li costa adormir-se i encara que es faci fosc no s'adorm. 
2. **Despertar contenta o de mal humor:** Quan la mascota estigui a l'`ESTAT_ADORMIT`, si es desperta perquè s'ha fet de dia i hi ha més claror, es desperta bé, contenta i passa a l'estat `ESTAT_NORMAL`. En canvi si la despertem sobtadament, apretant els dos botons alhora, la mascota es desperta enfadada, passant a l'**`ESTAT_ENFADAT`**.

> **💡 Pista:** Busca dins del `case ESTAT_ENFADAT` i també del `case ESTAT_ADORMIT`per canviar les condicions dels propers destins.


??? example "SOLUCIÖ: Fes clic aquí per desplegar i llegir el codi sencer"
    Aquest és el codi. Pots copiar-lo in engangar-lo al teu editor fent clic a la icona de copiar, adalt a la dreta d'aquesta caixa.

    ```Arduino title="mascota_maquina_estats_2.ino"
    --8<-- "Exemples/mascota_maquina_estats_2/mascota_maquina_estats_2.ino"
    ```

    

