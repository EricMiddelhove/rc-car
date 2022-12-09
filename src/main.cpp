#include <Arduino.h>

#define DEBUG_SD_ONLY 1
#define DEBUG_FULL 2
#define DEBUG_OFF 0

#define DEBUG_MODE DEBUG_FULL

#include "AcceleratorPedal.cpp"
#include "CarState.cpp"
#include "Gyroscope.cpp"
#include "SteeringWheel.cpp"

#if DEBUG_MODE > 0
#include "Logger.cpp"
Logger* logger = NULL;
#endif

SteeringWheel* steeringWheel = NULL;
AcceleratorPedal* acceleratorPedal = NULL;
Gyro* gyro = NULL;

void setup() {
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
    CarState carState(gyro, steeringWheel, acceleratorPedal);

    int steeringPercent = steeringWheel->getSteeringPercent();
    int accelerationPercent = acceleratorPedal->getAcceleratorPercent();

    logger->log(carState.getCSVLine());
  }
}

void loop() {
  steeringWheel->steer(0);
  acceleratorPedal->accelerate(0);

  // Serial.print("Steering: " + String(rawSteeringInputPWM) + "\t");
  // Serial.print("Acceleration: " + String(rawAcceleratorInputPWM) + "\n");
}