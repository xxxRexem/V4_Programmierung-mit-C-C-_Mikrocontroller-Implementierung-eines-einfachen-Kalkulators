// Arduino C Code für den Mikrocontroller-Kalkulator

/*
  Die Funktion setup() wird einmalig ausgeführt, wenn der Arduino
  gestartet oder resettet wird. Hier wird die serielle Schnittstelle initialisiert.
*/
void setup() {
  // Startet die serielle Kommunikation mit einer Baudrate von 9600 Bits pro Sekunde.
  // Diese Rate muss mit der Konfiguration der PC-Anwendung übereinstimmen.
  Serial.begin(9600);
}

/*
  Die Funktion loop() wird nach setup() in einer Endlosschleife ausgeführt.
  Sie prüft auf neue Daten, verarbeitet sie und sendet eine Antwort.
*/
void loop() {
  if (Serial.available() > 0) {
    String receivedString = Serial.readStringUntil('\n');

    // --- NEUE PARSER-LOGIK ---
    float operand1, operand2;
    char operation;
    bool parse_success = false;

    // Finde die Position des ersten Leerzeichens
    int first_space = receivedString.indexOf(' ');
    // Finde die Position des zweiten Leerzeichens
    int second_space = receivedString.lastIndexOf(' ');

    // Prüfe, ob beide Leerzeichen gefunden wurden und nicht an derselben Stelle sind
    if (first_space != -1 && second_space != -1 && first_space != second_space) {
        
        // Extrahiere die Teile des Strings
        String op1_str = receivedString.substring(0, first_space);
        String op_str = receivedString.substring(first_space + 1, second_space);
        String op2_str = receivedString.substring(second_space + 1);

        // Prüfe, ob der Operator nur ein einzelnes Zeichen ist
        if (op_str.length() == 1) {
            // Konvertiere die String-Teile in ihre Datentypen
            operand1 = op1_str.toFloat();
            operation = op_str.charAt(0);
            operand2 = op2_str.toFloat();
            parse_success = true;
        }
    }

    if (parse_success) {
      // Wenn das Parsen erfolgreich war, geht es weiter wie bisher...
      float result = 0.0;
      bool error = false;
      String errorMessage = "";

      switch (operation) {
        case '+': result = operand1 + operand2; break;
        case '-': result = operand1 - operand2; break;
        case '*': result = operand1 * operand2; break;
        case '/':
          if (operand2 == 0) {
            error = true;
            errorMessage = "Fehler: Division durch Null!";
          } else {
            result = operand1 / operand2;
          }
          break;
        default:
          error = true;
          errorMessage = "Fehler: Unbekannter Operator!";
          break;
      }

      if (error) {
        Serial.println(errorMessage);
      } else {
        Serial.println(result);
      }

    } else {
      // Wenn das manuelle Parsen fehlschlägt
      Serial.println("Fehler: Ungueltiges Format empfangen!");
    }
  }
}
