# Introducció a les pantalles OLED

Fins ara la nostra mascota s'ha comunicat  mitjançant llums (LED) i el port sèrie.Avui li afegirem ulls i veu propis. Per fer-ho, utilitzarem una pantalla OLED de 0.96 polzades i un brunzidor.

## Activitats
- ### "Hola món!" a la pantalla OLED




Arrenquem amb uns conceptes bàsics:

**El sistema de coordenades de la pantalla**

La pantalla OLED és una matriu de 128 píxels d'amplada per 64 píxels d'alçada. Per pintar qualsevol cosa a la pantalla, hem d'indicar-li una coordenada $(x, y)$:

L'origen $(0,0)$ es troba a la cantonada **superior esquerra**.  
L'eix $x$ creix cap a la dreta (de $0$ a $127$).  
L'eix $y$ creix cap abaix (de $0$ a $63$).  

La cantonada inferior dreta és la coordenada $(127, 63)$.

```
(0,0) ┌───────────────────────────────┐ (127,0)
      │                               │
      │                               │
      │         PANTALLA OLED         │
      │                               │
      │                               │
(0,63)└───────────────────────────────┘ (127,63)
```


**Llibreries necessàries**

Adafruit SSD1306 (el controlador del xip de la pantalla).  
Adafruit GFX Library (la llibreria gràfica que dibuixa text, cercles i línies).  


**"Hola Món!"**

Aquí tens el codi base per encendre la pantalla, escriure-hi el text de benvinguda i dibuixar un marc rectangular al voltant.  
També apagarem el led per assegurar-nos que no queda cap llum "residual" d'exemples anteriors.

??? example "EXEMPLE: Fes clic aquí per veure el codi sencer"
    ```arduino title="hola_mon_oled"
    --8<-- "Exemples/hola_mon_oled/hola_mon_oled.ino"
    ```





- ### Mini-repte de consolidació

Abans de continuar amb les lliçons de la mascota, intenta modificar el codi per aconseguir el següent:

Canvia la mida del text de "HOLA MON!", canvia els textos de la pantalla.

Dibuixa un petit quadrat ple a la cantonada inferior dreta. (Pista: utilitza la funció display.fillRect en lloc de display.drawRect i recorda les coordenades límits).
