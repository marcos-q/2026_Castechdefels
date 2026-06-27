# Guia d'exemples
## LED, sortida digital
- Led pump-pump, com si fos un cor bategant.
  [Solució](..\Exemples\ESP_C3_LED_cor\ESP_C3_LED_cor.ino)
- Led pump-pump, amb freqüècia cardíaca variable.
  [Solució](..\Exemples\ESP_C3_LED_cor_variable\ESP_C3_LED_cor_variable.ino)
  Si analitzem aquest codi, podem observar els inconvenients de l'ús de la instrucció `delay()`.

  **Reptes proposats:**
  * Podeu provar a canviar el progrma perquè, en llod d'indicar "Pausa entre batecs", digui "Polsacions per minut" (bpm).
  * Feu que, a mesura que passi el temps, la vostra mascota es vagi posant nerviosa.
  Només es calma quan li feu atenció prement el botó dret.
  [Solució](..\Exemples\ESP_C3_LED_cor_nervios\ESP_C3_LED_cor_nervios.ino)
  ***Observació***
  Novament podem comprovar que el `delay()` presenta inconvenients.
  A mesura que la mascota es posa nerviosa i el temps de pausa disminueix, la finestra d'oportunitat perquè el microcontrolador llegeixi el botó es redueix. Quan la mascota està al seu punt màxim de taquicardia, sembla que el botó no funcioni a no ser que el mantinguem premut de fins que reacciona. Podriem dir que la mascota està tan alterada, concentrada en el seu propi pànic, que no nota que la toquem si ho fem breument. Hem de deixar el botó premut perquè "se n'adoni".
  Haurem de buscar una alternativa al *delay* per a no bloquejar el microcontrolador. 



## LED, sortida analògica
- Exemple bàsic per encendre un led amb diferents nivells de lluentor. Ús de PWM (Pulse Width Modulation)
  [Solució](..\Exemples\led_4_nivells\led_4_nivells.ino) 
-  Led amb encesa i apagada progressiva, com si respirés.
  [Solució](..\Exemples\respiracio_delay\respiracio_delay.ino) 
  