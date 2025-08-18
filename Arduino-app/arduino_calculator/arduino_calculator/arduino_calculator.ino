// Arduino C Code für den Mikrocontroller-Kalkulator

/*
  Die Funktion setup() wird einmalig ausgefuehrt, wenn der Arduino
  gestartet oder resettet wird. Hier initialisieren wir alles Notwendige.
*/
void setup() {
  // Startet die serielle Kommunikation mit einer Baudrate von 9600 Bits pro Sekunde.
  // Diese Zahl muss mit der in unserem C++ Programm übereinstimmen (CBR_9600).
  Serial.begin(9600);
}

/*
  Die Funktion loop() wird nach dem Ende von setup() in einer Endlosschleife
  immer und immer wieder ausgefuehrt. Das ist das Herzstück unseres Programms.
*/
void loop() {
  // Prueft, ob neue Daten am seriellen Port angekommen sind.
  if (Serial.available() > 0) {
    // Wenn Daten vorhanden sind:

    // Lese den ankommenden String ein, bis das Newline-Zeichen ('\n') empfangen wird.
    // Das ist das Zeichen, das die PC-Anwendung am Ende jeder Nachricht sendet.
    String receivedString = Serial.readStringUntil('\n');

    // Sende eine Antwort zurück an die PC-Anwendung.
    // Einfügen von 'Echo', um festzustellen, dass die Antwort vom Arduino kommt.
    Serial.print("Echo: ");
    Serial.println(receivedString);
  }
}
