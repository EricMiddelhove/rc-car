#include <Arduino.h>

#include "AcceleratorPedal.cpp"
#include "CarState.cpp"
#include "Gyroscope.cpp"
#include "Logger.cpp"
#include "SteeringWheel.cpp"

SteeringWheel* steeringWheel = NULL;
AcceleratorPedal* acceleratorPedal = NULL;
Logger* logger = NULL;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  SteeringWheel sw(2, 9);
  steeringWheel = &sw;

  AcceleratorPedal ap(3, 10);
  acceleratorPedal = &ap;

  Gyro gyro;
  gyro.wake();

  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);

  Logger lg;
  logger = &lg;

  logger->log("Logger Initialized");
  logger->log("Log Ending");

  CarState initialCarState(&gyro, 0);

  delete logger;
  Serial.println("Logger deleted");

  delay(3000);
}

void loop() {
  // Serial.print("Steering: " + String(rawSteeringInputPWM) + "\t");
  // Serial.print("Acceleration: " + String(rawAcceleratorInputPWM) + "\n");
}