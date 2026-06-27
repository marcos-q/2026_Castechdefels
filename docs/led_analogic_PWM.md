\# 2. LED i Sortida Analògica



Fins ara hem vist com encendre (1) i apagar (0) un LED. Però, què passa si volem que el LED brilli a la meitat de la seva capacitat? Els microcontroladors són dispositius digitals i només saben treure 0 volts o el màxim voltatge (3.3V/5V), no poden enviar "la meitat" del voltatge.



Per solucionar això utilitzem el \*\*PWM (Pulse Width Modulation o Modulació per Amplada de Pols)\*\*.



\## Què és el PWM?

El PWM consisteix a encendre i apagar el LED tan increïblement ràpid (milers de vegades per segon) que el nostre ull no pot veure el parpelleig, sinó que ho percep com una reducció de la brillantor global. 



Utilitzarem la instrucció `analogWrite(pin, valor)` on el valor pot anar de `0` (0% encès) a `255` (100% encès).



\* `analogWrite(pin, 0)`: Apagat completament.

\* `analogWrite(pin, 127)`: Brillantor mitjana (50% del temps encès).

\* `analogWrite(pin, 255)`: Brillantor màxima.



\[📥 Descarrega l'exemple de prova: led\_4\_nivells.ino](../Exemples/led\_4\_nivells/led\_4\_nivells.ino)



\## L'efecte de respiració (Fading)

Veure el LED canviant de nivell de forma brusca està bé per entendre el PWM, però la natura és fluida. Per aconseguir que la mascota "respiri" lentament encenent i apagant el LED de forma suau, utilitzarem bucles `for`. 



Aquests bucles incrementaran o reduiran el valor de la brillantor d'un en un, afegint un petit `delay()` entre cada pas per controlar la velocitat de la respiració.



\[📥 Descarrega la solució: respiracio\_delay.ino](../Exemples/respiracio\_delay/respiracio\_delay.ino)

