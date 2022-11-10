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

int STEERING_PWM_PIN_INPUT;
int STEERING_PWM_PIN_OUTPUT;

int steeringPreviousTime;
int steeringInterruptPin;
int rawSteeringInputPWM;

bool steeringIsManual;

int steeringAngle;

int steeringManualPWMInput;

class SteeringWheel {
 public:
  byte steeringOutputPin;
  SteeringWheel(int pwmPinInput, int pwmPinOutput);
  void steer(int percent);

 private:
  Servo steeringServo;
};
#endif