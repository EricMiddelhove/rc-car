#include <Arduino.h>

#include "AcceleratorPedal.cpp"
#include "Gyroscope.cpp"
#include "Logger.cpp"
#include "SteeringWheel.cpp"

SteeringWheel* steeringWheel = NULL;
AcceleratorPedal* acceleratorPedal = NULL;
Logger* logger = NULL;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // SteeringWheel sw(2, 9);
  // steeringWheel = &sw;

  // AcceleratorPedal ap(3, 10);
  // acceleratorPedal = &ap;

  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);

  Logger lg;
  logger = &lg;

  logger->log("Logger Initialized");
  logger->log("Log Ending");

  deleteLogger(logger);

  delay(3000);
  // digitalWrite(13, HIGH);
}

void loop() {
  digitalWrite(13, HIGH);
  // Serial.print("Steering: " + String(rawSteeringInputPWM) + "\t");
  // Serial.print("Acceleration: " + String(rawAcceleratorInputPWM) + "\n");
}