#ifndef SteeringWheel_hpp
#define SteeringWheel_hpp

#include "Arduino.h"
#include "ESP32_Servo.h"

void fallingSteeringPWMPulse();
void risingSteeringPWMPulse();

const int INPUT_SAMPLE_SIZE = 10;

const int RAW_STEERING_FULL_LEFT = 1836;
const int RAW_STEERING_FULL_RIGHT = 1108;
const int RAW_STEERING_CENTER = 1472;

const int STEERING_FULL_LEFT = 200;
const int STEERING_FULL_RIGHT = 55;
const int STEERING_CENTER = 90;

const int MAXIMUM_SERVO_UPDATE_RATE_Hz = 10;

int8_t STEERING_PWM_PIN_INPUT;
int8_t STEERING_PWM_PIN_OUTPUT;

int steeringPreviousTime;
int8_t steeringInterruptPin;
bool steeringIsManual = false;
int rawSteeringInputPWM;

int steeringManualPWMInput;

class SteeringWheel {
 public:
  int8_t steeringOutputPin;
  SteeringWheel(int pwmPinInput, int pwmPinOutput);
  /**
   * @brief -100 (FULL RIGHT) to 100 (FULL LEFT)
   *
   * @param percent
   */
  void steer(int percent, bool force);
  void steer(int percent);
  int getSteeringPercent();

 private:
  int steeringPercent;
  Servo steeringServo;
};
#endif