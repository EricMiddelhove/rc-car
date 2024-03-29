#include "AcceleratorPedal.cpp"
#include "Arduino.h"
#include "CarState.cpp"
#include "Compass.cpp"
#include "Gyroscope.cpp"
#include "Logger.cpp"
#include "SPI.h"
#include "SteeringWheel.cpp"

#define BUTTON_PIN 5

Logger* logger = NULL;

SteeringWheel* steeringWheel = NULL;
AcceleratorPedal* acceleratorPedal = NULL;
Gyro* gyro = NULL;

Compass* compass = NULL;

void initialiseSensors() {
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
  Serial.println("Gyroscope Initialized");

  Compass c;
  compass = &c;
  Serial.println("Compass Initialized");
}

void emergencyTakeOver(CarState* carState) {
  Serial.println("MANUAL OVERRIDE");

  while (digitalRead(BUTTON_PIN) == 0) {
    int inputSteeringPercent = steeringWheel->getSteeringPercent();
    int inputAccelerationPercent = acceleratorPedal->getAcceleratorPercent();

    Serial.print("Steering: ");
    Serial.print(inputSteeringPercent);
    Serial.print(" Acceleration: ");
    Serial.println(inputAccelerationPercent);

    steeringWheel->steer(inputSteeringPercent);
    acceleratorPedal->accelerate(inputAccelerationPercent);
  }
}

void emergencyShutdown() {
  Serial.println("EMERGENCY SHUTDOWN");

  steeringWheel->steer(0);
  acceleratorPedal->accelerate(0);
}

/**
 * @brief Calculates the steering percent required to steer the car to the target course
 * Angle is calculated linearly from -100 to 100
 *
 * @param targetCourse
 * @param currentCourse
 * @param sensitivityFactor - the higher the value, the more sensitive the steering is (normal values are 1 - 2)
 * @return int
 */
int calculateSteeringPercent(int16_t targetCourse, int16_t currentCourse, uint8_t sensitivityFactor) {
  int16_t diff = targetCourse - currentCourse;

  if (diff > 180) {
    diff = diff - 360;
  } else if (diff < -180) {
    diff = diff + 360;
  }

  int16_t steeringPercent = (diff * 100) / 180;

  steeringPercent = steeringPercent * sensitivityFactor;

  if (steeringPercent > 100) {
    steeringPercent = 100;
  } else if (steeringPercent < -100) {
    steeringPercent = -100;
  }

  return -steeringPercent;
}

/**
 * @brief Calculates the steering percent required to steer the car to the target course
 *
 * @param targetCourse
 * @param currentCourse
 * @return int
 */
int calculateSteeringPercent(int16_t targetCourse, int16_t currentCourse) {
  return calculateSteeringPercent(targetCourse, currentCourse, 5);
}

void setup() {
  steeringIsManual = false;
  acceleratorIsManual = false;

  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  delay(5000);

  initialiseSensors();

  CarState* carState = new CarState(gyro, steeringWheel, acceleratorPedal, compass);

  carState->setTargetCourse(20);
  acceleratorPedal->accelerate(40);

  // Exit if button on pcb is pressed
  while (digitalRead(BUTTON_PIN) == 0) {
    uint16_t startTime = millis();
    carState->refresh();

    // accelerator feed through
    int inputAccelerationPercent = acceleratorPedal->getAcceleratorPercent();
    acceleratorPedal->accelerate(inputAccelerationPercent);

    if (steeringIsManual || acceleratorIsManual) {
      Serial.print(F("Steering is Manual: "));
      Serial.print(steeringIsManual);
      Serial.print(F("\tAcceleration is Manual: "));
      Serial.println(acceleratorIsManual);
      emergencyTakeOver(carState);
      break;
    }

    // Straight line steering
    const int targetCourse = carState->getTargetCourse();
    const int currentCourse = carState->getLocalCourse();

    Serial.print(F("Target Course: "));
    Serial.print(targetCourse);
    Serial.print(F("\tCurrent Course: "));
    Serial.print(currentCourse);

    int steeringPercent = calculateSteeringPercent(targetCourse, currentCourse, 5);
    Serial.print(F("\tSteering Percent: "));
    Serial.print(steeringPercent);

    Serial.print(F("\tButton: "));
    Serial.print(digitalRead(BUTTON_PIN));

    logger->bufLog(carState->getValues(), CarState::VALUES_LENGTH);
    // logger->log(carState->getValues(), CarState::VALUES_LENGTH);

    steeringWheel->steer(steeringPercent);

    uint16_t endTime = millis();
    uint16_t duration = endTime - startTime;
    Serial.print(F("\tDuration: "));
    Serial.print(duration);

    Serial.println();
  }

  emergencyShutdown();

  SPI.end();
  steeringWheel->steer(0);
  acceleratorPedal->accelerate(0);

  pinMode(13, OUTPUT);

  // Exit gracefully
  delete logger;
  delete carState;
  delete steeringWheel;
  delete acceleratorPedal;
  delete gyro;
  delete compass;
}

void loop() {
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
}