# Gràfics a la pantalla oled

Fins ara, la nostra pantalla OLED només ha mostrat text. Però si volem que el nostre robot tingui personalitat i es converteixi en una mascota, necessitem donar-li una cara!

A les següents activitats aprendrem a utilitzar les instruccions de dibuix geomètric. Pas a pas, construirem la cara de la nostra mascota.

## Dibuixant la nostra Mascota Píxel a Píxel

**El Mapa de la Pantalla: Les Coordenades (X, Y)**
Recordeu que la nostra pantalla OLED té una resolució de 128x64 píxels. Pensa en ella com una graella amb un sistema de coordenades:

L'eix X va d'esquerra a dreta (de 0 a 127).  
L'eix Y va de dalt a baix (de 0 a 63).  
El punt (0, 0) és la cantonada superior esquerra.  
El punt (127, 63) és la cantonada inferior dreta.

**IMPORTANT !!** La pantalla té una memòria "invisible". Totes les instruccions que veurem a continuació dibuixen en aquesta memòria oculta. Perquè el dibuix aparegui físicament a la pantalla, SEMPRE hem d'executar l'ordre `pantalla.display();`.

- ### Pas 1: El Píxel (El nas)
L'element més bàsic de qualsevol imatge és un sol punt de llum, un píxel. La instrucció per encendre'l és:
`pantalla.drawPixel(X, Y, COLOR);`

Dibuixem ara un petit nas just al mig de la pantalla (X=64, Y=32):

```Arduino
pantalla.drawPixel(64, 32, SSD1306_WHITE);
``` 

- ### Pas 2: Les Línies (La boca)
Per dibuixar una línia recta, només necessitem dir-li a la pantalla on comença i on acaba.
`pantalla.drawLine(Inici_X, Inici_Y, Final_X, Final_Y, COLOR);`

Dibuixarem una línia horitzontal a sota del nas perquè faci de boca:

```Arduino
pantalla.drawLine(44, 45, 84, 45, SSD1306_WHITE);
```
- ### Pas 3: Buit vs. Ple (Els ulls)
A partir d'aquí, les figures (cercles i rectangles) poden tenir dues variants:

`draw...`: Dibuixa només el contorn (la figura per dins estarà buida/negra).

`fill...`: Dibuixa la figura totalment farcida (plena de color blanc).

Dibuixem dos ulls utilitzant cercles. La instrucció ens demana el centre del cercle i el radi:
`pantalla.drawCircle(Centre_X, Centre_Y, Radi, COLOR);' 

Farem un ull ple de color blanc i un altre de buit (com si estigués picant l'ullet o tingués un ull robòtic diferent):

```Arduino
// Ull esquerre: ple de color blanc
pantalla.fillCircle(40, 20, 10, SSD1306_WHITE); 

// Ull dret: només el contorn
pantalla.drawCircle(88, 20, 10, SSD1306_WHITE); 
```

- ### Pas 4: Rectangles i Cantonades Suaus (El cap)
Per emmarcar tota la cara, dibuixarem un rectangle. La instrucció normal és drawRect, però n'hi ha una de més bonica anomenada drawRoundRect que arrodoneix les cantonades perquè la mascota sembli més amigable.

Li hem de donar la posició de la cantonada superior esquerra del rectangle, l'amplada, l'alçada i quant de rodones volem les cantonades:
`display.drawRoundRect(X, Y, Amplada, Alçada, Radi_Cantons, COLOR);`

```Arduino
pantalla.drawRoundRect(10, 5, 108, 54, 8, SSD1306_WHITE);
```

### El Codi Complet: Pintant la primera cara de la mascota

Ara que ja coneixem totes les instruccions, cal ajuntar-les en un sol programa per veure el resultat final!

Obre el teu IDE d'Arduino, copia aquest codi i puja'l a la teva placa:

??? example "EXEMPLE: Fes clic aquí per desplegar i llegir el codi sencer"
    Aquest és el codi. Pots copiar-lo in engangar-lo al teu editor fent clic a la icona de copiar, adalt a la dreta d'aquesta caixa.

    ```Arduino title="cara_simple.ino"
    --8<-- "Exemples/cara_simple/cara_simple.ino"
    ```


### Repte 
Com podries afegir una pupil·la a l'ull dret (el que està buit)? Intenta utilitzar la funció fillCircle per dibuixar un cercle molt petit, per exemple de radi 2 o 3, just a dins de l'ull dret!

