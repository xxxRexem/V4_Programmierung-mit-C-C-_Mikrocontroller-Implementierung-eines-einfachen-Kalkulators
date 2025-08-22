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
  // Prüft, ob neue Daten am seriellen Port angekommen sind.
  if (Serial.available() > 0) {
    // Liest den ankommenden String ein, bis das Newline-Zeichen ('\n') empfangen wird.
    String receivedString = Serial.readStringUntil('\n');

    // Deklariert die Zielvariablen für das Parsen des Strings.
    float operand1, operand2;
    char operation;
    // Eine Hilfsvariable um das erfolgreiche Parsen zu speichern.
    bool parse_success = false;

    // Findet die Position des ersten Leerzeichens.
    int first_space = receivedString.indexOf(' ');
    // Findet die Position des letzten Leerzeichens.
    int second_space = receivedString.lastIndexOf(' ');

    // Prüft, ob zwei unterschiedliche Leerzeichen gefunden wurden.
    if (first_space != -1 && second_space != -1 && first_space != second_space) {
        
        // Extrahiert die drei Teile (Operand1, Operator, Operand2) als separate Strings.
        String op1_str = receivedString.substring(0, first_space);
        String op_str = receivedString.substring(first_space + 1, second_space);
        String op2_str = receivedString.substring(second_space + 1);

        // Validiert, dass der Operator nur aus einem einzigen Zeichen besteht.
        if (op_str.length() == 1) {
            // Konvertiert die extrahierten String-Teile in die passenden Datentypen.
            operand1 = op1_str.toFloat();
            operation = op_str.charAt(0);
            operand2 = op2_str.toFloat();
            // Signalisiert der nachfolgenden Logik, dass die Eingabedaten gültig und bereit zur Berechnung sind.
            parse_success = true;
        }
    }

    // Führt die Berechnung nur aus, wenn das Parsen zuvor erfolgreich war.
    if (parse_success) {
      // Deklariert Variablen für das Ergebnis und die Fehlerbehandlung.
      float result = 0.0;
      bool error = false;
      String errorMessage = "";

      // Verzweigt zur passenden arithmetischen Operation basierend auf dem Operator-Zeichen.
      switch (operation) {
        case '+':
          result = operand1 + operand2;
          break;
        case '-':
          result = operand1 - operand2;
          break;
        case '*':
          result = operand1 * operand2;
          break;
        case '/':
          // Fängt die Division durch Null als arithmetischen Sonderfall ab.
          if (operand2 == 0) {
            error = true;
            errorMessage = "Fehler: Division durch Null!";
          } else {
            result = operand1 / operand2;
          }
          break;
        default:
          // Fängt alle nicht definierten Operatoren ab (z.B. '%', '^', etc.).
          error = true;
          errorMessage = "Fehler: Unbekannter Operator!";
          break;
      }

      // Sendet entweder die zuvor gesetzte Fehlermeldung oder das Berechnungsergebnis an den PC zurück.
      if (error) {
        Serial.println(errorMessage);
      } else {
        Serial.println(result);
      }

    } else {
      // Sendet eine Fehlermeldung, falls das empfangene String-Format ungültig war.
      Serial.println("Fehler: Ungueltiges Format empfangen!");
    }
  }
}
