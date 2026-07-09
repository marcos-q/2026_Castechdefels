# Escalfant motors: Més enllà de cercles i rectangles

Per començar farem dues petites proves de "gama alta". Fins ara hem dibuixat punts, línies, rectangles i cercles buits per fer les expressions de la mascota. Però recordeu que "qui pot projectar un punt, pot projectar la catedral de Burgos."

Aquí teniu dos petits experiments visuals. Descarregueu-los, proveu-los i mireu d'entendre com funcionen.


-  ###  Barra de progrés

Als videojocs i a les aplicacions reals, quan un sistema s'està iniciant o carregant dades, es mostra una barra que s'omple a poc a poc. 

Carregue aquest codi i proveu a tocar els botons.

??? example "EXEMPLE: Fes clic aquí per desplegar i llegir el codi sencer"
    Aquest és el codi. Pots copiar-lo in engangar-lo al teu editor fent clic a la icona de copiar, adalt a la dreta d'aquesta caixa.

    ```Arduino title="barra_energia.ino"
    --8<-- "Exemples/barra_energia/barra_energia.ino"
    ```

- ### Com dibuixar un arc

La llibreria d'Adafruit no té una funció directa de "dibuixar arc", de manera que els enginyers utilitzem les matemàtiques (sinus i cosinus) per dibuixar molts punts en cercle de manera consecutiva.

??? example "EXEMPLE: Fes clic aquí per desplegar i llegir el codi sencer"
    Aquest és el codi. Pots copiar-lo in engangar-lo al teu editor fent clic a la icona de copiar, adalt a la dreta d'aquesta caixa.

    ```Arduino title="arc_circumferencia.ino"
    --8<-- "Exemples/arc_circumferencia/arc_circumferencia.ino"
    ```