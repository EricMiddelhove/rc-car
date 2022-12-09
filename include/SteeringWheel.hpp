#ifndef SteeringWheel_hpp
#define SteeringWheel_hpp

#include "Arduino.h"
#include "Servo.h"

void fallingSteeringPWMPulse();
void risingSteeringPWMPulse();

const int INPUT_SAMPLE_SIZE = 10;

const int RAW_STEERING_FULL_LEFT = 1836;
const int RAW_STEERING_FULL_RIGHT = 1108;
const int RAW_STEERING_CENTER = 1472;

const int STEERING_FULL_LEFT = 200;
const int STEERING_FULL_RIGHT = 55;
const int STEERING_CENTER = 90;

int8_t STEERING_PWM_PIN_INPUT;
int8_t STEERING_PWM_PIN_OUTPUT;

int steeringPreviousTime;
int8_t steeringInterruptPin;
bool steeringIsManual;
int rawSteeringInputPWM;

int steeringManualPWMInput;

class SteeringWheel {
 public:
  int8_t steeringOutputPin;
  SteeringWheel(int pwmPinInput, int pwmPinOutput);
  void steer(int percent);
  int getSteeringPercent();

 private:
  int steeringPercent;
  Servo steeringServo;
};
#endif