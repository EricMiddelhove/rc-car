#ifndef SteeringWheel_cpp
#define SteeringWheel_cpp

#include "SteeringWheel.hpp"

#include "Arduino.h"
#include "Servo.h"

void fallingSteeringPWMPulse() {
  int currentTime = micros();
  int timeDifference = currentTime - previousTime;

  rawSteeringInputPWM = timeDifference;

  if (rawSteeringInputPWM < 1460 || rawSteeringInputPWM > 1480) {
    steeringIsManual = true;
  } else {
    steeringIsManual = false;
  }

  Serial.println(steeringIsManual);
  attachInterrupt(interruptPin, risingSteeringPWMPulse, RISING);
}

void risingSteeringPWMPulse() {
  previousTime = micros();
  attachInterrupt(interruptPin, fallingSteeringPWMPulse, FALLING);
}

void setSteeringAngle(int angle) {
  steeringAngle = angle;
}

void setSteeringInputPin(int pwmPin) {
  PWM_PIN = pwmPin;

  interruptPin = digitalPinToInterrupt(PWM_PIN);
  attachInterrupt(interruptPin, risingSteeringPWMPulse, RISING);

  return;
}

SteeringWheel::SteeringWheel(int pwmPin) {
  steeringOutputPin = pwmPin;
  steeringServo.attach(steeringOutputPin);
  steeringServo.write(0);
}

void SteeringWheel::steer(int percent) {
  // -100 (FULL LEFT) to 100 (FULL RIGHT)
  int steeringPwmOutput = map(percent, -100, 100, STEERING_FULL_LEFT, STEERING_FULL_RIGHT);

  steeringServo.write(steeringPwmOutput);
}

#endif