#include <Servo.h>
#include <DHT.h>

#define DHTPIN A0
#define DHTTYPE DHT22

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

DHT dht(DHTPIN, DHTTYPE);

const float HUMIDITY_THRESHOLD = 51.0;

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

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%, Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  if (temperature > 50) {
    Serial.println("Temperature above 50 degrees, suspected fire - Start servo movement");

    servo1.write(0);
    servo2.write(0);
    servo3.write(0);
    servo4.write(180);
    delay(10);
  }

  if (humidity > HUMIDITY_THRESHOLD || (temperature > 25 && temperature < 40)) {
    Serial.println("Humidity above 50% or temperature between 25°C and 40°C - Start servo movement");

      servo1.write(180);
      servo2.write(180);
      servo3.write(180);
      servo4.write(180);
      delay(10);
  } else {
    Serial.println("Conditions not fulfilled - servos remain stationary.");
  }

  delay(2000);
}