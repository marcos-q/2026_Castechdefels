# Celebrant l'aniversari!

La nostra mascota s'està fent gran i avui és el seu aniversari. El celebrarem carregant-li el següent codi:

??? example "EXEMPLE: Fes clic aquí per desplegar i llegir el codi sencer"
    Aquest és el codi. Pots copiar-lo in engangar-lo al teu editor fent clic a la icona de copiar, adalt a la dreta d'aquesta caixa.
    ```Arduino title="happy_birthday.ino"
    --8<-- "Exemples/happy_birthday/happy_birthday.ino"
    ```

Després de fer cantar el *Happy Birthday*, arriba el moment d'obrir els regals que li hem fet. Són dos regals tecnològics que li ampliaran les seves habilitats:

1. **Un rellotge intern (RTC - Real Time Clock):** Fins ara, l'ESP32 sabia comptar mil·lisegons amb `millis()`, però no tenia ni idea de si eren les 3 de la tarda o les 11 de la nit, ni si estàvem a dimarts o a diumenge. Amb l'RTC, la mascota sabrà l'hora exacta del món real i no la perdrà mai, ni tan sols si desconnectem la placa de l'ordinador
2. **Un termòmetre i higròmetre digitals (AHT20):** Un sensor d'alta precisió que li permetrà "sentir" la temperatura i la humitat ambient de l'aula. Ara sabrà si s'està congelant de fred o si s'està morint de calor.

---

## La clau tecnològica: El Bus I2C

Si mires la teva placa, veuràs que la pantalla OLED, el rellotge RTC i el sensor AHT20 estan connectats als **mateixos dos pins** de l'ESP32 (`SDA` i `SCL`). Com és possible que les dades no col·lisionin?

Demana una explicació de com funciona el bus I2C.

---

## Activitats per a la festa d'aniversari

- ### Repte: El pastís

  * Modifica la mascota perquè només començar mostri un pastís d'aniversari a la pantalla OLED mentre el brunzidor toca la melodia del *Happy Birthday*.
  * Pots afegir que, un cop acaba la cançó, la mascota passi al seu estat `NORMAL` i continui comportant-se com li hem programat a la màquina d'estats.

- ### El primer regal: el rellotge (RTC)

  Exemple d'ús: 

- ### El segon regal: el termòmetre i higròmetre AHT20

  Exemple d'ús:

??? example "EXEMPLE: Fes clic aquí per desplegar i llegir el codi sencer"
    Aquest és el codi. Pots copiar-lo in engangar-lo al teu editor fent clic a la icona de copiar, adalt a la dreta d'aquesta caixa.
    ```Arduino title="ESP32_C3_oled_AHT20y.ino"
    --8<-- "Exemples/ESP32_C3_oled_AHT20/ESP32_C3_oled_AHT20.ino"
    ```

- ### Repte avançat: La fase de maduresa

La nostra mascota va madurant i el nostre coneixement també. Ara que tenim totes les peces, modificarem la nostra **Màquina d'Estats** per combinar-les totes i afegir nous comportaments.

  * **El toc de queda:** Si l'RTC diu que ja són més tard de les **22:00h**, la mascota passarà automàticament a l'estat `ADORMIT` (ja no dependrà només de la LDR!). Pensa si vols modificar les condicions per a despertar-la
  * **Cop de calor:** Si el sensor AHT20 detecta que la temperatura de l'aula supera els **30 °C**, la mascota canviarà la seva cara per una expressió de calvari/ofegament i el LED RGB es posarà de color taronja per demanar que engeguem l'aire condicionat o obrim les finestres.