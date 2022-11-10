#ifndef SteeringWheel_cpp
#define SteeringWheel_cpp

#include "SteeringWheel.hpp"

#include "Arduino.h"
#include "Servo.h"

void fallingSteeringPWMPulse() {
  int currentTime = micros();
  int timeDifference = currentTime - steeringPreviousTime;

  rawSteeringInputPWM = timeDifference;

  if (rawSteeringInputPWM < 1460 || rawSteeringInputPWM > 1480) {
    steeringIsManual = true;
  } else {
    steeringIsManual = false;
  }

  attachInterrupt(steeringInterruptPin, risingSteeringPWMPulse, RISING);
}

void risingSteeringPWMPulse() {
  steeringPreviousTime = micros();
  attachInterrupt(steeringInterruptPin, fallingSteeringPWMPulse, FALLING);
}

void setSteeringAngle(int angle) {
  steeringAngle = angle;
}

SteeringWheel::SteeringWheel(int pwmPinInput, int pwmPinOutput) {
  Serial.print("SteeringWheel constructor called\n");

  STEERING_PWM_PIN_INPUT = pwmPinInput;
  STEERING_PWM_PIN_OUTPUT = pwmPinOutput;

  steeringInterruptPin = digitalPinToInterrupt(STEERING_PWM_PIN_INPUT);
  attachInterrupt(steeringInterruptPin, risingSteeringPWMPulse, RISING);

  steeringServo.attach(STEERING_PWM_PIN_OUTPUT);
  steeringServo.write(0);
}

void SteeringWheel::steer(int percent) {
  // -100 (FULL LEFT) to 100 (FULL RIGHT)
  int steeringPwmOutput = map(percent, -100, 100, STEERING_FULL_LEFT, STEERING_FULL_RIGHT);

  steeringServo.write(steeringPwmOutput);
}

#endif