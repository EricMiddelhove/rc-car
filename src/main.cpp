#include <Arduino.h>

#include "AcceleratorPedal.cpp"
#include "CarState.cpp"
#include "Gyroscope.cpp"
#include "Logger.cpp"
#include "SPI.h"
#include "SteeringWheel.cpp"

Logger* logger = NULL;

SteeringWheel* steeringWheel = NULL;
AcceleratorPedal* acceleratorPedal = NULL;
Gyro* gyro = NULL;

void setup() {
  analogWrite(10, RAW_NO_ACCELERATOR);
// put your setup code here, to run once:
#if (DEBUG_MODE > 1)
#endif
  Logger lg;
  logger = &lg;

  SteeringWheel sw(2, 9);
  steeringWheel = &sw;
  logger->log("Steering Wheel Initialized");

  AcceleratorPedal ap(3, 10);
  acceleratorPedal = &ap;
  logger->log("Accelerator Pedal Initialized");

  Gyro gy;
  gyro = &gy;

  gyro->wake();

  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);

  CarState initialCarState(gyro, steeringWheel, acceleratorPedal);

  logger->log("Car State Initialized");
  logger->log("Initializations Complete");

  logger->log(initialCarState.getCSVLine());

  delay(3000);

  while (true) {
    if (logger->errorFlag) {
      break;
    }

    CarState carState(gyro, steeringWheel, acceleratorPedal);

    // int steeringPercent = steeringWheel->getSteeringPercent();
    int accelerationPercent = acceleratorPedal->getAcceleratorPercent();

    // steeringWheel->steer(steeringPercent);
    acceleratorPedal->accelerate(accelerationPercent);

    logger->log(carState.getCSVLine());
  }
  SPI.end();
  pinMode(13, OUTPUT);
  steeringWheel->steer(0);
  acceleratorPedal->accelerate(0);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
}