#ifndef SteeringWheel_cpp
#define SteeringWheel_cpp

#include "SteeringWheel.hpp"

#include "Arduino.h"
#include "ESP32_Servo.h"

int sampleNumber = 0;
int sampleSum = 0;

int manualSteeringInputCounter = 0;
int steeringPulseCounter = 0;

long millisLastSteered = 0;
int minimumMillisBetweenSteering = 1000 / MAXIMUM_SERVO_UPDATE_RATE_Hz;

void fallingSteeringPWMPulse() {
  steeringPulseCounter++;
  if (steeringPulseCounter > 20) {
    steeringPulseCounter = 0;
    manualSteeringInputCounter = 0;
  }

  int currentTime = micros();
  int pulseWidth = currentTime - steeringPreviousTime;

  if (pulseWidth < 1420 || pulseWidth > 1500) {
    manualSteeringInputCounter++;

    if (manualSteeringInputCounter > 5) {
      // Serial.println(F("Manual Steering Detected"));
      steeringIsManual = true;
      manualSteeringInputCounter = 0;
    }

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

void SteeringWheel::steer(int percent, bool force) {
  steeringPercent = percent;

  if (millis() - millisLastSteered < 1000 / MAXIMUM_SERVO_UPDATE_RATE_Hz) {
    return;
  }

  int steeringPwmOutput = map(steeringPercent, -100, 100, RAW_STEERING_FULL_RIGHT, RAW_STEERING_FULL_LEFT);
  steeringServo.write(steeringPwmOutput);

  millisLastSteered = millis();
}

void SteeringWheel::steer(int percent) {
  steer(percent, false);
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