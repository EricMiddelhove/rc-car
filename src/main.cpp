#include <Arduino.h>

#include "SteeringWheel.cpp"

SteeringWheel* steeringWheel;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setSteeringInputPin(2);

  SteeringWheel sw(9);
  steeringWheel = &sw;

  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);

  steeringWheel->steer(STEERING_CENTER);
  delay(3000);
  digitalWrite(13, HIGH);
}

void loop() {
  steeringWheel->steer(100);
  delay(3000);
  steeringWheel->steer(-100);
  delay(3000);
}