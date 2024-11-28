const int lichtSensorPin = A0;  // Analoger Pin für den Lichtsensor
const int ledPin = 13;          // Digitaler Pin für die LED
const int schwellenwert = 200;  // Schwellenwert für Dunkelheit

void setup() {
  pinMode(ledPin, OUTPUT);      // LED-Pin als Ausgang festlegen
  Serial.begin(9600);           // Serielle Kommunikation starten
}

void loop() {
  int lichtWert = analogRead(lichtSensorPin);  // Lichtwert lesen
  Serial.println(lichtWert);                   // Lichtwert ausgeben

  if (lichtWert < schwellenwert) {
    digitalWrite(ledPin, HIGH);  // LED einschalten wenn dunkel
  } else {
    digitalWrite(ledPin, LOW);   // LED ausschalten wenn hell
  }

  delay(100);  // Kurze Pause zur Stabilisierung
}