#include <Arduino.h>

#include "AcceleratorPedal.cpp"
#include "SteeringWheel.cpp"

SteeringWheel* steeringWheel;
AcceleratorPedal* acceleratorPedal;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  SteeringWheel sw(2, 9);
  steeringWheel = &sw;

  AcceleratorPedal ap(3, 10);
  acceleratorPedal = &ap;

  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);

  // steeringWheel->steer(STEERING_CENTER);
  delay(3000);
  // digitalWrite(13, HIGH);
}

void loop() {
  Serial.print("Steering: " + String(rawSteeringInputPWM) + "\t");
  Serial.print("Acceleration: " + String(rawAcceleratorInputPWM) + "\n");
}