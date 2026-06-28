# LED, sortida analògica (PWM)

Fins ara hem vist com encendre (1) i apagar (0) un LED. Però, què passa si volem que el LED brilli a la meitat de la seva capacitat? Els microcontroladors són dispositius digitals i només permeten sortides ON/OFF,  0 volts o el màxim voltatge (3,3V/5V). No poden activar una sortida digital a "la meitat" del voltatge.

Per resoldre aquesta qûestió, utilitzem el **PWM** (*Pulse Width Modulation* o Modulació per Amplada de Pols). La instrucció per fer-ho és `analogWrite(pin, valor)` on el valor pot anar de `0` (0% encès) a `255` (100% encès).

## Exemples 



- ### Exemple bàsic: 4 nivells de brillantor

    Exemple bàsic per encendre un led amb diferents nivells de lluentor progressivament.
  
    ??? example "EXEMPLE: Fes clic aquí per desplegar i llegir el codi sencer"

        ```Arduino title="led_4_nivells.ino"
        --8<-- "Exemples/led_4_nivells/led_4_nivells.ino"
        ```
 
-  ### Efecte respiració
    En aquest exemple, encendrem el led de la mascota, augmentant i disminuint la seva lluentor repetidament, per simular l'efecte de la reswpiració.

    
    ??? example "EXEMPLE: Fes clic aquí per desplegar i llegir el codi sencer"


        ```Arduino title="respiracio_delay.ino"
        --8<-- "Exemples/respiracio_delay/respiracio_delay.ino"
        ```

> **Observació important:**  En aquest exemple continuem fent servir la instrucció `delay()` per marcar la temporització. Són notables els seus inconvenients. Ens queda pendent mostrar una tècnica per resoldre'ls.




