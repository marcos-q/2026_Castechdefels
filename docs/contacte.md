# Introducció i presa de contacte

Aquí hi trobareu el codi dels exemples que hem fer servir curant les primeres explicacions i alguna informació addicional.
- ## Instal·lació

[Guia d'instal·lació](Guia installacio.pdf)

- ## Primers programes

**Blink**

Aquest exemple el construirem des de zero per "refrescar" alguns conceptes.

??? example "EXEMPLE: Fes clic aquí per veure el codi sencer"
    ```arduino title="Blink.ino"
    --8<-- "Exemples\Blink\Blink.ino"
    ```

    Proveu a canviar la freqüència de la intermitència.

**Blink_Serial**

En aquest exemple afegirem comunicació amb el port sèrie.

??? example "EXEMPLE: Fes clic aquí per veure el codi sencer"
    ```arduino title="Blink_Serial.ino"
    --8<-- "Exemples\Blink_Altern\Blink_Serial.ino"
    ```

- ## Primeres soldadures
Abans de continuar, soldarem els primers "accessoris" de la nostra placa. Seguiu les indicacions del professor per muntar les primeres plaques.

- ## Primers programes amb els nostres accessoris

**Blink Alternatiu**

Escriviu un programa que encengui alternativament el led vermell i el led verd que acabeu de muntar. Per fer-ho modifiqueu el programa 'Blink.ino' que heu utilitzat abans.

??? example "SOLUCIÓ: Fes clic aquí per desplegar i llegir el codi sencer"

    Aquest és el codi. Pots copiar-lo in engangar-lo al teu editor fent clic a la icona de copiar (a la dreta de la zona del codi).

    ```Arduino title="Blink_Altern.ino"
    --8<-- "Exemples\Blink_Altern\Blink_Altern.ino"
    ```

**Lectura de polsadors**

??? example "EXEMPLE: Fes clic aquí per veure el codi sencer"
    ```arduino title="dig_Read.ino"
    --8<-- "Exemples\dig_Read\dig_Read.ino"
    ```

**Responent a estímuls externs**

Ara escriurem el nostre primer programa que respon a estímuls externs. Concretament, escriurem un programa que encengui un led mentre es prem el polsador, i que l'apagui en cas contrari.

??? example "EXEMPLE: Fes clic aquí per veure el codi sencer"
    ```arduino title="dig_Read_led.ino"
    --8<-- "Exemples\dig_Read_led\dig_Read_led.ino"
    ```