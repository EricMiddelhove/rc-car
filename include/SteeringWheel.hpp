#ifndef SteeringWheel_hpp
#define SteeringWheel_hpp

#include "Arduino.h"
#include "Servo.h"

void fallingSteeringPWMPulse();
void risingSteeringPWMPulse();

const int RAW_STEERING_FULL_LEFT = 1836;
const int RAW_STEERING_FULL_RIGHT = 1108;

const int STEERING_FULL_LEFT = 200;
const int STEERING_FULL_RIGHT = 55;
const int STEERING_CENTER = 90;

int PWM_PIN;

int previousTime;
int interruptPin;
int rawSteeringInputPWM;

bool steeringIsManual;

int steeringAngle;

int manualPWMInput;

class SteeringWheel {
 public:
  byte steeringOutputPin;
  SteeringWheel(int pwmPin);
  void steer(int percent);

 private:
  Servo steeringServo;
};

#endif