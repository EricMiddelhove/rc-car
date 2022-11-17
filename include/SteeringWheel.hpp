#ifndef SteeringWheel_hpp
#define SteeringWheel_hpp

#include "Arduino.h"
#include "Servo.h"

void fallingSteeringPWMPulse();
void risingSteeringPWMPulse();

const short int RAW_STEERING_FULL_LEFT = 1836;
const short int RAW_STEERING_FULL_RIGHT = 1108;

const short int STEERING_FULL_LEFT = 200;
const short int STEERING_FULL_RIGHT = 55;
const short int STEERING_CENTER = 90;

byte STEERING_PWM_PIN_INPUT;
byte STEERING_PWM_PIN_OUTPUT;

int steeringPreviousTime;
byte steeringInterruptPin;
short int rawSteeringInputPWM;

bool steeringIsManual;

byte steeringAngle;

short int steeringManualPWMInput;

class SteeringWheel {
 public:
  byte steeringOutputPin;
  SteeringWheel(int pwmPinInput, int pwmPinOutput);
  void steer(int percent);

 private:
  Servo steeringServo;
};
#endif