# Google Sheets: El diari de la nostra mascota

[Tutorial](Tutorial Google Sheets.pdf)

Script UPC

??? example "Fes clic aquí per desplegar i llegir el codi sencer"
    ```
    function doGet(e) { 
    Logger.log(JSON.stringify(e));
    var resultat  = 'Ok';
    if (e.parameter == 'undefined') {
        resultat  = 'No hi ha paràmetres a la trama';
    }
    else {
        
        var arxiu_id = 'XXXXXXXXXXX'; // substituir les XXXXXX per l'identificador del vostre full de càlcul	
        var nom_full = "YYYYYY"; // substituir les YYYYYY pel nom del full
        
        var arxiu_obert = SpreadsheetApp.openById(arxiu_id);
        var full_dades = arxiu_obert.getSheetByName(nom_full);

        var tasca_val = '';
        var n_registre = full_dades.getLastRow() - 2;
        var nova_fila = full_dades.getLastRow() + 1;
        
        var dades_entrada = [];
        var ultim_dia_hora;
        var ultim_n_registre;
        var ultima_temperatura;
        var ultima_humitat_relativa;
        

        var data_avui = Utilities.formatDate(new Date(), "Europe/Madrid", 'dd/MM/yyyy');
        var hora_ara = Utilities.formatDate(new Date(), "Europe/Madrid", 'HH:mm');
        dades_entrada[0] = data_avui + ' ' + hora_ara;
        ultim_dia_hora = data_avui + ' ' + hora_ara;
        
        dades_entrada[1] = n_registre;   
        ultim_n_registre = n_registre;  

        for (var param in e.parameter) {
        Logger.log('In for loop, param=' + param);
        var value = stripQuotes(e.parameter[param]);
        Logger.log(param + ':' + e.parameter[param]);
        switch (param) {
            case 'tasca':
            tasca_val = value;
            break;

            case 'temp':
            dades_entrada[2] = value;  // Obtenir el valor de la temperatura.
            ultima_temperatura = value;  
            resultat  += ', Temperatura guardada i actualitzada';
            break;

            case 'hr':
            dades_entrada[3] = value;  // Obtenir el valor de la humitat relativa
            ultima_humitat_relativa = value; 
            resultat  += ', Humitat relativa guardada i actualitzada';
            break;

            default:
            resultat  += ", paràmetres no acceptats";
        }
        }
        
        // Escriptura de dades rebudes al Google Sheets.
        if (tasca_val == 'escriptura') {
        Logger.log(JSON.stringify(dades_entrada));
        var newRangeDataLog = full_dades.getRange(nova_fila, 1, 1, dades_entrada.length);
        newRangeDataLog.setValues([dades_entrada]);
        
        // Actualització de les últimes dades.
        var RangeDataLatest = full_dades.getRange('A2:D2');
        RangeDataLatest.setValues([[ultim_dia_hora, ultim_n_registre, ultima_temperatura, ultima_humitat_relativa]]);

        return ContentService.createTextOutput(resultat);
        }
        
        // Enviament dels últims valors de Google Sheets a ESP32.
        if (tasca_val == 'lectura') {
        var ultimes_dades = full_dades.getRange('A2:D2').getDisplayValues();
        return ContentService.createTextOutput(ultimes_dades);
        }
    }
    }
    function stripQuotes( value ) {
    return value.replace(/^["']|['"]$/g, "");
    }
    ```
Exemple per carrecar a la ESP32C3
??? example "EXEMPLE: Fes clic aquí per desplegar i llegir el codi sencer"

    Aquest és el codi. Pots copiar-lo in engangar-lo al teu editor fent clic a la icona de copiar, adalt a la dreta d'aquesta caixa.

    ```Arduino title="ESP32_registre_GSheets.ino"
    --8<-- "Exemples/ESP32_registre_GSheets/ESP32_registre_GSheets.ino"
    ```