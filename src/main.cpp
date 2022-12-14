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
  Serial.println("Steering Wheel Initialized");

  AcceleratorPedal ap(3, 10, 100);
  acceleratorPedal = &ap;
  Serial.println("Accelerator Pedal Initialized");

  Gyro gy;
  gyro = &gy;

  gyro->wake();

  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);

  delay(3000);

  CarState* carState = new CarState(gyro, steeringWheel, acceleratorPedal);

  while (true) {
    if (logger->errorFlag) {
      break;
    }

    // int steeringPercent = *(carState->steeringPercent);
    // int accelerationPercent = *(carState->acceleratorPercent);

    // steeringWheel->steer(steeringPercent);
    // acceleratorPedal->accelerate(accelerationPercent);

    long before = micros();
    logger->log(carState->getValues(), carState->VALUES_LENGTH);
    long after = micros();

    Serial.println(after - before);
  }
  SPI.end();
  steeringWheel->steer(0);
  acceleratorPedal->accelerate(0);

  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
}