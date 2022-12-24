#include <Arduino.h>

#include "AcceleratorPedal.cpp"
#include "CarState.cpp"
#include "Compass.cpp"
#include "Gyroscope.cpp"
#include "Logger.cpp"
#include "SPI.h"
#include "SteeringWheel.cpp"

Logger* logger = NULL;

SteeringWheel* steeringWheel = NULL;
AcceleratorPedal* acceleratorPedal = NULL;
Gyro* gyro = NULL;

Compass* compass = NULL;

void setup() {
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
  Serial.println("Gyroscope Initialized");

  Compass c;
  compass = &c;
  Serial.println("Compass Initialized");

  gyro->wake();

  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);

  CarState* carState = new CarState(gyro, steeringWheel, acceleratorPedal, compass);

  while (true) {
    carState->refresh();

    int steeringPercent = carState->getSteeringPercent();
    int accelerationPercent = carState->getAcceleratorPercent();

    steeringWheel->steer(steeringPercent);
    acceleratorPedal->accelerate(accelerationPercent);

    // carState->getCourse();

    Serial.print(" external course: ");
    Serial.println(carState->getCourse());

    // delay(100);

    logger->log(carState->getValues(), carState->VALUES_LENGTH);
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