# Represa del Bloc 4

## Revisió del codi de Telegram

??? example "EXEMPLE: Fes clic aquí per desplegar i llegir el codi sencer"
    Aquest és el codi. Pots copiar-lo in engangar-lo al teu editor fent clic a la icona de copiar, adalt a la dreta d'aquesta caixa.
    ```Arduino title="ESP_Telegram_base.ino"
    --8<-- "Exemples/ESP_Telegram_base/ESP_Telegram_base.ino"
    ```

## Incorporació del codi de Telegram a la mascota

Recuperem la nostra mascota que s'enfada i s'adorm i fem que poguem interactuar-hi per telegram. Barregem els dos codis.

??? example "EXEMPLE: Fes clic aquí per desplegar i llegir el codi sencer"
    Aquest és el codi. Pots copiar-lo in engangar-lo al teu editor fent clic a la icona de copiar, adalt a la dreta d'aquesta caixa.
    ```Arduino title="ESP_Telegram_mascota_sense_pass.ino"
    --8<-- "Exemples/ESP_Telegram_mascota_sense_pass/ESP_Telegram_mascota_sense_pass.ino"
    ```

## El termòmetre i el rellotge
* Si no ho vau fer ahir proveu i reviseu el codi del termòmetre i higròmetre AHT20.
* El rellotge de temps real RTC DS3231.
    Aquí trobareu un exemple de com programar un rellotge que podem posar en hora amb els botons de la mascota o amb el monitor sèrie.
    Observeu que està programat com una màquina d'estats.
    També utilitza molots dels recursos que hem après durant el curs.
  
??? example "EXEMPLE: Fes clic aquí per desplegar i llegir el codi sencer"
    Aquest és el codi. Pots copiar-lo in engangar-lo al teu editor fent clic a la icona de copiar, adalt a la dreta d'aquesta caixa.
    ```Arduino title="RTC_2_botons_usb.ino"
    --8<-- "Exemples/RTC_2_botons_usb/RTC_2_botons_usb.ino"
    ```
