# La mascota t'escriu al mòbil: Connexió amb Telegram

Fins ara, per interactuar amb la nostra mascota havíem d'estar físicament al seu costat: prémer els seus botons, mirar la seva pantalla o tapar el sensor de llum. Però... i si poguéssim saber com està quan no som a casa o mentre anem cap a a l'institut? 

En aquesta última lliçó farem el salt definitiu cap al món de l'**IoT (Internet de les Coses)**. Aprofitarem la connexió Wi-Fi del nostre ESP32 per connectar la mascota a una de les aplicacions de missatgeria més conegudes: **Telegram**.

---

## Els bots de Telegram

A partir d'ara, la mascota tindrà el seu propi xat privat. Mitjançant la programació, configurarem un *Bot* de Telegram que farà de pont entre el mòbil i la placa. Això ens permetrà dues funcions espectaculars:

1. **Rebre alertes (La mascota t'escriu):** Si s'avorreix, si detecta que fa massa calor a l'aula o si s'ha despertat de mal humor, t'enviarà un missatge automàtic al mòbil dient: *"Ep!, estic avorrida, vine a jugar"* o *"Quina calor, obre la finestra!"*.
2. **Enviar ordres (Tu controles la mascota de lluny):** Podràs obrir el xat de Telegram des de qualsevol lloc del món i escriure-li comandes textuals com `/status` (perquè et respongui amb la temperatura de l'aula), `/calma` (per passar-la a estat normal a distància) o `/desperta`.

Prepareu els mòbils, perquè estem a punt de connectar la nostra mascota a la xarxa global!

[Tutorial per crear un Bot](Tutorial Telegram.pdf)

## Codi base de connexió