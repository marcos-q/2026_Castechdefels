# Represa del *Bloc 2* i escalfament

Ahir vam viure una sessió intensa de soldadura i muntatge per posar a punt la nostra mascota virtual.

Les vam veure de tots colors. Van sortir imprevistos típics d'aquests projectes (bé... i alguns de no tant típics amb els cables!). Però ens en vam sortir i tenim totes les mascotes acabades, amb l'autodiagnosi superada i amb bon estat de salut.


**Mentre arriba tothom i ens sincronitzem:**

1. Obre l'IDE i torna a provar els exemples del Bloc 2 sobre el **"LED, sortida digital"**.

2. **Repte ràpid:**
Heu d'aconseguir que, si mantenim premut el **Botó esquerre**, el LED RGB de la mascota es quedi fix en color **Blau** (indicant benestar); mentre mantinguem premut **Botó dret**, el led ha de quedar fix en color **Verd** (indicant placidesa) Si no apretem cap botó el led està apagat.
    **Consell**: Combineu el que sabeu de `digitalRead()` amb els exercicis de "LED, sortida digital" d'abans.

    ??? example "SOLUCIÓ: Fes clic aquí per desplegar i llegir el codi sencer"

        Aquest és el codi. Pots copiar-lo in engangar-lo al teu editor fent clic a la icona de copiar (a la dreta de la zona del codi).

        ```Arduino title="benestar_placidesa.ino"
        --8<-- "Exemples/benestar_placidesa/benestar_placidesa.ino"
        ```

3. **Repte ràpid 2:**
Modifiqueu el programa anterior perquè, a més a més,  si premem i mantenim els dos botons alhora,  el led faci pampallugues ràpides de color **Vermell** (com una alarma, indicant estrés).

    ??? example "SOLUCIÓ: Fes clic aquí per desplegar i llegir el codi sencer"

        Aquest és el codi. Pots copiar-lo in engangar-lo al teu editor fent clic a la icona de copiar (a la dreta de la zona del codi).

        ```Arduino title="benestar_placidesa_alarma.ino"
        --8<-- "Exemples/benestar_placidesa_alarma/benestar_placidesa_alarma.ino"
        ```





Intentarem revisar tots junts **"LED, sortida analògica (PWM)"** per entendre com funcionen els colors de la mascota.
