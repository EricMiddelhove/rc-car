#ifndef SteeringWheel_cpp
#define SteeringWheel_cpp

#include "SteeringWheel.hpp"

#include "Arduino.h"
#include "Servo.h"

int sampleNumber = 0;
int sampleSum = 0;
void fallingSteeringPWMPulse() {
  int currentTime = micros();
  int pulseWidth = currentTime - steeringPreviousTime;

  if (pulseWidth < 1460 || pulseWidth > 1480) {
    steeringIsManual = true;
  } else {
    steeringIsManual = false;
  }

  sampleSum += pulseWidth;
  sampleNumber++;

  if (sampleNumber >= INPUT_SAMPLE_SIZE) {
    rawSteeringInputPWM = sampleSum / INPUT_SAMPLE_SIZE;
    sampleNumber = 0;
    sampleSum = 0;

    attachInterrupt(steeringInterruptPin, risingSteeringPWMPulse, RISING);
    return;

  } else {
    attachInterrupt(steeringInterruptPin, risingSteeringPWMPulse, RISING);
    return;
  }
}

void risingSteeringPWMPulse() {
  steeringPreviousTime = micros();
  attachInterrupt(steeringInterruptPin, fallingSteeringPWMPulse, FALLING);
}

SteeringWheel::SteeringWheel(int pwmPinInput, int pwmPinOutput) {
  STEERING_PWM_PIN_INPUT = pwmPinInput;
  STEERING_PWM_PIN_OUTPUT = pwmPinOutput;

  steeringInterruptPin = digitalPinToInterrupt(STEERING_PWM_PIN_INPUT);
  attachInterrupt(steeringInterruptPin, risingSteeringPWMPulse, RISING);

  steeringServo.attach(STEERING_PWM_PIN_OUTPUT);
  this->steer(0);
}

void SteeringWheel::steer(int percent) {
  // -100 (FULL RIGHT) to 100 (FULL LEFT)

  steeringPercent = percent;

  int steeringPwmOutput = map(steeringPercent, -100, 100, RAW_STEERING_FULL_RIGHT, RAW_STEERING_FULL_LEFT);
  steeringServo.write(steeringPwmOutput);
}

int SteeringWheel::getSteeringPercent() {
  if (steeringIsManual) {
    steeringPercent = map(rawSteeringInputPWM, RAW_STEERING_FULL_LEFT, RAW_STEERING_FULL_RIGHT, -100, 100);
  } else {
    // TODO: AI Steering
    steeringPercent = 0;
  }
  return -steeringPercent;
}

#endif