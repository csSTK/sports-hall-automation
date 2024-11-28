#include <Servo.h>
#include <DHT.h>

#define DHTPIN 13
#define DHTTYPE DHT22

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

DHT dht(DHTPIN, DHTTYPE);

int i = 0;
const float HUMIDITY_THRESHOLD = 50.0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);
  servo4.attach(12);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Fehler beim Lesen des DHT-Sensors!");
    return;
  }

  Serial.print("Luftfeuchtigkeit: ");
  Serial.print(humidity);
  Serial.print("%, Temperatur: ");
  Serial.print(temperature);
  Serial.println("°C");

  // Entfernt die doppelte Bedingung für Luftfeuchtigkeit unter 50%
  if (humidity > HUMIDITY_THRESHOLD || (temperature > 25 && temperature < 40)) {
    Serial.println("Luftfeuchtigkeit über 50% oder Temperatur zwischen 25°C und 40°C - Starte Servo-Bewegung");

    for (i = 0; i < 180; i++) {
      servo1.write(i);
      servo2.write(i);
      servo3.write(i);
      servo4.write(i);
      delay(10);
    }
  } else {
    Serial.println("Bedingungen nicht erfüllt - Servos bleiben still.");
  }

  if (temperature > 50) {
    Serial.println("Temperatur über 50 Grad - Starte Servo-Bewegung");

    for (i = 180; i > 0; i--) {  // Korrigiert die Schleife für rückwärts
      servo1.write(i);
      servo2.write(i);
      servo3.write(i);
      delay(10);
    }

    for (i = 0; i < 180; i++) {
      servo4.write(i);
      delay(10);
    }
  }

  delay(2000);
}