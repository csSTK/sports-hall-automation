#include <LiquidCrystal.h>

// Pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(11, 10, 6, 5, 4, 3);

const int lightSensor = 2;
const int ledPin = 13;
const int sensorPin = 12;
const int sensorPin2 = 7;

int team1 = 0;
int team2 = 0;

void setup() {
  pinMode(lightSensor, INPUT);
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  lcd.begin(16, 2);  // Initialises the LCD with 16x2 characters
  lcd.print("Team 1:"); // First line
  lcd.setCursor(0, 1);  // Second line
  lcd.print("Team 2:");
  Serial.begin(9600);
}

void loop() {
  int sensorValue = digitalRead(lightSensor); // Read value of the sensor

  // Ausgabe des Wertes auf der seriellen Konsole
  Serial.println(sensorValue);

  // When the sensor detects light (depending on the potentiometer setting)
  if (sensorValue == HIGH) {
    digitalWrite(ledPin, HIGH); // LED on
  } else {
    digitalWrite(ledPin, LOW);  // LED off
  }

  int sensorValue2 = digitalRead(sensorPin); // Read value of the sensor
  int sensorValue3 = digitalRead(sensorPin2); // Read value of the sensor

  // When the sensor is triggered (obstacle detected)
  if (sensorValue2 == LOW) {
    Serial.println("Sensor 1 triggered: Obstacle detected!");
    team1++;
  } else {
    Serial.println("Sensor 1: No obstacle recognised.");
  }

  // When the sensor is triggered (obstacle detected)
  if (sensorValue3 == LOW) {
    Serial.println("Sensor 2 triggered: Obstacle detected!");
    team2++;
  } else {
    Serial.println("Sensor 1: No obstacle recognised.");
  }

  lcd.setCursor(8, 0); // Cursor "Team 1:"
  lcd.print(team1);    // Display points of team 1
  lcd.setCursor(8, 1); // Cursor "Team 2:"
  lcd.print(team2);    // Display points of team 2

  delay(1000); // Short pause to make the output readable
}
