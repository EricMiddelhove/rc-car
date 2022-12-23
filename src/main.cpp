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

  int course = 0;

  while (true) {
    // int steeringPercent = carState->getSteeringPercent();
    // int accelerationPercent = carState->getAcceleratorPercent();

    // Serial.print(",");
    // Serial.print(steeringPercent);
    // Serial.print(",");
    // Serial.print(accelerationPercent);

    // steeringWheel->steer(steeringPercent);
    // acceleratorPedal->accelerate(accelerationPercent);

    // int zGyro = gyro->getGyroDataOfAxis('Z');

    // zGyro = map(zGyro, -32765, 32765, -25000, 25000) - 100;
    // Serial.print(",");
    // Serial.println(zGyro);

    // course += zGyro / 10;

    // Serial.println(course / 100);

    // Serial.println(value);

    // Serial.print("X: ");
    // Serial.print(compass->getAxisValue('x'));

    // Serial.print(" Y: ");
    // Serial.print(compass->getAxisValue('y'));

    // Serial.print(" Z: ");
    // Serial.print(compass->getAxisValue('z'));

    Serial.print(" Azimuth: ");
    Serial.print(compass->getAzimuth());

    Serial.println();

    // delay(100);

    // logger->log(carState->getValues(), carState->VALUES_LENGTH);
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