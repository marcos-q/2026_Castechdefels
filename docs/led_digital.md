# LED, sortida digital
En aquesta secció aprendrem a controlar un LED de manera digital (encès o apagat) per donar vida a la nostra mascota robòtica creant un efecte de batec de cor.

## Exemples 
Per seguir aquests exemples donem per fet que coneixem les instruccions associades a `digitalWrite()` i a `delay()`.


- ### El batec bàsic (Pum-pum)

    El primer objectiu és simular el batec d'un cor utilitzant la instrucció fonamental d'espera: el `delay()`. Aquesta funció atura l'execució del microcontrolador durant els mil·lisegons que li indiquem.
    
    [Codi de l'exemple](..\Exemples\ESP_C3_LED_cor\ESP_C3_LED_cor.ino)





## Freqüència cardíaca variable

Per fer la mascota més interactiva, hem afegit dos botons. Un botó alenteix el pols i l'altre l'accelera. Això ens permet veure com el codi pot reaccionar a factors externs.



[📥 Descarrega la solució: ESP\_C3\_LED\_cor\_variable.ino](../Exemples/ESP\_C3\_LED\_cor\_variable/ESP\_C3\_LED\_cor\_variable.ino)



### L'inconvenient del `delay()`

Si proveu aquest codi detingudament, us adonareu d'un problema: a vegades premeu el botó i la mascota no fa cas. Per què passa això? Mentre la placa està executant un `delay()`, està completament "sorda" a la resta del món. Si premeu el botó just quan està esperant, no ho detectarà.



## Repte: La mascota nerviosa

Anem a portar aquest inconvenient a l'extrem per entendre bé per què necessitarem tècniques de programació més avançades. 



**El repte:** Feu que, a mesura que passi el temps, la vostra mascota es vagi posant nerviosa tota sola (reduint el temps entre batecs). Només es calmarà i tornarà a la normalitat quan li feu atenció prement el botó dret.



[📥 Descarrega la solució: ESP\_C3\_LED\_cor\_nervios.ino](../Exemples/ESP_C3\_LED\_cor\_nervios/ESP\_C3\_LED\_cor\_nervios.ino)



> **Observació important**  A mesura que la mascota es posa nerviosa i el temps de pausa disminueix, la finestra d'oportunitat perquè el microcontrolador llegeixi el botó es redueix dràsticament. Quan la mascota està al seu punt màxim de taquicàrdia, sembla que el botó no funcioni a no ser que el mantinguem premut fins que reacciona.> 

> Podríem dir narrativament que la mascota està tan alterada i concentrada en el seu propi pànic, que no nota que la toquem si ho fem breument. Hem de deixar el botó premut perquè "se n'adoni". Aquest és el límit del `delay()`: haurem de buscar alternatives per no bloquejar el microcontrolador.

